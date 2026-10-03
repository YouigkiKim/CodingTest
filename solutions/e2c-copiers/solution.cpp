#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// time초 동안 만들 수 있는 사본이 k장 이상인가?
bool enough(const vector<long long> &t, long long time, long long k) {
    long long copies = 0;
    for (long long x : t) {
        copies += time / x;
        if (copies >= k) return true;  // 일찍 끝내면 합이 불필요하게 커지지 않는다
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> t(n);
    for (long long &x : t) cin >> x;

    // 가장 빠른 복사기 한 대만 써도 min(t) * k초면 끝난다 → 답의 상한.
    long long lo = 1;
    long long hi = *min_element(t.begin(), t.end()) * k;
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (enough(t, mid, k)) {
            hi = mid;      // mid초면 충분 → 더 짧은 시간을 시도 (mid도 후보로 남긴다)
        } else {
            lo = mid + 1;  // 부족 → 더 긴 시간이 필요
        }
    }

    cout << lo << '\n';
    return 0;
}
