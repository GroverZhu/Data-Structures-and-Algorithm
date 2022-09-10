#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/maximum-product-subarray/
int maxProduct(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    vector<long long> maximum(size, 1);
    vector<long long> minimum(size, 1);
    long long result = nums[0];
    maximum[0] = nums[0];
    minimum[0] = nums[0];
    for (int i = 1; i < size; i++) {
        maximum[i] = max(static_cast<long long>(nums[i]), max(maximum[i - 1] * nums[i], minimum[i - 1] * nums[i]));
        minimum[i] = min(static_cast<long long>(nums[i]), min(maximum[i - 1] * nums[i], minimum[i - 1] * nums[i]));
        result = max(result, maximum[i]);
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<int> nums;

    nums = {2, 3, -2, 4};
    assert(6 == maxProduct(nums));

    nums = {-2, 0, -1};
    assert(0 == maxProduct(nums));

    nums = {-4, -3, -2};
    assert(12 == maxProduct(nums));
    return 0;
}