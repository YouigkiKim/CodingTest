# 08a 가장 가까운 합 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

가장 작은 수와 가장 큰 수의 합을 먼저 본다. 이 합이 T보다 **작다면**,
가장 작은 수를 다른 어떤 수와 짝지어도 합은 지금보다 커질 수 없다.
즉 가장 작은 수는 더 볼 필요가 없다. 합이 T보다 크다면 반대로 무엇을 버릴 수 있을까?

</details>

<details>
<summary>힌트 2단계</summary>

`left = 0`, `right = n - 1`에서 시작해 `left < right`인 동안:

1. `sum = a[left] + a[right]`로 `|sum - T|`의 최솟값을 갱신한다.
2. `sum < T`이면 `left++`, `sum > T`이면 `right--`, 같으면 답은 0.

차이는 최대 4×10^9이므로 `long long`.

</details>
