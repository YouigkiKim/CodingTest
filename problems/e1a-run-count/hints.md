# 모의 1-1 연속 문자 세기 - 힌트

[문제로 돌아가기](problem.md)

모의시험 시간이 끝난 뒤, 풀지 못한 문제를 다시 시도할 때 한 단계씩 펼쳐 보세요.

<details>
<summary>힌트 1단계</summary>

덩어리의 시작 위치 `i`를 잡고, 같은 문자가 계속되는 동안 끝 위치 `j`를 늘려 보자.
덩어리 하나를 처리한 다음에는 어디서 다시 시작해야 할까?

</details>

<details>
<summary>힌트 2단계</summary>

```
i = 0
while i < 길이:
    j = i
    while j < 길이 and s[j] == s[i]: j++
    출력에 s[i]와 to_string(j - i)를 붙인다
    i = j
```

횟수가 두 자리 이상일 수 있으므로 `to_string`을 쓴다.

</details>
