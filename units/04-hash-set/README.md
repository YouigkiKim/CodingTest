# 04 해시·집합

이전: [03 완전탐색](../03-brute-force/README.md) · 다음: [05 누적합](../05-prefix-sum/README.md) · [전체 목차](../../README.md) · [치트시트](../../docs/cheatsheet.md)

예상 소요: 2~3시간 · 문제: [04a 투표 집계](../../problems/04a-vote-count/problem.md), [04b 합이 T인 쌍](../../problems/04b-pair-sum-count/problem.md)

## 학습 목표

- `unordered_map`으로 빈도를 세고, `unordered_set`으로 존재 여부를 확인한다.
- `map`/`set`과 `unordered_` 계열의 차이를 알고 상황에 맞게 고른다.
- "앞에서 본 것을 기록해 두고 O(1)에 찾는다"는 패턴으로 O(N²)을 O(N)으로 줄인다.

## 선행 지식

[01단원](../01-array-string/README.md)의 빈도 배열, [03단원](../03-brute-force/README.md)의 모든 쌍 검사.

## 개념

빈도 배열은 값이 작은 정수일 때만 쓸 수 있다. 키가 문자열이거나 10^9까지의 큰 수라면
**키 → 값**을 저장하는 맵을 쓴다.

```cpp
#include <unordered_map>
#include <unordered_set>
unordered_map<string, int> freq;
freq["kim"]++;                       // 없으면 0으로 만들어진 뒤 +1
if (freq.count("lee")) { ... }       // 키가 있는가? (키를 만들지 않는다)
auto it = freq.find("lee");          // 없으면 freq.end()
for (const auto &e : freq) { e.first; e.second; }   // 전체 순회 (순서 없음)

unordered_set<int> seen;
seen.insert(5);
if (seen.count(5)) { ... }
seen.erase(5);
```

### 네 가지 컨테이너 비교

| 컨테이너 | 저장 | 삽입·조회·삭제 | 순회 순서 | 헤더 |
|---|---|---|---|---|
| `unordered_map<K,V>` | 키 → 값 | 평균 O(1) | 정해지지 않음 | `<unordered_map>` |
| `unordered_set<K>` | 키만 | 평균 O(1) | 정해지지 않음 | `<unordered_set>` |
| `map<K,V>` | 키 → 값 | O(log N) | 키 오름차순 | `<map>` |
| `set<K>` | 키만 | O(log N) | 오름차순 | `<set>` |

### 고르는 기준

- 빈도·존재 여부만 필요하다 → `unordered_map` / `unordered_set`
- 키 순서대로 출력해야 한다, 최소/최대 키가 필요하다, "x 이상인 첫 키"를 찾아야 한다 → `map` / `set`
- 키가 0~수십만의 작은 정수다 → 그냥 `vector`(빈도 배열)가 가장 빠르다
- 데이터가 한 번 주어지고 바뀌지 않는다 → 정렬된 `vector` + 이분탐색([07단원](../07-binary-search/README.md))도 좋다

### "기록해 두고 찾기" 패턴

"조건을 만족하는 **쌍**의 개수" 문제에서, 한쪽 원소 `x`를 고정하면 필요한 상대 값이 하나로 정해지는 경우가 많다.
왼쪽부터 보면서 지금까지 나온 값을 맵에 기록해 두면, 상대가 몇 개 있었는지 O(1)에 알 수 있다.

```cpp
for (long long x : a) {
    answer += (앞에서 나온 "필요한 값"의 개수);   // 먼저 센다
    seen[x]++;                                    // 그다음 자신을 등록한다
}
```

## 이런 문제에서 떠올린다

| 문제의 특징 | 떠올릴 것 |
|---|---|
| "이름/단어별 횟수", "가장 많이 등장한" | `unordered_map<string,int>` |
| "이미 나온 적 있는가", "중복 확인", "서로 다른 것의 수" | `unordered_set` |
| "두 개를 골라 합/차가 K" + N이 크다 | 기록해 두고 찾기 |
| "사전순으로 출력" + 삽입·삭제가 섞임 | `map` / `set` |
| O(N²) 풀이에서 안쪽 반복문이 "특정 값 찾기"다 | 해시로 안쪽 반복문 제거 |

## 작은 입력으로 따라가기

`a = [1, 5, 3, 3, 7]`, 합이 6인 쌍(i < j)의 개수

| x | 필요한 값 6-x | seen에서의 개수 | 누적 답 | seen (등록 후) |
|---|---|---|---|---|
| 1 | 5 | 0 | 0 | {1:1} |
| 5 | 1 | 1 | 1 | {1:1, 5:1} |
| 3 | 3 | 0 | 1 | {1:1, 5:1, 3:1} |
| 3 | 3 | 1 | 2 | {1:1, 5:1, 3:2} |
| 7 | -1 | 0 | 2 | {…, 7:1} |

세 번째 줄에서 3이 자기 자신과 짝지어지지 않은 것은 "먼저 세고 나중에 등록"했기 때문이다.

## 예제

| 예제 | 내용 | 실행 |
|---|---|---|
| [hash_basics.cpp](examples/hash_basics.cpp) | 빈도 세기, `[]`의 부작용, `count`/`find`, 중복 찾기 | `./ct example 04-hash_basics` |
| [ordered_vs_unordered.cpp](examples/ordered_vs_unordered.cpp) | `map`/`set`의 정렬 순회, 최소/최대, `lower_bound` | `./ct example 04-ordered_vs_unordered` |

## 복잡도

| | 시간 | 공간 |
|---|---|---|
| `unordered_map`에 N개 삽입·조회 | 평균 O(N) | O(N) |
| `map`에 N개 삽입·조회 | O(N log N) | O(N) |

"평균 O(1)"은 해시 충돌이 적다는 가정이다. 상수가 배열보다 훨씬 크므로(대략 수~수십 배),
키가 작은 정수면 배열을 쓰는 것이 낫다. 문자열 키는 해시 계산에 길이만큼의 시간이 든다.

## 자주 하는 실수와 반례

| 실수 | 반례 / 증상 |
|---|---|
| `if (m[key] > 0)`로 존재 확인 | 없는 키가 값 0으로 **생성**된다. 크기가 늘고, 순회 중이면 위험 → `count`/`find` |
| `unordered_map` 순회 순서에 의존 | 실행 환경에 따라 출력 순서가 달라져 오답 |
| 먼저 전부 등록하고 나서 쌍을 셈 | `[3]`, T=6 → 자기 자신과 짝지어 1로 셈 |
| 쌍의 개수를 `int`로 | 같은 값 20만 개 → 약 2×10^10 |
| `m.find(k)->second`를 확인 없이 사용 | 없는 키면 `end()`를 역참조 → 런타임 오류 |
| 순회하면서 같은 컨테이너에 삽입·삭제 | 반복자가 무효화된다 |
| `pair`를 `unordered_map`의 키로 사용 | 기본 해시가 없어 컴파일 오류 → `map`을 쓰거나 하나의 정수로 합친다 |

## 문제

1. [04a 투표 집계](../../problems/04a-vote-count/problem.md) (기본) - `./ct test 04a`
2. [04b 합이 T인 쌍](../../problems/04b-pair-sum-count/problem.md) (응용) - `./ct test 04b`

## 완료 체크리스트

- [ ] 네 컨테이너의 시간복잡도와 순회 순서를 표 없이 말할 수 있다.
- [ ] `m[key]`와 `m.count(key)`의 차이를 설명할 수 있다.
- [ ] "먼저 세고 나중에 등록"하는 이유를 예로 설명할 수 있다.
- [ ] 04a, 04b를 통과했다.
- [ ] 04b를 O(N²)으로 풀면 왜 안 되는지 숫자로 말할 수 있다.
