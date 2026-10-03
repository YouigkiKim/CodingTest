# 02 정렬

이전: [01 배열·문자열·구현](../01-array-string/README.md) · 다음: [03 완전탐색](../03-brute-force/README.md) · [전체 목차](../../README.md) · [치트시트](../../docs/cheatsheet.md)

예상 소요: 2~3시간 · 문제: [02a 중복 없는 정렬](../../problems/02a-distinct-sorted/problem.md), [02b 대회 순위표](../../problems/02b-scoreboard/problem.md)

## 학습 목표

- `sort`로 오름차순·내림차순 정렬을 한다.
- `pair`와 구조체를 여러 기준으로 정렬하는 비교 함수(람다)를 작성한다.
- `sort` + `unique` + `erase`로 중복을 제거한다.
- "정렬하면 쉬워지는 문제"를 알아본다.

## 선행 지식

[01단원](../01-array-string/README.md): `vector`, `string`. [00단원](../00-basics/README.md): `const` 참조.

## 개념

### sort

```cpp
#include <algorithm>
sort(v.begin(), v.end());                   // 오름차순
sort(v.begin(), v.end(), greater<int>());   // 내림차순 (<functional>)
```

`begin()`은 첫 원소, `end()`는 **마지막 원소의 다음**을 가리킨다. 즉 `[begin, end)` 반열린 구간이다.
이 "끝은 포함하지 않는다"는 규칙은 STL 전체에서 일관되게 쓰인다.

### pair

두 값을 묶는 자료형. 비교할 때 `first`를 먼저, 같으면 `second`를 본다.

```cpp
#include <utility>
pair<int, string> p = {90, "kim"};
p.first; p.second;
vector<pair<int, int>> v;  sort(v.begin(), v.end());  // first 오름차순, 같으면 second 오름차순
```

### 람다 비교 함수

람다는 이름 없는 함수다. `[](인자) { 본문 }` 형태로 쓴다.
`sort`의 세 번째 인자로 넘기는 비교 함수는 **"a가 b보다 앞에 와야 하면 true"**를 반환한다.

```cpp
sort(v.begin(), v.end(), [](const Student &a, const Student &b) {
    if (a.score != b.score) return a.score > b.score;  // 1순위: 점수 내림차순
    return a.name < b.name;                            // 2순위: 이름 오름차순
});
```

규칙: **같은 값끼리 비교하면 반드시 false**여야 한다. `>=`, `<=`를 쓰면 안 된다.

### 중복 제거

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

`unique`는 **연속한** 중복을 뒤로 밀고 새 끝 위치를 반환할 뿐, 크기를 줄이지 않는다. 그래서 `erase`가 필요하다.

## 이런 문제에서 떠올린다

| 문제의 특징 | 떠올릴 것 |
|---|---|
| "순서대로 출력", "순위", "k번째로 큰" | 정렬 |
| "여러 기준", "같으면 ~순" | 비교 함수 또는 pair/tuple |
| "서로 다른 값의 개수/목록" | sort + unique + erase |
| 같은 값끼리 모아 처리하고 싶다 | 정렬하면 같은 값이 이웃한다 |
| 가까운 값끼리 비교 (최소 차이 등) | 정렬 후 이웃만 보면 된다 |

정렬은 그 자체가 답이라기보다 **다른 방법의 준비 단계**인 경우가 많다(이분탐색, 투 포인터, 그리디).

## 작은 입력으로 따라가기

**다중 기준**: `(kim, 90, 21) (lee, 85, 20) (park, 90, 19) (choi, 85, 20)`을 점수↓, 나이↑, 이름↑로 정렬

| 비교 | 점수 | 나이 | 이름 | 결과 |
|---|---|---|---|---|
| park vs kim | 90 = 90 | 19 < 21 | - | park이 앞 |
| kim vs choi | 90 > 85 | - | - | kim이 앞 |
| choi vs lee | 85 = 85 | 20 = 20 | choi < lee | choi가 앞 |

결과: park, kim, choi, lee.

**중복 제거**: `4 1 4 2 1 4`

| 단계 | 배열 | size |
|---|---|---|
| sort | `1 1 2 4 4 4` | 6 |
| unique | `1 2 4 ? ? ?` (반환값은 인덱스 3 위치) | 6 |
| erase | `1 2 4` | 3 |

## 예제

| 예제 | 내용 | 실행 |
|---|---|---|
| [sort_basics.cpp](examples/sort_basics.cpp) | 오름차순·내림차순, pair, 부분 정렬, min/max_element | `./ct example 02-sort_basics` |
| [custom_sort_unique.cpp](examples/custom_sort_unique.cpp) | 람다 다중 기준 정렬, unique + erase | `./ct example 02-custom_sort_unique` |

## 복잡도

| 연산 | 시간 | 이유 |
|---|---|---|
| `sort` | O(N log N) | 비교 횟수가 N log N에 비례. N=20만이면 약 350만 번 |
| `reverse`, `unique`, `min_element` | O(N) | 한 번 훑는다 |
| 정렬 후 `erase(끝 구간)` | O(지우는 개수) | |

공간: `sort`는 추가 메모리를 거의 쓰지 않는다(O(log N)).
직접 이중 반복문으로 정렬(O(N²))하면 N=10만에서 시간초과다. 항상 `sort`를 쓴다.

## 자주 하는 실수와 반례

| 실수 | 반례 / 증상 |
|---|---|
| 비교 함수에 `>=` 사용 | `{3, 3, 3, ...}`처럼 같은 값이 많으면 런타임 오류 가능 |
| 기준을 `\|\|`로 섞음: `a.s > b.s \|\| a.p < b.p` | (s=1,p=0) vs (s=2,p=5): 점수가 낮은데 앞에 옴 |
| `unique` 후 `erase` 누락 | `size()`가 그대로라 뒤의 쓰레기 값까지 출력 |
| 정렬 없이 `unique` | `1 2 1` → 중복이 남는다 |
| 비교 함수 인자를 값으로 받음 | 문자열이 매번 복사되어 느려짐 |
| 숫자를 문자열로 정렬 | `"10" < "9"` (사전순) |
| 정렬하면 원래 순서(인덱스)를 잃는다는 점을 잊음 | 필요하면 `(값, 원래 인덱스)` pair로 정렬 |

## 문제

1. [02a 중복 없는 정렬](../../problems/02a-distinct-sorted/problem.md) (기본) - `./ct test 02a`
2. [02b 대회 순위표](../../problems/02b-scoreboard/problem.md) (응용) - `./ct test 02b`

## 완료 체크리스트

- [ ] `[begin, end)`가 무엇을 뜻하는지 설명할 수 있다.
- [ ] 세 가지 기준의 비교 람다를 보지 않고 작성할 수 있다.
- [ ] 비교 함수에서 `>=`를 쓰면 안 되는 이유를 말할 수 있다.
- [ ] `unique`가 반환하는 것과 `erase`가 필요한 이유를 설명할 수 있다.
- [ ] 02a, 02b를 통과했다.
