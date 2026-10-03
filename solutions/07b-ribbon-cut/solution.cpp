#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 길이 len짜리 조각을 k개 이상 만들 수 있는가?
bool can_make(const vector<long long> &a, long long len, long long k) {
    long long pieces = 0;
    for (long long x : a) pieces += x / len;
    return pieces >= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    // 불변식: lo는 "가능"(0은 '만들 수 없음'을 뜻하는 답으로 취급), hi + 1은 "불가능".
    long long lo = 0;
    long long hi = *max_element(a.begin(), a.end());
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;  // 올림: lo = mid로 갱신하므로 무한 루프 방지
        if (can_make(a, mid, k)) {
            lo = mid;       // mid는 가능 → 더 긴 길이를 시도
        } else {
            hi = mid - 1;   // mid는 불가능 → 더 짧게
        }
    }

    cout << lo << '\n';
    return 0;
}
