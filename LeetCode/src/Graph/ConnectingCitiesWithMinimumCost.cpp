#include <iostream>
#include <vector>
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

int main(int argc, char* argv[]) {
    int n = 3;
    vector<vector<int>> connections = {{1, 2, 5}, {1, 3, 6}, {2, 3, 1}};
    assert(6 == minimumCost(n, connections));

    n = 4;
    connections = {{1, 2, 3}, {3, 4, 4}};
    assert(-1 == minimumCost(n, connections));
    return 0;
}