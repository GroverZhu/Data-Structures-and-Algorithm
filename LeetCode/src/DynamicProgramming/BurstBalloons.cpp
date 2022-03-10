#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/burst-balloons/
int maxCoins(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    if (size <= 0) return 0;
    if (size == 1) return nums[0];

    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    size += 2;
    
    vector<vector<int>> coins(size, vector<int>(size, 0));
    coins[0][0] = 1;
    coins[size - 1][size - 1] = 1;

    for (int i = 1; i < size - 1; i++) coins[i][i] = nums[i - 1];

    for (int offset = 1; offset < size; offset++) {
        for (int i = 0; i < size - offset; i++) {
            int j = i + offset;
            for (int k = i + 1; k < j; k++) {
                coins[i][j] = max(coins[i][j], coins[i][k] + nums[i] * nums[k] * nums[j] + coins[k][j]);
            }
        }
    }

    return coins[0][size - 1];
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int ans;

    nums = {3, 1, 5, 8};
    ans = 167;
    assert(ans == maxCoins(nums));

    nums = {1, 5};
    ans = 10;
    assert(ans == maxCoins(nums));
    return 0;
}