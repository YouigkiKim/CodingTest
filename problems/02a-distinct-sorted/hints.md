# 02a 중복 없는 정렬 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

정렬을 먼저 하면 같은 값끼리 이웃하게 된다. 이웃한 중복만 지우면 되므로 일이 쉬워진다.

</details>

<details>
<summary>힌트 2단계</summary>

`sort(a.begin(), a.end());` 다음에 `a.erase(unique(a.begin(), a.end()), a.end());`.
`unique`는 크기를 줄이지 않고 "새로운 끝" 위치만 돌려주기 때문에 `erase`가 꼭 필요하다.

</details>
