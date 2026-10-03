#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);  // 'S' 출발, 'E' 도착, '.' 빈 칸, '#' 벽 (0-indexed)
    for (string &row : grid) cin >> row;

    // TODO: S에서 E까지의 최소 이동 횟수(갈 수 없으면 -1)를 출력한다.
    //       필요한 헤더는 직접 추가한다.

    return 0;
}
