#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    // TODO: 질문에 빠르게 답할 수 있도록 전처리한다.

    for (int i = 0; i < q; i++) {
        int l, r;  // 1-indexed, 양 끝 포함
        cin >> l >> r;

        // TODO: a_l + ... + a_r 을 출력한다.
    }

    return 0;
}
