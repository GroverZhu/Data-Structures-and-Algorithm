#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/jump-game/
bool canJump(vector<int>& nums) {
    int size = static_cast<int>(nums.size());

    int lens = 0;

    for (int i = 0; i <= size - 1; i++) {
        lens = max(lens, nums[i] + i);
        if (lens <= i) return false;
    }
    return lens >= size - 1;
}

// https://leetcode-cn.com/problems/jump-game-ii/
int jump(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    int begin = 0;
    int end = 0;
    int step = 0;
    int lens = 0;

    for (begin = 0; begin < size - 1; begin++) {
        lens = max(lens, begin + nums[begin]);
        if (begin == end) {
            ++step;
            end = lens;
        }
    }

    return step;
}

int main(int argc, char* argv[]) {
    vector<int> nums;

    nums = {2, 3, 1, 1, 4};
    assert(true == canJump(nums));

    nums = {3, 2, 1, 0, 4};
    assert(false == canJump(nums));

    nums = {2, 3, 1, 1, 4};
    assert(2 == jump(nums));

    nums = {2, 3, 0, 1, 4};
    assert(2 == jump(nums));

    return 0;
}