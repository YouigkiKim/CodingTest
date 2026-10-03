// 09-graph_bfs_dfs: 인접 리스트, DFS(재귀), BFS(큐), 연결 요소, 최단 거리
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 재귀 DFS: 한 방향으로 갈 수 있는 데까지 들어갔다가 되돌아온다.
void dfs(int node, const vector<vector<int>> &adj, vector<bool> &visited, vector<int> &order) {
    visited[node] = true;
    order.push_back(node);
    for (int next : adj[node]) {
        if (!visited[next]) dfs(next, adj, visited, order);
    }
}

int main() {
    // 정점 7개(0~6), 간선: 0-1, 0-2, 1-3, 2-3, 3-4, 5-6  (5, 6은 따로 떨어진 덩어리)
    int n = 7;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {5, 6}};

    // 인접 리스트: adj[u] = u와 연결된 정점 목록
    vector<vector<int>> adj(n);
    for (const auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);   // 양방향이면 반대쪽도 넣는다
    }

    // --- DFS ---
    vector<bool> visited(n, false);
    vector<int> order;
    dfs(0, adj, visited, order);
    cout << "DFS from 0:";
    for (int v : order) cout << ' ' << v;   // 0 1 3 2 4
    cout << '\n';

    // --- BFS: 가까운 정점부터. dist가 -1이면 미방문 ---
    vector<int> dist(n, -1);
    queue<int> q;
    dist[0] = 0;                            // 시작점: 큐에 넣을 때 방문 처리
    q.push(0);
    cout << "BFS from 0:";
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << ' ' << cur;                 // 0 1 2 3 4
        for (int next : adj[cur]) {
            if (dist[next] != -1) continue; // 이미 방문(또는 큐에 들어 있음)
            dist[next] = dist[cur] + 1;     // 큐에 넣는 순간 거리 확정 = 방문 처리
            q.push(next);
        }
    }
    cout << '\n';
    cout << "distance from 0:";
    for (int v = 0; v < n; v++) cout << ' ' << dist[v];  // 0 1 1 2 3 -1 -1
    cout << '\n';

    // --- 연결 요소의 개수: 미방문 정점을 만날 때마다 탐색을 새로 시작 ---
    vector<bool> seen(n, false);
    int components = 0;
    for (int start = 0; start < n; start++) {
        if (seen[start]) continue;
        components++;
        vector<int> group;
        dfs(start, adj, seen, group);
        cout << "component " << components << ":";
        for (int v : group) cout << ' ' << v;
        cout << '\n';
    }
    cout << "components = " << components << '\n';  // 2
    return 0;
}
