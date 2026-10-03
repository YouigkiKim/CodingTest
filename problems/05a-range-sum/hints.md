# 05a 구간 합 질의 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

질문마다 l부터 r까지 직접 더하면 최악의 경우 200,000 × 200,000번의 덧셈이 필요하다.
"앞에서부터 i개의 합"을 미리 전부 구해 두면, 구간의 합을 **두 값의 차**로 표현할 수 있다.

</details>

<details>
<summary>힌트 2단계</summary>

`vector<long long> prefix(n + 1, 0);`에 `prefix[i] = prefix[i-1] + a_i` (i는 1부터).
`[l, r]`의 합은 `prefix[r] - prefix[l - 1]`. `prefix[0] = 0`을 두면 `l = 1`도 예외 없이 처리된다.

</details>
