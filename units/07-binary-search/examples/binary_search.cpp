// 07-binary_search: 정렬된 배열에서의 이분탐색 직접 구현과 lower_bound/upper_bound
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// target의 위치(인덱스)를 반환, 없으면 -1. 닫힌 구간 [lo, hi]를 절반씩 줄인다.
int find_index(const vector<int> &a, int target) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;      // (lo + hi) / 2 의 오버플로 방지형
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1; // 답은 오른쪽 절반에
        else hi = mid - 1;                 // 답은 왼쪽 절반에
    }
    return -1;
}

// target "이상"인 첫 위치를 반환 (없으면 a.size()). lower_bound를 직접 구현한 것.
// 반열린 구간 [lo, hi): 답 후보가 lo..hi 범위에 있다.
int first_at_least(const vector<int> &a, int target) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= target) hi = mid;    // mid가 조건을 만족 -> 더 왼쪽에 답이 있을 수 있다
        else lo = mid + 1;                 // mid는 조건 불만족 -> mid는 답이 아니다
    }
    return lo;
}

int main() {
    vector<int> a = {1, 3, 3, 3, 7, 9, 12};  // 반드시 정렬되어 있어야 한다

    cout << "find 7  -> index " << find_index(a, 7) << '\n';   // 4
    cout << "find 8  -> index " << find_index(a, 8) << '\n';   // -1

    cout << "first >= 3  -> index " << first_at_least(a, 3) << '\n';   // 1
    cout << "first >= 8  -> index " << first_at_least(a, 8) << '\n';   // 5
    cout << "first >= 99 -> index " << first_at_least(a, 99) << '\n';  // 7 (= size, 없음)

    // 표준 라이브러리: 반복자를 반환하므로 begin()을 빼서 인덱스로 바꾼다.
    int lb = (int)(lower_bound(a.begin(), a.end(), 3) - a.begin());  // 3 이상인 첫 위치 -> 1
    int ub = (int)(upper_bound(a.begin(), a.end(), 3) - a.begin());  // 3 초과인 첫 위치 -> 4
    cout << "lower_bound(3) = " << lb << ", upper_bound(3) = " << ub << '\n';
    cout << "count of 3 = " << ub - lb << '\n';                      // 3

    // 존재 여부만 필요하면 binary_search (bool 반환)
    cout << "has 9? " << (binary_search(a.begin(), a.end(), 9) ? "yes" : "no") << '\n';

    // x 이하인 가장 큰 값: upper_bound의 바로 앞 원소
    int x = 8;
    auto it = upper_bound(a.begin(), a.end(), x);
    if (it != a.begin()) cout << "largest <= 8 : " << *(it - 1) << '\n';  // 7
    return 0;
}
