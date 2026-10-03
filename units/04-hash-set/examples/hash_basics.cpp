// 04-hash_basics: unordered_map(빈도 세기)과 unordered_set(존재 여부)
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    // --- unordered_map: 키 -> 값. 평균 O(1) 삽입/조회 ---
    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    unordered_map<string, int> freq;
    for (const string &w : words) freq[w]++;   // 없는 키는 0으로 만들어진 뒤 증가

    cout << "apple = " << freq["apple"] << '\n';  // 3

    // 주의: []로 "조회"만 해도 없는 키가 새로 만들어진다.
    cout << "size before = " << freq.size() << '\n';   // 3
    if (freq["durian"] > 0) cout << "has durian\n";
    cout << "size after [] = " << freq.size() << '\n'; // 4 (durian: 0 이 생겼다)

    // 존재 여부만 확인할 때는 count 또는 find를 쓴다. (키를 만들지 않는다)
    if (freq.count("grape") == 0) cout << "no grape\n";
    auto it = freq.find("banana");
    if (it != freq.end()) cout << it->first << " = " << it->second << '\n';  // banana = 2
    cout << "size after count/find = " << freq.size() << '\n';  // 여전히 4

    // 전체 순회: 순서는 정해져 있지 않다(실행 환경마다 다를 수 있다).
    int total = 0;
    for (const auto &entry : freq) total += entry.second;
    cout << "total = " << total << '\n';  // 6

    // --- unordered_set: 값의 존재 여부만 관리 ---
    vector<int> nums = {7, 3, 9, 3, 7, 1};
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) {
            cout << "first duplicate = " << x << '\n';  // 3
            break;
        }
        seen.insert(x);
    }

    // 서로 다른 값의 개수
    unordered_set<int> distinct(nums.begin(), nums.end());
    cout << "distinct count = " << distinct.size() << '\n';  // 4

    seen.erase(7);  // 삭제
    cout << "has 7? " << (seen.count(7) ? "yes" : "no") << '\n';  // no
    return 0;
}
