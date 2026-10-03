#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<vector<long long>> v(h, vector<long long>(w));  // 0-indexed
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) cin >> v[i][j];

    // TODO: (0,0)에서 (h-1,w-1)까지 오른쪽/아래로만 이동할 때 합의 최댓값을 출력한다.

    return 0;
}
