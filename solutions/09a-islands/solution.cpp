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

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    vector<vector<bool>> visited(h, vector<bool>(w, false));
    int islands = 0;

    for (int sr = 0; sr < h; sr++) {
        for (int sc = 0; sc < w; sc++) {
            if (grid[sr][sc] != '#' || visited[sr][sc]) continue;

            // 아직 방문하지 않은 땅 = 새로운 섬. 여기서 BFS로 섬 전체를 방문 처리한다.
            islands++;
            queue<pair<int, int>> q;
            visited[sr][sc] = true;  // 큐에 넣을 때 방문 처리
            q.push({sr, sc});
            while (!q.empty()) {
                pair<int, int> cur = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = cur.first + dr[d];
                    int nc = cur.second + dc[d];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;  // 범위 검사 먼저
                    if (grid[nr][nc] != '#' || visited[nr][nc]) continue;
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }

    cout << islands << '\n';
    return 0;
}
