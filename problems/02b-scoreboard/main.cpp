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

    // TODO: 규칙에 따라 정렬한 뒤 팀 이름을 한 줄에 하나씩 출력한다.

    return 0;
}
