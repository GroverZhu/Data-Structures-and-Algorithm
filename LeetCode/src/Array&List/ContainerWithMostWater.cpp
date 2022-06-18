#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/container-with-most-water/

int maxArea(vector<int>& height) {
    int size = static_cast<int>(height.size());

    int left = 0;
    int right = size - 1;
    int area = 0;

    while (left < right) {
        area = max(area, min(height[left], height[right]) * (right - left));
        if (height[left] < height[right]) {
            ++left;
        } else {
            --right;
        }
    }

    return area;
}

int main(int argc, char* argv[]) {
    vector<int> height;
    int ans, result;

    height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    result = maxArea(height);
    ans = 49;
    assert(result == ans);

    height = {1, 1};
    result = maxArea(height);
    ans = 1;
    assert(result == ans);

    height = {4, 3, 2, 1, 4};
    result = maxArea(height);
    ans = 16;
    assert(result == ans);

    return 0;
}