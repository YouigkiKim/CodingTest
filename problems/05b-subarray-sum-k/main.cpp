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

    // TODO: 합이 정확히 k인 연속 구간의 개수를 출력한다.
    //       필요한 헤더는 직접 추가한다.

    return 0;
}
