#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool is_balanced(const string &s) {
    stack<char> st;
    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
            continue;
        }
        // 닫는 괄호: 짝이 될 여는 괄호가 스택 맨 위에 있어야 한다.
        if (st.empty()) return false;  // top() 전에 반드시 비었는지 확인
        char open = st.top();
        st.pop();
        if (ch == ')' && open != '(') return false;
        if (ch == ']' && open != '[') return false;
        if (ch == '}' && open != '{') return false;
    }
    return st.empty();  // 닫히지 않은 괄호가 남으면 실패
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
