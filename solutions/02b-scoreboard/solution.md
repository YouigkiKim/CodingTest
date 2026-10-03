# 02b 대회 순위표 - 해설

[정답 코드](solution.cpp) · [문제](../../problems/02b-scoreboard/problem.md)

## 접근

**다중 기준 정렬**이다. 비교 함수는 "a가 b보다 앞에 와야 하는가?"에 답한다.
기준을 우선순위 순서대로 보면서, **값이 다르면 그 기준으로 결정하고 끝낸다.**

```cpp
if (a.solved != b.solved) return a.solved > b.solved;
if (a.penalty != b.penalty) return a.penalty < b.penalty;
return a.name < b.name;
```

다른 방법: `tuple<int,int,string>`에 `(-solved, penalty, name)`을 넣고 기본 `sort`를 써도 된다.
부호를 뒤집어 내림차순을 오름차순 문제로 바꾸는 요령이다.

## 복잡도

- 시간: O(N log N) 번의 비교. 문자열 비교는 길이(최대 10)에 비례.
- 공간: O(N).

## 자주 하는 실수

- 비교 함수에서 `>=`나 `<=`를 써서 **같은 원소에 true를 반환** → 정의되지 않은 동작(런타임 오류 가능).
- `return a.solved > b.solved || a.penalty < b.penalty;`처럼 기준을 섞어 쓰는 실수.
  (solved가 더 작은데 penalty가 작다는 이유로 앞에 오게 된다.)
- 비교 함수 인자를 값으로 받아 문자열 복사가 매번 일어남 → `const Team&`로 받는다.
- `endl`을 10만 번 호출해 출력이 느려짐 → `'\n'`을 쓴다.
