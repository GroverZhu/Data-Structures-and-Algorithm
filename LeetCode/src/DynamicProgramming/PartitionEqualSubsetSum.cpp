#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/partition-equal-subset-sum/

bool canPartition(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    if (size <= 1) return false;
    int sum = 0;
    for (auto num : nums) sum += num;
    if (sum % 2 != 0) return false;
    int cols = sum / 2 + 1;
    vector<vector<bool>> dp(size + 1, vector<bool>(cols, false));

    for (int i = 0; i <= size; i++) dp[i][0] = true;

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j < cols; j++) {
            if (j - nums[i - 1] >= 0) {
                dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[size][cols - 1];
}

int main(int argc, char* argv[]) {
    vector<int> nums = {1, 5, 11, 5};
    assert(canPartition(nums));

    nums = {1, 2, 3, 5};
    assert(!canPartition(nums));
    return 0;
}
