# 06 스택·큐·힙

이전: [05 누적합](../05-prefix-sum/README.md) · 다음: [07 이분탐색](../07-binary-search/README.md) · [전체 목차](../../README.md) · [치트시트](../../docs/cheatsheet.md)

예상 소요: 3시간 · 문제: [06a 괄호 검사](../../problems/06a-brackets/problem.md), [06b 막대 합치기](../../problems/06b-merge-sticks/problem.md)

## 학습 목표

- `stack`, `queue`, `priority_queue`의 "꺼내는 순서"를 구분한다.
- 스택으로 괄호의 짝을 검사한다.
- 최소 힙을 선언하고, "가장 작은 것을 반복해서 꺼내는" 문제에 적용한다.

## 선행 지식

[01단원](../01-array-string/README.md): `vector`, `string`. [02단원](../02-sorting/README.md): `pair`, `greater`.

## 개념

세 자료구조는 모두 "넣기(push)"와 "꺼내기(pop)"를 제공하지만 **무엇이 먼저 나오는가**가 다르다.

| 자료구조 | 먼저 나오는 것 | 읽기 | 헤더 | 비유 |
|---|---|---|---|---|
| `stack<T>` | 가장 **나중에** 넣은 것 (LIFO) | `top()` | `<stack>` | 쌓아 둔 접시 |
| `queue<T>` | 가장 **먼저** 넣은 것 (FIFO) | `front()` | `<queue>` | 줄 서기 |
| `priority_queue<T>` | 가장 **큰** 것 | `top()` | `<queue>` | 응급실 |

```cpp
stack<int> st;  st.push(1);  int x = st.top();  st.pop();
queue<int> q;   q.push(1);   int y = q.front(); q.pop();
priority_queue<int> pq;                                       // 최대 힙
priority_queue<int, vector<int>, greater<int>> min_pq;        // 최소 힙 (<functional>)
```

두 가지 규칙을 반드시 기억한다.

1. **`pop()`은 값을 반환하지 않는다.** 읽기(`top`/`front`)와 제거(`pop`)는 별개다.
2. **비어 있을 때 `top()`/`front()`/`pop()`을 호출하면 안 된다.** 항상 `empty()`를 먼저 확인한다.

### 우선순위 큐(힙)

"지금 있는 것 중 가장 큰(작은) 값"을 O(log N)에 꺼내고, 새 값을 O(log N)에 넣는다.
정렬과의 차이: 정렬은 한 번에 전부 순서를 매기지만, 힙은 **값이 계속 추가되는 중에도** 최댓값/최솟값을 빠르게 준다.

## 이런 문제에서 떠올린다

| 문제의 특징 | 떠올릴 것 |
|---|---|
| 괄호 짝, 가장 최근 것과 대응, 되돌리기(undo) | 스택 |
| "가장 최근에 본 ~" | 스택 |
| 도착한 순서대로 처리, 대기열, BFS([09단원](../09-bfs-dfs/README.md)) | 큐 |
| "가장 작은/큰 것을 꺼내 처리하고, 결과를 다시 넣는다"를 반복 | 우선순위 큐 |
| 값이 들어오는 중간중간 현재 최댓값/최솟값을 묻는다 | 우선순위 큐 |

## 작은 입력으로 따라가기

**괄호 검사**: `{[()]}` 와 `([)]`

| 문자 | 동작 | 스택 (아래→위) |
|---|---|---|
| `{` | push | `{` |
| `[` | push | `{ [` |
| `(` | push | `{ [ (` |
| `)` | top이 `(` → 짝 맞음, pop | `{ [` |
| `]` | top이 `[` → pop | `{` |
| `}` | top이 `{` → pop | (빈 스택) |

끝났을 때 스택이 비어 있으므로 올바르다.

| 문자 | 동작 | 스택 |
|---|---|---|
| `(` | push | `(` |
| `[` | push | `( [` |
| `)` | top이 `[` → **종류 불일치** | 실패 |

**최소 힙**: `10 1 1 1`에서 가장 작은 둘을 합쳐 다시 넣기

`{1,1,1,10}` → 1+1=2 넣음 → `{1,2,10}` → 1+2=3 넣음 → `{3,10}` → 13 → `{13}`.

## 예제

| 예제 | 내용 | 실행 |
|---|---|---|
| [stack_queue.cpp](examples/stack_queue.cpp) | 꺼내는 순서, 한 종류 괄호 검사, 되돌리기, 라운드 로빈 | `./ct example 06-stack_queue` |
| [priority_queue.cpp](examples/priority_queue.cpp) | 최대/최소 힙, pair 우선순위, 추가와 꺼내기가 섞인 처리 | `./ct example 06-priority_queue` |

## 복잡도

| 연산 | stack / queue | priority_queue |
|---|---|---|
| push | O(1) | O(log N) |
| pop | O(1) | O(log N) |
| top / front | O(1) | O(1) |
| 임의 위치 접근·검색 | 불가 | 불가 |

공간은 모두 O(저장한 원소 수). N개를 넣고 전부 꺼내면 힙은 O(N log N)으로, 정렬과 같은 수준이다.

## 자주 하는 실수와 반례

| 실수 | 반례 / 증상 |
|---|---|
| 빈 스택에서 `top()`/`pop()` | 입력 `)` → 런타임 오류 또는 엉뚱한 동작 |
| `int x = st.pop();` | 컴파일 오류(`pop`은 `void`) |
| 괄호 검사 후 스택이 비었는지 확인 안 함 | `((` → 올바르다고 답함 |
| 괄호 개수만 셈 | `([)]` → 개수는 맞지만 올바르지 않다 |
| 최소 힙이 필요한데 기본 `priority_queue` 사용 | 큰 값부터 나옴 |
| 최솟값을 반복해서 꺼내려고 매번 `sort` | O(N² log N) 시간초과 |
| `queue`에 `top()` / `stack`에 `front()` | 컴파일 오류. queue는 `front()`, stack·priority_queue는 `top()` |

`./ct asan 06a`로 실행하면 빈 컨테이너 접근 같은 오류를 더 잘 잡아낸다.

## 문제

1. [06a 괄호 검사](../../problems/06a-brackets/problem.md) (기본) - `./ct test 06a`
2. [06b 막대 합치기](../../problems/06b-merge-sticks/problem.md) (응용) - `./ct test 06b`

## 완료 체크리스트

- [ ] 세 자료구조에 1, 2, 3을 넣었을 때 나오는 순서를 각각 말할 수 있다.
- [ ] 최소 힙 선언문을 보지 않고 쓸 수 있다.
- [ ] `top()` 전에 `empty()`를 확인하는 습관이 들었다.
- [ ] 06a, 06b를 통과했다.
- [ ] 06b에서 "한 번만 정렬"로는 안 되는 이유를 설명할 수 있다.
