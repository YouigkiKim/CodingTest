#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> names(n);
    for (string &s : names) cin >> s;

    // TODO: 최다 득표자(동률이면 사전순으로 가장 앞선 이름)와 득표수를 출력한다.
    //       필요한 헤더는 직접 추가한다.

    return 0;
}
