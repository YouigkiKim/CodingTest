#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> need(n), have(m);
    for (int &x : need) cin >> x;
    for (int &x : have) cin >> x;

    // TODO (필요한 헤더는 직접 추가한다)

    return 0;
}
