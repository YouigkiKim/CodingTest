#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    cin >> n >> target;

    // seen[v] = 지금까지(현재 원소보다 앞에서) 값 v가 나온 횟수
    unordered_map<long long, int> seen;
    seen.reserve(n * 2);

    long long pairs = 0;  // 최대 N(N-1)/2 ≈ 2×10^10 → int로는 부족
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        auto it = seen.find(target - x);  // []를 쓰면 없는 키가 계속 생긴다
        if (it != seen.end()) pairs += it->second;
        seen[x]++;
    }

    cout << pairs << '\n';
    return 0;
}
