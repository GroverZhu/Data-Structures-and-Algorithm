#include <iostream>
#include <map>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/subarray-sum-equals-k/
int subarraySum(vector<int>& nums, int k) {
    map<int, int> prefix;
    prefix[0] = 1;
    int result = 0;
    int sum = 0;
    for (auto num : nums) {
        sum += num;
        // prefix[j] - prefix[i] == k --> prefix[i] == prefix[j] - k
        if (prefix.find(sum - k) != prefix.end()) {
            result += prefix[sum - k];
        }
        prefix[sum]++;
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int k;

    nums = {1, 1, 1};
    k = 2;
    assert(2 == subarraySum(nums, k));

    nums = {1, 2, 3};
    k = 3;
    assert(2 == subarraySum(nums, k));

    return 0;
}