# 02a 중복 없는 정렬 - 해설

[정답 코드](solution.cpp) · [문제](../../problems/02a-distinct-sorted/problem.md)

## 접근

정렬하면 같은 값이 서로 붙는다. 그 상태에서 `unique`로 연속 중복을 제거한다.

```cpp
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
```

`unique`는 컨테이너 크기를 바꾸지 않고 "중복이 제거된 구간의 끝"만 알려 주므로,
반드시 `erase`와 함께 쓴다. `set<int>`에 모두 넣어도 답은 같지만 보통 더 느리다.

## 복잡도

- 시간: O(N log N) - 정렬이 지배적. `unique`와 `erase`는 O(N).
- 공간: O(N).

## 자주 하는 실수

- `unique`만 호출하고 `erase`를 빼먹어 뒤쪽에 쓰레기 값이 남는다.
- 정렬하지 않고 `unique`를 호출한다(연속한 중복만 제거된다).
- 각 원소마다 "이미 나왔는지"를 선형 탐색하는 O(N²) 풀이는 시간초과.
