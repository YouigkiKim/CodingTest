#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);  // grid[r][c]: '#' 땅, '.' 바다 (0-indexed)
    for (string &row : grid) cin >> row;

    // TODO: 상하좌우로 이어진 '#' 덩어리의 개수를 출력한다.
    //       필요한 헤더는 직접 추가한다.

    return 0;
}
