#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    sort(a.begin(), a.end());  // 이분탐색의 전제: 정렬

    while (q--) {
        int lo, hi;
        cin >> lo >> hi;
        // lower_bound(lo): lo 이상인 첫 위치, upper_bound(hi): hi 초과인 첫 위치
        auto first = lower_bound(a.begin(), a.end(), lo);
        auto last = upper_bound(a.begin(), a.end(), hi);
        cout << (last - first) << '\n';  // 반열린 구간 [first, last)의 길이
    }
    return 0;
}
