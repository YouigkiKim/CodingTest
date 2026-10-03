#include <string>
#include <vector>

using namespace std;

vector<pair<int,int>> find_yellow_combination(int yellow){
    if (yellow == 1) return vector<pair<int,int>>{pair{1,1}};
    if (yellow == 2) return vector<pair<int,int>>{pair{2,1}};
    if (yellow == 3) return vector<pair<int,int>>{pair{3,1}};
    
    vector<pair<int,int>> combination;
    for(int i = 1 ; i*i <= yellow ; i++){ // Problem: 등호 붙이기 
        int residual = yellow % i;
        if (residual == 0){
            combination.push_back(pair<int,int>{yellow / i, i});
        }
    }
    return combination;
}

pair<int, int> find_dimension(vector<pair<int,int>> yellow_combination, int brown){
    for(const auto& dim : yellow_combination){
        if( dim.first * 2 + dim.second * 2 + 4 == brown ) return dim;
    }
}

vector<int> solution(int brown, int yellow) {
    // 가로 > 세로
    // 갈색 격자 수brown 은 8이상 5000이하
    //yellow는 1이상 2000000이하 자연수
    int w_y, h_y; 
    int w_b, h_b;
    // yellow의 직사각형 조합 찾기
    vector<pair<int, int>> yellow_combination = find_yellow_combination(yellow);
    // brown을 이용해 정확한 combination 찾기
    pair<int, int> yellow_dimension = find_dimension(yellow_combination, brown);

    vector<int> answer;
    answer.push_back(yellow_dimension.first + 2);
    answer.push_back(yellow_dimension.second + 2);
    
    return answer;
}