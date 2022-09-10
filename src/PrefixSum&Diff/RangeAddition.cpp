#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/range-addition/
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> diff(length + 1, 0);

    for (auto update : updates) {
        auto begin = update[0];
        auto end = update[1];
        auto num = update[2];
        diff[begin] += num;
        diff[end + 1] -= num;
    }

    vector<int> result(length, 0);
    result[0] = diff[0];
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] + diff[i];
    }

    return result;
}

int main(int argc, char* argv[]) {
    int length = 5;
    vector<vector<int>> updates = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
    vector<int> ans = {-2, 0, 3, 5, 3};
    assert(ans == getModifiedArray(length, updates));
    return 0;
}