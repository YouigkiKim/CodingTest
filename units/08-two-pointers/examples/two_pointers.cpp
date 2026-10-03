// 08-two_pointers: 정렬된 배열의 양 끝에서 좁혀 오는 투 포인터
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 1) 정렬된 배열에서 합이 target인 두 수 찾기
    vector<int> a = {1, 3, 4, 6, 8, 11};
    int target = 10;

    int left = 0, right = (int)a.size() - 1;
    bool found = false;
    while (left < right) {                 // 서로 다른 두 원소여야 하므로 <
        int sum = a[left] + a[right];
        cout << "check " << a[left] << " + " << a[right] << " = " << sum << '\n';
        if (sum == target) {
            found = true;
            break;
        }
        if (sum < target) left++;          // 합이 작다 -> 작은 쪽을 키운다
        else right--;                      // 합이 크다 -> 큰 쪽을 줄인다
    }
    if (found) cout << "found: " << a[left] << " + " << a[right] << '\n';  // 4 + 6
    else cout << "not found\n";

    // 2) 정렬되어 있지 않다면 먼저 정렬한다. 예: 두 수의 합이 limit 이하인 쌍의 개수
    vector<int> w = {7, 2, 9, 4, 5};
    int limit = 10;
    sort(w.begin(), w.end());              // 2 4 5 7 9
    long long pairs = 0;
    left = 0;
    right = (int)w.size() - 1;
    while (left < right) {
        if (w[left] + w[right] <= limit) {
            // w[left]는 left+1 .. right 의 모든 원소와 짝이 될 수 있다(그들은 w[right] 이하).
            pairs += right - left;
            left++;
        } else {
            right--;                       // w[right]는 남은 누구와도 limit을 넘는다
        }
    }
    cout << "pairs with sum <= 10 : " << pairs << '\n';  // (2,4)(2,5)(2,7)(4,5) = 4

    // 3) 같은 방향으로 움직이는 두 포인터: 정렬된 두 배열 합치기
    vector<int> x = {1, 4, 9}, y = {2, 3, 10, 12};
    vector<int> merged;
    size_t i = 0, j = 0;
    while (i < x.size() && j < y.size()) {
        if (x[i] <= y[j]) merged.push_back(x[i++]);
        else merged.push_back(y[j++]);
    }
    while (i < x.size()) merged.push_back(x[i++]);
    while (j < y.size()) merged.push_back(y[j++]);
    cout << "merged:";
    for (int v : merged) cout << ' ' << v;  // 1 2 3 4 9 10 12
    cout << '\n';
    return 0;
}
