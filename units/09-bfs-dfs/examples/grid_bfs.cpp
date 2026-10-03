// 09-grid_bfs: 격자를 그래프로 보고 BFS로 최단 거리 구하기
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    // '#': 벽, '.': 길. 왼쪽 위 (0,0)에서 각 칸까지의 최소 이동 횟수를 구한다.
    vector<string> grid = {
        "..#....",
        ".##.##.",
        "....#..",
        ".##...#",
        "...#...",
    };
    int h = (int)grid.size();
    int w = (int)grid[0].size();

    // 4방향 이동량: 아래, 위, 오른쪽, 왼쪽
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    vector<vector<int>> dist(h, vector<int>(w, -1));  // -1 = 미방문
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;  // 1) 범위
            if (grid[nr][nc] == '#') continue;                      // 2) 벽
            if (dist[nr][nc] != -1) continue;                       // 3) 이미 방문
            dist[nr][nc] = dist[r][c] + 1;                          // 큐에 넣을 때 방문 처리
            q.push({nr, nc});
        }
    }

    // 거리 지도 출력 (벽은 ##, 도달 불가는 ..)
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == '#') cout << " ##";
            else if (dist[r][c] == -1) cout << " ..";
            else cout << (dist[r][c] < 10 ? "  " : " ") << dist[r][c];
        }
        cout << '\n';
    }
    cout << "shortest distance to bottom-right = " << dist[h - 1][w - 1] << '\n';
    return 0;
}
