# 모의 1-3 출입 기록 - 힌트

[문제로 돌아가기](problem.md)

모의시험 시간이 끝난 뒤, 풀지 못한 문제를 다시 시도할 때 한 단계씩 펼쳐 보세요.

<details>
<summary>힌트 1단계</summary>

필요한 연산은 세 가지다: 이름 추가, 이름 삭제, 마지막에 사전순으로 전부 출력.
`vector`에서 이름을 찾아 지우는 것은 한 번에 O(N)이다. 추가와 삭제가 모두 빠른 자료구조는?

</details>

<details>
<summary>힌트 2단계</summary>

`set<string> inside;`를 쓴다. `in`이면 `insert`, `out`이면 `erase`.
`set`은 항상 정렬 상태이므로 마지막에 범위 기반 for로 순회하면 사전순이다.
(`unordered_set`을 썼다면 `vector`로 옮겨 정렬한 뒤 출력한다.)

</details>
