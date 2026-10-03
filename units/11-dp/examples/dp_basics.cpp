// 11-dp_basics: 상태·점화식·초기값·계산 순서로 푸는 DP 세 가지
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 비교용: 메모 없이 재귀로 구하는 계단 오르기 (같은 계산을 지수적으로 반복한다)
long long calls = 0;
long long stairs_naive(int n) {
    calls++;
    if (n <= 1) return 1;
    return stairs_naive(n - 1) + stairs_naive(n - 2);
}

int main() {
    // ---------------------------------------------------------------
    // 1) 계단 오르기: 한 번에 1칸 또는 2칸. n번 칸에 도착하는 방법의 수
    //    상태    ways[i] = i번 칸에 도착하는 방법의 수
    //    점화식  ways[i] = ways[i-1] + ways[i-2]   (직전 위치는 i-1 또는 i-2)
    //    초기값  ways[0] = 1, ways[1] = 1
    //    순서    i = 2 .. n
    int n = 30;
    vector<long long> ways(n + 1, 0);
    ways[0] = 1;
    ways[1] = 1;
    for (int i = 2; i <= n; i++) ways[i] = ways[i - 1] + ways[i - 2];
    cout << "stairs(30) = " << ways[n] << " with " << n - 1 << " additions\n";

    long long naive = stairs_naive(n);
    cout << "naive recursion gives " << naive << " after " << calls << " calls\n";

    // ---------------------------------------------------------------
    // 2) 격자 경로 수: 오른쪽/아래로만 이동, '#'은 지나갈 수 없다.
    //    상태    paths[r][c] = (0,0)에서 (r,c)까지의 경로 수
    //    점화식  paths[r][c] = paths[r-1][c] + paths[r][c-1]   (벽이면 0)
    //    초기값  paths[0][0] = 1
    //    순서    위에서 아래로, 왼쪽에서 오른쪽으로
    vector<string> grid = {
        "....",
        ".#..",
        "....",
    };
    int h = (int)grid.size(), w = (int)grid[0].size();
    vector<vector<long long>> paths(h, vector<long long>(w, 0));
    paths[0][0] = 1;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == '#') {
                paths[r][c] = 0;
                continue;
            }
            if (r > 0) paths[r][c] += paths[r - 1][c];
            if (c > 0) paths[r][c] += paths[r][c - 1];
        }
    }
    cout << "path table:\n";
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) cout << ' ' << paths[r][c];
        cout << '\n';
    }
    cout << "paths to bottom-right = " << paths[h - 1][w - 1] << '\n';  // 4

    // ---------------------------------------------------------------
    // 3) 이웃하지 않게 골라 최대 합: 연속한 두 원소를 함께 고를 수 없다.
    //    상태    best[i] = 앞의 i개만 고려했을 때의 최대 합
    //    점화식  best[i] = max(best[i-1],            // i번째를 고르지 않는다
    //                          best[i-2] + a[i-1])   // i번째를 고른다 (i-1번째는 못 고름)
    //    초기값  best[0] = 0, best[1] = max(0, a[0])
    vector<int> a = {6, 7, 1, 30, 8, 2, 4};
    int m = (int)a.size();
    vector<long long> best(m + 1, 0);
    best[1] = max(0, a[0]);
    for (int i = 2; i <= m; i++) {
        best[i] = max(best[i - 1], best[i - 2] + a[i - 1]);
    }
    cout << "best table:";
    for (long long x : best) cout << ' ' << x;   // 0 6 7 7 37 37 39 41
    cout << '\n';
    cout << "max non-adjacent sum = " << best[m] << '\n';  // 7 + 30 + 4 = 41
    return 0;
}
