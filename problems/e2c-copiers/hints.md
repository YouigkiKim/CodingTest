# 모의 2-3 복사기 - 힌트

[문제로 돌아가기](problem.md)

모의시험 시간이 끝난 뒤, 풀지 못한 문제를 다시 시도할 때 한 단계씩 펼쳐 보세요.

<details>
<summary>힌트 1단계</summary>

"최소 시간"을 직접 구하는 대신 "T초가 주어졌을 때 K장 이상 만들 수 있는가?"를 생각해 보자.
복사기 i는 T초 동안 `T / t_i`장을 만든다. 그리고 T초에 가능하면 T보다 긴 시간에도 당연히 가능하다.

</details>

<details>
<summary>힌트 2단계</summary>

T에 대해 이분탐색한다. 범위는 `1 ~ min(t) × K`.

```
while lo < hi:
    mid = lo + (hi - lo) / 2
    if 장수(mid) >= K: hi = mid
    else:             lo = mid + 1
답 = lo
```

모든 값을 `long long`으로. 장수를 더하다가 K 이상이 되면 바로 "가능"으로 판정하면 합이 지나치게 커지는 것도 막을 수 있다.

</details>
