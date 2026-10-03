#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    // TODO: 합이 k의 배수인 쌍 (i < j)의 개수를 구해 출력한다.

    return 0;
}
