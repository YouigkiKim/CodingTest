// 08-sliding_window: 고정 길이 창과, 조건에 따라 늘었다 줄었다 하는 창
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {2, 1, 5, 1, 3, 2};
    int n = (int)a.size();

    // 1) 고정 길이 k: 창을 한 칸 밀 때 "새로 들어온 값은 더하고, 빠진 값은 뺀다".
    int k = 3;
    long long window = 0;
    for (int i = 0; i < k; i++) window += a[i];   // 첫 창 [0, k)
    long long best = window;
    cout << "window [0,3) sum = " << window << '\n';
    for (int right = k; right < n; right++) {
        window += a[right];          // 오른쪽 원소가 들어오고
        window -= a[right - k];      // 왼쪽 원소가 나간다
        cout << "window [" << right - k + 1 << "," << right + 1 << ") sum = " << window << '\n';
        if (window > best) best = window;
    }
    cout << "max sum of length 3 = " << best << '\n';  // 5 + 1 + 3 = 9

    // 2) 가변 길이: 합이 limit 이하인 가장 긴 구간 (모든 원소가 양수일 때만 성립하는 방법)
    //    오른쪽을 늘리다가 조건이 깨지면, 다시 만족할 때까지 왼쪽을 줄인다.
    long long limit = 7;
    long long sum = 0;
    int left = 0, longest = 0;
    for (int right = 0; right < n; right++) {
        sum += a[right];
        while (sum > limit) {        // 조건 위반 -> 왼쪽을 당긴다
            sum -= a[left];
            left++;
        }
        // 이제 [left, right]는 조건을 만족하는, right로 끝나는 가장 긴 구간
        if (right - left + 1 > longest) longest = right - left + 1;
    }
    cout << "longest segment with sum <= 7 : " << longest << '\n';  // [1, 5, 1] 또는 [1, 3, 2] -> 3

    // 3) 음수가 있으면 위 방법이 틀릴 수 있다.
    //    b = {4, 5, -8, 1}, limit = 2: 정답은 전체 구간(합 2, 길이 4).
    //    하지만 위 방법은 [4, 5]에서 합이 limit을 넘자 왼쪽 원소를 버리고,
    //    뒤에 나오는 -8이 합을 다시 줄여 준다는 사실을 반영하지 못한다.
    vector<int> b = {4, 5, -8, 1};
    limit = 2;
    sum = 0;
    left = 0;
    longest = 0;
    for (int right = 0; right < (int)b.size(); right++) {
        sum += b[right];
        while (left <= right && sum > limit) {
            sum -= b[left];
            left++;
        }
        if (right - left + 1 > longest) longest = right - left + 1;
    }
    cout << "with negatives, sliding window says " << longest << " but the answer is 4\n";
    return 0;
}
