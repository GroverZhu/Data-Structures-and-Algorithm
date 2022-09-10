#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/move-zeroes/

void moveZeros(vector<int>& nums) {
    int size = static_cast<int>(nums.size());

    int first = 0;
    int second = 0;

    while (second < size) {
        if (nums[second] != 0) {
            if (first != second) {
                swap(nums[first], nums[second]);
            }
            ++first;
        }
        ++second;
    }
}

int main(int argc, char* argv[]) {
    vector<int> nums = {0, 1, 0, 3, 12};
    vector<int> ans = {1, 3, 12, 0, 0};
    moveZeros(nums);
    assert(nums == ans);

    return 0;
}