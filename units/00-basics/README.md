# 00 환경과 C++ 기본

[전체 목차](../../README.md) · 다음: [01 배열·문자열·구현](../01-array-string/README.md) · [치트시트](../../docs/cheatsheet.md)

예상 소요: 2~3시간 · 문제 없음(예제 실행과 변형으로 연습)

## 학습 목표

- C++ 파일을 컴파일하고 실행하는 과정을 직접 해 본다.
- 표준 입력을 읽고 표준 출력으로 쓰는 코딩테스트의 기본 형태를 익힌다.
- `int`와 `long long`의 범위, 정수 나눗셈을 구분한다.
- 함수에 값을 넘기는 두 방식(복사, 참조)과 `const`의 의미를 설명할 수 있다.

## 선행 지식

다른 언어로 변수·조건문·반복문·함수를 써 본 경험. C++ 경험은 없어도 된다.

## 1. 컴파일과 실행

C++은 소스 코드(`.cpp`)를 **컴파일**해서 실행 파일을 만든 뒤 실행한다.

```bash
g++ -std=c++17 -Wall -Wextra hello.cpp -o hello   # 컴파일 (hello 라는 실행 파일 생성)
./hello                                            # 실행
./hello < input.txt                                # 파일 내용을 표준 입력으로 넣어 실행
```

- `-std=c++17`: C++17 문법 사용
- `-Wall -Wextra`: 실수하기 쉬운 코드에 경고를 출력. **경고는 읽고 없애는 습관**을 들인다.

이 코스에서는 위 과정을 `./ct`가 대신 해 준다.

```bash
./ct example 00-hello_io     # 예제 하나를 컴파일하고 실행
./ct example 00              # 00단원의 예제를 모두 실행
```

VS Code에서는 파일을 연 상태로 `Ctrl+Shift+B`(빌드), `F5`(디버깅)를 쓸 수 있다.

## 2. 프로그램의 기본 형태

```cpp
#include <iostream>   // cin, cout
#include <vector>     // 필요한 헤더를 하나씩 명시한다
using namespace std;  // std::cout 대신 cout 으로 쓰기 위함

int main() {
    ios::sync_with_stdio(false);  // 입출력 속도 향상 (두 줄을 세트로 외운다)
    cin.tie(nullptr);

    int n;
    cin >> n;                     // 입력
    cout << n * 2 << '\n';        // 출력
    return 0;
}
```

- `cin >> x`는 공백과 줄바꿈을 건너뛰고 값 하나를 읽는다. 그래서 "한 줄에 N개"든 "N줄에 하나씩"이든 같은 코드로 읽힌다.
- 줄바꿈은 `endl` 대신 `'\n'`을 쓴다. `endl`은 매번 버퍼를 비워 출력이 많을 때 매우 느리다.

## 3. 자료형

| 자료형 | 저장하는 값 | 범위(대략) | 언제 |
|---|---|---|---|
| `int` | 정수 | ±2.1×10^9 | 기본 |
| `long long` | 큰 정수 | ±9.2×10^18 | 합·곱·개수가 21억을 넘을 수 있을 때 |
| `double` | 실수 | 유효숫자 약 15자리 | 평균, 비율 |
| `char` | 문자 하나 | `'a'` | 문자 처리 |
| `bool` | 참/거짓 | `true`, `false` | 플래그 |
| `string` | 문자열 | `"abc"` | `<string>` 필요 |

가장 흔한 사고는 **`int` 오버플로**다.

```cpp
int a = 100000, b = 100000;
long long wrong = a * b;        // int끼리 먼저 곱해져 이미 오버플로
long long right = 1LL * a * b;  // 1LL을 먼저 곱해 long long으로 계산 -> 10000000000
```

그리고 정수끼리의 나눗셈은 소수점 아래를 버린다: `7 / 2 == 3`, `7 / 2.0 == 3.5`, `7 % 2 == 1`.

## 4. 조건문과 반복문

```cpp
if (x > 0) { ... } else if (x == 0) { ... } else { ... }

for (int i = 0; i < n; i++) { ... }   // i = 0, 1, ..., n-1  (n번 반복)
while (조건) { ... }                   // 조건이 참인 동안 반복
```

- `break`: 반복문 탈출, `continue`: 이번 반복만 건너뜀.
- 같음 비교는 `==`. `=`는 대입이다(`if (x = 0)`은 버그).

## 5. 함수, 값 전달과 참조, const

```cpp
void by_value(int x)             { x += 1; }  // 복사본을 바꾼다 -> 호출한 쪽은 그대로
void by_reference(int &x)        { x += 1; }  // 원본을 바꾼다
long long sum_of(const vector<int> &v);        // 복사 없이 읽기만 한다
```

| 형태 | 복사 발생 | 원본 수정 | 언제 |
|---|---|---|---|
| `T x` | O | X | `int`, `char` 같은 작은 값 |
| `T &x` | X | O | 함수가 원본을 바꿔야 할 때 |
| `const T &x` | X | X | `vector`, `string`을 읽기만 할 때 (기본 선택) |

`vector`를 값으로 넘기면 호출할 때마다 **전체가 복사**된다. 10만 개짜리를 10만 번 넘기면 그것만으로 시간초과다.

## 작은 입력으로 따라가기

`hello_io` 예제의 입력은 다음과 같다.

```
4
10 20 30 40
hello
this is a whole line
```

| 코드 | 읽은 것 | 입력에 남은 것 |
|---|---|---|
| `cin >> n` | `4` | `\n10 20 30 40\nhello\n...` |
| `cin >> a[i]` ×4 | `10 20 30 40` | `\nhello\nthis is ...` |
| `cin >> word` | `hello` | `\nthis is a whole line\n` |
| `cin.ignore()` | 줄바꿈 한 글자를 버림 | `this is a whole line\n` |
| `getline(cin, line)` | `this is a whole line` | (없음) |

`cin.ignore()`가 없으면 `getline`은 `hello` 뒤에 남은 줄바꿈까지만 읽어 **빈 문자열**을 얻는다.

## 예제

| 예제 | 내용 | 실행 |
|---|---|---|
| [hello_io.cpp](examples/hello_io.cpp) | 입력 읽기, `getline`, 출력 | `./ct example 00-hello_io` |
| [types_and_loops.cpp](examples/types_and_loops.cpp) | 자료형, 나눗셈, 조건문, 반복문 | `./ct example 00-types_and_loops` |
| [functions_refs.cpp](examples/functions_refs.cpp) | 값 전달, 참조, const | `./ct example 00-functions_refs` |

**직접 해 보기**: 예제를 실행한 뒤 코드를 고쳐 보고 결과를 예측해 본다.

1. `types_and_loops.cpp`에서 `1LL *`를 지우면 `big`은 어떻게 출력되는가? (컴파일 경고도 확인)
2. `hello_io.cpp`에서 `cin.ignore();`를 지우면 `line`은 무엇이 되는가?
3. `functions_refs.cpp`의 `double_all`에서 `int &x`를 `int x`로 바꾸면?
4. `./ct example 00-hello_io --interactive`로 직접 입력을 타이핑해 본다(입력 끝은 `Ctrl+D`).

## 시간·공간 감각

- 단순 연산 약 1억(10^8) 번이 1초 안팎이라는 감각을 기준으로 삼는다(환경에 따라 다르다).
- `int` 하나는 4바이트, `long long`은 8바이트. `int` 100만 개 ≈ 4MB.
- 자세한 표는 [복잡도 가이드](../../docs/complexity.md) 참고.

## 자주 하는 실수와 반례

| 실수 | 반례 / 증상 |
|---|---|
| `int`끼리 곱한 뒤 `long long`에 대입 | `100000 * 100000` → 음수나 엉뚱한 값 |
| 정수 나눗셈으로 평균 계산 | `(3 + 4) / 2` → 3 (3.5가 아님) |
| `cin >>` 뒤 바로 `getline` | 빈 줄을 읽음 |
| `endl` 남용 | 출력 20만 줄에서 시간초과 |
| `if (x = 5)` | 항상 참, x가 5로 바뀜 |
| 큰 `vector`를 값으로 전달 | 느려짐(논리는 맞지만 시간초과) |
| 변수 초기화 누락 (`int sum;`) | 실행할 때마다 다른 값 |

## 완료 체크리스트

- [ ] `./ct doctor`가 모두 OK로 나온다.
- [ ] 세 예제를 실행하고, 출력의 각 줄이 왜 그렇게 나오는지 설명할 수 있다.
- [ ] "직접 해 보기" 1~3의 결과를 실행 전에 예측했고 맞았다.
- [ ] `int`와 `long long`의 대략적인 범위를 외웠다.
- [ ] `const vector<int> &v`의 `const`와 `&`가 각각 무엇을 뜻하는지 말할 수 있다.
- [ ] 빈 파일에서 "정수 N과 N개의 수를 읽어 합을 출력"하는 프로그램을 보지 않고 작성할 수 있다.
