#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long capacity;
    cin >> n >> capacity;
    vector<long long> w(n);
    for (long long &x : w) cin >> x;

    sort(w.begin(), w.end());  // 가벼운 상자부터

    int count = 0;
    long long total = 0;
    for (long long x : w) {
        if (total + x > capacity) break;  // 이후 상자는 더 무거우므로 더 볼 필요가 없다
        total += x;
        count++;
    }

    cout << count << '\n';
    return 0;
}
