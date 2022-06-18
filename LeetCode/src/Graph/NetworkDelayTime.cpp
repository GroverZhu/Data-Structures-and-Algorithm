#include <cassert>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct State {
    int cur;
    int distanceFromStart;

    State(int cur, int dis) {
        this->cur = cur;
        this->distanceFromStart = dis;
    }
};

// https://leetcode-cn.com/problems/network-delay-time/
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // 建图
    map<int, vector<State>> graph;
    for (auto node : times) {
        int from = node[0] - 1;
        int to = node[1] - 1;
        int cost = node[2];
        graph[from].push_back(State(to, cost));
    }
    auto cmp = [](const State& lhs, const State& rhs) { return lhs.distanceFromStart > rhs.distanceFromStart; };
    vector<int> distances(n, INT_MAX);
    distances[k - 1] = 0;
    priority_queue<State, vector<State>, decltype(cmp)> q(cmp);
    q.push(State(k - 1, 0));

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        if (node.distanceFromStart > distances[node.cur]) {
            continue;
        }
        for (auto next : graph[node.cur]) {
            auto nextNode = next.cur;
            auto dis = distances[node.cur] + next.distanceFromStart;
            if (distances[nextNode] > dis) {
                distances[nextNode] = dis;
                q.push(State(nextNode, dis));
            }
        }
    }
    int result = distances[0];
    for (int i = 0; i < n; i++) {
        if (distances[i] == INT_MAX) return -1;
        result = max(result, distances[i]);
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> times;
    int n, k;
    times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    n = 4;
    k = 2;
    assert(2 == networkDelayTime(times, n, k));

    times = {{1, 2, 1}};
    n = 2;
    k = 1;
    assert(1 == networkDelayTime(times, n, k));

    times = {{1, 2, 1}};
    n = 2;
    k = 2;
    assert(-1 == networkDelayTime(times, n, k));
    return 0;
}