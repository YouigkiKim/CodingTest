#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (string &row : grid) cin >> row;

    // dist[r][c] = 그 칸에 불이 붙는 시각, -1이면 아직 안 붙음
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;

    // 모든 불씨를 시각 0으로 한꺼번에 큐에 넣고 시작한다.
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == 'F') {
                dist[r][c] = 0;
                q.push({r, c});
            }
        }
    }

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};
    int last = 0;  // 가장 늦게 불이 붙은 시각
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        last = dist[cur.first][cur.second];  // BFS는 시각 순서대로 꺼내므로 마지막 값이 최대
        for (int d = 0; d < 4; d++) {
            int nr = cur.first + dr[d];
            int nc = cur.second + dc[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (grid[nr][nc] != '.' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            q.push({nr, nc});
        }
    }

    // 불이 닿지 않은 빈 칸이 있으면 -1
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == '.' && dist[r][c] == -1) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }

    cout << last << '\n';
    return 0;
}
