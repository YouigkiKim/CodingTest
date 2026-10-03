# C++ 코딩테스트 기초 학습 코스

채용 과정의 **60분·4문제 코딩테스트**를 대비해, C++ STL과 기본 풀이 패턴을 처음부터 체계적으로 복습하는 자습 코스다.
설명을 읽고 → 예제를 실행하고 → 문제를 풀고 → 로컬 테스트로 채점받는 과정을 VS Code(또는 GitHub Codespaces)와 터미널만으로 진행한다.

- **범위**: C++ 기본, 배열·문자열·구현, 정렬, 완전탐색, 해시, 누적합, 스택·큐·힙, 이분탐색, 투 포인터, BFS·DFS, 그리디 기초, DP 기초
- **구성**: 단원 13개(00~12), 실행 예제 22개, 연습문제 22개(01~11단원 × 2), 모의시험 2세트(4문제씩)
- **제외**: 세그먼트 트리, 고급 그래프, 고급 DP 등 → [추후 학습 목록](docs/next-steps.md)
- 설명은 한국어, 코드와 파일 이름은 영어, 표준은 C++17.

## 빠른 시작

### 1. 환경 준비

**GitHub Codespaces**: 저장소 페이지에서 `Code` → `Codespaces` → `Create codespace on main`.
컨테이너가 만들어지면 g++, gdb, Python 3가 준비되고, 환경 점검(`./ct doctor`)과 채점용 테스트 생성이 자동으로 실행된다(처음 한 번, 약 3~4분).

**로컬(Ubuntu/WSL)**: 아래 명령으로 도구를 설치한다.

```bash
sudo apt-get update && sudo apt-get install -y g++ gdb python3
```

**채점용 테스트**: `tests/` 폴더는 용량(약 50MB) 때문에 `.gitignore`에 들어 있어 git으로 전달되지 않는다.
저장소를 새로 받았는데 `tests/`가 없다면 한 번 생성한다(고정된 시드로 항상 같은 테스트가 만들어진다).

```bash
python3 tools/make_tests.py     # 약 3~4분
```

### 2. 처음 입력할 명령 3개

```bash
./ct doctor                 # 1) 환경 점검 (컴파일러, C++17, sanitizer)
./ct example 00-hello_io    # 2) 첫 예제 컴파일·실행
./ct test 01a               # 3) 첫 문제 채점 (아직 풀지 않았으므로 오답이 정상)
```

### 3. 첫 문제 풀어 보기

1. [units/01-array-string/README.md](units/01-array-string/README.md)를 읽는다. (C++이 처음이면 [00단원](units/00-basics/README.md)부터)
2. [problems/01a-score-mode/problem.md](problems/01a-score-mode/problem.md)에서 문제를 읽는다.
3. [problems/01a-score-mode/main.cpp](problems/01a-score-mode/main.cpp)의 `TODO`에 풀이를 작성한다.
4. `./ct test 01a`로 채점한다. 실패하면 실패한 입력, 예상 출력, 내 출력이 표시된다.
5. 막히면 같은 폴더의 `hints.md`(2단계), 다 풀었으면 `solutions/01a-score-mode/solution.md`를 본다.

## 학습 순서

번호 순서대로 진행한다. 각 단원은 앞 단원에서 배운 것만 사용한다.

| 단원 | 주제 | 예상 시간 | 문제 | 완료 기준 |
|---|---|---|---|---|
| [00](units/00-basics/README.md) | 환경과 C++ 기본 | 2~3시간 | - | 예제 3개 실행·변형, 체크리스트 |
| [01](units/01-array-string/README.md) | 배열·문자열·구현 | 3~4시간 | 01a, 01b | 두 문제 AC + 체크리스트 |
| [02](units/02-sorting/README.md) | 정렬 | 2~3시간 | 02a, 02b | 〃 |
| [03](units/03-brute-force/README.md) | 완전탐색 | 2~3시간 | 03a, 03b | 〃 |
| [04](units/04-hash-set/README.md) | 해시·집합 | 2~3시간 | 04a, 04b | 〃 |
| [05](units/05-prefix-sum/README.md) | 누적합 | 2시간 | 05a, 05b | 〃 |
| [06](units/06-stack-queue-heap/README.md) | 스택·큐·힙 | 3시간 | 06a, 06b | 〃 |
| [07](units/07-binary-search/README.md) | 이분탐색 | 3~4시간 | 07a, 07b | 〃 |
| [08](units/08-two-pointers/README.md) | 투 포인터·슬라이딩 윈도우 | 3시간 | 08a, 08b | 〃 |
| [09](units/09-bfs-dfs/README.md) | BFS·DFS | 4~5시간 | 09a, 09b | 〃 |
| [10](units/10-greedy/README.md) | 그리디 기초 | 2~3시간 | 10a, 10b | 〃 |
| [11](units/11-dp/README.md) | DP 기초 | 4~5시간 | 11a, 11b | 〃 |
| [12](units/12-practice/README.md) | 실전 연습 | 3~4시간 | 모의시험 2세트 | 두 세트 응시 + 회고 작성 |

전체 약 35~45시간. 날짜가 아니라 **완료 기준**으로 진행한다: 한 단원의 문제를 통과하고 체크리스트를 채운 뒤 다음으로 넘어간다.

**한 단원을 공부하는 방법**

1. 단원 `README.md`를 읽는다(개념 → 떠올리는 신호 → 작은 입력 따라가기).
2. 예제를 실행하고(`./ct example <단원번호>`), 코드를 고쳐 보며 결과를 예측한다.
3. 기본 문제(`a`) → 응용 문제(`b`) 순으로 푼다. 문제당 30~40분 고민해도 안 되면 힌트를 한 단계씩 본다.
4. 통과한 뒤에도 해설을 읽고 "자주 하는 실수"와 복잡도를 내 풀이와 비교한다.
5. 단원 끝의 체크리스트를 확인한다.

### 시간이 부족할 때

1. **먼저**: [01 구현](units/01-array-string/README.md) → [02 정렬](units/02-sorting/README.md) → [04 해시](units/04-hash-set/README.md) → [03 완전탐색](units/03-brute-force/README.md)
   (쉬운 문제를 확실히 푸는 데 필요한 도구들이다. C++이 낯설면 [00](units/00-basics/README.md)을 먼저.)
2. **그다음**: [09 BFS·DFS](units/09-bfs-dfs/README.md) → [07 이분탐색](units/07-binary-search/README.md) → [11 DP](units/11-dp/README.md)
3. **남은 시간에**: [05](units/05-prefix-sum/README.md), [06](units/06-stack-queue-heap/README.md), [08](units/08-two-pointers/README.md), [10](units/10-greedy/README.md)
4. 어느 경우든 [자주 하는 실수](docs/pitfalls.md)는 한 번 통독하고, [모의시험](exams/README.md) 한 세트는 시간을 재고 치른다.

이 순서는 기초 문제에서 폭넓게 쓰이는 도구를 앞에 둔 것이며, 특정 시험의 출제 비중을 조사해 정한 것은 아니다.

## 참고 문서

| 문서 | 내용 |
|---|---|
| [docs/cheatsheet.md](docs/cheatsheet.md) | STL 치트시트: 헤더, 사용 예, 반환값, 시간복잡도 |
| [docs/pitfalls.md](docs/pitfalls.md) | 자주 하는 실수 16가지와 고치는 법 |
| [docs/complexity.md](docs/complexity.md) | 입력 크기별 복잡도, 2^N과 N!, 자료형 선택 |
| [docs/next-steps.md](docs/next-steps.md) | 이 과정에서 제외한 심화 주제 목록 |

## 모의시험

```bash
./ct exam 1            # 문제 목록·파일 위치 확인 → 타이머 60분
./ct test e1a          # 문제별 채점
./ct exam 1 --grade    # 종료 후 4문제 일괄 채점
```

- [모의시험 1](exams/exam1/README.md): 구현·문자열·정렬·해시·누적합 중심
- [모의시험 2](exams/exam2/README.md): 이분탐색·탐색·그리디·DP 등 혼합
- 시험 후 [회고 양식](exams/retrospective-template.md)을 복사해 작성한다.

문제 제목과 본문에는 알고리즘 이름이 없다. 사용한 방법은 해설에서 확인한다.
모의시험은 연습용으로 직접 만든 것이며, 실제 기업의 출제 경향이나 합격 기준을 반영·검증한 것이 아니다.

## 실행·채점 도구 (`./ct`)

| 명령 | 기능 |
|---|---|
| `./ct list` | 전체 단원·예제·문제 목록과 실행 명령 |
| `./ct example <예제ID\|단원번호>` | 예제 컴파일·실행 (예: `00-hello_io`, `03`) |
| `./ct test <문제ID>` | 내 풀이(`problems/.../main.cpp`) 채점 |
| `./ct test <문제ID> -v` | 실패한 테스트를 모두 자세히 표시 |
| `./ct test <문제ID> --case 03` | 특정 테스트만 실행 |
| `./ct asan <문제ID>` | AddressSanitizer/UBSan으로 채점 (범위 밖 접근, 오버플로 등 탐지) |
| `./ct run <문제ID>` | 내 풀이를 컴파일해 직접 입력으로 실행 (`./ct run 01a < my_input.txt`도 가능) |
| `./ct test <문제ID> --solution` | 정답 코드로 채점 |
| `./ct exam <1\|2> [--grade]` | 모의시험 안내 / 일괄 채점 |
| `./ct verify [--asan]` | 모든 예제·정답 코드 일괄 검증 |
| `./ct doctor` | 개발 환경 점검 |
| `./ct clean` | 빌드 결과(`build/`) 삭제 |

**판정**

| 판정 | 의미 |
|---|---|
| AC | 정답 |
| WA | 오답 (출력이 예상과 다름) |
| TLE | 시간초과 (테스트당 기본 2초, sanitizer 모드는 10초) |
| RE | 런타임 오류 (비정상 종료: 범위 밖 접근, 0으로 나누기, 스택 오버플로 등) |
| CE | 컴파일 오류 |

- 출력은 **토큰 단위**로 비교한다. 공백·줄바꿈의 개수 차이는 무시된다.
- 빌드: `g++ -std=c++17 -Wall -Wextra -O2`. sanitizer 모드: `-g -O1 -fsanitize=address,undefined -fno-sanitize-recover=all`.
- 빌드 결과는 `build/`에 저장되며 git에서 제외된다. 채점 도구는 풀이 파일을 읽기만 하고 수정하지 않는다.
- 문제·경로·시간제한은 [manifest.json](manifest.json) 하나를 기준으로 한다.
- 다른 컴파일러를 쓰려면 `CXX=clang++ ./ct test 01a`.

**VS Code에서 직접 빌드·디버깅**

- `Ctrl+Shift+B`: 현재 C++ 파일을 디버그 빌드(`build/debug/`)
- `F5`: 현재 파일을 gdb로 디버깅(중단점, 변수 확인). 입력은 하단 터미널에 직접 타이핑한다.
- `Terminal → Run Task...`: "build and run active file", "build and run active file (ASan+UBSan)"
- 터미널에서 직접:
  ```bash
  g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined problems/01a-score-mode/main.cpp -o build/a && ./build/a
  ```

## 폴더 구조

```
.devcontainer/      Codespaces/devcontainer 설정
.vscode/            빌드 작업(tasks.json), 디버깅(launch.json)
README.md           이 문서
manifest.json       단원·예제·문제·모의시험 목록 (도구의 단일 기준)
ct                  실행·채점 도구 진입점 (tools/ct.py 호출)
docs/               치트시트, 실수 모음, 복잡도 가이드, 추후 학습 목록
units/NN-name/      단원 설명(README.md)과 예제(examples/*.cpp)
problems/ID-name/   문제(problem.md), 풀이 파일(main.cpp), 힌트(hints.md)
solutions/ID-name/  정답 코드(solution.cpp), 해설(solution.md)
tests/ID-name/      채점용 입력(NN.in)과 예상 출력(NN.out) (git 제외, tools/make_tests.py로 생성)
exams/              모의시험 안내문, 회고 양식
tools/              ct.py(채점 도구), make_tests.py(테스트 생성·검증 스크립트)
build/              빌드 결과 (자동 생성, git 제외)
```

**정답과 테스트에 관하여**: 문제를 읽을 때 정답이 바로 보이지 않도록 힌트·정답·테스트를 별도 파일과 폴더로 분리했다.
하지만 로컬 저장소이므로 보안상 숨겨진 것은 아니다. `solutions/`, `tests/`, `tools/make_tests.py`(참조 구현 포함)는
문제를 충분히 고민한 뒤에 여는 것을 스스로의 규칙으로 삼자.

## 전체 진행 체크리스트

- [ ] 환경 준비: `./ct doctor` 통과
- [ ] 00 환경과 C++ 기본 (예제 3개)
- [ ] 01 배열·문자열·구현 (01a, 01b)
- [ ] 02 정렬 (02a, 02b)
- [ ] 03 완전탐색 (03a, 03b)
- [ ] 04 해시·집합 (04a, 04b)
- [ ] 05 누적합 (05a, 05b)
- [ ] 06 스택·큐·힙 (06a, 06b)
- [ ] 07 이분탐색 (07a, 07b)
- [ ] 08 투 포인터·슬라이딩 윈도우 (08a, 08b)
- [ ] 09 BFS·DFS (09a, 09b)
- [ ] 10 그리디 기초 (10a, 10b)
- [ ] 11 DP 기초 (11a, 11b)
- [ ] [치트시트](docs/cheatsheet.md)와 [자주 하는 실수](docs/pitfalls.md) 통독
- [ ] 12 실전 연습 읽기
- [ ] 모의시험 1 응시 + 회고
- [ ] 모의시험 2 응시 + 회고
- [ ] 틀렸던 문제를 빈 파일에서 다시 풀어 통과

## 가정과 참고 사항

이 코스를 만들 때 정한 기본값이다.

- **기존 파일**: 저장소에 있던 `HyundaiMobis/`, `RideFlux/` 폴더와 그 안의 풀이 파일은 수정하지 않았다.
  `.vscode/settings.json`에는 기존 설정을 그대로 두고 C++ 관련 항목만 추가했다. 저장소에 `AGENTS.md` 같은 별도 지침 파일은 없었다.
- **문제**: 모든 문제는 이 코스를 위해 직접 작성했다. 소재가 널리 알려진 유형과 비슷할 수는 있으나 외부 사이트의 문제 본문을 가져오지 않았고 외부 링크에 의존하지 않는다.
- **입출력**: 모든 문제는 표준 입력/표준 출력을 사용하고, 답이 유일하도록 설계해 토큰 비교로 채점한다.
- **시간제한**: 테스트당 2초(`manifest.json`의 `defaults.time_limit_sec`). 실행 환경이 느리면 이 값을 늘린다.
  실제 시험의 채점 환경과는 속도가 다를 수 있다.
- **풀이 스타일**: `using namespace std;`와 표준 헤더의 명시적 include를 사용한다. `bits/stdc++.h`는 쓰지 않는다.
- **풀이 파일**: `main.cpp`에는 입출력 뼈대와 `TODO`만 있다. 필요한 헤더는 풀면서 직접 추가한다.
- **테스트**: 손으로 계산한 예제, 무작위 작은 입력(완전탐색 구현과 대조), 경계값·최대 크기 입력으로 구성했다.
  생성 방식은 `tools/make_tests.py` 상단 설명 참고.
- **재귀 깊이**: 스택 크기는 환경마다 다르다. 깊은 재귀가 필요한 풀이는 로컬에서 통과하더라도 다른 환경에서 실패할 수 있다.
- **메모리 제한**은 채점 도구에서 강제하지 않는다.
