#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/combinations/
void dfs(vector<vector<int>>& result, int n, int k, int index, vector<int>& temp) {
    if (static_cast<int>(temp.size()) == k) {
        result.emplace_back(temp);
        return;
    }

    for (int i = index; i <= n; i++) {
        if (static_cast<int>(temp.size()) < k) {
            temp.push_back(i);
            dfs(result, n, k, i + 1, temp);
            temp.pop_back();
        }
    }

}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> temp;
    dfs(result, n, k, 1, temp);
    return result;

}

int main(int argc, char* argv[]) {
    int n = 4;
    int k = 2;
    set<vector<int>> ans = {{2,4},{3,4},{2,3},{1,2},{1,3},{1,4}};
    auto result = combine(n, k);
    set<vector<int>> transfer(result.begin(), result.end());
    assert(transfer == ans);
    return 0;
}