# 07a 범위 안의 개수 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

질문마다 N개를 모두 확인하면 10^5 × 10^5 = 10^10번이다.
배열을 **정렬**해 두면 lo 이상 hi 이하인 값들은 연속해서 놓인다.
그 연속 구간의 시작 위치와 끝 위치만 빨리 찾으면 된다.

</details>

<details>
<summary>힌트 2단계</summary>

정렬 후
`upper_bound(a.begin(), a.end(), hi) - lower_bound(a.begin(), a.end(), lo)`.

- `lower_bound(lo)`: lo **이상**인 첫 위치
- `upper_bound(hi)`: hi **초과**인 첫 위치

</details>
