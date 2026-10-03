#include <string>
#include <vector>
#include <set>

using namespace std;

bool IsPrime(int value){
    if(value < 2) return false;
    if(value == 2) return true;
    if(value % 2) return false;
    for(int i = 0 ; i*i < value ; i+=2){
        if(value % i == 0) return false;
    }
    return true;
}

void dfs(set<int>& nums, const string& numbers, string cur_num, vector<bool>& used){
    
    for (int i=0 ; i<numbers.size() ; i++){
        cur_num +=numbers[i];
        used[i] = true;
        nums.insert(stoi(cur_num));
        dfs(nums, numbers, cur_num, used);
    }
}
int solution(string numbers) {
    int answer = 0;
    set<int> nums;
    vector<bool> used(numbers.size(), false);
    string cur_num = "";
    dfs(nums, numbers, cur_num, used);
    int count = 0;
    for(const auto& num : nums){
        if(IsPrime(num)) count++;
    }
    answer = count;
    return answer;
}