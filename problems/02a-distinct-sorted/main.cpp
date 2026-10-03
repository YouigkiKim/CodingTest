#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // TODO: 중복을 제거하고 오름차순으로 정렬한 뒤, 개수와 값들을 출력한다.

    return 0;
}
