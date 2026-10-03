// 06-priority_queue: 항상 가장 큰(또는 작은) 값을 꺼내는 우선순위 큐(힙)
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    // --- 기본: 최대 힙 (top이 가장 큰 값) ---
    priority_queue<int> max_heap;
    for (int x : {5, 1, 8, 3}) max_heap.push(x);   // push: O(log N)
    cout << "max-heap pops:";
    while (!max_heap.empty()) {
        cout << ' ' << max_heap.top();              // top: O(1)
        max_heap.pop();                             // pop: O(log N)
    }
    cout << '\n';  // 8 5 3 1

    // --- 최소 힙 (top이 가장 작은 값) ---
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int x : {5, 1, 8, 3}) min_heap.push(x);
    cout << "min-heap pops:";
    while (!min_heap.empty()) {
        cout << ' ' << min_heap.top();
        min_heap.pop();
    }
    cout << '\n';  // 1 3 5 8

    // --- pair를 넣으면 first가 우선순위가 된다 ---
    priority_queue<pair<int, string>> tasks;        // (우선순위, 이름), 큰 우선순위 먼저
    tasks.push({2, "write report"});
    tasks.push({5, "fix outage"});
    tasks.push({1, "clean desk"});
    cout << "most urgent: " << tasks.top().second << '\n';  // fix outage

    // --- 응용: 값이 계속 추가되는 중에 "현재까지 가장 작은 값"을 반복해서 꺼내기 ---
    // 한 번 정렬해 두는 것으로는 부족하고(새 값이 들어온다), 매번 정렬하면 느리다 -> 힙.
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<string> events = {"add 7", "add 2", "take", "add 5", "add 1", "take", "take"};
    for (const string &e : events) {
        if (e.substr(0, 3) == "add") {
            pq.push(stoi(e.substr(4)));
        } else if (!pq.empty()) {                   // 비어 있을 때 top()을 부르면 안 된다
            cout << "take -> " << pq.top() << '\n'; // 2, 1, 5
            pq.pop();
        }
    }
    cout << "left in heap = " << pq.size() << '\n';  // 1 (7)
    return 0;
}
