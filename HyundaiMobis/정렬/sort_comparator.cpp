/*
sort의 Comparator 구성하기
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> vec_str;
    for (int num: numbers) vec_str.push_back(to_string(num));
    
    sort(vec_str.begin(), vec_str.end(), [](const string& a, const string& b){
        return a + b > b + a ; // lamda가 true이면 안바꾼다 false면 바꾼다 comparator는 전체vector에 대해 적용된다 >> 전반적인 규칙을 세운다고 생각해야함
    });
    
    if (vec_str[0] == "0") {
        return "0";
    }
    
    for(string s_num : vec_str){
        answer += s_num;
    }
    
    return answer;
}