#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    sort(a.begin(), a.end());
    // unique는 연속한 중복을 뒤로 밀고 '새로운 끝' 반복자를 돌려준다. 크기는 erase로 줄인다.
    a.erase(unique(a.begin(), a.end()), a.end());

    cout << a.size() << '\n';
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
