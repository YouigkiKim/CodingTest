#!/usr/bin/env python3
"""tests/ 디렉터리의 채점용 테스트(.in/.out)를 다시 만드는 관리용 스크립트.

tests/는 .gitignore에 들어 있으므로, 저장소를 새로 받은 환경(Codespaces 등)에서는
이 스크립트를 한 번 실행해 테스트를 만들어야 한다(약 3~4분, devcontainer는 자동 실행).
난수 시드가 고정되어 있어 항상 같은 테스트가 만들어진다.
주의: 각 문제의 파이썬 참조 구현이 들어 있으므로 풀이 전에 읽으면 스포일러가 된다.

예상 출력을 만드는 방식
  1. HAND: 문제 명세를 보고 손으로 계산한 (입력, 예상 출력). 참조 구현의 결과와 다르면 즉시 실패한다.
  2. 무작위 작은 입력에서 참조 구현(ref)과 완전탐색 구현(brute)을 대조한다. 다르면 즉시 실패한다.
  3. 큰 입력의 예상 출력은 위 두 단계를 통과한 참조 구현으로 만든다.
C++ 정답 코드는 이 스크립트와 독립적으로 작성되었고 `./ct verify`로 같은 테스트를 통과하는지 확인한다.

사용법: python3 tools/make_tests.py [문제ID ...]
"""
import itertools
import json
import random
import sys
from collections import Counter, deque
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MOD = 1_000_000_007
P = {}  # id -> dict(hand, ref, brute, small, big)


def lines(*rows):
    return "\n".join(rows) + "\n"


def nums(seq):
    return " ".join(map(str, seq))


def tok(s):
    return s.split()


# ------------------------------------------------------------------ 01a
def ref_01a(s):
    t = tok(s); a = list(map(int, t[1:]))
    cnt = [0] * 101
    for x in a:
        cnt[x] += 1
    best = max(range(101), key=lambda v: (cnt[v], -v))
    return f"{best} {cnt[best]}"


def brute_01a(s):
    t = tok(s); a = list(map(int, t[1:]))
    best = None
    for v in sorted(set(a)):
        c = a.count(v)
        if best is None or c > best[1]:
            best = (v, c)
    return f"{best[0]} {best[1]}"


def small_01a(r):
    n = r.randint(1, 8)
    return lines(str(n), nums(r.randint(0, 4) * 25 for _ in range(n)))


def big_01a(r):
    n = 200000
    yield lines(str(n), nums(r.randint(0, 100) for _ in range(n)))
    yield lines(str(n), nums([100] * n))
    yield lines(str(n), nums([i % 101 for i in range(n)]))


P["01a"] = dict(hand=[
    ("5\n70 80 70 90 80\n", "70 2"),
    ("1\n0\n", "0 1"),
    ("4\n100 100 100 100\n", "100 4"),
    ("6\n3 1 2 3 1 2\n", "1 2"),
    ("3\n100 0 50\n", "0 1"),
], ref=ref_01a, brute=brute_01a, small=small_01a, big=big_01a)


# ------------------------------------------------------------------ 01b
def ref_01b(s):
    t = tok(s); h, w, cmd = int(t[0]), int(t[1]), t[2]
    dr = [0, 1, 0, -1]; dc = [1, 0, -1, 0]  # 동 남 서 북
    r = c = 1; d = 0; ignored = 0
    for ch in cmd:
        if ch == "L":
            d = (d + 3) % 4
        elif ch == "R":
            d = (d + 1) % 4
        else:
            nr, nc = r + dr[d], c + dc[d]
            if 1 <= nr <= h and 1 <= nc <= w:
                r, c = nr, nc
            else:
                ignored += 1
    return f"{r} {c} {ignored}"


def brute_01b(s):
    t = tok(s); h, w, cmd = int(t[0]), int(t[1]), t[2]
    left = {"E": "N", "N": "W", "W": "S", "S": "E"}
    right = {v: k for k, v in left.items()}
    step = {"E": (0, 1), "W": (0, -1), "S": (1, 0), "N": (-1, 0)}
    pos = (1, 1); face = "E"; ignored = 0
    for ch in cmd:
        if ch == "L":
            face = left[face]
        elif ch == "R":
            face = right[face]
        else:
            nxt = (pos[0] + step[face][0], pos[1] + step[face][1])
            if nxt[0] < 1 or nxt[0] > h or nxt[1] < 1 or nxt[1] > w:
                ignored += 1
            else:
                pos = nxt
    return f"{pos[0]} {pos[1]} {ignored}"


def small_01b(r):
    return lines(f"{r.randint(1, 4)} {r.randint(1, 4)}", "".join(r.choice("LRFF") for _ in range(r.randint(1, 12))))


def big_01b(r):
    n = 200000
    yield lines("1000 1000", "".join(r.choice("LRFFFF") for _ in range(n)))
    yield lines("5 5", "".join(r.choice("LRFFF") for _ in range(n)))
    yield lines("1 1000", "F" * n)


P["01b"] = dict(hand=[
    ("3 4\nFFRFLF\n", "2 4 0"),
    ("1 1\nFFLFRRF\n", "1 1 4"),
    ("2 2\nLF\n", "1 1 1"),
    ("3 3\nRFFFRF\n", "3 1 2"),
    ("2 3\nLLLL\n", "1 1 0"),
    ("2 3\nFFFRFFRFFF\n", "2 1 3"),
], ref=ref_01b, brute=brute_01b, small=small_01b, big=big_01b)


# ------------------------------------------------------------------ 02a
def ref_02a(s):
    t = tok(s); a = sorted(set(map(int, t[1:])))
    return f"{len(a)}\n{nums(a)}"


def brute_02a(s):
    t = tok(s); a = list(map(int, t[1:]))
    out = []
    for x in a:
        if x not in out:
            out.append(x)
    for i in range(len(out)):          # 선택 정렬
        for j in range(i + 1, len(out)):
            if out[j] < out[i]:
                out[i], out[j] = out[j], out[i]
    return f"{len(out)}\n{nums(out)}"


def small_02a(r):
    n = r.randint(1, 8)
    return lines(str(n), nums(r.randint(-3, 3) for _ in range(n)))


def big_02a(r):
    n = 200000
    yield lines(str(n), nums(r.randint(-10**9, 10**9) for _ in range(n)))
    yield lines(str(n), nums(r.randint(-50, 50) for _ in range(n)))
    yield lines(str(n), nums(range(n, 0, -1)))


P["02a"] = dict(hand=[
    ("5\n3 1 3 2 1\n", "3\n1 2 3"),
    ("1\n-5\n", "1\n-5"),
    ("4\n7 7 7 7\n", "1\n7"),
    ("6\n1000000000 -1000000000 0 5 -5 0\n", "5\n-1000000000 -5 0 5 1000000000"),
    ("3\n1 2 3\n", "3\n1 2 3"),
], ref=ref_02a, brute=brute_02a, small=small_02a, big=big_02a)


# ------------------------------------------------------------------ 02b
def parse_02b(s):
    t = tok(s); n = int(t[0])
    return [(t[1 + 3 * i], int(t[2 + 3 * i]), int(t[3 + 3 * i])) for i in range(n)]


def ref_02b(s):
    rows = parse_02b(s)
    rows.sort(key=lambda x: (-x[1], x[2], x[0]))
    return "\n".join(x[0] for x in rows)


def brute_02b(s):
    rows = parse_02b(s)

    def before(a, b):  # a가 b보다 앞인가
        if a[1] != b[1]:
            return a[1] > b[1]
        if a[2] != b[2]:
            return a[2] < b[2]
        return a[0] < b[0]
    out = []
    for x in rows:  # 삽입 정렬
        i = 0
        while i < len(out) and before(out[i], x):
            i += 1
        out.insert(i, x)
    return "\n".join(x[0] for x in out)


def name_of(i):
    s = ""
    i += 1
    while i:
        i, d = divmod(i - 1, 26)
        s = chr(97 + d) + s
    return s


def small_02b(r):
    n = r.randint(1, 7)
    ids = r.sample(range(40), n)
    return lines(str(n), *(f"{name_of(i)} {r.randint(0, 2)} {r.randint(0, 2)}" for i in ids))


def big_02b(r):
    n = 100000
    ids = r.sample(range(10**6), n)
    yield lines(str(n), *(f"{name_of(i)} {r.randint(0, 20)} {r.randint(0, 300)}" for i in ids))
    ids = r.sample(range(10**6), n)
    yield lines(str(n), *(f"{name_of(i)} {r.randint(0, 20)} {r.randint(0, 10**9)}" for i in ids))


P["02b"] = dict(hand=[
    ("4\nkim 3 120\nlee 5 300\npark 3 100\nchoi 5 300\n", "choi\nlee\npark\nkim"),
    ("1\na 0 0\n", "a"),
    ("3\nc 1 10\nb 1 10\na 1 10\n", "a\nb\nc"),
    ("3\nx 2 50\ny 3 999\nz 2 49\n", "y\nz\nx"),
    ("5\naa 0 5\nab 0 5\nb 1 1000000000\nc 1 999999999\na 0 5\n", "c\nb\na\naa\nab"),
], ref=ref_02b, brute=brute_02b, small=small_02b, big=big_02b)


# ------------------------------------------------------------------ 03a
def ref_03a(s):
    t = tok(s); n, k = int(t[0]), int(t[1]); a = list(map(int, t[2:]))
    cnt = Counter(x % k for x in a)
    total = 0
    for rem, c in cnt.items():
        other = (k - rem) % k
        if other == rem:
            total += c * (c - 1) // 2
        elif rem < other:
            total += c * cnt.get(other, 0)
    return str(total)


def brute_03a(s):
    t = tok(s); n, k = int(t[0]), int(t[1]); a = list(map(int, t[2:]))
    return str(sum(1 for i in range(n) for j in range(i + 1, n) if (a[i] + a[j]) % k == 0))


def small_03a(r):
    n = r.randint(1, 8)
    return lines(f"{n} {r.randint(1, 6)}", nums(r.randint(1, 12) for _ in range(n)))


def big_03a(r):
    n = 2000
    yield lines(f"{n} 7", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000", nums([10**9] * n))
    yield lines(f"{n} 999999999", nums(r.choice([10**9 - 1, 999999998, 1, 10**9]) for _ in range(n)))


P["03a"] = dict(hand=[
    ("4 3\n1 2 3 6\n", "2"),
    ("1 5\n10\n", "0"),
    ("3 1\n5 6 7\n", "3"),
    ("2 1000000000\n1000000000 1000000000\n", "1"),
    ("4 10\n5 5 5 5\n", "6"),
    ("3 7\n1 2 3\n", "0"),
], ref=ref_03a, brute=brute_03a, small=small_03a, big=big_03a)


# ------------------------------------------------------------------ 03b
def parse_03b(s):
    t = list(map(int, tok(s))); n = t[0]
    return n, [t[1 + i * n: 1 + (i + 1) * n] for i in range(n)]


def ref_03b(s):  # 비트마스크 DP
    n, d = parse_03b(s)
    INF = float("inf")
    dp = [[INF] * n for _ in range(1 << n)]
    dp[1][0] = 0
    for mask in range(1 << n):
        for last in range(n):
            cur = dp[mask][last]
            if cur == INF:
                continue
            for nxt in range(n):
                if not mask >> nxt & 1:
                    nm = mask | 1 << nxt
                    dp[nm][nxt] = min(dp[nm][nxt], cur + d[last][nxt])
    return str(min(dp[(1 << n) - 1]))


def brute_03b(s):
    n, d = parse_03b(s)
    best = None
    for perm in itertools.permutations(range(1, n)):
        cur, pos = 0, 0
        for x in perm:
            cur += d[pos][x]; pos = x
        best = cur if best is None else min(best, cur)
    return str(best)


def gen_03b(r, n, hi):
    return lines(str(n), *(nums(0 if i == j else r.randint(0, hi) for j in range(n)) for i in range(n)))


def small_03b(r):
    return gen_03b(r, r.randint(2, 6), 9)


def big_03b(r):
    yield gen_03b(r, 8, 10**6)
    yield gen_03b(r, 8, 100)
    yield lines("8", *(nums(0 if i == j else 10**6 for j in range(8)) for i in range(8)))
    yield gen_03b(r, 7, 1000)


P["03b"] = dict(hand=[
    ("3\n0 5 2\n5 0 4\n2 4 0\n", "6"),
    ("2\n0 7\n3 0\n", "7"),
    ("3\n0 1 10\n100 0 100\n1 1 0\n", "11"),
    ("4\n0 1 2 3\n1 0 1 2\n2 1 0 1\n3 2 1 0\n", "3"),
    ("3\n0 0 0\n0 0 0\n0 0 0\n", "0"),
], ref=ref_03b, brute=brute_03b, small=small_03b, big=big_03b)


# ------------------------------------------------------------------ 04a
def ref_04a(s):
    t = tok(s)[1:]
    cnt = Counter(t)
    name = min(cnt, key=lambda x: (-cnt[x], x))
    return f"{name} {cnt[name]}"


def brute_04a(s):
    t = tok(s)[1:]
    best = None
    for name in sorted(t):
        c = t.count(name)
        if best is None or c > best[1]:
            best = (name, c)
    return f"{best[0]} {best[1]}"


def small_04a(r):
    n = r.randint(1, 8)
    return lines(str(n), *(r.choice(["a", "ab", "b", "abc", "z"]) for _ in range(n)))


def big_04a(r):
    n = 200000
    pool = [name_of(i) for i in r.sample(range(10**7), 1000)]
    yield lines(str(n), *(r.choice(pool) for _ in range(n)))
    ids = r.sample(range(10**7), n)
    yield lines(str(n), *(name_of(i) for i in ids))
    yield lines(str(n), *(["zzzzzzzzzz"] * (n // 2) + ["zzzzzzzzzy"] * (n // 2)))


P["04a"] = dict(hand=[
    ("5\nkim\nlee\nkim\npark\nlee\n", "kim 2"),
    ("1\nzzz\n", "zzz 1"),
    ("4\nb\na\nb\na\n", "a 2"),
    ("3\nc\nb\na\n", "a 1"),
    ("6\nab\na\nab\nabc\nab\na\n", "ab 3"),
], ref=ref_04a, brute=brute_04a, small=small_04a, big=big_04a)


# ------------------------------------------------------------------ 04b
def ref_04b(s):
    t = list(map(int, tok(s))); n, T = t[0], t[1]; a = t[2:]
    seen = Counter(); total = 0
    for x in a:
        total += seen[T - x]
        seen[x] += 1
    return str(total)


def brute_04b(s):
    t = list(map(int, tok(s))); n, T = t[0], t[1]; a = t[2:]
    return str(sum(1 for i in range(n) for j in range(i + 1, n) if a[i] + a[j] == T))


def small_04b(r):
    n = r.randint(1, 8)
    return lines(f"{n} {r.randint(-6, 6)}", nums(r.randint(-4, 4) for _ in range(n)))


def big_04b(r):
    n = 200000
    yield lines(f"{n} 10", nums([5] * n))
    yield lines(f"{n} 100", nums(r.randint(-100, 200) for _ in range(n)))
    yield lines(f"{n} 2000000000", nums(r.choice([10**9, 10**9 - 1, 1]) for _ in range(n)))
    yield lines(f"{n} -2000000000", nums(r.randint(-10**9, 10**9) for _ in range(n)))


P["04b"] = dict(hand=[
    ("5 6\n1 5 3 3 7\n", "2"),
    ("1 2\n1\n", "0"),
    ("4 4\n2 2 2 2\n", "6"),
    ("3 0\n-1 1 0\n", "1"),
    ("2 2000000000\n1000000000 1000000000\n", "1"),
    ("4 10\n1 2 3 4\n", "0"),
    ("5 -4\n-2 -2 -2 0 -4\n", "4"),
], ref=ref_04b, brute=brute_04b, small=small_04b, big=big_04b)


# ------------------------------------------------------------------ 05a
def parse_05a(s):
    t = list(map(int, tok(s))); n, q = t[0], t[1]
    a = t[2:2 + n]; qs = t[2 + n:]
    return a, [(qs[2 * i], qs[2 * i + 1]) for i in range(q)]


def ref_05a(s):
    a, qs = parse_05a(s)
    pre = [0]
    for x in a:
        pre.append(pre[-1] + x)
    return "\n".join(str(pre[r] - pre[l - 1]) for l, r in qs)


def brute_05a(s):
    a, qs = parse_05a(s)
    return "\n".join(str(sum(a[l - 1:r])) for l, r in qs)


def gen_05a(r, n, q, lo, hi, wide=False):
    qs = []
    for _ in range(q):
        if wide:
            l = r.randint(1, max(1, n // 10)); rr = r.randint(n - n // 10, n)
        else:
            l = r.randint(1, n); rr = r.randint(l, n)
        qs.append(f"{l} {rr}")
    return lines(f"{n} {q}", nums(r.randint(lo, hi) for _ in range(n)), *qs)


def small_05a(r):
    return gen_05a(r, r.randint(1, 7), r.randint(1, 5), -5, 5)


def big_05a(r):
    yield gen_05a(r, 200000, 200000, 10**9, 10**9, wide=True)
    yield gen_05a(r, 200000, 200000, -10**9, 10**9)
    yield gen_05a(r, 2000, 2000, -100, 100)


P["05a"] = dict(hand=[
    ("5 3\n1 2 3 4 5\n1 5\n2 4\n3 3\n", "15\n9\n3"),
    ("1 1\n-7\n1 1\n", "-7"),
    ("3 2\n1000000000 1000000000 1000000000\n1 3\n2 3\n", "3000000000\n2000000000"),
    ("4 3\n5 -5 5 -5\n1 4\n1 1\n2 3\n", "0\n5\n0"),
], ref=ref_05a, brute=brute_05a, small=small_05a, big=big_05a)


# ------------------------------------------------------------------ 05b
def ref_05b(s):
    t = list(map(int, tok(s))); n, k = t[0], t[1]; a = t[2:]
    seen = Counter({0: 1}); pre = 0; total = 0
    for x in a:
        pre += x
        total += seen[pre - k]
        seen[pre] += 1
    return str(total)


def brute_05b(s):
    t = list(map(int, tok(s))); n, k = t[0], t[1]; a = t[2:]
    return str(sum(1 for i in range(n) for j in range(i, n) if sum(a[i:j + 1]) == k))


def small_05b(r):
    n = r.randint(1, 8)
    return lines(f"{n} {r.randint(-4, 4)}", nums(r.randint(-3, 3) for _ in range(n)))


def big_05b(r):
    n = 200000
    yield lines(f"{n} 0", nums([0] * n))
    yield lines(f"{n} 0", nums(r.randint(-3, 3) for _ in range(n)))
    yield lines(f"{n} 100000000000000", nums([10**9] * n))
    yield lines(f"{n} 5", nums(r.randint(0, 2) for _ in range(n)))


P["05b"] = dict(hand=[
    ("5 3\n1 2 1 2 1\n", "4"),
    ("1 5\n5\n", "1"),
    ("1 5\n4\n", "0"),
    ("3 0\n0 0 0\n", "6"),
    ("4 0\n1 -1 1 -1\n", "4"),
    ("3 -2\n-1 -1 -1\n", "2"),
    ("2 2000000000\n1000000000 1000000000\n", "1"),
], ref=ref_05b, brute=brute_05b, small=small_05b, big=big_05b)


# ------------------------------------------------------------------ 06a
def ok_brackets(w):
    st = []
    pair = {")": "(", "]": "[", "}": "{"}
    for ch in w:
        if ch in "([{":
            st.append(ch)
        elif not st or st.pop() != pair[ch]:
            return False
    return not st


def ref_06a(s):
    return "\n".join("YES" if ok_brackets(w) else "NO" for w in tok(s)[1:])


def brute_06a(s):
    out = []
    for w in tok(s)[1:]:
        while True:
            nw = w.replace("()", "").replace("[]", "").replace("{}", "")
            if nw == w:
                break
            w = nw
        out.append("YES" if not w else "NO")
    return "\n".join(out)


def rand_valid(r, pairs):
    st = []; out = []; opened = 0
    while opened < pairs or st:
        if opened < pairs and (not st or r.random() < 0.5):
            ch = r.choice("([{"); st.append(ch); out.append(ch); opened += 1
        else:
            out.append({"(": ")", "[": "]", "{": "}"}[st.pop()])
    return "".join(out)


def small_06a(r):
    ws = []
    for _ in range(r.randint(1, 4)):
        if r.random() < 0.5:
            ws.append("".join(r.choice("()[]{}") for _ in range(r.randint(1, 6))))
        else:
            w = list(rand_valid(r, r.randint(1, 4)))
            if r.random() < 0.5:
                w[r.randrange(len(w))] = r.choice("()[]{}")
            ws.append("".join(w))
    return lines(str(len(ws)), *ws)


def big_06a(r):
    yield lines("1", "(" * 100000 + ")" * 100000)
    yield lines("1", "[" * 200000)
    ws = []
    for i in range(1000):
        w = list(rand_valid(r, 100))
        if i % 2:
            j = r.randrange(len(w)); w[j] = r.choice([c for c in "()[]{}" if c != w[j]])
        ws.append("".join(w))
    yield lines(str(len(ws)), *ws)
    yield lines("2", rand_valid(r, 50000), rand_valid(r, 49999) + "(]")


P["06a"] = dict(hand=[
    ("6\n()\n([]{})\n(]\n((\n)(\n{[()]}[]\n", "YES\nYES\nNO\nNO\nNO\nYES"),
    ("1\n)\n", "NO"),
    ("1\n(\n", "NO"),
    ("2\n([)]\n(((())))\n", "NO\nYES"),
    ("3\n}{\n{}{}{}\n[[]\n", "NO\nYES\nNO"),
], ref=ref_06a, brute=brute_06a, small=small_06a, big=big_06a)


# ------------------------------------------------------------------ 06b
def ref_06b(s):
    import heapq
    a = list(map(int, tok(s)))[1:]
    heapq.heapify(a); total = 0
    while len(a) > 1:
        x = heapq.heappop(a) + heapq.heappop(a)
        total += x
        heapq.heappush(a, x)
    return str(total)


def brute_06b(s):
    a = list(map(int, tok(s)))[1:]

    def go(v):
        if len(v) == 1:
            return 0
        best = None
        for i in range(len(v)):
            for j in range(i + 1, len(v)):
                rest = [v[k] for k in range(len(v)) if k != i and k != j] + [v[i] + v[j]]
                c = v[i] + v[j] + go(rest)
                best = c if best is None else min(best, c)
        return best
    return str(go(a))


def small_06b(r):
    n = r.randint(1, 6)
    return lines(str(n), nums(r.randint(1, 9) for _ in range(n)))


def big_06b(r):
    n = 200000
    yield lines(str(n), nums([10**9] * n))
    yield lines(str(n), nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(str(n), nums(range(n, 0, -1)))


P["06b"] = dict(hand=[
    ("3\n1 2 3\n", "9"),
    ("1\n100\n", "0"),
    ("2\n5 7\n", "12"),
    ("4\n1 1 1 1\n", "8"),
    ("4\n10 1 1 1\n", "18"),
    ("3\n1000000000 1000000000 1000000000\n", "5000000000"),
], ref=ref_06b, brute=brute_06b, small=small_06b, big=big_06b)


# ------------------------------------------------------------------ 07a
def parse_07a(s):
    t = list(map(int, tok(s))); n, q = t[0], t[1]
    a = t[2:2 + n]; qs = t[2 + n:]
    return a, [(qs[2 * i], qs[2 * i + 1]) for i in range(q)]


def ref_07a(s):
    import bisect
    a, qs = parse_07a(s); a.sort()
    return "\n".join(str(bisect.bisect_right(a, hi) - bisect.bisect_left(a, lo)) for lo, hi in qs)


def brute_07a(s):
    a, qs = parse_07a(s)
    return "\n".join(str(sum(1 for x in a if lo <= x <= hi)) for lo, hi in qs)


def gen_07a(r, n, q, v):
    qs = []
    for _ in range(q):
        lo = r.randint(-v, v); hi = r.randint(lo, v)
        qs.append(f"{lo} {hi}")
    return lines(f"{n} {q}", nums(r.randint(-v, v) for _ in range(n)), *qs)


def small_07a(r):
    return gen_07a(r, r.randint(1, 8), r.randint(1, 5), 6)


def big_07a(r):
    yield gen_07a(r, 100000, 100000, 10**9)
    yield gen_07a(r, 100000, 100000, 50)
    yield lines("100000 100000", nums([7] * 100000), *(["7 7", "-1000000000 1000000000", "8 9", "6 6"] * 25000))


P["07a"] = dict(hand=[
    ("5 3\n4 1 7 4 9\n4 4\n1 9\n5 6\n", "2\n5\n0"),
    ("1 2\n5\n5 5\n6 10\n", "1\n0"),
    ("4 3\n-3 -3 0 3\n-3 -3\n-1000000000 1000000000\n-2 2\n", "2\n4\n1"),
    ("3 2\n2 2 2\n1 1\n3 3\n", "0\n0"),
], ref=ref_07a, brute=brute_07a, small=small_07a, big=big_07a)


# ------------------------------------------------------------------ 07b
def ref_07b(s):
    t = list(map(int, tok(s))); n, k = t[0], t[1]; a = t[2:]
    lo, hi = 0, max(a)  # lo는 항상 가능(0은 '불가능'을 뜻하는 답), hi+1은 불가능
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if sum(x // mid for x in a) >= k:
            lo = mid
        else:
            hi = mid - 1
    return str(lo)


def brute_07b(s):
    t = list(map(int, tok(s))); n, k = t[0], t[1]; a = t[2:]
    for L in range(max(a), 0, -1):
        if sum(x // L for x in a) >= k:
            return str(L)
    return "0"


def small_07b(r):
    n = r.randint(1, 5)
    return lines(f"{n} {r.randint(1, 12)}", nums(r.randint(1, 20) for _ in range(n)))


def big_07b(r):
    n = 100000
    yield lines(f"{n} 1000000000", nums([10**9] * n))
    yield lines(f"{n} 1000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 77777", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000", nums(r.randint(1, 5000) for _ in range(n)))
    yield lines(f"{n} 1", nums(r.randint(1, 10**9) for _ in range(n)))


P["07b"] = dict(hand=[
    ("3 4\n10 7 5\n", "5"),
    ("1 1\n1\n", "1"),
    ("2 5\n1 2\n", "0"),
    ("2 2\n1000000000 1000000000\n", "1000000000"),
    ("3 7\n8 8 8\n", "2"),
    ("1 1000000000\n1000000000\n", "1"),
    ("4 3\n5 5 5 1\n", "5"),
], ref=ref_07b, brute=brute_07b, small=small_07b, big=big_07b)


# ------------------------------------------------------------------ 08a
def ref_08a(s):
    t = list(map(int, tok(s))); n, T = t[0], t[1]; a = t[2:]
    i, j = 0, n - 1; best = None
    while i < j:
        cur = a[i] + a[j]
        d = abs(cur - T)
        best = d if best is None else min(best, d)
        if cur < T:
            i += 1
        elif cur > T:
            j -= 1
        else:
            break
    return str(best)


def brute_08a(s):
    t = list(map(int, tok(s))); n, T = t[0], t[1]; a = t[2:]
    return str(min(abs(a[i] + a[j] - T) for i in range(n) for j in range(i + 1, n)))


def small_08a(r):
    n = r.randint(2, 8)
    return lines(f"{n} {r.randint(-25, 25)}", nums(sorted(r.randint(-10, 10) for _ in range(n))))


def big_08a(r):
    n = 200000
    yield lines(f"{n} 123456789", nums(sorted(r.randint(-10**9, 10**9) for _ in range(n))))
    yield lines(f"{n} -2000000000", nums([10**9] * n))
    yield lines(f"{n} 1", nums(range(0, 4 * n, 4)))
    yield lines(f"{n} 1999999999", nums(sorted(r.randint(-10**9, 10**9) for _ in range(n))))


P["08a"] = dict(hand=[
    ("5 10\n1 3 4 8 9\n", "0"),
    ("2 0\n5 6\n", "11"),
    ("4 100\n1 2 3 4\n", "93"),
    ("4 -100\n1 2 3 4\n", "103"),
    ("5 13\n1 2 4 8 16\n", "1"),
    ("3 2000000000\n-1000000000 -1000000000 -1000000000\n", "4000000000"),
    ("3 7\n2 2 2\n", "3"),
], ref=ref_08a, brute=brute_08a, small=small_08a, big=big_08a)


# ------------------------------------------------------------------ 08b
def ref_08b(s):
    t = list(map(int, tok(s))); n, S = t[0], t[1]; a = t[2:]
    best = 0; left = 0; cur = 0
    for right in range(n):
        cur += a[right]
        while cur >= S:
            length = right - left + 1
            best = length if best == 0 else min(best, length)
            cur -= a[left]; left += 1
    return str(best)


def brute_08b(s):
    t = list(map(int, tok(s))); n, S = t[0], t[1]; a = t[2:]
    best = 0
    for i in range(n):
        for j in range(i, n):
            if sum(a[i:j + 1]) >= S and (best == 0 or j - i + 1 < best):
                best = j - i + 1
    return str(best)


def small_08b(r):
    n = r.randint(1, 8)
    return lines(f"{n} {r.randint(1, 25)}", nums(r.randint(1, 8) for _ in range(n)))


def big_08b(r):
    n = 200000
    yield lines(f"{n} {n}", nums([1] * n))
    yield lines(f"{n} 100000000000000", nums([10**9] * n))
    yield lines(f"{n} 50000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 100001", nums([1] * (n - 1) + [100000]))


P["08b"] = dict(hand=[
    ("6 15\n5 1 3 5 10 7\n", "2"),
    ("3 100\n1 2 3\n", "0"),
    ("1 5\n5\n", "1"),
    ("1 6\n5\n", "0"),
    ("5 15\n1 2 3 4 5\n", "5"),
    ("4 1\n1 1 1 1\n", "1"),
    ("3 3000000000\n1000000000 1000000000 1000000000\n", "3"),
    ("5 7\n2 3 1 2 4\n", "3"),
], ref=ref_08b, brute=brute_08b, small=small_08b, big=big_08b)


# ------------------------------------------------------------------ 09a
def parse_grid(s):
    t = tok(s); h, w = int(t[0]), int(t[1])
    return h, w, t[2:2 + h]


def ref_09a(s):
    h, w, g = parse_grid(s)
    seen = [[False] * w for _ in range(h)]
    count = 0
    for sr in range(h):
        for sc in range(w):
            if g[sr][sc] != "#" or seen[sr][sc]:
                continue
            count += 1
            seen[sr][sc] = True
            dq = deque([(sr, sc)])
            while dq:
                r, c = dq.popleft()
                for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
                    if 0 <= nr < h and 0 <= nc < w and g[nr][nc] == "#" and not seen[nr][nc]:
                        seen[nr][nc] = True
                        dq.append((nr, nc))
    return str(count)


def brute_09a(s):  # union-find
    h, w, g = parse_grid(s)
    parent = list(range(h * w))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    for r in range(h):
        for c in range(w):
            if g[r][c] != "#":
                continue
            if r + 1 < h and g[r + 1][c] == "#":
                parent[find(r * w + c)] = find((r + 1) * w + c)
            if c + 1 < w and g[r][c + 1] == "#":
                parent[find(r * w + c)] = find(r * w + c + 1)
    return str(len({find(r * w + c) for r in range(h) for c in range(w) if g[r][c] == "#"}))


def rand_grid(r, h, w, p, chars="#."):
    return ["".join(chars[0] if r.random() < p else chars[1] for _ in range(w)) for _ in range(h)]


def small_09a(r):
    h, w = r.randint(1, 5), r.randint(1, 5)
    return lines(f"{h} {w}", *rand_grid(r, h, w, 0.5))


def snake(h, w):
    rows = []
    for i in range(h):
        if i % 2 == 0:
            rows.append("#" * w)
        elif i % 4 == 1:
            rows.append("." * (w - 1) + "#")
        else:
            rows.append("#" + "." * (w - 1))
    return rows


def big_09a(r):
    yield lines("500 500", *snake(500, 500))
    yield lines("500 500", *(["#" * 500] * 500))
    yield lines("500 500", *rand_grid(r, 500, 500, 0.5))
    yield lines("500 500", *("".join("#" if (i + j) % 2 == 0 else "." for j in range(500)) for i in range(500)))
    yield lines("500 500", *rand_grid(r, 500, 500, 0.62))


P["09a"] = dict(hand=[
    ("3 4\n#..#\n#..#\n..##\n", "2"),
    ("1 1\n.\n", "0"),
    ("1 1\n#\n", "1"),
    ("3 3\n#.#\n.#.\n#.#\n", "5"),
    ("2 5\n#####\n#####\n", "1"),
    ("3 5\n#.#.#\n#.#.#\n###.#\n", "2"),
], ref=ref_09a, brute=brute_09a, small=small_09a, big=big_09a)


# ------------------------------------------------------------------ 09b
def find_ch(g, ch):
    for r, row in enumerate(g):
        c = row.find(ch)
        if c >= 0:
            return r, c


def ref_09b(s):
    h, w, g = parse_grid(s)
    sr, sc = find_ch(g, "S"); er, ec = find_ch(g, "E")
    dist = [[-1] * w for _ in range(h)]
    dist[sr][sc] = 0
    dq = deque([(sr, sc)])
    while dq:
        r, c = dq.popleft()
        for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
            if 0 <= nr < h and 0 <= nc < w and g[nr][nc] != "#" and dist[nr][nc] < 0:
                dist[nr][nc] = dist[r][c] + 1
                dq.append((nr, nc))
    return str(dist[er][ec])


def brute_09b(s):  # 변화가 없을 때까지 반복 완화
    h, w, g = parse_grid(s)
    sr, sc = find_ch(g, "S"); er, ec = find_ch(g, "E")
    INF = 10**9
    dist = [[INF] * w for _ in range(h)]
    dist[sr][sc] = 0
    changed = True
    while changed:
        changed = False
        for r in range(h):
            for c in range(w):
                if g[r][c] == "#":
                    continue
                for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
                    if 0 <= nr < h and 0 <= nc < w and dist[nr][nc] + 1 < dist[r][c]:
                        dist[r][c] = dist[nr][nc] + 1
                        changed = True
    return str(dist[er][ec] if dist[er][ec] < INF else -1)


def place_se(r, rows):
    h, w = len(rows), len(rows[0])
    a, b = r.sample(range(h * w), 2)
    g = [list(x) for x in rows]
    g[a // w][a % w] = "S"; g[b // w][b % w] = "E"
    return ["".join(x) for x in g]


def small_09b(r):
    while True:
        h, w = r.randint(1, 5), r.randint(1, 5)
        if h * w >= 2:
            break
    return lines(f"{h} {w}", *place_se(r, rand_grid(r, h, w, 0.3)))


def big_09b(r):
    n = 1000
    g = [["."] * n for _ in range(n)]
    g[0][0] = "S"; g[n - 1][n - 1] = "E"
    yield lines(f"{n} {n}", *("".join(x) for x in g))
    yield lines(f"{n} {n}", *place_se(r, rand_grid(r, n, n, 0.3)))
    rows = [list(x) for x in snake(n, n)]
    rows = [["." if ch == "#" else "#" for ch in row] for row in rows]  # 길이 뱀 모양
    rows[0][0] = "S"; rows[n - 1][0 if rows[n - 1][0] == "." else n - 1] = "E"
    yield lines(f"{n} {n}", *("".join(x) for x in rows))
    yield lines(f"{n} {n}", *place_se(r, rand_grid(r, n, n, 0.45)))
    yield lines(f"{n} {n}", *place_se(r, rand_grid(r, n, n, 0.2)))


P["09b"] = dict(hand=[
    ("3 4\nS..#\n.#..\n...E\n", "5"),
    ("1 2\nSE\n", "1"),
    ("1 3\nS#E\n", "-1"),
    ("3 3\nS#.\n##.\n..E\n", "-1"),
    ("3 5\nS.#..\n#.#.#\n#...E\n", "6"),
    ("2 2\nES\n..\n", "1"),
], ref=ref_09b, brute=brute_09b, small=small_09b, big=big_09b)


# ------------------------------------------------------------------ 10a
def ref_10a(s):
    t = list(map(int, tok(s))); n, cap = t[0], t[1]; a = sorted(t[2:])
    cnt = 0; total = 0
    for x in a:
        if total + x > cap:
            break
        total += x; cnt += 1
    return str(cnt)


def brute_10a(s):
    t = list(map(int, tok(s))); n, cap = t[0], t[1]; a = t[2:]
    best = 0
    for mask in range(1 << n):
        tot = sum(a[i] for i in range(n) if mask >> i & 1)
        if tot <= cap:
            best = max(best, bin(mask).count("1"))
    return str(best)


def small_10a(r):
    n = r.randint(1, 8)
    return lines(f"{n} {r.randint(1, 30)}", nums(r.randint(1, 10) for _ in range(n)))


def big_10a(r):
    n = 200000
    yield lines(f"{n} 100000000000000", nums([10**9] * n))
    yield lines(f"{n} 1000000000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 3000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000000000", nums(r.randint(1, 1000) for _ in range(n)))


P["10a"] = dict(hand=[
    ("5 10\n4 8 1 3 5\n", "3"),
    ("1 5\n6\n", "0"),
    ("1 6\n6\n", "1"),
    ("3 3000000000\n1000000000 1000000000 1000000000\n", "3"),
    ("4 5\n2 2 2 2\n", "2"),
    ("3 1\n1 1 1\n", "1"),
], ref=ref_10a, brute=brute_10a, small=small_10a, big=big_10a)


# ------------------------------------------------------------------ 10b
def parse_pairs(s):
    t = list(map(int, tok(s))); n = t[0]
    return [(t[1 + 2 * i], t[2 + 2 * i]) for i in range(n)]


def ref_10b(s):
    iv = sorted(parse_pairs(s), key=lambda x: x[1])
    cnt = 0; last = None
    for l, r in iv:
        if last is None or l > last:
            cnt += 1; last = r
    return str(cnt)


def brute_10b(s):
    iv = parse_pairs(s)
    cands = sorted({r for _, r in iv})  # 오른쪽 끝점만 후보로 충분하다
    for k in range(1, len(cands) + 1):
        for pts in itertools.combinations(cands, k):
            if all(any(l <= p <= r for p in pts) for l, r in iv):
                return str(k)


def small_10b(r):
    n = r.randint(1, 6)
    rows = []
    for _ in range(n):
        l = r.randint(-5, 8); rows.append(f"{l} {r.randint(l, 9)}")
    return lines(str(n), *rows)


def gen_10b(r, n, v, maxlen):
    rows = []
    for _ in range(n):
        l = r.randint(-v, v); rows.append(f"{l} {min(v, l + r.randint(0, maxlen))}")
    return lines(str(n), *rows)


def big_10b(r):
    n = 200000
    yield gen_10b(r, n, 10**9, 10**5)
    yield gen_10b(r, n, 10**9, 10**9)
    yield gen_10b(r, n, 1000, 3)
    yield lines(str(n), *(f"{i} {i + 1}" for i in range(n)))


P["10b"] = dict(hand=[
    ("3\n1 4\n2 6\n5 8\n", "2"),
    ("1\n5 5\n", "1"),
    ("3\n1 2\n3 4\n5 6\n", "3"),
    ("3\n1 10\n2 3\n4 5\n", "2"),
    ("4\n1 5\n5 9\n9 12\n5 5\n", "2"),
    ("2\n-1000000000 1000000000\n-1000000000 -1000000000\n", "1"),
    ("4\n1 3\n1 3\n1 3\n1 3\n", "1"),
], ref=ref_10b, brute=brute_10b, small=small_10b, big=big_10b)


# ------------------------------------------------------------------ 11a
def ref_11a(s):
    t = list(map(int, tok(s))); n, m = t[0], t[1]; broken = set(t[2:2 + m])
    f = [0] * (n + 1); f[0] = 1
    for i in range(1, n + 1):
        if i in broken:
            continue
        f[i] = (f[i - 1] + (f[i - 2] if i >= 2 else 0) + (f[i - 3] if i >= 3 else 0)) % MOD
    return str(f[n])


def brute_11a(s):
    t = list(map(int, tok(s))); n, m = t[0], t[1]; broken = set(t[2:2 + m])

    def go(pos):
        if pos == n:
            return 1
        return sum(go(pos + d) for d in (1, 2, 3) if pos + d <= n and pos + d not in broken)
    return str(go(0) % MOD)


def small_11a(r):
    n = r.randint(1, 12)
    b = r.sample(range(1, n), r.randint(0, min(n - 1, 4))) if n > 1 else []
    return lines(f"{n} {len(b)}", nums(b)) if b else f"{n} 0\n"


def big_11a(r):
    n = 10**6
    yield f"{n} 0\n"
    b = r.sample(range(1, n), 1000)
    yield lines(f"{n} {len(b)}", nums(b))
    yield "40 0\n"
    b = [i for i in range(1, n) if i % 3 != 0]  # 3의 배수 칸만 남는다 -> 경로 1개
    yield lines(f"{n - 1} {len([x for x in b if x < n - 1])}", nums(x for x in b if x < n - 1))
    b = r.sample(range(1, 1000), 400)
    yield lines(f"1000 {len(b)}", nums(b))


P["11a"] = dict(hand=[
    ("4 0\n", "7"),
    ("1 0\n", "1"),
    ("4 1\n2\n", "3"),
    ("5 3\n2 3 4\n", "0"),
    ("3 2\n1 2\n", "1"),
    ("2 1\n1\n", "1"),
    ("6 2\n1 4\n", "5"),
], ref=ref_11a, brute=brute_11a, small=small_11a, big=big_11a)


# ------------------------------------------------------------------ 11b
def parse_int_grid(s):
    t = list(map(int, tok(s))); h, w = t[0], t[1]
    return h, w, [t[2 + i * w: 2 + (i + 1) * w] for i in range(h)]


def ref_11b(s):
    h, w, g = parse_int_grid(s)
    dp = [[0] * w for _ in range(h)]
    for i in range(h):
        for j in range(w):
            if i == 0 and j == 0:
                best = 0
            elif i == 0:
                best = dp[i][j - 1]
            elif j == 0:
                best = dp[i - 1][j]
            else:
                best = max(dp[i - 1][j], dp[i][j - 1])
            dp[i][j] = best + g[i][j]
    return str(dp[h - 1][w - 1])


def brute_11b(s):
    h, w, g = parse_int_grid(s)

    def go(i, j):
        if i == h - 1 and j == w - 1:
            return g[i][j]
        opts = []
        if i + 1 < h:
            opts.append(go(i + 1, j))
        if j + 1 < w:
            opts.append(go(i, j + 1))
        return g[i][j] + max(opts)
    return str(go(0, 0))


def gen_11b(r, h, w, lo, hi):
    return lines(f"{h} {w}", *(nums(r.randint(lo, hi) for _ in range(w)) for _ in range(h)))


def small_11b(r):
    return gen_11b(r, r.randint(1, 5), r.randint(1, 5), -9, 9)


def big_11b(r):
    yield gen_11b(r, 300, 300, 10**9, 10**9)
    yield gen_11b(r, 300, 300, -10**9, -10**9)
    yield gen_11b(r, 300, 300, -10**9, 10**9)
    yield gen_11b(r, 1, 300, -1000, 1000)
    yield gen_11b(r, 300, 1, -1000, 1000)


P["11b"] = dict(hand=[
    ("2 3\n1 2 3\n4 5 6\n", "16"),
    ("1 1\n-5\n", "-5"),
    ("1 4\n1 -2 3 -4\n", "-2"),
    ("3 1\n1\n2\n3\n", "6"),
    ("2 2\n-1 -2\n-3 -4\n", "-7"),
    ("3 3\n1 2 1\n1 1 1\n100 1 1\n", "104"),
    ("2 2\n1000000000 1000000000\n1000000000 1000000000\n", "3000000000"),
], ref=ref_11b, brute=brute_11b, small=small_11b, big=big_11b)


# ------------------------------------------------------------------ e1a
def ref_e1a(s):
    w = tok(s)[0]
    return "".join(f"{ch}{len(list(grp))}" for ch, grp in itertools.groupby(w))


def brute_e1a(s):
    w = tok(s)[0]
    out = ""; i = 0
    while i < len(w):
        j = i
        while j < len(w) and w[j] == w[i]:
            j += 1
        out += w[i] + str(j - i)
        i = j
    return out


def small_e1a(r):
    return "".join(r.choice("ab") for _ in range(r.randint(1, 10))) + "\n"


def big_e1a(r):
    yield "a" * 100000 + "\n"
    yield "".join(r.choice("ab") for _ in range(100000)) + "\n"
    yield "".join(chr(97 + i % 26) for i in range(100000)) + "\n"
    yield "".join(r.choice("xyz") * r.randint(1, 30) for _ in range(5000)) + "\n"


P["e1a"] = dict(hand=[
    ("aaabbc\n", "a3b2c1"),
    ("a\n", "a1"),
    ("abc\n", "a1b1c1"),
    ("zzzzzzzzzzzz\n", "z12"),
    ("aabaa\n", "a2b1a2"),
], ref=ref_e1a, brute=brute_e1a, small=small_e1a, big=big_e1a)


# ------------------------------------------------------------------ e1b
def parse_e1b(s):
    t = tok(s); n = int(t[0]); rows = []
    for i in range(n):
        name, hms = t[1 + 2 * i], t[2 + 2 * i]
        hh, mm, ss = hms.split(":")
        rows.append((int(hh) * 3600 + int(mm) * 60 + int(ss), name))
    return rows


def ref_e1b(s):
    rows = sorted(parse_e1b(s))
    return "\n".join(f"{name} {sec - rows[0][0]}" for sec, name in rows)


def brute_e1b(s):
    rows = parse_e1b(s); out = []
    first = min(sec for sec, _ in rows)
    while rows:
        best = rows[0]
        for x in rows:
            if x[0] < best[0] or (x[0] == best[0] and x[1] < best[1]):
                best = x
        rows.remove(best)
        out.append(f"{best[1]} {best[0] - first}")
    return "\n".join(out)


def hms(sec):
    return f"{sec // 3600:02d}:{sec // 60 % 60:02d}:{sec % 60:02d}"


def small_e1b(r):
    n = r.randint(1, 6)
    ids = r.sample(range(30), n)
    return lines(str(n), *(f"{name_of(i)} {hms(r.choice([0, 59, 60, 3599, 3600, 3661]))}" for i in ids))


def big_e1b(r):
    n = 100000
    ids = r.sample(range(10**6), n)
    yield lines(str(n), *(f"{name_of(i)} {hms(r.randint(0, 359999))}" for i in ids))
    ids = r.sample(range(10**6), n)
    yield lines(str(n), *(f"{name_of(i)} {hms(r.randint(7200, 7300))}" for i in ids))


P["e1b"] = dict(hand=[
    ("3\nkim 01:00:00\nlee 00:59:59\npark 01:00:01\n", "lee 0\nkim 1\npark 2"),
    ("1\nsolo 99:59:59\n", "solo 0"),
    ("3\nb 00:10:00\na 00:10:00\nc 00:09:00\n", "c 0\na 60\nb 60"),
    ("2\nx 10:00:00\ny 00:00:00\n", "y 0\nx 36000"),
    ("2\nab 02:03:04\naa 02:03:04\n", "aa 0\nab 0"),
], ref=ref_e1b, brute=brute_e1b, small=small_e1b, big=big_e1b)


# ------------------------------------------------------------------ e1c
def ref_e1c(s):
    t = tok(s); n = int(t[0]); inside = set()
    for i in range(n):
        name, act = t[1 + 2 * i], t[2 + 2 * i]
        if act == "in":
            inside.add(name)
        else:
            inside.discard(name)
    return "\n".join([str(len(inside))] + sorted(inside))


def brute_e1c(s):
    t = tok(s); n = int(t[0]); last = {}
    for i in range(n):
        last[t[1 + 2 * i]] = t[2 + 2 * i]  # 유효한 기록이므로 마지막 기록만 보면 된다
    names = sorted(k for k, v in last.items() if v == "in")
    return "\n".join([str(len(names))] + names)


def gen_e1c(r, n, pool):
    inside = set(); rows = []
    for _ in range(n):
        name = r.choice(pool)
        if name in inside:
            inside.remove(name); rows.append(f"{name} out")
        else:
            inside.add(name); rows.append(f"{name} in")
    return lines(str(n), *rows)


def small_e1c(r):
    return gen_e1c(r, r.randint(1, 10), ["a", "b", "ab", "c"])


def big_e1c(r):
    n = 200000
    yield gen_e1c(r, n, [name_of(i) for i in r.sample(range(10**6), 50000)])
    yield gen_e1c(r, n, [name_of(i) for i in r.sample(range(10**6), 300)])
    ids = r.sample(range(10**7), n)
    yield lines(str(n), *(f"{name_of(i)} in" for i in ids))
    ids = r.sample(range(10**7), n // 2)
    yield lines(str(n), *([f"{name_of(i)} in" for i in ids] + [f"{name_of(i)} out" for i in ids]))


P["e1c"] = dict(hand=[
    ("5\nkim in\nlee in\nkim out\npark in\nkim in\n", "3\nkim\nlee\npark"),
    ("2\na in\na out\n", "0"),
    ("1\nzed in\n", "1\nzed"),
    ("6\nb in\na in\nb out\nb in\nb out\na out\n", "0"),
    ("4\nd in\nc in\nb in\na in\n", "4\na\nb\nc\nd"),
], ref=ref_e1c, brute=brute_e1c, small=small_e1c, big=big_e1c)


# ------------------------------------------------------------------ e1d
def ref_e1d(s):
    t = list(map(int, tok(s))); n, m = t[0], t[1]; a = t[2:]
    seen = Counter({0: 1}); pre = 0; total = 0
    for x in a:
        pre = (pre + x) % m
        total += seen[pre]
        seen[pre] += 1
    return str(total)


def brute_e1d(s):
    t = list(map(int, tok(s))); n, m = t[0], t[1]; a = t[2:]
    return str(sum(1 for i in range(n) for j in range(i, n) if sum(a[i:j + 1]) % m == 0))


def small_e1d(r):
    n = r.randint(1, 8)
    return lines(f"{n} {r.randint(1, 5)}", nums(r.randint(0, 9) for _ in range(n)))


def big_e1d(r):
    n = 200000
    yield lines(f"{n} 1000000000", nums([0] * n))
    yield lines(f"{n} 1000", nums(r.randint(0, 10**9) for _ in range(n)))
    yield lines(f"{n} 999999937", nums(r.randint(0, 10**9) for _ in range(n)))
    yield lines(f"{n} 3", nums([10**9] * n))
    yield lines(f"{n} 1", nums(r.randint(0, 10**9) for _ in range(n)))


P["e1d"] = dict(hand=[
    ("5 3\n1 2 3 4 5\n", "7"),
    ("1 5\n5\n", "1"),
    ("1 5\n4\n", "0"),
    ("3 1\n7 8 9\n", "6"),
    ("4 2\n0 0 0 0\n", "10"),
    ("3 1000000000\n1000000000 1000000000 1000000000\n", "6"),
    ("3 7\n1 2 3\n", "0"),
], ref=ref_e1d, brute=brute_e1d, small=small_e1d, big=big_e1d)


# ------------------------------------------------------------------ e2a
def parse_e2a(s):
    t = list(map(int, tok(s))); n, m = t[0], t[1]
    return t[2:2 + n], t[2 + n:2 + n + m]


def ref_e2a(s):
    need, have = parse_e2a(s)
    need.sort(); have.sort()
    i = 0
    for x in have:
        if i < len(need) and x >= need[i]:
            i += 1
    return str(i)


def brute_e2a(s):
    need, have = parse_e2a(s)

    def go(i, used):  # i번째 사람부터 배정, used는 쓴 우산 비트마스크
        if i == len(need):
            return 0
        best = go(i + 1, used)
        for j, x in enumerate(have):
            if not used >> j & 1 and x >= need[i]:
                best = max(best, 1 + go(i + 1, used | 1 << j))
        return best
    return str(go(0, 0))


def small_e2a(r):
    n, m = r.randint(1, 5), r.randint(1, 5)
    return lines(f"{n} {m}", nums(r.randint(1, 8) for _ in range(n)), nums(r.randint(1, 8) for _ in range(m)))


def big_e2a(r):
    n = 200000
    yield lines(f"{n} {n}", nums(r.randint(1, 10**9) for _ in range(n)), nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} {n}", nums(range(n, 0, -1)), nums(range(1, n + 1)))
    yield lines(f"{n} 1000", nums(r.randint(1, 100) for _ in range(n)), nums(r.randint(1, 100) for _ in range(1000)))
    yield lines(f"{n} {n}", nums([10**9] * n), nums([10**9 - 1] * n))


P["e2a"] = dict(hand=[
    ("3 3\n5 7 9\n6 8 4\n", "2"),
    ("1 1\n5\n5\n", "1"),
    ("1 1\n5\n4\n", "0"),
    ("3 1\n1 2 3\n10\n", "1"),
    ("2 4\n10 10\n1 2 3 10\n", "1"),
    ("3 3\n1 1 1\n1 1 1\n", "3"),
    ("3 3\n3 2 1\n2 2 2\n", "2"),
], ref=ref_e2a, brute=brute_e2a, small=small_e2a, big=big_e2a)


# ------------------------------------------------------------------ e2b
def ref_e2b(s):
    a = list(map(int, tok(s)))[1:]
    prev2, prev1 = 0, a[0]          # prev2: 강가(0), prev1: 1번 돌
    for i in range(1, len(a)):
        prev2, prev1 = prev1, max(prev1, prev2) + a[i]
    return str(prev1)


def brute_e2b(s):
    a = list(map(int, tok(s)))[1:]; n = len(a)

    def go(pos):  # pos: 현재 돌 번호(1-indexed), 0은 강가
        if pos == n:
            return 0
        opts = [a[pos] + go(pos + 1)]
        if pos + 2 <= n:
            opts.append(a[pos + 1] + go(pos + 2))
        return max(opts)
    return str(go(0))


def small_e2b(r):
    n = r.randint(1, 10)
    return lines(str(n), nums(r.randint(-9, 9) for _ in range(n)))


def big_e2b(r):
    n = 200000
    yield lines(str(n), nums([10**9] * n))
    yield lines(str(n), nums([-10**9] * n))
    yield lines(str(n), nums(r.randint(-10**9, 10**9) for _ in range(n)))
    yield lines(str(n - 1), nums([-10**9] * (n - 1)))


P["e2b"] = dict(hand=[
    ("5\n3 -5 2 -1 4\n", "9"),
    ("1\n-7\n", "-7"),
    ("2\n-3 5\n", "5"),
    ("2\n3 5\n", "8"),
    ("3\n-1 -2 -3\n", "-4"),
    ("4\n1000000000 1000000000 1000000000 1000000000\n", "4000000000"),
    ("4\n-1 -1 -1 -1\n", "-2"),
], ref=ref_e2b, brute=brute_e2b, small=small_e2b, big=big_e2b)


# ------------------------------------------------------------------ e2c
def ref_e2c(s):
    t = list(map(int, tok(s))); n, k = t[0], t[1]; a = t[2:]
    lo, hi = 1, min(a) * k
    while lo < hi:
        mid = (lo + hi) // 2
        if sum(mid // x for x in a) >= k:
            hi = mid
        else:
            lo = mid + 1
    return str(lo)


def brute_e2c(s):
    t = list(map(int, tok(s))); n, k = t[0], t[1]; a = t[2:]
    if n == 1:  # 복사기가 한 대면 답은 자명하다(1초씩 늘리는 탐색은 너무 느리다)
        return str(a[0] * k)
    T = 1
    while sum(T // x for x in a) < k:
        T += 1
    return str(T)


def small_e2c(r):
    n = r.randint(1, 5)
    return lines(f"{n} {r.randint(1, 20)}", nums(r.randint(1, 9) for _ in range(n)))


def big_e2c(r):
    n = 100000
    yield lines(f"{n} 1000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000", nums([10**9] * n))
    yield lines(f"{n} 1000000000", nums(r.randint(1, 10) for _ in range(n)))
    yield lines(f"{n} 1", nums(r.randint(5, 10**9) for _ in range(n)))
    yield lines(f"{n} 999999999", nums([1] + [10**9] * (n - 1)))


P["e2c"] = dict(hand=[
    ("2 5\n2 3\n", "6"),
    ("1 1\n7\n", "7"),
    ("1 1000000000\n1000000000\n", "1000000000000000000"),
    ("3 1\n5 3 9\n", "3"),
    ("2 3\n1 100\n", "3"),
    ("3 10\n2 2 2\n", "8"),
    ("2 4\n3 5\n", "9"),
], ref=ref_e2c, brute=brute_e2c, small=small_e2c, big=big_e2c)


# ------------------------------------------------------------------ e2d
def ref_e2d(s):
    h, w, g = parse_grid(s)
    dist = [[-1] * w for _ in range(h)]
    dq = deque()
    for r in range(h):
        for c in range(w):
            if g[r][c] == "F":
                dist[r][c] = 0; dq.append((r, c))
    last = 0
    while dq:
        r, c = dq.popleft()
        last = dist[r][c]
        for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
            if 0 <= nr < h and 0 <= nc < w and g[nr][nc] == "." and dist[nr][nc] < 0:
                dist[nr][nc] = dist[r][c] + 1
                dq.append((nr, nc))
    for r in range(h):
        for c in range(w):
            if g[r][c] == "." and dist[r][c] < 0:
                return "-1"
    return str(last)


def brute_e2d(s):  # 1분씩 시뮬레이션
    h, w, g = parse_grid(s)
    g = [list(x) for x in g]
    minutes = 0
    while True:
        new = []
        for r in range(h):
            for c in range(w):
                if g[r][c] == "." and any(
                        0 <= nr < h and 0 <= nc < w and g[nr][nc] == "F"
                        for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1))):
                    new.append((r, c))
        if not new:
            break
        for r, c in new:
            g[r][c] = "F"
        minutes += 1
    return "-1" if any("." in row for row in g) else str(minutes)


def gen_e2d(r, h, w, pwall, fires):
    g = [list(x) for x in rand_grid(r, h, w, pwall)]
    for pos in r.sample(range(h * w), fires):
        g[pos // w][pos % w] = "F"
    return lines(f"{h} {w}", *("".join(x) for x in g))


def small_e2d(r):
    h, w = r.randint(1, 5), r.randint(1, 5)
    return gen_e2d(r, h, w, r.choice([0.0, 0.2, 0.35]), r.randint(1, min(3, h * w)))


def big_e2d(r):
    n = 1000
    g = [["."] * n for _ in range(n)]; g[0][0] = "F"
    yield lines(f"{n} {n}", *("".join(x) for x in g))
    yield gen_e2d(r, n, n, 0.0, 50)
    yield gen_e2d(r, n, n, 0.25, 2000)
    rows = [["." if ch == "#" else "#" for ch in row] for row in snake(n, n)]
    rows[0][0] = "F"
    yield lines(f"{n} {n}", *("".join(x) for x in rows))
    g = [["."] * n for _ in range(n)]
    for i in range(n):
        g[i][500] = "#"
    g[0][500] = "."; g[999][0] = "F"
    yield lines(f"{n} {n}", *("".join(x) for x in g))


P["e2d"] = dict(hand=[
    ("3 4\nF...\n.#..\n...F\n", "2"),
    ("1 1\nF\n", "0"),
    ("1 3\nF#.\n", "-1"),
    ("1 5\nF....\n", "4"),
    ("1 5\n..F..\n", "2"),
    ("2 2\nF#\n#F\n", "0"),
    ("3 3\n...\n.F.\n...\n", "2"),
    ("3 3\nF#.\n##.\n...\n", "-1"),
], ref=ref_e2d, brute=brute_e2d, small=small_e2d, big=big_e2d)


# ------------------------------------------------------------------ 큰 입력(용량 절약판)
# 원칙: (1) 시간초과 유도용은 "N 최대 + 자릿수 작은 값", (2) 오버플로 유도용은 "작은 N + 큰 값".
# 위쪽의 big_* 정의 대신 아래 정의를 사용한다.
BIG = {}


def big(pid):
    def deco(fn):
        BIG[pid] = fn
        return fn
    return deco


@big("01a")
def _(r):
    n = 200000
    yield lines(str(n), nums(r.randint(0, 100) for _ in range(n)))
    yield lines(str(n), nums([100] * n))


@big("01b")
def _(r):
    n = 200000
    yield lines("1000 1000", "".join(r.choice("LRFFFF") for _ in range(n)))
    yield lines("5 5", "".join(r.choice("LRFFF") for _ in range(n)))
    yield lines("1 1000", "F" * n)


@big("02a")
def _(r):
    yield lines("200000", nums(range(200000, 0, -1)))
    yield lines("20000", nums(r.randint(-10**9, 10**9) for _ in range(20000)))
    yield lines("20000", nums(r.randint(-50, 50) for _ in range(20000)))


@big("02b")
def _(r):
    n = 100000
    ids = r.sample(range(400000), n)
    yield lines(str(n), *(f"{name_of(i)} {r.randint(0, 20)} {r.randint(0, 99)}" for i in ids))
    ids = r.sample(range(10**6), 5000)
    yield lines("5000", *(f"{name_of(i)} {r.randint(0, 3)} {r.randint(0, 10**9)}" for i in ids))


@big("03a")
def _(r):
    n = 2000
    yield lines(f"{n} 7", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000", nums([10**9] * n))
    yield lines(f"{n} 999999999", nums(r.choice([10**9 - 1, 999999998, 1, 10**9]) for _ in range(n)))


BIG["03b"] = big_03b


@big("04a")
def _(r):
    n = 200000
    pool = [name_of(i) for i in r.sample(range(18000), 1000)]
    yield lines(str(n), *(r.choice(pool) for _ in range(n)))
    ids = r.sample(range(450000), n)
    yield lines(str(n), *(name_of(i) for i in ids))
    yield lines("2000", *(["zzzzzzzzzz"] * 1000 + ["zzzzzzzzzy"] * 1000))


@big("04b")
def _(r):
    n = 200000
    yield lines(f"{n} 10", nums([5] * n))
    yield lines(f"{n} 100", nums(r.randint(-100, 200) for _ in range(n)))
    yield lines("20000 2000000000", nums(r.choice([10**9, 10**9 - 1, 1]) for _ in range(20000)))
    yield lines("20000 -7", nums(r.randint(-10**9, 10**9) for _ in range(20000)))


@big("05a")
def _(r):
    yield gen_05a(r, 200000, 200000, 1, 9, wide=True)
    yield gen_05a(r, 20000, 20000, 10**9, 10**9, wide=True)
    yield gen_05a(r, 20000, 20000, -10**9, 10**9)


@big("05b")
def _(r):
    n = 200000
    yield lines(f"{n} 0", nums([0] * n))
    yield lines(f"{n} 0", nums(r.randint(-3, 3) for _ in range(n)))
    yield lines("20000 10000000000000", nums([10**9] * 20000))
    yield lines(f"{n} 5", nums(r.randint(0, 2) for _ in range(n)))


BIG["06a"] = big_06a


@big("06b")
def _(r):
    yield lines("200000", nums(r.randint(1, 9) for _ in range(200000)))
    yield lines("20000", nums([10**9] * 20000))
    yield lines("20000", nums(r.randint(1, 10**9) for _ in range(20000)))


@big("07a")
def _(r):
    yield gen_07a(r, 100000, 100000, 50)
    yield lines("100000 100000", nums([7] * 100000), *(["7 7", "-9 9", "8 9", "6 6"] * 25000))
    yield gen_07a(r, 10000, 10000, 10**9)


@big("07b")
def _(r):
    yield lines("100000 1000000000", nums(r.randint(1, 10**9) for _ in range(100000)))
    n = 10000
    yield lines(f"{n} 1000000000", nums([10**9] * n))
    yield lines(f"{n} 77777", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000", nums(r.randint(1, 5000) for _ in range(n)))
    yield lines(f"{n} 1", nums(r.randint(1, 10**9) for _ in range(n)))


@big("08a")
def _(r):
    n = 200000
    yield lines(f"{n} 1", nums(range(0, 4 * n, 4)))
    yield lines(f"{n} 399998", nums(range(-n, n, 2)))
    yield lines("20000 123456789", nums(sorted(r.randint(-10**9, 10**9) for _ in range(20000))))
    yield lines("20000 1999999999", nums(sorted(r.randint(-10**9, 10**9) for _ in range(20000))))
    yield lines("1000 -2000000000", nums([10**9] * 1000))


@big("08b")
def _(r):
    n = 200000
    yield lines(f"{n} {n}", nums([1] * n))
    yield lines(f"{n} 100001", nums([1] * (n - 1) + [100000]))
    yield lines(f"{n} 400000", nums(r.randint(1, 9) for _ in range(n)))
    yield lines("20000 10000000000000", nums([10**9] * 20000))
    yield lines("20000 50000000000", nums(r.randint(1, 10**9) for _ in range(20000)))
    yield lines("20000 1000000000000000", nums(r.randint(1, 10**9) for _ in range(20000)))


BIG["09a"] = big_09a


@big("09b")
def _(r):
    n = 500
    g = [["."] * n for _ in range(n)]
    g[0][0] = "S"; g[n - 1][n - 1] = "E"
    yield lines(f"{n} {n}", *("".join(x) for x in g))
    yield lines(f"{n} {n}", *place_se(r, rand_grid(r, n, n, 0.3)))
    rows = [["." if ch == "#" else "#" for ch in row] for row in snake(n, n)]  # 길이 뱀 모양
    rows[0][0] = "S"
    last = max(c for c in range(n) if rows[n - 2][c] == ".")
    rows[n - 2][last if last != 0 else 0] = "E"
    yield lines(f"{n} {n}", *("".join(x) for x in rows))
    yield lines(f"{n} {n}", *place_se(r, rand_grid(r, n, n, 0.45)))
    yield lines(f"{n} {n}", *place_se(r, rand_grid(r, n, n, 0.2)))


@big("10a")
def _(r):
    n = 200000
    yield lines(f"{n} 50000000", nums(r.randint(1, 1000) for _ in range(n)))
    yield lines("20000 10000000000000", nums([10**9] * 20000))
    yield lines("20000 3000000000", nums(r.randint(1, 10**9) for _ in range(20000)))
    yield lines("20000 1000000000000000", nums(r.randint(1, 10**9) for _ in range(20000)))


@big("10b")
def _(r):
    yield gen_10b(r, 200000, 1000, 3)
    yield gen_10b(r, 20000, 10**9, 10**5)
    yield gen_10b(r, 20000, 10**9, 10**9)
    yield lines("20000", *(f"{i} {i + 1}" for i in range(20000)))


@big("11a")
def _(r):
    n = 10**6
    yield f"{n} 0\n"
    b = r.sample(range(1, n), 1000)
    yield lines(f"{n} {len(b)}", nums(b))
    yield "40 0\n"
    b = [i for i in range(1, 30000) if i % 3 != 0]   # 3의 배수 칸만 남는다 -> 경로 1개
    yield lines(f"30000 {len(b)}", nums(b))
    b = r.sample(range(1, 1000), 400)
    yield lines(f"1000 {len(b)}", nums(b))


@big("11b")
def _(r):
    yield gen_11b(r, 300, 300, 10**9, 10**9)
    yield gen_11b(r, 100, 100, -10**9, -10**9)
    yield gen_11b(r, 300, 300, -999, 999)
    yield gen_11b(r, 100, 100, -10**9, 10**9)
    yield gen_11b(r, 1, 300, -1000, 1000)
    yield gen_11b(r, 300, 1, -1000, 1000)


BIG["e1a"] = big_e1a


@big("e1b")
def _(r):
    n = 100000
    ids = r.sample(range(400000), n)
    yield lines(str(n), *(f"{name_of(i)} {hms(r.randint(7200, 7300))}" for i in ids))
    ids = r.sample(range(10**6), 5000)
    yield lines("5000", *(f"{name_of(i)} {hms(r.randint(0, 359999))}" for i in ids))


@big("e1c")
def _(r):
    n = 100000
    yield gen_e1c(r, n, [name_of(i) for i in r.sample(range(18000), 300)])
    yield gen_e1c(r, n, [name_of(i) for i in r.sample(range(450000), 30000)])
    ids = r.sample(range(450000), n // 2)
    yield lines(str(n), *([f"{name_of(i)} in" for i in ids] + [f"{name_of(i)} out" for i in ids]))
    ids = r.sample(range(450000), 20000)
    yield lines("20000", *(f"{name_of(i)} in" for i in ids))


@big("e1d")
def _(r):
    n = 200000
    yield lines(f"{n} 1000000000", nums([0] * n))
    yield lines(f"{n} 7", nums(r.randint(0, 9) for _ in range(n)))
    yield lines("20000 999999937", nums(r.randint(0, 10**9) for _ in range(20000)))
    yield lines("20000 3", nums([10**9] * 20000))
    yield lines("20000 1", nums(r.randint(0, 10**9) for _ in range(20000)))


@big("e2a")
def _(r):
    n = 200000
    yield lines(f"{n} {n}", nums(r.randint(1, 999) for _ in range(n)), nums(r.randint(1, 999) for _ in range(n)))
    n = 20000
    yield lines(f"{n} {n}", nums(r.randint(1, 10**9) for _ in range(n)), nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} {n}", nums(range(n, 0, -1)), nums(range(1, n + 1)))
    yield lines(f"{n} 1000", nums(r.randint(1, 100) for _ in range(n)), nums(r.randint(1, 100) for _ in range(1000)))
    yield lines("2000 2000", nums([10**9] * 2000), nums([10**9 - 1] * 2000))


@big("e2b")
def _(r):
    yield lines("200000", nums(r.randint(-9, 9) for _ in range(200000)))
    n = 20000
    yield lines(str(n), nums([10**9] * n))
    yield lines(str(n), nums([-10**9] * n))
    yield lines(str(n), nums(r.randint(-10**9, 10**9) for _ in range(n)))
    yield lines(str(n - 1), nums([-10**9] * (n - 1)))


@big("e2c")
def _(r):
    yield lines("100000 1000000000", nums(r.randint(1, 10) for _ in range(100000)))
    n = 10000
    yield lines(f"{n} 1000000000", nums(r.randint(1, 10**9) for _ in range(n)))
    yield lines(f"{n} 1000000000", nums([10**9] * n))
    yield lines(f"{n} 1", nums(r.randint(5, 10**9) for _ in range(n)))
    yield lines(f"{n} 999999999", nums([1] + [10**9] * (n - 1)))


@big("e2d")
def _(r):
    n = 500
    g = [["."] * n for _ in range(n)]; g[0][0] = "F"
    yield lines(f"{n} {n}", *("".join(x) for x in g))
    yield gen_e2d(r, n, n, 0.0, 20)
    yield gen_e2d(r, n, n, 0.25, 500)
    rows = [["." if ch == "#" else "#" for ch in row] for row in snake(n, n)]
    rows[0][0] = "F"
    yield lines(f"{n} {n}", *("".join(x) for x in rows))
    g = [["."] * n for _ in range(n)]
    for i in range(n):
        g[i][250] = "#"
    g[0][250] = "."; g[n - 1][0] = "F"
    yield lines(f"{n} {n}", *("".join(x) for x in g))


for _pid, _fn in BIG.items():
    P[_pid]["big"] = _fn


# ------------------------------------------------------------------ driver
CROSS_CHECKS = 300


def build(pid, slug):
    spec = P[pid]
    rng = random.Random(f"course-{pid}")
    for i, (inp, exp) in enumerate(spec["hand"], 1):
        got = spec["ref"](inp)
        assert got.split() == exp.split(), f"{pid} 손계산 테스트 {i}: 참조 구현 {got!r} != 예상 {exp!r}"
        got = spec["brute"](inp)
        assert got.split() == exp.split(), f"{pid} 손계산 테스트 {i}: 완전탐색 {got!r} != 예상 {exp!r}"
    small_cases = []
    for _ in range(CROSS_CHECKS):
        inp = spec["small"](rng)
        a, b = spec["ref"](inp), spec["brute"](inp)
        assert a.split() == b.split(), f"{pid} 대조 실패\n입력:\n{inp}\nref={a!r}\nbrute={b!r}"
        small_cases.append((inp, a))
    cases = list(spec["hand"])
    cases += small_cases[:3]                       # 무작위 작은 입력 3개(완전탐색과 일치 확인됨)
    cases += [(inp, spec["ref"](inp)) for inp in spec["big"](rng)]

    out_dir = ROOT / "tests" / slug
    out_dir.mkdir(parents=True, exist_ok=True)
    for old in list(out_dir.glob("*.in")) + list(out_dir.glob("*.out")):
        old.unlink()
    assert set(BIG) == set(P), "큰 입력 정의가 빠진 문제가 있습니다"
    for i, (inp, exp) in enumerate(cases, 1):
        (out_dir / f"{i:02d}.in").write_text(inp, encoding="utf-8")
        (out_dir / f"{i:02d}.out").write_text(exp.rstrip("\n") + "\n", encoding="utf-8")
    return len(spec["hand"]), len(cases)


def main():
    manifest = json.loads((ROOT / "manifest.json").read_text(encoding="utf-8"))
    wanted = set(sys.argv[1:])
    for p in manifest["problems"]:
        if wanted and p["id"] not in wanted:
            continue
        hand, total = build(p["id"], p["slug"])
        print(f"{p['id']}: 테스트 {total}개 (손계산 {hand}개, 대조 {CROSS_CHECKS}회 통과)")


if __name__ == "__main__":
    main()
