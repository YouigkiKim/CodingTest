#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long target;
    cin >> n >> target;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    // TODO: a[i] + a[j] == target (i < j)인 쌍의 개수를 출력한다.
    //       N이 크다는 점과 답의 크기에 주의한다. 필요한 헤더는 직접 추가한다.

    return 0;
}
