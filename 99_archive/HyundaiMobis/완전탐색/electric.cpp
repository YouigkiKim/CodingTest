#include <string>
#include <vector>
#include <iostream>

using namespace std;

void dfs(int cur_node, const vector<vector<int>>& connection, vector<bool>& visit){
    visit[cur_node] = true;
    for (int next : connection[cur_node]){
        if(visit[next]) continue;
        dfs(next, connection, visit);
    }
}

int solution(int n, vector<vector<int>> wires) {
    
    // 나누는 반복문
    vector<int> node_num;
    for (int i = 0 ; i < wires.size() ; i++){
        
        vector<vector<int>> deleted_wires;
        for(int j = 0 ; j < wires.size() ; j++){
            if (j == i) continue;
            deleted_wires.push_back(wires[j]);
        }
        
        /* node가 1부터 시작하므로 노드번호 그대로 쓰려면 connection 1개 더 있어야함*/
        vector<vector<int>> connection;
        connection.push_back(vector<int>());
        for(int i = 0 ; i < n ; i++){
            vector<int> tmp;
            connection.push_back(tmp);
        }
        // 삭제된 연결을 빼고 양방향 connection으로 바꾸고 dfs진행
        for (const auto& wire : deleted_wires){
            connection[wire[0]].push_back(wire[1]);
            connection[wire[1]].push_back(wire[0]);
        }

        int cur_node = 1;
        vector<bool> visit(n+1, false);
        dfs(cur_node, connection, visit);
        //방문한 노드 기록, visit 개수 세
        int visit_num = 0;
        for (bool v : visit) if (v) visit_num++;
        node_num.push_back(visit_num);
    }
    
    int answer = n;
    for(int num : node_num) {
        int diff = abs(n - 2*num); // 기존 코드 오타: 수식에 비교문넣음 => 무조건 1나옴 answer > abs(n - 2*num);
        if(answer > abs(n - 2*num))
            answer =  diff;
    }
    return answer;
}