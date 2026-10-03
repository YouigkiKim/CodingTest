/*
string answer = ""; // 빈 문자열 선언

answer 이 빈배열인데 바로 0,1 로 접근하려함

try catch문법
try{
}
catch(exception& e){
    cout << e.what() << endl;
}

*/
#include <string>
#include <iostream>
#include <exception>
#include <vector>

using namespace std;
string LEFT = "left";
string RIGHT = "right";
string UP = "up";
string DOWN = "down";

void move(const string& keyinput, vector<int>& coordinate){
    if (keyinput == LEFT){
        coordinate[0]--;
    }else if(keyinput == RIGHT){
        coordinate[0]++;
    }else if(keyinput == UP){
        coordinate[1]++;
    }else if(keyinput==DOWN){
        coordinate[1]--;
    }
}

vector<int> solution(vector<string> keyinput, vector<int> board) {
    vector<int> answer;
    answer.push_back(0);
    answer.push_back(0);
    int max_x = static_cast<int>(board[0] / 2);
    int max_y = static_cast<int>(board[1] / 2);
    for(const auto& in : keyinput){
        move(in, answer);
        if (abs(answer[0]) > max_x){
            if (answer[0] > 0){
                answer[0] = max_x;
            }else{
                answer[0] = -max_x;
            }
        }
        if(abs(answer[1]) > max_y){
            if(answer[1] > 0){
                answer[1] = max_y;
            }else{
                answer[1] = -max_y;
            }
        }
    }
    return answer;
}