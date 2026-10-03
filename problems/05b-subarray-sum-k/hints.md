# 05b 합이 K인 구간 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

누적합 `prefix`로 표현하면 구간의 합은 `prefix[j] - prefix[i]` (i < j)이다.
이 값이 K라는 것은 `prefix[i] == prefix[j] - K`와 같다.
끝점 j를 고정하면 "찾아야 하는 앞쪽 누적합 값"이 하나로 정해진다. 04b(합이 T인 쌍)와 닮지 않았는가?

</details>

<details>
<summary>힌트 2단계</summary>

`unordered_map<long long, int> seen`에 "지금까지 나온 누적합 값의 횟수"를 기록한다.
시작 전에 `seen[0] = 1`(아무것도 더하지 않은 상태)을 넣는다.
원소를 하나 더할 때마다: 답에 `seen`에서 `prefix - K`의 횟수를 더하고, 그다음 `seen[prefix]++`.

</details>
