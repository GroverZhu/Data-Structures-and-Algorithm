#include <climits>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/jump-game/
bool canJump(vector<int>& nums) {
    int size = static_cast<int>(nums.size());

    vector<bool> access(size, false);

    access[0] = true;

    for (int i = 1; i < size; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (access[j] && j + nums[j] >= i) {
                access[i] = true;
                break;
            }
        }
    }
    return access[size - 1];
}

// https://leetcode-cn.com/problems/jump-game-ii/
// 使用DP可能会超时
int jump(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    vector<int> steps(size, INT_MAX);

    steps[0] = 0;

    for (int i = 1; i < size; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (j + nums[j] >= i) {  // 题目中每个位置是可达的
                steps[i] = min(steps[i], steps[j] + 1);
            }
        }
    }

    return steps[size - 1] == INT_MAX ? -1 : steps[size - 1];
}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/jump-game/
    vector<int> nums = {2, 3, 1, 1, 4};
    assert(true == canJump(nums));

    nums = {3, 2, 1, 0, 4};
    assert(false == canJump(nums));

    nums = {2, 5, 0, 0};
    assert(true == canJump(nums));

    nums = {2, 3, 1, 1, 4};
    assert(2 == jump(nums));

    nums = {2, 3, 0, 1, 4};
    assert(2 == jump(nums));

    nums = {2, 1};
    assert(1 == jump(nums));

    return 0;
}
