#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> d[i][j];

    // 방문 순서 후보: 장소 1..n-1 (0번이 출발지). 오름차순에서 시작해야 모든 순열을 돈다.
    vector<int> order(n - 1);
    iota(order.begin(), order.end(), 1);

    long long best = -1;
    do {
        long long cost = 0;
        int cur = 0;
        for (int next : order) {
            cost += d[cur][next];
            cur = next;
        }
        if (best == -1 || cost < best) best = cost;
    } while (next_permutation(order.begin(), order.end()));

    cout << best << '\n';
    return 0;
}
