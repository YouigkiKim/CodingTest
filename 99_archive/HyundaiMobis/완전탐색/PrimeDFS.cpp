/*

문제 설명
한자리 숫자가 적힌 종이 조각이 흩어져있습니다. 흩어진 종이 조각을 붙여 소수를 몇 개 만들 수 있는지 알아내려 합니다.

각 종이 조각에 적힌 숫자가 적힌 문자열 numbers가 주어졌을 때, 종이 조각으로 만들 수 있는 소수가 몇 개인지 return 하도록 solution 함수를 완성해주세요.

제한사항
numbers는 길이 1 이상 7 이하인 문자열입니다.
numbers는 0~9까지 숫자만으로 이루어져 있습니다.
"013"은 0, 1, 3 숫자가 적힌 종이 조각이 흩어져있다는 의미입니다.
입출력 예
numbers	return
"17"	3
"011"	2
입출력 예 설명
예제 #1
[1, 7]으로는 소수 [7, 17, 71]를 만들 수 있습니다.

예제 #2
[0, 1, 1]으로는 소수 [11, 101]를 만들 수 있습니다.

11과 011은 같은 숫자로 취급합니다.

*/
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

bool IsPrime(int value){
    if(value < 2) return false;
    for(int i = 2 ; i*i <= value ; i++){
        if(value % i == 0) {
            // cout << "is not prime "<< value << endl;
            return false;}
    }
    // cout << "is prime " << value << endl;
    return true;
}

void dfs(set<int>& nums, const string& numbers, string cur_num, vector<bool>& used){
    
    // cout << "numbers ";
    //     for (auto num : numbers) cout << num;
    // cout << " " << cur_num ;
    // cout << " used ";
    //     for (auto use : used) cout << use << endl;

    /*  ======================================================================================
        for문 내부에서 다음 스텝에 유지되어야 하는 변수들 [cur_num, used]는 업데이트 금지. 아니면 업데이트 이후 복원작업필요
        ====================================================================================== */ 
    for (int i=0 ; i<numbers.size() ; i++){
        string step_cur_num = cur_num; // 복사 후 새로운 변수로 instert수행
        if (used[i] ) continue ; 
        
        step_cur_num += numbers[i];
        
        // cout << "added cur_num "<< step_cur_num<<endl; 
        nums.insert(stoi(step_cur_num)); // insert를 dfs시작에 empty검사 후 진행하면 변수 복사 불필요

        used[i] = true;
        dfs(nums, numbers, step_cur_num, used);
        used[i] = false; // 다음 for문스텝에서 재사용해야돼서 false로 바꿔줘야함
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