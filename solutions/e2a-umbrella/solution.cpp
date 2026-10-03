#include <algorithm>
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

    sort(need.begin(), need.end());
    sort(have.begin(), have.end());

    // 요구가 작은 사람부터, 쓸 수 있는 가장 짧은 우산을 준다.
    int matched = 0;  // 다음에 우산을 받을 사람의 인덱스이자 지금까지 받은 사람 수
    for (int j = 0; j < m && matched < n; j++) {
        if (have[j] >= need[matched]) matched++;
        // 아니라면 이 우산은 남은 누구에게도 맞지 않으므로 버린다.
    }

    cout << matched << '\n';
    return 0;
}
