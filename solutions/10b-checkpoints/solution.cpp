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
    vector<pair<int, int>> seg(n);  // (왼쪽 끝, 오른쪽 끝)
    for (auto &s : seg) cin >> s.first >> s.second;

    // 오른쪽 끝이 빠른 구간부터 처리한다.
    sort(seg.begin(), seg.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    int count = 0;
    bool has_point = false;
    int last = 0;  // 가장 최근에 설치한 지점의 좌표
    for (const auto &s : seg) {
        if (has_point && s.first <= last) continue;  // 이미 설치한 지점이 이 구간 안에 있다
        last = s.second;  // 이 구간의 오른쪽 끝에 새로 설치
        has_point = true;
        count++;
    }

    cout << count << '\n';
    return 0;
}
