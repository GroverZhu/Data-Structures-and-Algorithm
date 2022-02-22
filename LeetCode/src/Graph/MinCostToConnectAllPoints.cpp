#include <iostream>
#include <vector>
#include <algorithm>

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

    int getCount() {
        return this->count;
    }
private:
    vector<int> parent;
    int size;
    int count;
};

// https://leetcode-cn.com/problems/min-cost-to-connect-all-points/
int minCosstConnectPoints(vector<vector<int>>& points) {
    int size = static_cast<int>(points.size());
    vector<vector<int>> connections;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int manhanntanDistance = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            connections.push_back({i, j, manhanntanDistance});
        }
    }

    sort(connections.begin(), connections.end(), [](vector<int>& lhs, vector<int>& rhs){
        return lhs[2] < rhs[2];
    });

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


int main(int argc, char* argv[]) {
    vector<vector<int>> points = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    // cout << minCosstConnectPoints(points) << endl;
    assert(20 == minCosstConnectPoints(points));

    points = {{3, 12}, {-2, 5}, {-4, 1}};
    assert(18 == minCosstConnectPoints(points));

    points = {{0,0}, {1,1}, {1, 0}, {-1, 1}};
    assert(4 == minCosstConnectPoints(points));
    return 0;
}