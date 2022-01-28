#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/count-number-of-nice-subarrays/
int numberOfSubarrays(vector<int>& nums, int k) {
    map<int, int> prefix;
    int result = 0;
    prefix[0] = 1;
    int cnt = 0;
    for (auto num : nums) {
        cnt += (num & 1);
        // prefix[j] - prefix[i] = k --> prefix[i] = prefix[j] - k
        if (prefix.find(cnt - k) != prefix.end()) {
            result += prefix[cnt - k];
        }
        prefix[cnt]++;
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int k;

    nums = {1, 1, 2, 1, 1};
    k = 3;
    assert(2 == numberOfSubarrays(nums, k));

    nums = {2, 4, 6};
    k = 1;
    assert(0 == numberOfSubarrays(nums, k));


    nums = {2,2,2,1,2,2,1,2,2,2};
    k = 2;
    assert(16 == numberOfSubarrays(nums, k));

    return 0;
}