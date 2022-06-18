#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
int largestRectangleArea(vector<int>& heights) {
    int size = static_cast<int>(heights.size());
    vector<int> left(size, 0);
    stack<int> stk;
    for (int i = 0; i < size; i++) {
        while (!stk.empty() && heights[i] <= heights[stk.top()]) {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }

    vector<int> right(size, 0);
    stk = {};
    for (int i = size - 1; i >= 0; i--) {
        while (!stk.empty() && heights[i] <= heights[stk.top()]) {
            stk.pop();
        }
        right[i] = stk.empty() ? size : stk.top();
        stk.push(i);
    }

    int area = 0;
    for (int i = 0; i < size; i++) {
        area = max(area, heights[i] * (right[i] - left[i] - 1));
    }

    return area;
}

int main(int argc, char* argv[]) {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    assert(10 == largestRectangleArea(heights));

    heights = {2, 4};
    assert(4 == largestRectangleArea(heights));

    heights = {1, 1};
    assert(2 == largestRectangleArea(heights));
    return 0;
}