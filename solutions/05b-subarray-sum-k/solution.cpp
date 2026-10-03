#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    // seen[s] = 지금까지 누적합이 s였던 위치의 수. 아무것도 더하지 않은 상태(0)를 미리 넣는다.
    unordered_map<long long, int> seen;
    seen.reserve(n * 2);
    seen[0] = 1;

    long long prefix = 0;
    long long count = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prefix += x;
        // prefix - (이전 누적합) == k  <=>  이전 누적합 == prefix - k
        auto it = seen.find(prefix - k);
        if (it != seen.end()) count += it->second;
        seen[prefix]++;
    }

    cout << count << '\n';
    return 0;
}
