// 03-permutations: next_permutation으로 모든 순서를 만들어 보기
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // 1) 모든 순열 출력. 반드시 "오름차순으로 정렬된 상태"에서 시작해야 전부 나온다.
    vector<int> v = {1, 2, 3};
    int count = 0;
    do {
        for (int x : v) cout << x << ' ';
        cout << '\n';
        count++;
    } while (next_permutation(v.begin(), v.end()));  // 다음 순열이 없으면 false
    cout << "count = " << count << '\n';  // 3! = 6

    // 2) 순서를 정하는 문제: 세 가지 작업의 순서에 따라 "대기 시간의 합"이 달라진다.
    //    i번째로 처리되는 작업의 대기 시간 = 앞선 작업들의 소요 시간 합
    vector<int> duration = {5, 1, 3};
    vector<int> order = {0, 1, 2};       // 작업 번호의 순열 (오름차순에서 시작)
    int best = -1;
    vector<int> best_order;
    do {
        int elapsed = 0, waiting = 0;
        for (int job : order) {
            waiting += elapsed;          // 이 작업이 시작되기까지 기다린 시간
            elapsed += duration[job];
        }
        if (best == -1 || waiting < best) {
            best = waiting;
            best_order = order;
        }
    } while (next_permutation(order.begin(), order.end()));

    cout << "min total waiting = " << best << " with order:";
    for (int job : best_order) cout << ' ' << job;
    cout << '\n';  // 5 with order: 1 2 0  (짧은 작업부터)

    // 3) 문자열에도 쓸 수 있다. 중복 문자가 있으면 서로 다른 순열만 만든다.
    string s = "aab";
    sort(s.begin(), s.end());
    do {
        cout << s << ' ';
    } while (next_permutation(s.begin(), s.end()));
    cout << '\n';  // aab aba baa

    // 참고: N개의 순열은 N!개. 8! = 40,320 / 10! = 3,628,800 / 11!부터는 약 4천만으로 위험.
    return 0;
}
