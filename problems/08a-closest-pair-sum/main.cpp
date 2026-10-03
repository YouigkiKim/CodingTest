#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    cin >> n >> target;
    vector<long long> a(n);  // 오름차순으로 주어진다
    for (long long &x : a) cin >> x;

    // TODO: 서로 다른 두 원소의 합과 target의 차이(절댓값)의 최솟값을 출력한다.

    return 0;
}
