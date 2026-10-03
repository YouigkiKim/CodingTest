#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);  // 두 수의 합이 int 범위를 넘을 수 있으므로 long long
    for (long long &x : a) cin >> x;

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  // j를 i+1부터: 각 쌍을 한 번만 센다
            if ((a[i] + a[j]) % k == 0) count++;
        }
    }

    cout << count << '\n';
    return 0;
}
