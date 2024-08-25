#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

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

// 中位数，第k个数
double findKthFromSortedArrays(vector<int>& left, int left_bgn, vector<int>& right, int right_bgn, int k) {
    int left_size = static_cast<int>(left.size());
    int right_size = static_cast<int>(right.size());

    if (left_bgn >= left_size) return right[right_bgn + k - 1];
    if (right_bgn >= right_size) return left[left_bgn + k - 1];

    if (k == 1) {
        return min(left[left_bgn], right[right_bgn]);
    }

    int left_val = (left_bgn + k / 2 - 1) < left_size ? left[left_bgn + k / 2 - 1] : INT_MAX;
    int right_val = (right_bgn + k / 2 - 1) < right_size ? right[right_bgn + k / 2 - 1] : INT_MAX;

    if (left_val < right_val) {
        return findKthFromSortedArrays(left, left_bgn + k / 2, right, right_bgn, k - k / 2);
    } else {
        return findKthFromSortedArrays(left, left_bgn, right, right_bgn + k / 2, k - k / 2);
    }
}

// https://leetcode.cn/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
#if 1

    int size1 = static_cast<int>(nums1.size());
    int size2 = static_cast<int>(nums2.size());
    int total = size1 + size2;

    int first = (total + 1) / 2;
    int second = (total + 2) / 2;

    return (findKthFromSortedArrays(nums1, 0, nums2, 0, first) + findKthFromSortedArrays(nums1, 0, nums2, 0, second)) /
           2.0;

#endif

#if 0
    double ans = 0.0;
    int size1 = static_cast<int>(nums1.size());
    int size2 = static_cast<int>(nums2.size());

    int index = 0;
    int total = (size1 + size2);

    int index1 = 0;
    int index2 = 0;

    int first = 0;
    int second = 0;

    while (index1 < size1 || index2 < size2) {
        int val1 = index1 < size1 ? nums1[index1] : INT_MAX;
        int val2 = index2 < size2 ? nums2[index2] : INT_MAX;

        if (val1 < val2) {
            ++index1;
            second = val1;
        } else {
            ++index2;
            second = val2;
        }

        if (index == total / 2) {
            if (total % 2) {
                ans = second;
            } else {
                ans = double(first + second) / 2.0;
            }
            break;
        }
        first = second;
        ++index;
    }

    return ans;

#endif
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

    double epsilon = 1e-5;
    double result;
    nums1 = {1, 3};
    nums2 = {2};
    result = 2.0;
    cout << findMedianSortedArrays(nums1, nums2) << endl;
    assert(abs(findMedianSortedArrays(nums1, nums2) - result) < epsilon);

    nums1 = {1, 2};
    nums2 = {3, 4};
    result = 2.50;
    assert(abs(findMedianSortedArrays(nums1, nums2) - result) < epsilon);

    return 0;
}