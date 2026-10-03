#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MOD = 1000000007;

    int n, m;
    cin >> n >> m;
    vector<bool> broken(n + 1, false);  // broken[i]: i번 칸을 밟을 수 없는가
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        broken[b] = true;
    }

    // TODO: 0번 칸에서 n번 칸에 도착하는 방법의 수를 MOD로 나눈 나머지를 출력한다.

    return 0;
}
