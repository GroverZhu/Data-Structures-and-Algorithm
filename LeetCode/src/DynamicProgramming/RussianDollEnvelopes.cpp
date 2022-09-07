#include <algorithm>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/russian-doll-envelopes/
int maxEnvelopes(vector<vector<int>>& envelopes) {
    int size = static_cast<int>(envelopes.size());
    if (size <= 1) return size;

    auto cmp = [](const vector<int>& lhs, const vector<int>& rhs) {
        if (lhs[0] == rhs[0]) {
            return lhs[1] > rhs[1];
        }

        return lhs[0] < rhs[0];
    };
    sort(envelopes.begin(), envelopes.end(), cmp);

    vector<int> nums(size);
    for (int i = 0; i < size; i++) {
        nums[i] = envelopes[i][1];
    }
    // 二分查找最长上升子序列
    vector<int> top(size, 0);
    int piles = 0;
    for (int i = 0; i < size; i++) {
        int poker = nums[i];
        int left = 0;
        int right = piles;
        while (left < right) {
            int mid = (right - left) / 2 + left;  // [left, right)
            if (poker < top[mid]) {
                right = mid;
            } else if (poker > top[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        if (left == piles) {
            piles++;
        }
        top[left] = poker;
    }
    return piles;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> envelopes;

    envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    assert(3 == maxEnvelopes(envelopes));

    envelopes = {{1, 1}, {1, 1}, {1, 1}};
    assert(1 == maxEnvelopes(envelopes));

    return 0;
}