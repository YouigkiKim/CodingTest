#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> seg(n);  // (l, r), 양 끝 포함
    for (auto &s : seg) cin >> s.first >> s.second;

    // TODO: 모든 구간이 적어도 한 지점을 포함하도록 하는 최소 지점 수를 출력한다.

    return 0;
}
