# 08b 가장 짧은 구간 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

모든 원소가 양수다. 그러면 구간의 오른쪽 끝을 늘리면 합이 커지고, 왼쪽 끝을 당기면 합이 작아진다.
오른쪽 끝을 한 칸씩 늘려 가면서, 합이 S 이상인 동안 왼쪽 끝을 최대한 당겨 보자.
왼쪽 끝이 뒤로 돌아가야 할 일이 있을까?

</details>

<details>
<summary>힌트 2단계</summary>

```
left = 0, sum = 0, best = 0
for right in 0..n-1:
    sum += a[right]
    while sum >= S:
        best = min(best, right - left + 1)   // best가 0이면 그냥 대입
        sum -= a[left]; left++
```

`left`와 `right`가 각각 최대 N번만 움직이므로 전체 O(N).

</details>
