# C++ STL 치트시트

[전체 목차](../README.md) · [자주 하는 실수](pitfalls.md) · [복잡도 가이드](complexity.md)

학습 중 빠르게 찾아보기 위한 요약이다. 시간복잡도의 N은 컨테이너의 원소 수.

**목차**: [기본 문법](#기본-문법) · [vector](#vector) · [string](#string) · [pair](#pair) ·
[해시·트리 컨테이너](#unordered_map--unordered_set--map--set) · [stack·queue·priority_queue](#stack--queue--priority_queue) ·
[정렬·순서](#정렬과-순서) · [최소·최대·합](#최소최대합) · [탐색](#탐색) · [채우기·중복 제거](#채우기와-중복-제거) ·
[문자열 변환](#문자열-변환) · [순열](#순열) · [입출력](#입출력) · [코드 뼈대](#코드-뼈대)

---

## 기본 문법

### 범위 기반 for, auto, 참조

```cpp
vector<int> v = {1, 2, 3};
for (int x : v) { }              // 복사본으로 순회 (원본 수정 불가)
for (int &x : v) { x *= 2; }     // 참조: 원본 수정
for (const string &s : names) { } // const 참조: 복사 없이 읽기만 (큰 원소의 기본 선택)
for (const auto &e : my_map) { e.first; e.second; }   // auto: 자료형을 컴파일러가 추론
auto it = v.begin();             // 반복자처럼 긴 자료형에 유용
```

| 형태 | 복사 | 원본 수정 | 용도 |
|---|---|---|---|
| `T x` | O | X | `int`, `char` 등 작은 값 |
| `T &x` | X | O | 원본을 바꿀 때 |
| `const T &x` | X | X | `string`, `vector`, `pair` 등을 읽을 때 |

### 람다

```cpp
auto is_even = [](int x) { return x % 2 == 0; };          // 기본형: [](인자) { 본문 }
int k = 3;
auto add_k = [k](int x) { return x + k; };                // [k]: 바깥 변수 k를 복사해 사용
auto count_up = [&](int x) { total += x; };               // [&]: 바깥 변수를 참조로 사용
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });   // 가장 흔한 용도: 비교 함수
```

### 반복자와 `[begin, end)`

- `v.begin()`: 첫 원소. `v.end()`: **마지막 원소의 다음**(원소가 아니다, 역참조 금지).
- STL 알고리즘은 모두 반열린 구간 `[first, last)`를 받는다.
- 인덱스 변환: `it - v.begin()`. 값 읽기: `*it`.
- 부분 구간: `sort(v.begin() + 1, v.begin() + 4)`는 인덱스 1, 2, 3을 정렬.

---

## vector

헤더 `<vector>`

| 기능 | 예시 | 반환 | 시간 |
|---|---|---|---|
| 선언 | `vector<int> v;` `vector<int> v(n);` `vector<int> v(n, -1);` `vector<int> v = {1,2,3};` | | O(n) |
| 2차원 | `vector<vector<int>> g(h, vector<int>(w, 0));` | | O(h·w) |
| 접근 | `v[i]`, `v.front()`, `v.back()` | 원소 참조 | O(1) |
| 크기 | `v.size()`, `v.empty()` | `size_t`(부호 없음), `bool` | O(1) |
| 뒤에 추가/삭제 | `v.push_back(x)`, `v.pop_back()` | 없음 | 평균 O(1) |
| 중간 삽입/삭제 | `v.insert(v.begin() + i, x)`, `v.erase(v.begin() + i)` | 반복자 | O(N) |
| 구간 삭제 | `v.erase(first, last)` | 반복자 | O(N) |
| 비우기/크기 변경 | `v.clear()`, `v.resize(n)`, `v.assign(n, x)` | 없음 | O(N) |
| 복사 | `vector<int> b = a;` | | O(N) |
| 비교 | `a == b`, `a < b`(사전순) | `bool` | O(N) |

- 인덱스는 0 ~ `size()-1`. 범위 밖 접근은 검사되지 않는다.
- `v.size() - 1`은 `v`가 비어 있으면 매우 큰 수가 된다 → `(int)v.size() - 1`.
- 빈 vector에서 `front()`, `back()`, `pop_back()` 금지.

## string

헤더 `<string>`

| 기능 | 예시 | 반환 | 시간 |
|---|---|---|---|
| 선언 | `string s = "abc";` `string s(5, 'x');` | | O(길이) |
| 접근 | `s[i]`, `s.front()`, `s.back()` | `char&` | O(1) |
| 길이 | `s.size()`, `s.length()`, `s.empty()` | `size_t`, `bool` | O(1) |
| 이어 붙이기 | `s += "de";` `s += 'c';` `s.push_back('c');` | | 평균 O(추가 길이) |
| 마지막 삭제 | `s.pop_back()` | 없음 | O(1) |
| 부분 문자열 | `s.substr(pos, len)`, `s.substr(pos)`(끝까지) | 새 `string` | O(len) |
| 찾기 | `s.find("ab")`, `s.find('c', start)` | 첫 위치(`size_t`), 없으면 `string::npos` | O(N·M) |
| 비교 | `s == t`, `s < t`(사전순) | `bool` | O(길이) |
| 정렬/뒤집기 | `sort(s.begin(), s.end())`, `reverse(s.begin(), s.end())` | | O(N log N), O(N) |

```cpp
size_t pos = s.find("needle");
if (pos != string::npos) { /* 찾음: pos가 시작 위치 */ }   // 반드시 npos와 비교

int idx = ch - 'a';        // 'a'..'z' -> 0..25
int digit = ch - '0';      // '0'..'9' -> 0..9
char up = (char)(ch - 'a' + 'A');
bool lower = ('a' <= ch && ch <= 'z');   // <cctype>의 islower, isdigit, toupper도 가능
```

- `substr(pos, len)`의 두 번째 인자는 **길이**다(끝 위치가 아니다).
- `s + t`를 반복문에서 매번 하면 O(N²)이 될 수 있다. `+=`를 쓴다.
- 문자 하나는 `'a'`(char), 문자열은 `"a"`(string). `s[i] == "a"`는 컴파일 오류.

## pair

헤더 `<utility>`

```cpp
pair<int, string> p = {3, "kim"};
p.first; p.second;
auto q = make_pair(1, 2);
vector<pair<int, int>> v;  v.push_back({a, b});
```

- 비교: `first`를 먼저, 같으면 `second`. `sort`, `priority_queue`, `map`의 키에 그대로 쓸 수 있다.
- 세 값 이상은 `struct` 또는 `tuple`(`<tuple>`, `get<0>(t)`).

---

## unordered_map · unordered_set · map · set

| | `unordered_map<K,V>` | `unordered_set<K>` | `map<K,V>` | `set<K>` |
|---|---|---|---|---|
| 헤더 | `<unordered_map>` | `<unordered_set>` | `<map>` | `<set>` |
| 삽입·조회·삭제 | 평균 O(1) | 평균 O(1) | O(log N) | O(log N) |
| 순회 순서 | 정해지지 않음 | 정해지지 않음 | 키 오름차순 | 오름차순 |
| 최소/최대 | X | X | `begin()`, `rbegin()` | `*begin()`, `*rbegin()` |
| `lower_bound(k)` | X | X | O(log N) | O(log N) |

| 기능 | 예시 | 반환 |
|---|---|---|
| 삽입/수정 (map) | `m[key] = v;` `m[key]++;` | 값 참조. **없는 키는 기본값(0, "")으로 생성된다** |
| 삽입 (set) | `s.insert(x)` | (중복이면 무시) |
| 존재 확인 | `m.count(key)`, `s.count(x)` | 0 또는 1. 키를 만들지 않는다 |
| 찾기 | `auto it = m.find(key);` | 반복자, 없으면 `m.end()` |
| 값 읽기 | `it->first`, `it->second` (map) / `*it` (set) | |
| 삭제 | `m.erase(key)`, `s.erase(x)` | 지운 개수 |
| 크기 | `m.size()`, `m.empty()` | |
| 순회 | `for (const auto &e : m) { e.first; e.second; }` | |

```cpp
// 조회만 할 때는 []를 쓰지 않는다
if (m.count(key)) use(m[key]);
auto it = m.find(key);
if (it != m.end()) use(it->second);

// set/map 전용 멤버 함수 (std::lower_bound가 아니라 멤버 함수를 쓴다)
auto it2 = s.lower_bound(x);     // x 이상인 첫 원소, 없으면 s.end()
```

고르는 기준: 빈도·존재 여부만 → `unordered_*` / 정렬된 순회·최소·최대·"x 이상인 첫 값" → `map`/`set` /
키가 작은 정수 → `vector`.

`unordered_map`의 키로 `pair`나 `vector`는 바로 쓸 수 없다(해시 미정의). `map`을 쓰거나 키를 정수 하나로 합친다
(예: `r * W + c`).

---

## stack · queue · priority_queue

| | `stack<T>` | `queue<T>` | `priority_queue<T>` |
|---|---|---|---|
| 헤더 | `<stack>` | `<queue>` | `<queue>` |
| 넣기 | `push(x)` O(1) | `push(x)` O(1) | `push(x)` O(log N) |
| 읽기 | `top()` | `front()`, `back()` | `top()` (가장 큰 값) |
| 꺼내기 | `pop()` O(1) | `pop()` O(1) | `pop()` O(log N) |
| 나오는 순서 | 나중에 넣은 것 먼저 | 먼저 넣은 것 먼저 | 큰 값 먼저 |
| 공통 | `size()`, `empty()` | | |

```cpp
// pop()은 값을 반환하지 않는다. 읽고 나서 지운다.
while (!st.empty()) {
    int x = st.top();
    st.pop();
}

priority_queue<int> max_pq;                                   // 최대 힙
priority_queue<int, vector<int>, greater<int>> min_pq;        // 최소 힙, <functional>
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;  // (비용, 번호) 최소 힙
```

- 빈 상태에서 `top()`, `front()`, `pop()` 금지. 항상 `empty()` 확인.
- 순회, 인덱스 접근, 검색은 지원하지 않는다.
- 양쪽 끝에서 넣고 빼야 하면 `deque`(`<deque>`): `push_front`, `push_back`, `pop_front`, `pop_back`, `d[i]`.

---

## 정렬과 순서

헤더 `<algorithm>`

| 기능 | 예시 | 반환 | 시간 |
|---|---|---|---|
| 오름차순 | `sort(v.begin(), v.end());` | 없음 | O(N log N) |
| 내림차순 | `sort(v.begin(), v.end(), greater<int>());` (`<functional>`) | | O(N log N) |
| 사용자 기준 | `sort(v.begin(), v.end(), [](const T &a, const T &b) { return a.x < b.x; });` | | O(N log N) |
| 같은 값의 원래 순서 유지 | `stable_sort(...)` | | O(N log N) |
| 뒤집기 | `reverse(v.begin(), v.end());` | 없음 | O(N) |

비교 함수 규칙: "a가 b보다 **앞에 와야 하면** true". **같은 값끼리는 반드시 false**(`<`, `>`만 사용, `<=`, `>=` 금지).

```cpp
// 다중 기준: 다르면 그 기준으로 결정
[](const T &a, const T &b) {
    if (a.score != b.score) return a.score > b.score;   // 내림차순
    return a.name < b.name;                             // 오름차순
}
```

## 최소·최대·합

| 기능 | 예시 | 반환 | 헤더 | 시간 |
|---|---|---|---|---|
| 두 값 | `min(a, b)`, `max(a, b)` | 값 (두 인자의 자료형이 같아야 함) | `<algorithm>` | O(1) |
| 여러 값 | `max({a, b, c})` | 값 | `<algorithm>` | O(개수) |
| 구간 최소/최대 | `*min_element(v.begin(), v.end())`, `*max_element(...)` | **반복자**(값은 `*`로) | `<algorithm>` | O(N) |
| 최대의 위치 | `max_element(v.begin(), v.end()) - v.begin()` | 인덱스 | | O(N) |
| 합 | `accumulate(v.begin(), v.end(), 0LL)` | 초기값의 자료형 | `<numeric>` | O(N) |
| 교환 | `swap(a, b)` | 없음 | `<utility>` | O(1) |

- `accumulate`의 결과 자료형은 **세 번째 인자(초기값)**가 정한다. `0`이면 `int`로 더해 오버플로한다 → **`0LL`**.
- `min(a, b)`에서 `int`와 `long long`을 섞으면 컴파일 오류 → `min<long long>(a, b)` 또는 형 변환.
- 빈 구간에 `*min_element`는 금지(`end()` 역참조).

## 탐색

| 기능 | 예시 | 반환 | 전제 | 시간 |
|---|---|---|---|---|
| 선형 찾기 | `find(v.begin(), v.end(), x)` | 첫 위치 반복자, 없으면 `v.end()` | 없음 | O(N) |
| 선형 개수 | `count(v.begin(), v.end(), x)` | 개수 | 없음 | O(N) |
| x 이상인 첫 위치 | `lower_bound(v.begin(), v.end(), x)` | 반복자, 없으면 `v.end()` | **정렬** | O(log N) |
| x 초과인 첫 위치 | `upper_bound(v.begin(), v.end(), x)` | 반복자, 없으면 `v.end()` | **정렬** | O(log N) |
| 존재 여부 | `binary_search(v.begin(), v.end(), x)` | `bool` | **정렬** | O(log N) |

```cpp
// 정렬된 v = {1, 3, 3, 3, 7}
int lb = lower_bound(v.begin(), v.end(), 3) - v.begin();   // 1
int ub = upper_bound(v.begin(), v.end(), 3) - v.begin();   // 4
int cnt = ub - lb;                                          // 3의 개수 = 3
// [lo, hi] 범위의 개수 = upper_bound(hi) - lower_bound(lo)
// x 이하의 개수 = upper_bound(x) - begin,  x 미만의 개수 = lower_bound(x) - begin
```

- `find`는 `<algorithm>`의 선형 탐색(O(N))과 `string::find`, `map::find`(멤버 함수)가 서로 다르다.
- `set`/`map`에는 `s.lower_bound(x)` 멤버 함수를 쓴다. `std::lower_bound(s.begin(), s.end(), x)`는 O(N).

## 채우기와 중복 제거

| 기능 | 예시 | 반환 | 시간 |
|---|---|---|---|
| 채우기 | `fill(v.begin(), v.end(), 0);` | 없음 | O(N) |
| 연속 번호 채우기 | `iota(v.begin(), v.end(), 0);` (`<numeric>`) → 0,1,2,… | 없음 | O(N) |
| 연속 중복 제거 | `unique(v.begin(), v.end())` | **새 끝 반복자** (크기는 그대로) | O(N) |
| 중복 제거 관용구 | `sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());` | | O(N log N) |

`unique`는 (1) **연속한** 중복만 제거하므로 먼저 정렬해야 하고, (2) 크기를 줄이지 않으므로 `erase`와 함께 써야 한다.

## 문자열 변환

| 기능 | 예시 | 반환 | 헤더 |
|---|---|---|---|
| 문자열 → `int` | `stoi("123")` | `int` (범위 초과나 숫자가 아니면 예외 → 런타임 오류) | `<string>` |
| 문자열 → `long long` | `stoll("12345678901")` | `long long` | `<string>` |
| 수 → 문자열 | `to_string(42)` | `string` | `<string>` |
| 숫자 문자 → 수 | `ch - '0'` | `int` | |
| 공백으로 나누기 | `stringstream ss(line); while (ss >> word) { }` | | `<sstream>` |

```cpp
#include <sstream>
string line = "12 apple 3.5";
stringstream ss(line);
int n; string w; double d;
ss >> n >> w >> d;                  // cin처럼 사용

// 특정 구분자로 나누기
stringstream ss2("a,b,c");
string token;
while (getline(ss2, token, ',')) { /* token = "a", "b", "c" */ }
```

- 10자리 이상의 수에 `stoi`를 쓰면 범위 초과 → `stoll`.
- 자릿수 합 등은 문자열로 읽어 `ch - '0'`으로 처리하는 편이 간단하다.

## 순열

```cpp
#include <algorithm>
sort(v.begin(), v.end());                        // 오름차순에서 시작
do {
    // v의 현재 순서 사용
} while (next_permutation(v.begin(), v.end()));  // 다음 순열로 바꾸고 true, 마지막이었으면 false
```

- 반환: `bool`. 한 번 호출 O(N). 전체 N!개 순회는 O(N! × N).
- 정렬하지 않고 시작하면 현재 순열 **이후**의 것만 본다. `do-while`이 아니면 첫 순열을 건너뛴다.
- 중복 원소가 있으면 서로 다른 순열만 만든다.
- N ≤ 10 정도까지만(10! ≈ 363만). **2^N과 N!을 혼동하지 말 것**: 2^12 = 4,096, 12! ≈ 4.8억.

---

## 입출력

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);

int n;            cin >> n;                  // 공백·줄바꿈을 건너뛰고 하나 읽음
string word;      cin >> word;               // 공백 전까지
string line;      getline(cin, line);        // 한 줄 전체(공백 포함)
cin >> n; cin.ignore(); getline(cin, line);  // >> 다음에 getline을 쓸 때는 줄바꿈을 버린다
while (cin >> x) { }                         // 입력 끝까지 읽기

cout << a << ' ' << b << '\n';               // endl 대신 '\n'
cout << fixed << setprecision(2) << 3.14159; // 3.14, <iomanip>
```

## 코드 뼈대

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    // 풀이

    cout << answer << '\n';
    return 0;
}
```

격자 BFS 뼈대:

```cpp
const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};
vector<vector<int>> dist(h, vector<int>(w, -1));
queue<pair<int, int>> q;
dist[sr][sc] = 0;
q.push({sr, sc});
while (!q.empty()) {
    int r = q.front().first, c = q.front().second;
    q.pop();
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
        dist[nr][nc] = dist[r][c] + 1;
        q.push({nr, nc});
    }
}
```

이분탐색 뼈대(자세한 설명은 [07단원](../units/07-binary-search/README.md)):

```cpp
// 가능한 최댓값 (O O O X X)          // 가능한 최솟값 (X X O O O)
while (lo < hi) {                      while (lo < hi) {
    mid = lo + (hi - lo + 1) / 2;          mid = lo + (hi - lo) / 2;
    if (ok(mid)) lo = mid;                 if (ok(mid)) hi = mid;
    else hi = mid - 1;                     else lo = mid + 1;
}                                      }
```
