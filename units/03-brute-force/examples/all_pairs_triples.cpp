// 03-all_pairs_triples: 모든 쌍 / 모든 세 개 조합을 빠짐없이, 중복 없이 검사하기
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {8, 3, 5, 1, 7};
    int n = (int)a.size();

    // 1) 모든 쌍 (i < j): 차이가 가장 작은 쌍 찾기
    //    j를 i+1부터 시작하면 (i, j)와 (j, i)를 두 번 보지 않고, 자기 자신과도 짝짓지 않는다.
    int best_diff = -1, bi = 0, bj = 0;
    int pair_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pair_count++;
            int diff = a[i] > a[j] ? a[i] - a[j] : a[j] - a[i];
            if (best_diff == -1 || diff < best_diff) {
                best_diff = diff;
                bi = i;
                bj = j;
            }
        }
    }
    cout << "pairs checked = " << pair_count << '\n';  // 5*4/2 = 10
    cout << "closest pair: " << a[bi] << ", " << a[bj] << " (diff " << best_diff << ")\n";  // 8, 7

    // 2) 모든 세 개 조합 (i < j < k): 합이 정확히 15인 조합의 수
    int triples = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (a[i] + a[j] + a[k] == 15) {
                    triples++;
                    cout << "  " << a[i] << " + " << a[j] << " + " << a[k] << " = 15\n";
                }
            }
        }
    }
    cout << "triples with sum 15 = " << triples << '\n';  // 1 ({3, 5, 7})

    // 3) 가능한 "답"을 전부 시도하기: x*x + y*y == 50인 양의 정수 (x <= y) 찾기
    for (int x = 1; x * x <= 50; x++) {
        for (int y = x; x * x + y * y <= 50; y++) {
            if (x * x + y * y == 50) cout << "x = " << x << ", y = " << y << '\n';  // (1,7), (5,5)
        }
    }
    return 0;
}
