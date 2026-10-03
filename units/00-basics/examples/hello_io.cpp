// 00-hello_io: 표준 입력을 읽고 표준 출력으로 쓰는 가장 기본적인 형태
// 실행: ./ct example 00-hello_io   (hello_io.in 파일이 입력으로 들어간다)
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // 입출력 속도를 높이는 두 줄. 코딩테스트에서는 습관처럼 넣는다.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) 공백/줄바꿈으로 구분된 값은 >> 로 하나씩 읽는다.
    int n;
    cin >> n;

    // 2) n개의 정수를 vector에 읽는다.
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // 3) 단어 하나(공백 없는 문자열)를 읽는다.
    string word;
    cin >> word;

    // 4) 공백이 포함된 한 줄 전체를 읽으려면 getline.
    //    직전의 >> 가 줄바꿈 문자를 남겨 두므로 먼저 버려야 한다.
    cin.ignore();
    string line;
    getline(cin, line);

    long long sum = 0;  // 합은 커질 수 있으므로 long long
    for (int x : a) sum += x;

    cout << "n = " << n << '\n';
    cout << "sum = " << sum << '\n';
    cout << "word = " << word << '\n';
    cout << "line = [" << line << "]\n";  // '\n'은 endl보다 빠르다
    return 0;
}
