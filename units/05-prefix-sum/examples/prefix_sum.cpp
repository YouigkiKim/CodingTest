// 05-prefix_sum: 누적합 배열을 만들고 구간 합을 O(1)에 구하기
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {3, 1, 4, 1, 5, 9};
    int n = (int)a.size();

    // prefix[i] = a[0] + ... + a[i-1]  (앞에서부터 i개의 합)
    // 크기를 n+1로 잡고 prefix[0] = 0 으로 두는 것이 핵심.
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];

    cout << "a      :";
    for (int x : a) cout << ' ' << x;
    cout << "\nprefix :";
    for (long long x : prefix) cout << ' ' << x;   // 0 3 4 8 9 14 23
    cout << '\n';

    // 반열린 구간 [l, r) (0-indexed, l 포함 r 미포함)의 합 = prefix[r] - prefix[l]
    int l = 1, r = 4;  // a[1] + a[2] + a[3] = 1 + 4 + 1
    cout << "sum of [1, 4) = " << prefix[r] - prefix[l] << '\n';  // 6

    // 1-indexed 닫힌 구간 [L, R] (문제에서 흔한 형태)의 합 = prefix[R] - prefix[L-1]
    int L = 2, R = 5;  // 2번째~5번째 = 1 + 4 + 1 + 5
    cout << "sum of 2nd..5th = " << prefix[R] - prefix[L - 1] << '\n';  // 11

    // 전체 합, 원소 하나도 같은 식으로 구해진다.
    cout << "total = " << prefix[n] - prefix[0] << '\n';              // 23
    cout << "a[3] alone = " << prefix[4] - prefix[3] << '\n';         // 1

    // 응용: 길이 3인 구간 중 합이 가장 큰 구간
    int len = 3;
    long long best = prefix[len] - prefix[0];
    int best_start = 0;
    for (int start = 1; start + len <= n; start++) {
        long long cur = prefix[start + len] - prefix[start];
        if (cur > best) {
            best = cur;
            best_start = start;
        }
    }
    cout << "best window of length 3 starts at " << best_start << " with sum " << best << '\n';  // 3, 15
    return 0;
}
