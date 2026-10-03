#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    cin >> n >> m;

    // seen[r] = 지금까지 (누적합 % m)이 r이었던 위치의 수
    unordered_map<long long, int> seen;
    seen.reserve(n * 2);
    seen[0] = 1;  // 아무것도 더하지 않은 상태

    long long prefix_mod = 0;
    long long count = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prefix_mod = (prefix_mod + x) % m;
        // 누적합의 나머지가 같은 두 위치 사이의 구간은 합이 m의 배수다.
        int &same = seen[prefix_mod];
        count += same;
        same++;
    }

    cout << count << '\n';
    return 0;
}
