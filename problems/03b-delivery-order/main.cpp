#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // d[i][j]: 장소 i에서 j로 가는 거리 (0-indexed, 출발지는 0번)
    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> d[i][j];

    // TODO: 0번에서 출발해 나머지를 모두 한 번씩 방문하는 최소 총 거리를 출력한다.

    return 0;
}
