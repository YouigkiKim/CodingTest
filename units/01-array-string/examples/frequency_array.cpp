// 01-frequency_array: 값(또는 문자)을 인덱스로 써서 개수를 세는 빈도 배열
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // 1) 문자열에서 각 알파벳이 몇 번 나오는지 센다.
    string s = "mississippi";
    vector<int> cnt(26, 0);          // cnt[0] = 'a'의 개수, ..., cnt[25] = 'z'의 개수
    for (char ch : s) cnt[ch - 'a']++;

    cout << "letters in " << s << ":";
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) cout << ' ' << (char)('a' + i) << '=' << cnt[i];
    }
    cout << '\n';  // i=4 m=1 p=2 s=4

    // 2) 두 문자열이 애너그램(문자 구성이 같은지)인지 확인한다.
    string a = "listen", b = "silent";
    vector<int> diff(26, 0);
    for (char ch : a) diff[ch - 'a']++;
    for (char ch : b) diff[ch - 'a']--;
    bool anagram = true;
    for (int x : diff) {
        if (x != 0) anagram = false;
    }
    cout << a << " / " << b << (anagram ? " : anagram\n" : " : not anagram\n");

    // 3) 값의 범위가 작은 정수의 빈도 (주사위 눈 1~6)
    vector<int> dice = {3, 6, 1, 3, 3, 6};
    vector<int> face(7, 0);          // 인덱스 1~6을 쓰기 위해 크기 7
    for (int d : dice) face[d]++;
    int best = 1;
    for (int f = 2; f <= 6; f++) {
        if (face[f] > face[best]) best = f;   // '>' 이므로 동률이면 작은 눈이 남는다
    }
    cout << "most frequent face = " << best << " (" << face[best] << " times)\n";  // 3 (3 times)
    return 0;
}
