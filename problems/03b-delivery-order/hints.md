# 03b 배달 순서 - 힌트

[문제로 돌아가기](problem.md)

힌트는 한 단계씩만 펼쳐 보세요. 1단계를 보고 최소 10분은 다시 시도한 뒤 2단계를 보는 것을 권장합니다.

<details>
<summary>힌트 1단계</summary>

출발지는 고정이므로 정해야 하는 것은 나머지 N-1곳의 **방문 순서**뿐이다.
N ≤ 8이면 순서는 최대 7! = 5,040가지. 모든 순서를 만들어 거리를 계산해 볼 수 있다.

</details>

<details>
<summary>힌트 2단계</summary>

`vector<int> order = {1, 2, ..., n-1}`(오름차순)을 만들고

```cpp
do {
    // order 순서대로 방문했을 때의 총 거리를 계산해 최솟값 갱신
} while (next_permutation(order.begin(), order.end()));
```

`do-while`을 써야 첫 번째 순열(오름차순)도 검사한다.

</details>
