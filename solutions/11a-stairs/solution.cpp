#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MOD = 1000000007;

    int n, m;
    cin >> n >> m;
    vector<bool> broken(n + 1, false);
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        broken[b] = true;
    }

    // ways[i] = 바닥(0)에서 i번 칸까지 오는 방법의 수 (mod)
    vector<int> ways(n + 1, 0);
    ways[0] = 1;  // 아무것도 하지 않는 방법 1가지
    for (int i = 1; i <= n; i++) {
        if (broken[i]) continue;  // 밟을 수 없는 칸은 0으로 둔다
        long long sum = ways[i - 1];
        if (i >= 2) sum += ways[i - 2];
        if (i >= 3) sum += ways[i - 3];
        ways[i] = static_cast<int>(sum % MOD);
    }

    cout << ways[n] << '\n';
    return 0;
}
