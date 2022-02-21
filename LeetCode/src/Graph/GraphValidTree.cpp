#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class UF {
private:
    int count;
    vector<int> parent;

public:
    UF(int n) {
        this->count = n;
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        int root = i;
        while (this->parent[root] != root) {
            root = parent[root];
        }

        while (parent[i] != root) {
            int tmp = parent[i];
            parent[i] = root;
            i = tmp;
        }
        return root;
    }

    void unions(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        parent[root_i] = parent[root_j];
        --count;
    }

    bool connected(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        return root_i == root_j;
    }

    int getCount() {
        return this->count;
    }

};

// https://leetcode-cn.com/problems/graph-valid-tree/
bool validTree(int n, vector<vector<int>>& edges) {
    UF uf = UF(n);

    for (auto edge : edges) {
        int from = edge[0];
        int to = edge[1];
        if (uf.connected(from, to)) {
            return false;
        }
        uf.unions(from, to);
    }

    return uf.getCount() == 1;
}

int main(int argc, char* argv[]) {
    int n = 5;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
    assert(true == validTree(n, edges));

    n = 5;
    edges = {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
    assert(false == validTree(n, edges));


    n = 4;
    edges = {{0, 1}, {2, 3}};
    assert(false == validTree(n, edges));
    
    n = 4;
    edges = {{0, 1}, {2, 3}, {1, 2}};
    assert(true == validTree(n, edges));
    return 0;
}