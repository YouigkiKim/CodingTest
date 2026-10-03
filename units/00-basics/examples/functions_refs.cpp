// 00-functions_refs: 함수, 값 전달과 참조 전달, const
#include <iostream>
#include <vector>
using namespace std;

// 값 전달: x는 호출한 쪽 변수의 "복사본"이다. 여기서 바꿔도 원본은 그대로.
void add_one_by_value(int x) {
    x += 1;
}

// 참조 전달(&): x는 원본의 "다른 이름"이다. 여기서 바꾸면 원본이 바뀐다.
void add_one_by_reference(int &x) {
    x += 1;
}

// const 참조: 복사하지 않고(빠르다), 수정도 하지 않겠다(안전하다)는 약속.
// 큰 vector나 string을 읽기만 할 때의 기본 형태.
long long sum_of(const vector<int> &v) {
    long long total = 0;
    for (int x : v) total += x;
    // v.push_back(1);  // 컴파일 오류: const 참조는 수정할 수 없다
    return total;
}

// 참조로 받아 원본 vector를 수정하는 함수
void double_all(vector<int> &v) {
    for (int &x : v) x *= 2;  // 원소도 참조(int&)로 받아야 실제 값이 바뀐다
}

int main() {
    int n = 10;
    add_one_by_value(n);
    cout << "after by_value: " << n << '\n';      // 10 (그대로)
    add_one_by_reference(n);
    cout << "after by_reference: " << n << '\n';  // 11

    vector<int> v = {1, 2, 3};
    cout << "sum = " << sum_of(v) << '\n';        // 6
    double_all(v);
    cout << "sum after double_all = " << sum_of(v) << '\n';  // 12

    // 범위 기반 for에서도 같은 규칙이 적용된다.
    cout << "copies times 10:";
    for (int x : v) {        // x는 원소의 복사본
        x *= 10;             // 복사본을 바꾸므로 v는 그대로
        cout << ' ' << x;    // 20 40 60
    }
    cout << '\n';
    cout << "v[0] after copy loop = " << v[0] << '\n';  // 2
    for (int &x : v) x = 0;  // 참조이므로 v가 바뀐다
    cout << "v[0] after ref loop = " << v[0] << '\n';   // 0

    const int LIMIT = 100;   // const 변수: 값을 바꿀 수 없다
    cout << "LIMIT = " << LIMIT << '\n';
    return 0;
}
