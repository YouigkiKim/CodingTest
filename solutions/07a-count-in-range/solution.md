# 07a 범위 안의 개수 - 해설

[정답 코드](solution.cpp) · [문제](../../problems/07a-count-in-range/problem.md)

## 접근

질문마다 배열 전체를 훑으면 O(N×Q) = 10^10. 정렬해 두면 "lo 이상 hi 이하"인 값들은 **연속한 구간**을 이룬다.

- `lower_bound(lo)`: `lo` **이상**인 첫 위치
- `upper_bound(hi)`: `hi` **초과**인 첫 위치

두 반복자의 차이가 곧 개수다. 반열린 구간 `[first, last)`이므로 `+1` 같은 보정이 필요 없다.

### 작은 예 (정렬 후 1 4 4 7 9)

- `[4, 4]`: lower_bound(4) = 인덱스 1, upper_bound(4) = 인덱스 3 → 2개
- `[5, 6]`: lower_bound(5) = 인덱스 3, upper_bound(6) = 인덱스 3 → 0개

## 복잡도

- 시간: O((N + Q) log N). 공간: O(N).

## 자주 하는 실수

- 정렬하지 않고 `lower_bound` 호출(결과가 무의미해진다).
- `upper_bound(hi) - lower_bound(lo) + 1`처럼 불필요한 +1.
- 둘 다 `lower_bound`를 써서 `hi`와 같은 값을 빼먹는다.
