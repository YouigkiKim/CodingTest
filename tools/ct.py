#!/usr/bin/env python3
"""ct: C++ 코딩테스트 학습 코스 실행·채점 도구.

표준 라이브러리만 사용한다. 문제/단원/경로 정보는 저장소 루트의 manifest.json 하나만 기준으로 삼는다.
사용법은 `./ct help` 참고.
"""
import argparse
import json
import os
import shutil
import signal
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MANIFEST = ROOT / "manifest.json"
BUILD = ROOT / "build"
CXX = os.environ.get("CXX", "g++")

BASE_FLAGS = ["-std=c++17", "-Wall", "-Wextra"]
MODE_FLAGS = {
    "release": ["-O2"],
    "asan": ["-g", "-O1", "-fsanitize=address,undefined",
             "-fno-sanitize-recover=all", "-fno-omit-frame-pointer"],
}
ASAN_TIME_FACTOR = 5          # sanitizer 실행은 느리므로 시간제한을 늘린다
MAX_OUTPUT_BYTES = 32 * 1024 * 1024
SHOW_LINES = 15
SHOW_CHARS = 1200

USE_COLOR = sys.stdout.isatty()
sys.stdout.reconfigure(line_buffering=True)  # 자식 프로세스 출력과 순서가 섞이지 않게 한다


def color(text, code):
    return f"\033[{code}m{text}\033[0m" if USE_COLOR else text


def green(t): return color(t, "32")
def red(t): return color(t, "31")
def yellow(t): return color(t, "33")
def bold(t): return color(t, "1")


def die(msg):
    print(red(f"오류: {msg}"), file=sys.stderr)
    sys.exit(2)


# ---------------------------------------------------------------- manifest

def load_manifest():
    try:
        with open(MANIFEST, encoding="utf-8") as f:
            return json.load(f)
    except (OSError, json.JSONDecodeError) as e:
        die(f"manifest.json을 읽을 수 없습니다: {e}")


def get_problem(m, pid):
    for p in m["problems"]:
        if p["id"] == pid:
            return p
    ids = " ".join(p["id"] for p in m["problems"])
    die(f"문제 ID '{pid}'를 찾을 수 없습니다. 사용 가능한 ID: {ids}")


def problem_paths(p):
    slug = p["slug"]
    return {
        "dir": ROOT / "problems" / slug,
        "main": ROOT / "problems" / slug / "main.cpp",
        "statement": ROOT / "problems" / slug / "problem.md",
        "hints": ROOT / "problems" / slug / "hints.md",
        "solution": ROOT / "solutions" / slug / "solution.cpp",
        "explanation": ROOT / "solutions" / slug / "solution.md",
        "tests": ROOT / "tests" / slug,
    }


def time_limit(m, p):
    return float(p.get("time_limit_sec", m["defaults"]["time_limit_sec"]))


def example_list(m):
    """[(example_id, unit, cpp_path, in_path_or_None)]"""
    out = []
    for u in m["units"]:
        for name in u["examples"]:
            cpp = ROOT / "units" / u["slug"] / "examples" / f"{name}.cpp"
            inp = cpp.with_suffix(".in")
            out.append((f"{u['id']}-{name}", u, cpp, inp if inp.exists() else None))
    return out


def rel(path):
    try:
        return str(Path(path).relative_to(ROOT))
    except ValueError:
        return str(path)


# ---------------------------------------------------------------- compile / run

def compile_cpp(src, exe, mode):
    """컴파일한다. (성공 여부, 컴파일러 메시지)를 반환한다. 소스 파일은 읽기만 한다."""
    if shutil.which(CXX) is None:
        die(f"컴파일러 '{CXX}'를 찾을 수 없습니다. Codespaces/devcontainer에서 실행하거나 g++를 설치하세요.")
    exe.parent.mkdir(parents=True, exist_ok=True)
    cmd = [CXX] + BASE_FLAGS + MODE_FLAGS[mode] + [str(src), "-o", str(exe)]
    proc = subprocess.run(cmd, capture_output=True, text=True, errors="replace")
    return proc.returncode == 0, proc.stderr.strip()


def exe_path(mode, kind, name):
    return BUILD / mode / kind / name / "prog"


def clip(text):
    lines = text.splitlines()
    clipped = len(lines) > SHOW_LINES
    s = "\n".join(lines[:SHOW_LINES])
    if len(s) > SHOW_CHARS:
        s = s[:SHOW_CHARS]
        clipped = True
    if not s.strip():
        s = "(비어 있음)"
    return s + ("\n... (생략됨)" if clipped else "")


def describe_exit(code):
    if code < 0:
        try:
            name = signal.Signals(-code).name
        except ValueError:
            name = f"signal {-code}"
        hint = {
            "SIGSEGV": "잘못된 메모리 접근 또는 스택 오버플로(깊은 재귀)",
            "SIGABRT": "abort 호출(assert 실패, 예외 미처리, sanitizer 감지 등)",
            "SIGFPE": "0으로 나누기 등 산술 오류",
        }.get(name, "")
        return f"{name}" + (f" - {hint}" if hint else "")
    return f"종료 코드 {code}"


def run_case(exe, in_path, limit):
    """한 테스트를 실행한다. dict(verdict, time, out, err, detail)를 반환한다."""
    out_file = exe.parent / "stdout.txt"
    start = time.monotonic()
    try:
        with open(in_path, "rb") as fin, open(out_file, "wb") as fout:
            proc = subprocess.run([str(exe)], stdin=fin, stdout=fout,
                                  stderr=subprocess.PIPE, timeout=limit)
    except subprocess.TimeoutExpired:
        return {"verdict": "TLE", "time": limit, "out": "", "err": "",
                "detail": f"시간제한 {limit:g}초 초과"}
    elapsed = time.monotonic() - start
    err = proc.stderr.decode("utf-8", "replace")
    size = out_file.stat().st_size
    with open(out_file, "rb") as f:
        out = f.read(MAX_OUTPUT_BYTES).decode("utf-8", "replace")
    res = {"time": elapsed, "out": out, "err": err, "detail": ""}
    if proc.returncode != 0:
        res["verdict"] = "RE"
        res["detail"] = describe_exit(proc.returncode)
    elif size > MAX_OUTPUT_BYTES:
        res["verdict"] = "WA"
        res["detail"] = "출력이 너무 큽니다(출력 초과)"
    else:
        res["verdict"] = None  # 비교는 호출자가 수행
    return res


def first_diff(expected, actual):
    for i, (e, a) in enumerate(zip(expected, actual)):
        if e != a:
            return f"{i + 1}번째 토큰이 다릅니다: 예상 '{e}', 실제 '{a}'"
    if len(expected) != len(actual):
        return f"토큰 개수가 다릅니다: 예상 {len(expected)}개, 실제 {len(actual)}개"
    return ""


VERDICT_NAME = {
    "AC": "정답", "WA": "오답", "TLE": "시간초과", "RE": "런타임 오류", "CE": "컴파일 오류",
}


def paint(verdict):
    return green(verdict) if verdict == "AC" else red(verdict)


def judge(exe, tests_dir, limit, only=None, verbose=False, quiet=False):
    """tests_dir의 모든 *.in을 채점한다. (통과 수, 전체 수, 최종 판정)을 반환한다."""
    inputs = sorted(tests_dir.glob("*.in"))
    if not inputs and not tests_dir.exists():
        die(f"테스트 디렉터리가 없습니다: {rel(tests_dir)}\n"
            "tests/는 git에서 제외되어 있으므로 새로 받은 저장소에서는 먼저 생성해야 합니다:\n"
            "  python3 tools/make_tests.py   (약 3~4분)")
    if only:
        inputs = [p for p in inputs if p.stem == only]
    if not inputs:
        die(f"테스트를 찾을 수 없습니다: {rel(tests_dir)}" + (f" (케이스 {only})" if only else ""))

    passed = 0
    final = "AC"
    failures = []
    for in_path in inputs:
        exp_path = in_path.with_suffix(".out")
        if not exp_path.exists():
            die(f"예상 출력 파일이 없습니다: {rel(exp_path)}")
        res = run_case(exe, in_path, limit)
        if res["verdict"] is None:
            expected = exp_path.read_text(encoding="utf-8").split()
            actual = res["out"].split()
            if expected == actual:
                res["verdict"] = "AC"
            else:
                res["verdict"] = "WA"
                res["detail"] = first_diff(expected, actual)
        if res["verdict"] == "AC":
            passed += 1
        else:
            if final == "AC":
                final = res["verdict"]
            failures.append((in_path, exp_path, res))
        if not quiet:
            detail = f"  {res['detail']}" if res["detail"] else ""
            print(f"  테스트 {in_path.stem}  {paint(res['verdict']):<3}  {res['time']:.2f}s{detail}")

    if not quiet:
        shown = failures if verbose else failures[:1]
        for in_path, exp_path, res in shown:
            print()
            print(bold(f"--- 실패한 테스트 {in_path.stem}: {VERDICT_NAME[res['verdict']]}({res['verdict']}) "
                       f"/ 입력 파일 {rel(in_path)} ---"))
            print(yellow("[입력]"))
            print(clip(in_path.read_text(encoding="utf-8")))
            print(yellow("[예상 출력]"))
            print(clip(exp_path.read_text(encoding="utf-8")))
            if res["verdict"] != "TLE":
                print(yellow("[실제 출력]"))
                print(clip(res["out"]))
            if res["err"].strip():
                print(yellow("[표준 에러(stderr)]"))
                print(clip(res["err"]))
        if len(failures) > len(shown):
            print(f"\n(실패한 테스트가 {len(failures) - len(shown)}개 더 있습니다. -v 옵션으로 모두 볼 수 있습니다.)")
    return passed, len(inputs), final


def build_and_judge(m, p, src, kind, mode, only=None, verbose=False, quiet=False):
    """컴파일 후 채점. 최종 판정 문자열(AC/WA/TLE/RE/CE)을 반환한다."""
    if not src.exists():
        die(f"소스 파일이 없습니다: {rel(src)}")
    exe = exe_path(mode, kind, p["id"])
    ok, log = compile_cpp(src, exe, mode)
    if not ok:
        if not quiet:
            print(red("컴파일 오류(CE)"))
            print(log)
        return "CE", 0, 0
    if log and not quiet:
        print(yellow("컴파일 경고:"))
        print(clip(log))
    limit = time_limit(m, p) * (ASAN_TIME_FACTOR if mode == "asan" else 1)
    passed, total, final = judge(exe, problem_paths(p)["tests"], limit, only, verbose, quiet)
    return final, passed, total


# ---------------------------------------------------------------- commands

def cmd_list(args):
    m = load_manifest()
    by_unit = {}
    for p in m["problems"]:
        by_unit.setdefault(p["unit"], []).append(p)
    print(bold("단원 (units/)"))
    for u in m["units"]:
        print(f"\n{bold(u['id'])} {u['title']}  [예상 {u['hours']}시간]  units/{u['slug']}/README.md")
        for name in u["examples"]:
            print(f"    예제  {u['id']}-{name:<24} ./ct example {u['id']}-{name}")
        for p in by_unit.get(u["id"], []):
            print(f"    문제  {p['id']}  {p['title']} ({p['level']})   ./ct test {p['id']}")
    print()
    print(bold("모의시험 (exams/)"))
    for e in m["exams"]:
        print(f"\n{bold('exam ' + e['id'])} {e['title']} ({e['minutes']}분)  exams/{e['slug']}/README.md")
        for pid in e["problems"]:
            p = get_problem(m, pid)
            print(f"    문제  {p['id']}  {p['title']}   ./ct test {p['id']}")


def cmd_example(args):
    m = load_manifest()
    examples = example_list(m)
    chosen = [e for e in examples if e[0] == args.id]
    if not chosen:
        chosen = [e for e in examples if e[1]["id"] == args.id]
    if not chosen:
        ids = "\n  ".join(e[0] for e in examples)
        die(f"예제 '{args.id}'를 찾을 수 없습니다. 사용 가능한 예제 ID:\n  {ids}")
    mode = "asan" if args.asan else "release"
    status = 0
    for eid, _u, cpp, inp in chosen:
        print(bold(f"=== 예제 {eid}: {rel(cpp)} ==="))
        exe = exe_path(mode, "example", eid)
        ok, log = compile_cpp(cpp, exe, mode)
        if not ok:
            print(red("컴파일 오류(CE)"))
            print(log)
            status = 1
            continue
        if log:
            print(yellow("컴파일 경고:"))
            print(log)
        if inp is not None and not args.interactive:
            print(f"(표준 입력: {rel(inp)} / 직접 입력하려면 --interactive)")
            with open(inp, "rb") as fin:
                rc = subprocess.run([str(exe)], stdin=fin).returncode
        else:
            rc = subprocess.run([str(exe)]).returncode
        if rc != 0:
            print(red(f"비정상 종료: {describe_exit(rc)}"))
            status = 1
        print()
    return status


def user_source(p, args):
    if getattr(args, "solution", False):
        return problem_paths(p)["solution"], "solution", "정답 코드"
    if getattr(args, "file", None):
        return Path(args.file).resolve(), "user", "지정한 파일"
    return problem_paths(p)["main"], "user", "내 풀이"


def cmd_test(args, force_asan=False):
    m = load_manifest()
    p = get_problem(m, args.id)
    src, kind, label = user_source(p, args)
    mode = "asan" if (force_asan or args.asan) else "release"
    limit = time_limit(m, p) * (ASAN_TIME_FACTOR if mode == "asan" else 1)
    print(bold(f"[{p['id']}] {p['title']} - {label}: {rel(src)}"))
    print(f"모드: {mode} / 플래그: {' '.join(BASE_FLAGS + MODE_FLAGS[mode])} / 테스트당 시간제한 {limit:g}초")
    final, passed, total = build_and_judge(m, p, src, kind, mode, args.case, args.verbose)
    print()
    if final == "CE":
        print(red("결과: 컴파일 오류(CE) - 테스트를 실행하지 못했습니다."))
        return 1
    if final == "AC":
        print(green(f"결과: {passed}/{total} 통과 - 정답(AC)"))
        return 0
    print(red(f"결과: {passed}/{total} 통과 - {VERDICT_NAME[final]}({final})"))
    return 1


def cmd_asan(args):
    return cmd_test(args, force_asan=True)


def cmd_run(args):
    m = load_manifest()
    p = get_problem(m, args.id)
    src, kind, _label = user_source(p, args)
    mode = "asan" if args.asan else "release"
    exe = exe_path(mode, kind, p["id"])
    ok, log = compile_cpp(src, exe, mode)
    if not ok:
        print(red("컴파일 오류(CE)"))
        print(log)
        return 1
    if log:
        print(yellow("컴파일 경고:"), file=sys.stderr)
        print(log, file=sys.stderr)
    if sys.stdin.isatty():
        print("(입력을 직접 타이핑하세요. 입력 끝은 Ctrl+D)", file=sys.stderr)
    rc = subprocess.run([str(exe)]).returncode
    if rc != 0:
        print(red(f"비정상 종료: {describe_exit(rc)}"), file=sys.stderr)
    return 0 if rc == 0 else 1


def cmd_exam(args):
    m = load_manifest()
    exam = next((e for e in m["exams"] if e["id"] == args.id), None)
    if exam is None:
        die("모의시험 ID는 " + ", ".join(e["id"] for e in m["exams"]) + " 중 하나여야 합니다.")
    print(bold(f"{exam['title']} - {exam['minutes']}분 / {len(exam['problems'])}문제"))
    print(f"안내문: exams/{exam['slug']}/README.md\n")
    if not args.grade:
        for pid in exam["problems"]:
            p = get_problem(m, pid)
            paths = problem_paths(p)
            print(f"  {p['id']}  {p['title']}")
            print(f"       문제: {rel(paths['statement'])}")
            print(f"       풀이: {rel(paths['main'])}")
            print(f"       채점: ./ct test {p['id']}")
        print(f"\n타이머를 {exam['minutes']}분으로 맞추고 시작하세요. 종료 후 일괄 채점: ./ct exam {exam['id']} --grade")
        return 0
    solved = 0
    for pid in exam["problems"]:
        p = get_problem(m, pid)
        final, passed, total = build_and_judge(m, p, problem_paths(p)["main"], "user", "release", quiet=True)
        if final == "AC":
            solved += 1
        print(f"  {p['id']}  {p['title']:<12} {paint(final)}  ({passed}/{total})")
    print(f"\n해결: {solved}/{len(exam['problems'])} 문제. 실패 상세는 ./ct test <ID>로 확인하세요.")
    print("회고 양식: exams/retrospective-template.md")
    return 0 if solved == len(exam["problems"]) else 1


def cmd_verify(args):
    """관리용: 모든 예제와 정답 코드를 검증하고, 풀이 뼈대(main.cpp)가 컴파일되는지 확인한다."""
    m = load_manifest()
    bad = 0
    modes = ["release"] + (["asan"] if args.asan else [])

    print(bold("[1/3] 예제 컴파일·실행"))
    for eid, _u, cpp, inp in example_list(m):
        if not cpp.exists():
            print(f"  {eid:<28} {red('파일 없음')}")
            bad += 1
            continue
        for mode in modes:
            exe = exe_path(mode, "example", eid)
            ok, log = compile_cpp(cpp, exe, mode)
            if not ok:
                print(f"  {eid:<28} {mode:<8} {red('CE')}\n{log}")
                bad += 1
                continue
            stdin = open(inp, "rb") if inp else subprocess.DEVNULL
            try:
                proc = subprocess.run([str(exe)], stdin=stdin, capture_output=True, timeout=20)
                rc = proc.returncode
                note = "" if proc.stdout.strip() else " (출력 없음!)"
            except subprocess.TimeoutExpired:
                rc, note = 1, " (시간초과)"
            finally:
                if inp:
                    stdin.close()
            warn = yellow(" 경고 있음") if log else ""
            if rc == 0 and not note:
                print(f"  {eid:<28} {mode:<8} {green('OK')}{warn}")
            else:
                print(f"  {eid:<28} {mode:<8} {red('FAIL')} {describe_exit(rc)}{note}")
                bad += 1

    print(bold("\n[2/3] 정답 코드 채점"))
    for p in m["problems"]:
        paths = problem_paths(p)
        for key in ("statement", "main", "hints", "solution", "explanation"):
            if not paths[key].exists():
                print(f"  {p['id']}  {red('파일 없음')}: {rel(paths[key])}")
                bad += 1
        if not paths["solution"].exists():
            continue
        for mode in modes:
            final, passed, total = build_and_judge(m, p, paths["solution"], "solution", mode, quiet=True)
            print(f"  {p['id']}  {p['title']:<12} {mode:<8} {paint(final)}  ({passed}/{total})")
            if final != "AC":
                bad += 1

    print(bold("\n[3/3] 풀이 뼈대(main.cpp) 컴파일 확인 - 사용자 파일은 읽기만 합니다"))
    ce = []
    for p in m["problems"]:
        main = problem_paths(p)["main"]
        if main.exists():
            ok, _log = compile_cpp(main, exe_path("release", "user", p["id"]), "release")
            if not ok:
                ce.append(p["id"])
    if ce:
        print(f"  {red('컴파일 실패')}: {' '.join(ce)}")
        bad += len(ce)
    else:
        print(f"  {green('OK')} 모든 main.cpp가 컴파일됩니다.")

    print()
    if bad:
        print(red(f"검증 실패: 문제 {bad}건"))
        return 1
    print(green("검증 완료: 모든 예제와 정답 코드가 통과했습니다."))
    return 0


def cmd_doctor(args):
    """환경 점검: 컴파일러, 디버거, C++17 빌드, sanitizer 동작 확인."""
    ok_all = True

    def check(name, ok, info=""):
        nonlocal ok_all
        ok_all = ok_all and ok
        print(f"  {name:<34} {green('OK') if ok else red('실패')}  {info}")

    print(f"  {'python3':<34} {green('OK')}  {sys.version.split()[0]}")
    cxx = shutil.which(CXX)
    ver = ""
    if cxx:
        ver = subprocess.run([CXX, "--version"], capture_output=True, text=True).stdout.splitlines()[0]
    check(f"C++ 컴파일러 ({CXX})", cxx is not None, ver)
    gdb = shutil.which("gdb")
    if gdb:
        check("gdb (VS Code 디버깅용)", True, gdb)
    else:  # 채점에는 필요 없으므로 경고만 한다
        print(f"  {'gdb (VS Code 디버깅용)':<34} {yellow('경고')}  없음 - 채점은 가능, 디버깅하려면 sudo apt-get install -y gdb")
    if cxx:
        src = BUILD / "doctor" / "doctor.cpp"
        src.parent.mkdir(parents=True, exist_ok=True)
        src.write_text('#include <iostream>\n#include <optional>\n'
                       'int main() { std::optional<int> v = 17; std::cout << *v << "\\n"; }\n')
        for mode in ("release", "asan"):
            exe = BUILD / "doctor" / f"prog_{mode}"
            ok, log = compile_cpp(src, exe, mode)
            ran = False
            if ok:
                proc = subprocess.run([str(exe)], capture_output=True, text=True)
                ran = proc.returncode == 0 and proc.stdout.strip() == "17"
                log = log or proc.stderr
            label = "C++17 빌드·실행" if mode == "release" else "ASan/UBSan 빌드·실행"
            check(label, ok and ran, "" if ok and ran else clip(log))
    print()
    print(green("환경 준비 완료.") if ok_all else red("일부 항목이 실패했습니다. README의 '개발 환경' 절을 확인하세요."))
    return 0 if ok_all else 1


def cmd_clean(args):
    if BUILD.exists():
        shutil.rmtree(BUILD)
    print("build/ 디렉터리를 삭제했습니다.")
    return 0


HELP_EPILOG = """\
자주 쓰는 명령:
  ./ct list                  전체 단원·예제·문제 목록
  ./ct example 00-hello_io   예제 하나 컴파일·실행 (./ct example 00 은 단원의 모든 예제)
  ./ct test 01a              문제 01a의 내 풀이(problems/.../main.cpp) 채점
  ./ct test 01a -v           실패한 테스트를 모두 자세히 표시
  ./ct test 01a --case 03    03번 테스트만 실행
  ./ct asan 01a              AddressSanitizer/UBSan으로 채점 (메모리 오류·오버플로 탐지)
  ./ct run 01a               내 풀이를 컴파일해 직접 입력으로 실행
  ./ct test 01a --solution   정답 코드로 채점 (정답이 궁금할 때가 아니라 테스트 확인용)
  ./ct exam 1                모의시험 1 안내, ./ct exam 1 --grade 로 4문제 일괄 채점
  ./ct verify                모든 예제·정답 코드 일괄 검증
  ./ct doctor                개발 환경 점검
판정: AC 정답 / WA 오답 / TLE 시간초과 / RE 런타임 오류 / CE 컴파일 오류
환경 변수 CXX로 컴파일러를 바꿀 수 있습니다 (기본 g++).
"""


def main():
    parser = argparse.ArgumentParser(prog="ct", description="C++ 코딩테스트 학습 코스 실행·채점 도구",
                                     epilog=HELP_EPILOG, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="cmd")

    sub.add_parser("list", help="단원·예제·문제 목록").set_defaults(fn=cmd_list)
    sub.add_parser("help", help="도움말").set_defaults(fn=lambda a: parser.print_help())

    ex = sub.add_parser("example", help="예제 컴파일·실행")
    ex.add_argument("id", help="예제 ID(예: 00-hello_io) 또는 단원 번호(예: 00)")
    ex.add_argument("--asan", action="store_true", help="sanitizer로 빌드")
    ex.add_argument("--interactive", action="store_true", help="준비된 입력 파일 대신 직접 입력")
    ex.set_defaults(fn=cmd_example)

    def add_problem_args(sp, with_asan=True):
        sp.add_argument("id", help="문제 ID (예: 01a)")
        sp.add_argument("--solution", action="store_true", help="내 풀이 대신 정답 코드를 사용")
        sp.add_argument("--file", help="main.cpp 대신 채점할 소스 파일 경로")
        if with_asan:
            sp.add_argument("--asan", action="store_true", help="ASan/UBSan으로 빌드")

    for name, fn, with_asan, text in (("test", cmd_test, True, "풀이 채점"),
                                      ("asan", cmd_asan, False, "sanitizer로 풀이 채점")):
        sp = sub.add_parser(name, help=text)
        add_problem_args(sp, with_asan)
        if not with_asan:
            sp.set_defaults(asan=True)
        sp.add_argument("--case", help="특정 테스트만 실행 (예: 03)")
        sp.add_argument("-v", "--verbose", action="store_true", help="실패한 테스트를 모두 자세히 표시")
        sp.set_defaults(fn=fn)

    rn = sub.add_parser("run", help="풀이를 컴파일해 표준 입력으로 실행")
    add_problem_args(rn)
    rn.set_defaults(fn=cmd_run)

    exm = sub.add_parser("exam", help="모의시험 안내·일괄 채점")
    exm.add_argument("id", help="모의시험 번호 (1 또는 2)")
    exm.add_argument("--grade", action="store_true", help="4문제를 일괄 채점")
    exm.set_defaults(fn=cmd_exam)

    vf = sub.add_parser("verify", help="모든 예제·정답 코드 검증")
    vf.add_argument("--asan", action="store_true", help="sanitizer 빌드로도 검증")
    vf.set_defaults(fn=cmd_verify)

    sub.add_parser("doctor", help="개발 환경 점검").set_defaults(fn=cmd_doctor)
    sub.add_parser("clean", help="build/ 삭제").set_defaults(fn=cmd_clean)

    args = parser.parse_args()
    if not args.cmd:
        parser.print_help()
        return 0
    return args.fn(args) or 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        sys.exit(130)
    except BrokenPipeError:  # 예: ./ct list | head
        os.dup2(os.open(os.devnull, os.O_WRONLY), sys.stdout.fileno())
        sys.exit(1)
