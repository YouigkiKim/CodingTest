#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> len(n);
    for (long long &x : len) cin >> x;

    // TODO: 같은 길이의 조각을 k개 이상 만들 수 있는 최대 조각 길이(불가능하면 0)를 출력한다.

    return 0;
}
