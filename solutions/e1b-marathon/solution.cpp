#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, string>> runners(n);  // (초 단위 기록, 이름)
    for (int i = 0; i < n; i++) {
        string name, t;
        cin >> name >> t;  // t = "HH:MM:SS" (자리 수 고정)
        int hh = stoi(t.substr(0, 2));
        int mm = stoi(t.substr(3, 2));
        int ss = stoi(t.substr(6, 2));
        runners[i] = {hh * 3600 + mm * 60 + ss, name};
    }

    // pair의 기본 비교: first(기록) 오름차순, 같으면 second(이름) 오름차순
    sort(runners.begin(), runners.end());

    int winner = runners[0].first;
    for (const auto &r : runners) {
        cout << r.second << ' ' << (r.first - winner) << '\n';
    }
    return 0;
}
