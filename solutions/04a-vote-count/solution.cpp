#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<string, int> votes;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        votes[name]++;  // 없는 키는 0으로 만들어진 뒤 1 증가한다
    }

    string best_name;
    int best_count = 0;
    for (const auto &entry : votes) {
        const string &name = entry.first;
        int count = entry.second;
        // unordered_map은 순서가 없으므로 동률 규칙을 직접 비교한다.
        if (count > best_count || (count == best_count && name < best_name)) {
            best_name = name;
            best_count = count;
        }
    }

    cout << best_name << ' ' << best_count << '\n';
    return 0;
}
