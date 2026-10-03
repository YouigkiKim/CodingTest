#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> s(n + 1);  // s[1..n]: 돌의 점수 (1-indexed)
    for (int i = 1; i <= n; i++) cin >> s[i];

    // TODO (필요한 헤더는 직접 추가한다)

    return 0;
}
