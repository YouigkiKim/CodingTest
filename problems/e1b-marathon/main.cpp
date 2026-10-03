#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> name(n), record(n);  // record[i]는 "HH:MM:SS"
    for (int i = 0; i < n; i++) cin >> name[i] >> record[i];

    // TODO (필요한 헤더는 직접 추가한다)

    return 0;
}
