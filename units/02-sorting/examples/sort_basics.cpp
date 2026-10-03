// 02-sort_basics: sort의 기본, 내림차순, pair 정렬
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void print(const string &label, const vector<int> &v) {
    cout << label << ":";
    for (int x : v) cout << ' ' << x;
    cout << '\n';
}

int main() {
    vector<int> v = {5, 2, 8, 2, 9, 1};

    sort(v.begin(), v.end());                    // 오름차순 (기본)
    print("ascending", v);                       // 1 2 2 5 8 9

    sort(v.begin(), v.end(), greater<int>());    // 내림차순
    print("descending", v);                      // 9 8 5 2 2 1

    reverse(v.begin(), v.end());                 // 뒤집기
    print("reversed", v);                        // 1 2 2 5 8 9

    // 일부 구간만 정렬: [begin+1, begin+4) = 인덱스 1, 2, 3
    vector<int> part = {9, 7, 5, 3, 1};
    sort(part.begin() + 1, part.begin() + 4);
    print("partial", part);                      // 9 3 5 7 1

    // pair는 first를 먼저 비교하고, 같으면 second를 비교한다.
    vector<pair<int, string>> people = {{30, "kim"}, {25, "lee"}, {30, "choi"}};
    sort(people.begin(), people.end());
    cout << "pairs:";
    for (const auto &p : people) cout << " (" << p.first << ", " << p.second << ")";
    cout << '\n';                                // (25, lee) (30, choi) (30, kim)

    // 문자열도 정렬할 수 있다 (문자 단위로 사전순).
    string s = "banana";
    sort(s.begin(), s.end());
    cout << "sorted string: " << s << '\n';      // aaabnn

    // 최솟값/최댓값만 필요하면 정렬 없이 O(N)으로 구한다.
    vector<int> w = {4, 9, 2};
    cout << "min = " << *min_element(w.begin(), w.end())
         << ", max = " << *max_element(w.begin(), w.end()) << '\n';
    return 0;
}
