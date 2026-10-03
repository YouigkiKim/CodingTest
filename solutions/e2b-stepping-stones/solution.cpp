#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];

    // best[i] = i번 돌에 서 있을 때까지 얻을 수 있는 최대 점수 합. best[0] = 강가(점수 0).
    vector<long long> best(n + 1);
    best[0] = 0;
    best[1] = s[1];  // 1번 돌은 강가에서만 올 수 있다
    for (int i = 2; i <= n; i++) {
        best[i] = max(best[i - 1], best[i - 2]) + s[i];
    }

    cout << best[n] << '\n';
    return 0;
}
