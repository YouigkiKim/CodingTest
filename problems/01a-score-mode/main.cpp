#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> scores(n);
    for (int &x : scores) cin >> x;

    // TODO: 최빈 점수(동률이면 가장 작은 점수)와 그 횟수를 구해 출력한다.
    map<int, int> map;
    for(auto& val : scores) map[val]++;

    int large_count = 0;
    int ans = -1;
    for(auto& pair_ : map){
        if(ans == -1) ans = pair_.first;
        if(pair_.second > large_count){
            ans = pair_.first;
            large_count = pair_.second;
        }else if(pair_.second == large_count && ans > pair_.first){
            large_count = pair_.second;
            ans = pair_.first;
        }
    }
    std::cout << ans << " "<< large_count <<std::endl;

    return 0;
}
