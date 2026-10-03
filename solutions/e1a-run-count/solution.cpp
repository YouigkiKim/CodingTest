#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    string out;
    size_t i = 0;
    while (i < s.size()) {
        size_t j = i;
        while (j < s.size() && s[j] == s[i]) j++;  // [i, j)가 같은 문자의 연속 구간
        out += s[i];
        out += to_string(j - i);
        i = j;
    }

    cout << out << '\n';
    return 0;
}
