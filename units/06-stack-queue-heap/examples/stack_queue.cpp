// 06-stack_queue: stack(나중에 넣은 것 먼저)과 queue(먼저 넣은 것 먼저)
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int main() {
    // --- stack: LIFO ---
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    cout << "stack pops:";
    while (!st.empty()) {          // top()/pop() 전에는 반드시 empty() 확인
        int x = st.top();          // 값 읽기
        st.pop();                  // 제거 (pop은 값을 반환하지 않는다)
        cout << ' ' << x;
    }
    cout << '\n';                  // 3 2 1

    // --- queue: FIFO ---
    queue<string> q;
    q.push("first");
    q.push("second");
    q.push("third");
    cout << "queue pops:";
    while (!q.empty()) {
        string s = q.front();
        q.pop();
        cout << ' ' << s;
    }
    cout << '\n';                  // first second third

    // --- 스택 응용 1: 한 종류 괄호의 짝 검사 ---
    string expr = "(()())(";
    stack<char> open;
    bool ok = true;
    for (char ch : expr) {
        if (ch == '(') {
            open.push(ch);
        } else {
            if (open.empty()) { ok = false; break; }  // 닫을 괄호가 없다
            open.pop();
        }
    }
    if (!open.empty()) ok = false;  // 닫히지 않은 괄호가 남았다
    cout << expr << " -> " << (ok ? "balanced" : "not balanced") << '\n';  // not balanced

    // --- 스택 응용 2: 되돌리기(backspace). '#'은 직전 문자를 지운다 ---
    string typed = "abc##d#e";
    string result;                 // string도 push_back/pop_back/back으로 스택처럼 쓸 수 있다
    for (char ch : typed) {
        if (ch == '#') {
            if (!result.empty()) result.pop_back();
        } else {
            result.push_back(ch);
        }
    }
    cout << typed << " -> " << result << '\n';  // ae

    // --- 큐 응용: 줄 서서 차례로 처리, 덜 끝난 작업은 맨 뒤로 ---
    queue<int> jobs;               // 남은 작업량
    for (int w : {3, 1, 2}) jobs.push(w);
    cout << "round-robin:";
    while (!jobs.empty()) {
        int left = jobs.front() - 1;   // 한 번에 1만큼 처리
        jobs.pop();
        cout << ' ' << left;
        if (left > 0) jobs.push(left); // 남았으면 다시 줄의 맨 뒤로
    }
    cout << '\n';                  // 2 0 1 1 0 0
    return 0;
}
