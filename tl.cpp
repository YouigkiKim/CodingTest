#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

size_t MAX_ITER=256;

size_t RES_TIME_IDX=0;
size_t RES_IS_YELLOW_IDX=1;

size_t GREEN_IDX=0;
size_t YELLOW_IDX=1;
size_t RED_IDX=2;

bool all_yellow(const vector<vector<int>>& signals, const size_t& iter){
    
    bool is_all_yellow = true;
    
    for(size_t i = 0; i<signals.size() ; i++){
        const vector<int>& signal = signals[i];
        int period = 0;
        for (int x=0;x<signal.size();x++){
            period += signal[x];
        }

        size_t residual = static_cast<size_t>(static_cast<int>(iter) % period);
        //2 1 2  | 3~ | ~1
        if (residual >= signal[GREEN_IDX] + signal[YELLOW_IDX] || residual < signal[GREEN_IDX] )
            is_all_yellow = false;
        
        if (! is_all_yellow)
            return is_all_yellow;
    }
    
    return is_all_yellow;
        
}

int solution(vector<vector<int>> signals) {
    int answer = -1;
    size_t iter = 0;
    while(iter < MAX_ITER){
        bool res = all_yellow(signals, iter);
        if (res){
            answer = iter +1;
            break;
        }
        iter++;
    }
    return answer;
}