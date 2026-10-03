#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<vector<long long>> v(h, vector<long long>(w));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) cin >> v[i][j];

    // best[i][j] = (0,0)에서 (i,j)까지 오는 경로의 최대 합
    vector<vector<long long>> best(h, vector<long long>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i == 0 && j == 0) {
                best[i][j] = v[i][j];
            } else if (i == 0) {
                best[i][j] = best[i][j - 1] + v[i][j];  // 첫 행: 왼쪽에서만 올 수 있다
            } else if (j == 0) {
                best[i][j] = best[i - 1][j] + v[i][j];  // 첫 열: 위에서만 올 수 있다
            } else {
                best[i][j] = max(best[i - 1][j], best[i][j - 1]) + v[i][j];
            }
        }
    }

    cout << best[h - 1][w - 1] << '\n';
    return 0;
}
