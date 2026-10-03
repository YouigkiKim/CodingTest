#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Team {
    string name;
    int solved;
    int penalty;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Team> teams(n);
    for (Team &t : teams) cin >> t.name >> t.solved >> t.penalty;

    // "a가 b보다 앞에 와야 하면 true". 기준을 우선순위대로 하나씩 비교한다.
    sort(teams.begin(), teams.end(), [](const Team &a, const Team &b) {
        if (a.solved != b.solved) return a.solved > b.solved;     // 많이 푼 팀 먼저
        if (a.penalty != b.penalty) return a.penalty < b.penalty; // 벌점 적은 팀 먼저
        return a.name < b.name;                                   // 이름 사전순
    });

    for (const Team &t : teams) cout << t.name << '\n';
    return 0;
}
