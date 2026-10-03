#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long s;
    cin >> n >> s;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    int best = 0;       // 0 = 아직 조건을 만족하는 구간을 못 찾음
    int left = 0;
    long long sum = 0;  // 현재 구간 [left, right]의 합
    for (int right = 0; right < n; right++) {
        sum += a[right];
        // 조건을 만족하는 동안 왼쪽을 줄여 가며 더 짧은 구간을 찾는다.
        while (sum >= s) {
            int len = right - left + 1;
            if (best == 0 || len < best) best = len;
            sum -= a[left];
            left++;
        }
    }

    cout << best << '\n';
    return 0;
}
