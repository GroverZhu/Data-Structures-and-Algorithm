#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/permutations/

void dfs(vector<vector<int>>& result, vector<int>& nums, vector<bool>& visited, vector<int>& temp) {
    if (temp.size() == nums.size()) {
        result.emplace_back(temp);
        return;
    }

    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        if (visited[i]) continue;
        temp.emplace_back(nums[i]);
        visited[i] = true;
        dfs(result, nums, visited, temp);
        visited[i] = false;
        temp.pop_back();
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    int size = static_cast<int>(nums.size());
    if (size <= 0) return result;
    vector<bool> visited(size, false);
    vector<int> temp;
    dfs(result, nums, visited, temp);
    return result;
}

// https://leetcode-cn.com/problems/permutations-ii/
void dfsUnique(vector<vector<int>>& result, vector<int>& nums, vector<bool>& visited, vector<int>& temp) {
    if (temp.size() == nums.size()) {
        result.emplace_back(temp);
        return;
    }

    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
        if (visited[i]) continue;
        if (i > 0 && visited[i - 1] && nums[i] == nums[i - 1]) continue;

        visited[i] = true;
        temp.emplace_back(nums[i]);

        dfsUnique(result, nums, visited, temp);

        visited[i] = false;
        temp.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> result;
    int size = static_cast<int>(nums.size());
    if (size <= 0) return result;
    sort(nums.begin(), nums.end());
    vector<bool> visited(size, false);
    vector<int> temp;

    dfsUnique(result, nums, visited, temp);

    return result;
}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/permutations/

    vector<int> nums = {1, 2, 3};
    set<vector<int>> ans = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    auto result = permute(nums);
    set<vector<int>> transfer(result.begin(), result.end());
    assert(transfer == ans);

    // https://leetcode-cn.com/problems/permutations-ii/
    nums = {1, 1, 2};
    ans = {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};
    result = permuteUnique(nums);
    transfer = set<vector<int>>(result.begin(), result.end());
    assert(transfer.size() == result.size());
    assert(transfer == ans);

    return 0;
}