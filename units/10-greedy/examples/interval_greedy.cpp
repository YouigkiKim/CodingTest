// 10-interval_greedy: 회의실 배정 - 그럴듯한 기준들을 완전탐색과 비교해 반례 찾기
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using Meeting = pair<int, int>;  // (시작, 끝). 반열린 구간 [시작, 끝): 끝나는 시각에 다음 회의 시작 가능

// 주어진 순서대로 보면서, 직전에 고른 회의와 겹치지 않으면 고른다.
int pick_in_order(const vector<Meeting> &sorted) {
    int count = 0;
    vector<Meeting> chosen;
    for (const Meeting &m : sorted) {
        bool overlap = false;
        for (const Meeting &c : chosen) {
            if (m.first < c.second && c.first < m.second) overlap = true;  // 두 구간이 겹치는 조건
        }
        if (!overlap) {
            chosen.push_back(m);
            count++;
        }
    }
    return count;
}

int greedy_by_start(vector<Meeting> v) {     // 기준 A: 일찍 시작하는 회의부터
    sort(v.begin(), v.end());
    return pick_in_order(v);
}

int greedy_by_length(vector<Meeting> v) {    // 기준 B: 짧은 회의부터
    sort(v.begin(), v.end(), [](const Meeting &a, const Meeting &b) {
        return a.second - a.first < b.second - b.first;
    });
    return pick_in_order(v);
}

int greedy_by_end(vector<Meeting> v) {       // 기준 C: 일찍 끝나는 회의부터 (올바른 기준)
    sort(v.begin(), v.end(), [](const Meeting &a, const Meeting &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    int count = 0;
    bool any = false;
    int last_end = 0;
    for (const Meeting &m : v) {
        if (!any || m.first >= last_end) {   // 직전 회의가 끝난 뒤(같은 시각 포함)에 시작
            any = true;
            last_end = m.second;
            count++;
        }
    }
    return count;
}

// 완전탐색: 모든 부분집합을 확인한다 (회의 수가 작을 때만 가능, 2^N).
int brute_force(const vector<Meeting> &v) {
    int n = (int)v.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<Meeting> chosen;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) chosen.push_back(v[i]);
        }
        sort(chosen.begin(), chosen.end());
        bool ok = true;
        for (size_t i = 1; i < chosen.size(); i++) {
            if (chosen[i].first < chosen[i - 1].second) ok = false;
        }
        if (ok) best = max(best, (int)chosen.size());
    }
    return best;
}

void report(const string &label, const vector<Meeting> &v) {
    cout << label << '\n';
    cout << "  by start  : " << greedy_by_start(v) << '\n';
    cout << "  by length : " << greedy_by_length(v) << '\n';
    cout << "  by end    : " << greedy_by_end(v) << '\n';
    cout << "  brute     : " << brute_force(v) << "  (정답)\n";
}

int main() {
    // 반례 1: 일찍 시작하지만 아주 긴 회의가 나머지를 모두 막는다.
    report("case 1: [0,10) [1,2) [3,4) [5,6)", {{0, 10}, {1, 2}, {3, 4}, {5, 6}});

    // 반례 2: 짧은 회의 하나가 긴 회의 두 개 사이에 걸쳐 있다.
    report("case 2: [0,5) [4,6) [5,10)", {{0, 5}, {4, 6}, {5, 10}});

    // 일반적인 경우
    report("case 3: [1,4) [3,5) [0,6) [5,7) [3,8) [5,9) [6,10) [8,11)",
           {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}});
    return 0;
}
