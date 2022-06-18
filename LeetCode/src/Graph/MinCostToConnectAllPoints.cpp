#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include <cassert>

using namespace std;

// 并查集
class UnionFind {
   public:
    UnionFind(int n) {
        size = n;
        count = n;
        parent = vector<int>(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        int root = i;
        while (root != parent[root]) {
            root = parent[root];
        }

        while (i != parent[i]) {
            int tmp = parent[i];
            parent[i] = root;
            i = tmp;
        }
        return root;
    }

    bool isConnected(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        return root_i == root_j;
    }

    void unions(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        parent[root_i] = root_j;
        --count;
    }

    int getCount() { return this->count; }

   private:
    vector<int> parent;
    int size;
    int count;
};

// https://leetcode-cn.com/problems/min-cost-to-connect-all-points/
int minCostConnectPoints(vector<vector<int>>& points) {
    int size = static_cast<int>(points.size());
    vector<vector<int>> connections;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int manhanntanDistance = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            connections.push_back({i, j, manhanntanDistance});
        }
    }

    sort(connections.begin(), connections.end(), [](vector<int>& lhs, vector<int>& rhs) { return lhs[2] < rhs[2]; });

    UnionFind uf = UnionFind(size);

    int minCost = 0;
    for (auto connect : connections) {
        int from = connect[0];
        int to = connect[1];
        int cost = connect[2];
        if (uf.isConnected(from, to)) continue;
        uf.unions(from, to);
        minCost += cost;
    }

    return uf.getCount() == 1 ? minCost : -1;
}

// prim 最小生成树算法
int prim(vector<vector<int>>& points) {
    int size = static_cast<int>(points.size());
    map<int, vector<pair<int, int>>> graph;
    for (int i = 0; i < size; i++) {
        graph[i] = vector<pair<int, int>>();
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int manhanntanDistance = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            graph[i].push_back({j, manhanntanDistance});
            graph[j].push_back({i, manhanntanDistance});
        }
    }

    vector<bool> visited(size, false);
    auto cmp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) { return lhs.second > rhs.second; };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    int minCost = 0;
    visited[0] = true;
    for (auto edge : graph[0]) {
        int to = edge.first;
        if (visited[to]) continue;
        q.push(edge);
    }

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        int from = node.first;
        int cost = node.second;
        if (visited[from]) continue;
        visited[from] = true;
        minCost += cost;
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
    vector<vector<int>> points = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    // cout << minCosstConnectPoints(points) << endl;
    assert(20 == minCostConnectPoints(points));
    assert(minCostConnectPoints(points) == prim(points));

    points = {{3, 12}, {-2, 5}, {-4, 1}};
    assert(18 == minCostConnectPoints(points));
    assert(minCostConnectPoints(points) == prim(points));

    points = {{0, 0}, {1, 1}, {1, 0}, {-1, 1}};
    assert(4 == minCostConnectPoints(points));
    assert(minCostConnectPoints(points) == prim(points));

    return 0;
}