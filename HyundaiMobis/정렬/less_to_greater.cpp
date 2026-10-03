#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<vector<int>> truncated_array;
    for(int vec_idx=0; vec_idx < commands.size() ; vec_idx++){
        truncated_array.push_back(vector<int>());
        for(int i = commands[vec_idx][0]-1 ; i <= commands[vec_idx][1]-1 ; i++){
            truncated_array[vec_idx].push_back(array[i]);
        }
        // less "부터", greater "부터"
        sort(truncated_array[vec_idx].begin(), truncated_array[vec_idx].end(), less<>()); //오름차순 작은수 => 큰수, 내림차순 큰수 => 작은수
    }
    
    vector<int> answer;
    for(int i = 0 ; i < commands.size(); i++){
        answer.push_back( truncated_array[i][commands[i][2] -1 ] );
    }
    return answer;
}