# 모의 1-4 묶음 포장 - 힌트

[문제로 돌아가기](problem.md)

모의시험 시간이 끝난 뒤, 풀지 못한 문제를 다시 시도할 때 한 단계씩 펼쳐 보세요.

<details>
<summary>힌트 1단계</summary>

구간의 합은 두 누적합의 차 `prefix[j] - prefix[i]`다.
두 수의 차가 M의 배수라는 것은, 두 수를 M으로 나눈 **나머지가 같다**는 뜻이다.

</details>

<details>
<summary>힌트 2단계</summary>

누적합을 M으로 나눈 나머지를 왼쪽부터 구해 가면서, `unordered_map<long long, int> seen`에
"이 나머지가 지금까지 몇 번 나왔는지"를 기록한다. 시작 전에 `seen[0] = 1`.
새 나머지 `r`을 얻을 때마다 답에 `seen[r]`을 더하고 `seen[r]++`.
M이 최대 10^9이라 크기 M의 배열은 만들 수 없고, 답은 `long long`이어야 한다.

</details>
