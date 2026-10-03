#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    string cmd;
    cin >> h >> w >> cmd;

    // 방향 번호: 0=동, 1=남, 2=서, 3=북 (오른쪽으로 돌 때마다 +1)
    const int dr[4] = {0, 1, 0, -1};
    const int dc[4] = {1, 0, -1, 0};

    int r = 1, c = 1, dir = 0;
    int ignored = 0;

    for (char ch : cmd) {
        if (ch == 'R') {
            dir = (dir + 1) % 4;
        } else if (ch == 'L') {
            dir = (dir + 3) % 4;  // -1 대신 +3: 음수 나머지를 피한다
        } else {  // 'F'
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 1 || nr > h || nc < 1 || nc > w) {
                ignored++;
            } else {
                r = nr;
                c = nc;
            }
        }
    }

    cout << r << ' ' << c << ' ' << ignored << '\n';
    return 0;
}
