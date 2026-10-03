#include <string>
#include <vector>
#include <iostream>
using namespace std;

void dfs(const string word, const vector<char> char_list, int& number, string compared, int& ans ){
    if(ans != 0 ) return ;
    for(char c : char_list){
        number++;
        if(compared + c == word){
            ans = number;
        }
        if(compared.size() + 1 == 5) continue;
        dfs(word, char_list, number, compared + c, ans);
    }
}
int solution(string word) {
    int answer = 0;
    int number = 0;
    vector<char> char_list{'A','E', 'I', 'O', 'U'};
    
    string compared = "";
    
    dfs(word, char_list, number, compared, answer);
    return answer;
}