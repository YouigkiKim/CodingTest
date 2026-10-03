#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    cin >> n >> target;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;  // 이미 오름차순으로 주어진다

    int left = 0, right = n - 1;
    long long best = -1;
    while (left < right) {
        long long sum = a[left] + a[right];
        long long diff = sum > target ? sum - target : target - sum;
        if (best == -1 || diff < best) best = diff;

        if (sum < target) {
            left++;   // 합을 키워야 한다 → 작은 쪽을 오른쪽으로
        } else if (sum > target) {
            right--;  // 합을 줄여야 한다 → 큰 쪽을 왼쪽으로
        } else {
            break;    // 차이 0보다 좋을 수 없다
        }
    }

    cout << best << '\n';
    return 0;
}
