#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int findCircleNum(vector<vector<int>>& isConnected) {
    int size = static_cast<int>(isConnected.size());
    if (size <= 1) return size;

    auto Find = [](vector<int>& nums, int j) {
        int root = j;
        while (nums[root] != root) {
            root = nums[root];
        }

        while (nums[j] != j) {
            int temp = j;
            j = nums[j];
            nums[temp] = root;

        }

        return root;
    };

    auto Union = [&Find](vector<int>& nums, int i, int j) {
        int root_i = Find(nums, i);
        int root_j = Find(nums, j);
        nums[root_i] = nums[root_j];
    };

    vector<int> disjoint(size, 0);
    std::iota(disjoint.begin(), disjoint.end(), 0);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (isConnected[i][j] == 1) {
                Union(disjoint, i, j);
            }
        }
    }

    int cnt = 0;
    for (int i  = 0; i < size; i++) {
        if (disjoint[i] == i) ++cnt;
    }

    return cnt;
}



int main() {
    vector<vector<int>> graph = {{1, 0, 0, 1, 0}, {0, 1, 1, 0, 1}, {0, 1, 1, 1, 0}, {1, 0, 1, 1, 0}, {0, 1, 1, 0, 1}};
    cout << findCircleNum(graph) << endl;
    return 0;
}