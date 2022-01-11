#include <iostream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

// https://leetcode-cn.com/problems/trapping-rain-water/

int trap(vector<int>& height) {
    int size = static_cast<int>(height.size());
    stack<int> stk;
    int water = 0;
    for (int i = 0; i < size; i++) {
        while (!stk.empty() && height[i] >= height[stk.top()]) {
            int right = i;
            int mid = stk.top();
            stk.pop();
            if (stk.empty()) break;
            int left = stk.top();
            water += (right - left - 1) * (min(height[right], height[left]) - height[mid]);
        }
        stk.push(i);
    }
    return water;
    
}

int main(int argc, char* argv[]) {
    time_t begin = time(nullptr);

    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(6 == trap(height));

    height = {4, 2, 0, 3, 2, 5};
    assert(9 == trap(height));

    time_t end = time(nullptr);

    cout << "Test time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 10000 << "ms" << endl;

    return 0;
}