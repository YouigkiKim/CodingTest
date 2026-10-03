#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);  // 'F' 불, '.' 빈 칸, '#' 방화벽 (0-indexed)
    for (string &row : grid) cin >> row;

    // TODO (필요한 헤더는 직접 추가한다)

    return 0;
}
