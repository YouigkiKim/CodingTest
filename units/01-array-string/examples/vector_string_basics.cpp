// 01-vector_string_basics: vector와 string의 기본 사용법
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // --- vector: 크기가 변하는 배열 ---
    vector<int> v;               // 빈 vector
    v.push_back(3);              // 뒤에 추가 -> {3}
    v.push_back(1);              // {3, 1}
    v.push_back(4);              // {3, 1, 4}
    cout << "size = " << v.size() << ", first = " << v[0] << ", last = " << v.back() << '\n';

    vector<int> zeros(5, 0);     // 크기 5, 모두 0
    zeros[2] = 7;                // 인덱스는 0부터 size()-1까지

    // 인덱스로 순회: i의 자료형에 주의 (size()는 부호 없는 정수)
    for (int i = 0; i < (int)zeros.size(); i++) cout << zeros[i] << ' ';
    cout << '\n';

    // 2차원 vector: 3행 4열, 모두 0
    vector<vector<int>> grid(3, vector<int>(4, 0));
    grid[1][2] = 5;
    cout << "rows = " << grid.size() << ", cols = " << grid[0].size() << '\n';

    // --- string: 문자의 vector처럼 다룰 수 있다 ---
    string s = "hello";
    s += " world";                              // 이어 붙이기
    cout << s << " (length " << s.size() << ")\n";
    cout << "s[0] = " << s[0] << '\n';          // 문자 하나(char)
    cout << "substr(6, 5) = " << s.substr(6, 5) << '\n';  // 6번 위치부터 5글자 -> world

    // 문자는 정수처럼 계산할 수 있다.
    char c = 'd';
    int index = c - 'a';                        // 'a'->0, 'b'->1, ... 'd'->3
    char upper = (char)(c - 'a' + 'A');         // 대문자로
    int digit = '7' - '0';                      // 숫자 문자 -> 정수 7
    cout << "index = " << index << ", upper = " << upper << ", digit = " << digit << '\n';

    // 문자열 뒤집어 팰린드롬(앞뒤가 같은 문자열)인지 확인
    string word = "level";
    bool palindrome = true;
    for (int i = 0, j = (int)word.size() - 1; i < j; i++, j--) {
        if (word[i] != word[j]) palindrome = false;
    }
    cout << word << (palindrome ? " is" : " is not") << " a palindrome\n";
    return 0;
}
