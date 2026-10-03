# 06b 막대 합치기 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

일찍 합쳐진 막대의 길이는 그 뒤의 합치기 비용에 계속 다시 포함된다.
그렇다면 일찍 합칠 막대로는 긴 것과 짧은 것 중 어느 쪽이 유리할까?
그리고 합쳐서 생긴 막대도 다시 후보가 된다는 점에 주의하자. 한 번 정렬하는 것으로 충분할까?

</details>

<details>
<summary>힌트 2단계</summary>

매번 **가장 짧은 두 막대**를 꺼내 합치고, 결과를 다시 넣는다. 막대가 하나 남을 때까지 반복.
"최솟값 꺼내기 + 새 값 넣기"를 반복하므로 최소 힙을 쓴다.

```cpp
priority_queue<long long, vector<long long>, greater<long long>> pq;
```

비용 합은 `long long`으로.

</details>
