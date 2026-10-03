# 07 이분탐색

이전: [06 스택·큐·힙](../06-stack-queue-heap/README.md) · 다음: [08 투 포인터·슬라이딩 윈도우](../08-two-pointers/README.md) · [전체 목차](../../README.md) · [치트시트](../../docs/cheatsheet.md)

예상 소요: 3~4시간 · 문제: [07a 범위 안의 개수](../../problems/07a-count-in-range/problem.md), [07b 리본 자르기](../../problems/07b-ribbon-cut/problem.md)

## 학습 목표

- 정렬된 배열에서 이분탐색을 직접 구현하고, 무한 루프 없이 경계를 다룬다.
- `lower_bound`/`upper_bound`의 반환값을 정확히 해석한다.
- "답을 정해 놓고 가능한지 판정"하는 방식(매개변수 탐색)을 단조성과 함께 이해한다.

## 선행 지식

[02단원](../02-sorting/README.md): `sort`, `[begin, end)`.

## 개념

### 이분탐색

정렬된 배열에서 가운데 값과 비교해 **탐색 범위를 절반으로** 줄인다. 범위가 매번 반으로 줄어 O(log N).
N = 10억이어도 약 30번이면 끝난다.

```cpp
int lo = 0, hi = n - 1;                 // 닫힌 구간 [lo, hi]
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == target) return mid;
    if (a[mid] < target) lo = mid + 1;
    else hi = mid - 1;
}
return -1;
```

### lower_bound / upper_bound

정렬된 구간에서 **경계 위치**를 찾는다. 값이 없어도 "들어갈 자리"를 알려 준다.

| 함수 | 반환 | `1 3 3 3 7`에서 값 3 |
|---|---|---|
| `lower_bound(b, e, x)` | x **이상**인 첫 위치 | 인덱스 1 |
| `upper_bound(b, e, x)` | x **초과**인 첫 위치 | 인덱스 4 |

- 인덱스로 바꾸려면 `it - v.begin()`.
- 조건을 만족하는 원소가 없으면 `v.end()`를 반환한다(역참조 금지).
- `upper_bound - lower_bound` = x의 개수.
- x 이하인 가장 큰 값 = `upper_bound`의 바로 앞(단, `begin()`이 아닐 때).

### 답에 대한 이분탐색 (매개변수 탐색)

"조건을 만족하는 **최대/최소 값**을 구하라"는 문제에서, 답 X를 직접 구하기는 어려워도
"X로 **가능한가**?"는 쉽게 판정할 수 있는 경우가 있다. 그리고 판정 결과가

```
X :   1    2    3    4    5    6    7
가능? O    O    O    O    X    X    X      ← 한 번만 바뀐다 (단조)
```

처럼 한쪽은 전부 가능, 다른 쪽은 전부 불가능이라면 그 **경계**를 이분탐색으로 찾을 수 있다.

두 가지 형태를 구분해 외운다.

```cpp
// (A) 가능한 "최댓값" 찾기: O O O O X X X  에서 마지막 O
while (lo < hi) {
    long long mid = lo + (hi - lo + 1) / 2;   // 올림
    if (ok(mid)) lo = mid; else hi = mid - 1;
}
// (B) 가능한 "최솟값" 찾기: X X X O O O O  에서 첫 O
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;       // 내림
    if (ok(mid)) hi = mid; else lo = mid + 1;
}
```

`lo = mid`로 갱신하는 쪽은 올림, `hi = mid`로 갱신하는 쪽은 내림. 반대로 하면 `lo`와 `hi`가 1 차이일 때 범위가 줄지 않아 무한 루프에 빠진다.

## 이런 문제에서 떠올린다

| 문제의 특징 | 떠올릴 것 |
|---|---|
| 정렬된(또는 정렬해도 되는) 배열에서 값 찾기·개수 세기를 **여러 번** | `lower_bound` / `upper_bound` |
| "x 이상인 가장 작은 값", "x 이하인 가장 큰 값" | `lower_bound` / `upper_bound` |
| "~할 수 있는 최댓값/최솟값" + 답의 범위가 매우 큼(10^9, 10^18) | 답에 대한 이분탐색 |
| 판정은 쉬운데 최적값을 직접 계산하기 어렵다 | 판정 함수 + 단조성 확인 |

단조성 확인 질문: **"X에서 가능하면 X+1(또는 X-1)에서도 반드시 가능한가?"**

## 작은 입력으로 따라가기

**직접 구현**: `a = [1, 3, 3, 3, 7, 9, 12]`에서 7 찾기

| lo | hi | mid | a[mid] | 판단 |
|---|---|---|---|---|
| 0 | 6 | 3 | 3 | 3 < 7 → lo = 4 |
| 4 | 6 | 5 | 9 | 9 > 7 → hi = 4 |
| 4 | 4 | 4 | 7 | 찾음 |

**매개변수 탐색**: 리본 `10 7 5`에서 같은 길이 조각 4개 이상, 최대 길이 (형태 A)

| lo | hi | mid | 조각 수 | 판단 |
|---|---|---|---|---|
| 0 | 10 | 5 | 2+1+1=4 | 가능 → lo=5 |
| 5 | 10 | 8 | 1+0+0=1 | 불가능 → hi=7 |
| 5 | 7 | 6 | 1+1+0=2 | 불가능 → hi=5 |

lo = hi = 5.

## 예제

| 예제 | 내용 | 실행 |
|---|---|---|
| [binary_search.cpp](examples/binary_search.cpp) | 직접 구현 두 가지, `lower_bound`/`upper_bound`, 개수 세기 | `./ct example 07-binary_search` |
| [parametric_search.cpp](examples/parametric_search.cpp) | 판정 함수와 단조성, 최소 처리량 찾기 | `./ct example 07-parametric_search` |

## 복잡도

| | 시간 |
|---|---|
| 이분탐색 1회 | O(log N) |
| 정렬 + Q번 탐색 | O(N log N + Q log N) |
| 매개변수 탐색 | O(log(답의 범위) × 판정 1회 비용) |

판정이 O(N), 답의 범위가 10^9이면 약 30N. 범위가 10^18이어도 약 60N이다.
공간은 O(1) 추가(정렬된 배열 제외).

## 자주 하는 실수와 반례

| 실수 | 반례 / 증상 |
|---|---|
| 정렬하지 않고 이분탐색 | `[3, 1, 2]`에서 1을 못 찾음 |
| `lo = mid`인데 `mid`를 내림으로 계산 | `lo=3, hi=4` → mid=3 → 영원히 반복 |
| `mid = (lo + hi) / 2`에서 오버플로 | lo, hi가 10^18 근처일 때 → `lo + (hi - lo) / 2` |
| `lower_bound` 결과를 확인 없이 `*it` | 모든 원소보다 큰 값을 찾으면 `end()` |
| `upper_bound`와 `lower_bound` 혼동 | "x 이하의 개수"는 `upper_bound(x) - begin` |
| 판정 함수의 합을 `int`로 | 리본 10만 개 × 10^9 → 오버플로 |
| 탐색 범위에 0을 넣고 0으로 나눔 | 런타임 오류(SIGFPE) |
| 단조가 아닌 조건에 이분탐색 | 틀린 답. 먼저 단조성을 확인한다 |
| `set`에 `std::lower_bound(s.begin(), s.end(), x)` | O(N). `s.lower_bound(x)`를 쓴다 |

## 문제

1. [07a 범위 안의 개수](../../problems/07a-count-in-range/problem.md) (기본) - `./ct test 07a`
2. [07b 리본 자르기](../../problems/07b-ribbon-cut/problem.md) (응용) - `./ct test 07b`

## 완료 체크리스트

- [ ] `lower_bound`와 `upper_bound`의 정의를 "이상/초과"로 정확히 말할 수 있다.
- [ ] 형태 A(최댓값)와 형태 B(최솟값)의 반복문을 보지 않고 쓸 수 있다.
- [ ] 올림/내림을 잘못 고르면 무한 루프가 되는 이유를 `lo=3, hi=4`로 설명할 수 있다.
- [ ] 어떤 문제의 판정 결과가 단조인지 스스로 확인할 수 있다.
- [ ] 07a, 07b를 통과했다.
