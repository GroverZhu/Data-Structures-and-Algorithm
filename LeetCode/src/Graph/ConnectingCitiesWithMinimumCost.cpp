#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

#include <cassert>

using namespace std;

int find(vector<int>& nums, int i) {
    int root = i;
    while (root != nums[root]) {
        root = nums[root];
    }
    while (nums[i] != i) {
        int tmp = nums[i];
        nums[i] = root;
        i = tmp;
    }
    return root;
}

void unions(vector<int>& nums, int i, int j) {
    int root_i = find(nums, i);
    int root_j = find(nums, j);
    nums[root_i] = root_j;
}

// https://leetcode-cn.com/problems/connecting-cities-with-minimum-cost/
int minimumCost(int n, vector<vector<int>>& connections) {
    sort(connections.begin(), connections.end(), [](vector<int>& lhs, vector<int>& rhs) {
        return lhs[2] < rhs[2];
    });

    int min_cost = 0;
    vector<int> disjoint(n);
    for (int i = 0; i < n; i++) {
        disjoint[i] = i;
    }
    for (auto edge : connections) {
        int from  = edge[0] - 1;
        int to = edge[1] - 1;
        int cost = edge[2];

        int root_from = find(disjoint, from);
        int root_to = find(disjoint, to);
        if (root_from == root_to) {
            continue;
        }
        unions(disjoint, from, to);
        min_cost += cost;
        
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i == disjoint[i]) ++count;
    }

    return count == 1 ? min_cost : -1;

}


int prim(int n, vector<vector<int>>& connections) {
    // 建图
    map<int, vector<pair<int, int>>> graph;
    for (int i = 0; i < n; i++) {
        graph[i] = vector<pair<int, int>>();
    }
    for (auto connect : connections) {
        int from = connect[0] - 1;
        int to = connect[1] - 1;
        int cost = connect[2];
        graph[from].push_back({to, cost});
        graph[to].push_back({from, cost});
    }

    vector<bool> visited(n, false);
    auto cmp = [](pair<int, int>& lhs, pair<int, int>& rhs) {
        return lhs.second > rhs.second; // 小根堆
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    int minCost = 0;

    visited[0] = true;
    for (auto edge : graph[0]) {
        int to = edge.first;
        if (visited[to]) continue;
        q.push(edge);
    }

    while (!q.empty()) {
        auto edge = q.top();
        q.pop();
        int from = edge.first;
        int cost = edge.second;
        if (visited[from]) continue;
        minCost += cost;
        visited[from] = true;
        for (auto next : graph[from]) {
            int to = next.first;
            if (visited[to]) continue;
            q.push(next);
        }
    }

    for (auto vis : visited) {
        if (!vis) return -1;
    }

    return minCost;


}

int main(int argc, char* argv[]) {
    int n = 3;
    vector<vector<int>> connections = {{1, 2, 5}, {1, 3, 6}, {2, 3, 1}};
    assert(6 == minimumCost(n, connections));
    // cout << prim(n, connections) << endl;
    assert(prim(n, connections) == minimumCost(n, connections));

    n = 4;
    connections = {{1, 2, 3}, {3, 4, 4}};
    assert(-1 == minimumCost(n, connections));
    assert(prim(n, connections) == minimumCost(n, connections));
    return 0;
}