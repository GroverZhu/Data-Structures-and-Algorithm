#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/range-sum-query-immutable/
class NumArray {
public:
    NumArray(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        prefix = vector<int>(size + 1, 0);
        for (int i = 1; i <= size; i++) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
    }

    // [left, right]
    int sumRange(int left, int right) { return prefix[right + 1] - prefix[left]; }

private:
    vector<int> prefix;
};

int main(int argc, char* argv[]) {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray test = NumArray(nums);
    assert(1 == test.sumRange(0, 2));
    assert(-1 == test.sumRange(2, 5));
    assert(-3 == test.sumRange(0, 5));

    return 0;
}