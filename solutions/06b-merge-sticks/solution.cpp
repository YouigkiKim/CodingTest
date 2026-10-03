#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 최소 힙: 가장 작은 값이 top에 온다. (기본 priority_queue는 최대 힙)
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        pq.push(x);
    }

    long long total = 0;
    while (pq.size() > 1) {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();
        total += a + b;
        pq.push(a + b);  // 합친 막대는 다시 후보가 된다
    }

    cout << total << '\n';
    return 0;
}
