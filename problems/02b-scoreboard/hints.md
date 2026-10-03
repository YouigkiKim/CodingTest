# 02b 대회 순위표 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

`sort`의 세 번째 인자로 비교 함수(람다)를 넘길 수 있다.
비교 함수는 "첫 번째 인자가 두 번째 인자보다 **앞에 와야 하면** true"를 반환한다.
기준이 여러 개일 때는 우선순위가 높은 기준부터 "다르면 그 기준으로 결정"하는 식으로 쓴다.

</details>

<details>
<summary>힌트 2단계</summary>

```cpp
sort(teams.begin(), teams.end(), [](const Team &a, const Team &b) {
    if (a.solved != b.solved) return /* 문제 수 비교 */;
    if (a.penalty != b.penalty) return /* 벌점 비교 */;
    return /* 이름 비교 */;
});
```

내림차순은 `>`, 오름차순은 `<`. `>=`/`<=`는 쓰지 않는다(같은 값에 true를 반환하면 안 된다).

</details>
