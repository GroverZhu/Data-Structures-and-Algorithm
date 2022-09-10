#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// [beign, end]
void reverse(vector<int>& nums, int begin, int end) {
    while (begin < end) {
        swap(nums[begin], nums[end]);
        ++begin;
        --end;
    }
}
// https://leetcode-cn.com/problems/rotate-array/
void rotate(vector<int>& nums, int k) {
    int size = static_cast<int>(nums.size());
    k = k % size;
    if (k == 0) return;
    reverse(nums, 0, size - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, size - 1);
}

int main(int argc, char* argv[]) {
    vector<int> nums, ans;
    int k;

    nums = {1, 2, 3, 4, 5, 6, 7};
    k = 3;
    ans = {5, 6, 7, 1, 2, 3, 4};
    rotate(nums, k);
    assert(nums == ans);

    nums = {-1, -100, 3, 99};
    k = 2;
    ans = {3, 99, -1, -100};
    rotate(nums, k);
    assert(nums == ans);

    return 0;
}
