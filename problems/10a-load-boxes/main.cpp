#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long capacity;
    cin >> n >> capacity;
    vector<long long> weight(n);
    for (long long &x : weight) cin >> x;

    // TODO: 무게 합이 capacity 이하가 되도록 실을 수 있는 상자의 최대 개수를 출력한다.

    return 0;
}
