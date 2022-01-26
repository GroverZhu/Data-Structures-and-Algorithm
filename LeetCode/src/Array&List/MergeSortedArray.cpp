#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/merge-sorted-array/ 
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int end = m + n - 1;
    int index1 = m - 1;
    int index2 = n - 1;

    while (index1 >= 0 && index2 >= 0) {
        if (nums1[index1] >= nums2[index2]) {
            nums1[end] = nums1[index1];
            --index1;
        } else {
            nums1[end] = nums2[index2];
            --index2;
        }
        --end;
    }

    while (index1 >= 0) nums1[end--] = nums1[index1--];
    while (index2 >= 0) nums1[end--] = nums2[index2--];

}

int main(int argc, char* argv[]) {
    vector<int> nums1, nums2, ans;
    int m, n;

    nums1 = {1, 2, 3, 0, 0, 0};
    nums2 = {2, 5, 6};
    m = 3, n = 3;
    merge(nums1, m, nums2, n);
    ans = {1, 2, 2, 3, 5, 6};
    assert(ans == nums1);

    nums1 = {1};
    nums2 = {};
    m = 1, n = 0;
    merge(nums1, m, nums2, n);
    ans = {1};
    assert(ans == nums1);

    nums1 = {0};
    nums2 = {1};
    m = 0, n = 1;
    merge(nums1, m, nums2, n);
    ans = {1};
    assert(ans == nums1);

    return 0;
}