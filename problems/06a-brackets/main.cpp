#include <iostream>
#include <string>
using namespace std;

// TODO: s가 올바른 괄호 문자열이면 true를 반환하도록 구현한다.
//       필요한 헤더는 직접 추가한다.
bool is_balanced(const string &s) {
    (void)s;  // 구현하면서 이 줄은 지운다 (사용하지 않는 매개변수 경고 방지용)
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << (is_balanced(s) ? "YES" : "NO") << '\n';
    }
    return 0;
}
