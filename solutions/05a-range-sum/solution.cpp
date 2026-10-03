#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // prefix[i] = 앞에서부터 i개의 합 (prefix[0] = 0)
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        // 1-indexed 닫힌 구간 [l, r]의 합 = (앞 r개의 합) - (앞 l-1개의 합)
        cout << prefix[r] - prefix[l - 1] << '\n';
    }
    return 0;
}
