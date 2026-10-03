#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<string> inside;  // 현재 건물 안에 있는 사람 (정렬된 상태로 유지됨)
    for (int i = 0; i < n; i++) {
        string name, action;
        cin >> name >> action;
        if (action == "in") {
            inside.insert(name);
        } else {
            inside.erase(name);
        }
    }

    cout << inside.size() << '\n';
    for (const string &name : inside) cout << name << '\n';
    return 0;
}
