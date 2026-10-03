#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 점수는 0~100이므로 크기 101짜리 빈도 배열이면 충분하다.
    vector<int> cnt(101, 0);
    for (int i = 0; i < n; i++) {
        int score;
        cin >> score;
        cnt[score]++;
    }

    // 작은 점수부터 보면서 '더 클 때만' 갱신하면 동률일 때 가장 작은 점수가 남는다.
    int best = 0;
    for (int s = 1; s <= 100; s++) {
        if (cnt[s] > cnt[best]) best = s;
    }

    cout << best << ' ' << cnt[best] << '\n';
    return 0;
}
