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

    int sr = 0, sc = 0, er = 0, ec = 0;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == 'S') { sr = r; sc = c; }
            if (grid[r][c] == 'E') { er = r; ec = c; }
        }
    }

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    // dist[r][c] = 출발점에서 (r, c)까지의 최소 이동 횟수, -1이면 아직 방문 안 함
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = cur.first + dr[d];
            int nc = cur.second + dc[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            q.push({nr, nc});
        }
    }

    cout << dist[er][ec] << '\n';  // 도달하지 못했다면 -1 그대로
    return 0;
}
