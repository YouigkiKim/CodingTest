# 모의 1-2 마라톤 기록 - 힌트

[문제로 돌아가기](problem.md)

모의시험 시간이 끝난 뒤, 풀지 못한 문제를 다시 시도할 때 한 단계씩 펼쳐 보세요.

<details>
<summary>힌트 1단계</summary>

`HH:MM:SS`를 그대로 다루지 말고 **초 단위 정수 하나**로 바꾸면 비교와 뺄셈이 쉬워진다.
형식의 자리 수가 고정이므로 문자열의 정해진 위치를 잘라 숫자로 바꿀 수 있다.

</details>

<details>
<summary>힌트 2단계</summary>

`stoi(t.substr(0, 2)) * 3600 + stoi(t.substr(3, 2)) * 60 + stoi(t.substr(6, 2))`.
`vector<pair<int, string>>`에 `(초, 이름)`으로 넣고 `sort`하면 기본 비교가 곧 문제의 순서다.
정렬 후 맨 앞 원소의 초를 기준으로 차이를 출력한다.

</details>
