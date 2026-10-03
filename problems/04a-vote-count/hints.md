# 04a 투표 집계 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

01a(점수 분포)에서는 점수를 배열 인덱스로 썼다. 이름은 인덱스로 쓸 수 없지만,
"키 → 값"을 저장하는 자료구조를 쓰면 `횟수[이름]++`와 같은 코드를 그대로 쓸 수 있다.

</details>

<details>
<summary>힌트 2단계</summary>

`unordered_map<string, int> votes;`에 `votes[name]++`.
그다음 `for (const auto &entry : votes)`로 전체를 돌면서
"득표수가 더 많거나, 같고 이름이 사전순으로 더 앞서면" 답을 갱신한다.
(`map<string, int>`를 쓰면 이름 순서로 순회되어 "더 많을 때만" 갱신해도 된다.)

</details>
