// 01-simulation_grid: 방향 배열(dr, dc)로 격자 위를 움직이는 시뮬레이션
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // 4행 5열 격자. '#'은 벽, '.'은 빈 칸. 행은 아래로, 열은 오른쪽으로 증가한다.
    vector<string> grid = {
        ".....",
        ".##..",
        ".....",
        "...#.",
    };
    int h = (int)grid.size();
    int w = (int)grid[0].size();

    // 명령 문자 -> 이동량. U(위)는 행이 1 줄어든다는 점에 주의.
    const string dirs = "UDLR";
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    int r = 0, c = 0;                 // 시작: 왼쪽 위
    string commands = "RRDDLDRRR";

    for (char cmd : commands) {
        int d = (int)dirs.find(cmd);  // 명령 문자가 몇 번째 방향인지
        int nr = r + dr[d];
        int nc = c + dc[d];

        // 순서가 중요: 범위 검사를 먼저 하고, 그다음에 grid[nr][nc]를 읽는다.
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
            cout << cmd << ": out of grid, stay at (" << r << ", " << c << ")\n";
            continue;
        }
        if (grid[nr][nc] == '#') {
            cout << cmd << ": wall, stay at (" << r << ", " << c << ")\n";
            continue;
        }
        r = nr;
        c = nc;
        cout << cmd << ": move to (" << r << ", " << c << ")\n";
    }

    cout << "final position = (" << r << ", " << c << ")\n";
    return 0;
}
