/*
vector.empty(): 벡터 비어있는지 검사
map 초기화 시 {pair<int,int>{k,v}}  할때 동일 k값으로 반복 초기화
*/

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    vector<int> mark1{1,2,3,4,5};
    vector<int> mark2{2,1,2,3,2,4,2,5};
    vector<int> mark3{3,3,1,1,2,2,4,4,5,5};
    int size_1 = mark1.size();
    int size_2 = mark2.size();
    int size_3 = mark3.size();
    
    map<int, int> count{pair<int,int>{1,0}, pair<int,int>{2,0}, pair<int,int>{3,0}};
    
    for (int i=0 ; i < answers.size() ; i++){
        int& ans = answers[i];
        if (ans == mark1[i % size_1]) {count[1]++;}
        if (ans == mark2[i % size_2]) {count[2]++;}
        if (ans == mark3[i % size_3]) {count[3]++;}
    }
    
    int max_count =0;
    std::vector<int> max_people;
    for(const auto& count_per_person : count){
        if(count_per_person.second > max_count) {
            max_count = count_per_person.second;
            max_people.clear();
            max_people.push_back(count_per_person.first);
        }else if(count_per_person.second == max_count){
            max_people.push_back(count_per_person.first);
        }
    }
    
    answer = max_people;
    return answer;
}