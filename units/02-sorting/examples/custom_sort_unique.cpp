// 02-custom_sort_unique: 람다 비교 함수, 다중 기준 정렬, 중복 제거
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    int score;
    int age;
};

int main() {
    vector<Student> students = {
        {"kim", 90, 21}, {"lee", 85, 20}, {"park", 90, 19}, {"choi", 85, 20},
    };

    // 람다: [](인자) { 본문 } 형태의 이름 없는 함수.
    // 비교 함수는 "a가 b보다 앞에 와야 하면 true"를 반환한다.
    // 기준: 점수 내림차순 -> 나이 오름차순 -> 이름 사전순
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        if (a.score != b.score) return a.score > b.score;
        if (a.age != b.age) return a.age < b.age;
        return a.name < b.name;
    });

    for (const Student &s : students) {
        cout << s.name << ' ' << s.score << ' ' << s.age << '\n';
    }
    // park 90 19 / kim 90 21 / choi 85 20 / lee 85 20

    // 주의: 비교 함수에서 같은 값에 true를 반환하면 안 된다.
    //   return a.score >= b.score;   // 잘못된 예 (정의되지 않은 동작)

    // --- 중복 제거: sort 후 unique + erase ---
    vector<int> v = {4, 1, 4, 2, 1, 4};
    sort(v.begin(), v.end());                        // 1 1 2 4 4 4
    auto new_end = unique(v.begin(), v.end());       // 1 2 4 ? ? ?  (크기는 여전히 6)
    cout << "size right after unique = " << v.size() << '\n';
    v.erase(new_end, v.end());                       // 여기서 실제로 줄어든다
    cout << "after erase:";
    for (int x : v) cout << ' ' << x;                // 1 2 4
    cout << " (size " << v.size() << ")\n";
    return 0;
}
