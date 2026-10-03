// 07-parametric_search: "답을 정해 놓고 가능한지 판정"하며 경계를 찾는 이분탐색
#include <iostream>
#include <vector>
using namespace std;

// 하루에 최대 capacity만큼 처리할 수 있을 때, 작업들을 "순서대로" 끝내는 데 며칠이 걸리는가?
// (작업 하나가 capacity보다 크면 불가능 -> 매우 큰 수 반환)
int days_needed(const vector<int> &work, int capacity) {
    int days = 1, used = 0;
    for (int w : work) {
        if (w > capacity) return 1000000000;
        if (used + w > capacity) {  // 오늘은 더 못 한다 -> 다음 날로
            days++;
            used = 0;
        }
        used += w;
    }
    return days;
}

int main() {
    // 문제: 작업을 순서대로 처리해 3일 안에 끝내려면, 하루 처리량(capacity)이 최소 얼마여야 하는가?
    vector<int> work = {4, 2, 7, 1, 5, 3};
    int limit_days = 3;

    // 관찰: capacity가 클수록 필요한 날 수는 줄어든다(늘지 않는다).
    //   capacity : 7  8  9  10 11 12 ...
    //   days     : 4  3  3  3  3  2  ...   (3일 안에: 7은 불가능, 8부터는 계속 가능 -> 단조)
    for (int c = 7; c <= 12; c++) {
        cout << "capacity " << c << " -> " << days_needed(work, c) << " days\n";
    }

    // "가능한 최소 capacity"를 찾는다.
    // 불변식: lo-1 이하는 불가능(또는 범위 밖), hi는 가능.
    int lo = 1, hi = 0;
    for (int w : work) hi += w;      // 전부를 하루에 하는 capacity면 반드시 가능
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;            // 최솟값 탐색 -> 내림
        if (days_needed(work, mid) <= limit_days) {
            hi = mid;                // mid로 가능 -> mid도 후보로 남기고 더 작은 쪽을 본다
        } else {
            lo = mid + 1;            // mid로 불가능 -> mid는 버린다
        }
    }
    cout << "minimum capacity for " << limit_days << " days = " << lo << '\n';  // 8

    // 정리: (1) 답의 범위를 정한다 (2) 판정 함수를 만든다 (3) 판정 결과가 단조인지 확인한다
    //       (4) 최솟값을 찾는지 최댓값을 찾는지에 맞춰 경계를 갱신한다
    return 0;
}
