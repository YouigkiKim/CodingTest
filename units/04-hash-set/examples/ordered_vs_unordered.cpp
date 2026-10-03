// 04-ordered_vs_unordered: map/set(정렬 유지)과 unordered_map/set(순서 없음)의 차이
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    // --- map: 키가 항상 정렬된 상태로 유지된다. 삽입/조회 O(log N) ---
    map<string, int> score;
    score["kim"] = 80;
    score["choi"] = 95;
    score["lee"] = 70;

    cout << "map iterates in key order:\n";
    for (const auto &entry : score) {
        cout << "  " << entry.first << " " << entry.second << '\n';  // choi, kim, lee
    }
    cout << "smallest key = " << score.begin()->first << '\n';    // choi
    cout << "largest key = " << score.rbegin()->first << '\n';    // lee

    // --- set: 중복 없이 정렬된 값의 모음 ---
    set<int> s = {40, 10, 30, 10, 20};      // 10은 한 번만 들어간다
    cout << "set:";
    for (int x : s) cout << ' ' << x;        // 10 20 30 40
    cout << '\n';

    s.insert(25);
    s.erase(10);
    cout << "min = " << *s.begin() << ", max = " << *s.rbegin() << '\n';  // 20, 40

    // 정렬된 구조라서 "x 이상인 가장 작은 값"을 O(log N)에 찾을 수 있다.
    auto it = s.lower_bound(26);             // 26 이상인 첫 원소
    if (it != s.end()) cout << "first >= 26 : " << *it << '\n';   // 30
    it = s.lower_bound(100);
    if (it == s.end()) cout << "nothing >= 100\n";

    // --- 어떤 것을 고를까 ---
    // unordered_map / unordered_set : 빈도·존재 여부만 필요할 때 (평균 O(1))
    // map / set                     : 정렬된 순회, 최소/최대, "x 이상인 첫 값"이 필요할 때 (O(log N))
    // 정렬된 vector + 이분탐색      : 데이터가 바뀌지 않을 때 가장 가볍다
    return 0;
}
