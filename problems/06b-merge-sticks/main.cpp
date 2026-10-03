#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> len(n);
    for (long long &x : len) cin >> x;

    // TODO: 모든 막대를 하나로 합치는 최소 총비용을 출력한다.
    //       필요한 헤더는 직접 추가한다.

    return 0;
}
