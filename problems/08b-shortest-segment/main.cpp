#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long s;
    cin >> n >> s;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    // TODO: 합이 s 이상인 연속 구간의 최소 길이(없으면 0)를 출력한다.

    return 0;
}
