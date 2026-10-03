#include <string>
#include <vector>
#include <numeric>

using namespace std;
int point_to_idx(int point){
    return point + 100;
}
int solution(vector<vector<int>> lines) {
    int answer = 0;
    vector<int> mask(200, 0);

    for (int i=0; i<lines.size() ; i++){
        for(int j=lines[i][0]; j<lines[i][1] ; j++){
            mask[point_to_idx(j)] ++;
        }
    }

    for (int m : mask){
        if (m > 1) answer++;
    }

    return answer;
}