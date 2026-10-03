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

    // TODO: 질문에 빠르게 답할 수 있도록 준비한다.

    for (int i = 0; i < q; i++) {
        int lo, hi;
        cin >> lo >> hi;

        // TODO: lo 이상 hi 이하인 값의 개수를 출력한다.
    }

    return 0;
}
