// 00-types_and_loops: 자료형의 범위, 정수 나눗셈, 조건문, 반복문
#include <iostream>
#include <string>
using namespace std;

int main() {
    // --- 자료형 ---
    int a = 2000000000;            // int: 약 ±2.1 * 10^9 까지
    long long big = 1LL * a * 3;   // 1LL을 먼저 곱해 long long으로 계산 (int끼리 곱하면 오버플로)
    double avg = 7 / 2.0;          // 한쪽이 실수면 실수 나눗셈
    int quotient = 7 / 2;          // 정수끼리 나누면 소수점 아래를 버린다 -> 3
    int remainder = 7 % 2;         // 나머지 -> 1
    char grade = 'A';              // 문자 하나는 작은따옴표
    bool ok = (a > 0);             // true / false
    string name = "cpp";           // 문자열은 큰따옴표

    cout << "big = " << big << '\n';
    cout << "7 / 2 = " << quotient << ", 7 % 2 = " << remainder << ", 7 / 2.0 = " << avg << '\n';
    cout << "grade = " << grade << ", ok = " << ok << ", name = " << name << '\n';

    // --- 조건문 ---
    int score = 85;
    if (score >= 90) {
        cout << "A\n";
    } else if (score >= 80) {
        cout << "B\n";
    } else {
        cout << "C\n";
    }

    // --- for: 반복 횟수가 정해져 있을 때 ---
    int total = 0;
    for (int i = 1; i <= 10; i++) {  // i = 1, 2, ..., 10
        if (i % 2 == 0) continue;    // 짝수는 건너뛴다
        total += i;
    }
    cout << "1~10 odd sum = " << total << '\n';  // 1+3+5+7+9 = 25

    // --- while: 조건이 참인 동안 반복 ---
    int x = 100, steps = 0;
    while (x > 1) {
        x /= 2;  // 100 -> 50 -> 25 -> 12 -> 6 -> 3 -> 1
        steps++;
    }
    cout << "halving steps = " << steps << '\n';  // 6

    // --- 이중 반복문 ---
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= i; j++) cout << '*';
        cout << '\n';
    }
    return 0;
}
