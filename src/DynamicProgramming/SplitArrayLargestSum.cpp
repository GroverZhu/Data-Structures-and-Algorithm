#include <ctype.h>
#include <climits>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/split-array-largest-sum/
int splitArray(vector<int>& nums, int m) {
    int size = static_cast<int>(nums.size());

    vector<long long> prefixSum(size + 1, 0);

    for (int i = 1; i <= size; i++) {
        prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
    }

    vector<vector<long long>> sums(size + 1, vector<long long>(m + 1, LONG_MAX));
    sums[0][0] = 0;

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= min(i, m); j++) {
            for (int k = 0; k < i; k++) {
                sums[i][j] = min(sums[i][j], max(sums[k][j - 1], prefixSum[i] - prefixSum[k]));
            }
        }
    }
    return sums[size][m];
}

int main(int argc, char* argv[]) {
    vector<int> nums = {7, 2, 5, 10, 8};
    int m = 2;
    assert(18 == splitArray(nums, m));

    nums = {1, 2, 3, 4, 5};
    m = 2;
    assert(9 == splitArray(nums, m));

    nums = {1, 4, 4};
    m = 3;
    assert(4 == splitArray(nums, m));

    nums = {1, 4, 4};
    m = 2;
    assert(5 == splitArray(nums, m));
    return 0;
}