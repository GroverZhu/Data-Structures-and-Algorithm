#include <iostream>
#include <vector>

#include <algorithm>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/merge-intervals/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int size = static_cast<int>(intervals.size());
    if (size == 1) return intervals;
    sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
        if (lhs[0] == rhs[0]) {
            return lhs[1] > rhs[1];
        }
        return lhs[0] < rhs[0];
    });

    vector<vector<int>> result;
    
    result.push_back(intervals[0]);

    for (int i = 1; i < size; i++) {
        if (result.back()[1] >= intervals[i][0]) {
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        } else {
            result.push_back(intervals[i]);
        }
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> ans = {{1,6},{8,10},{15,18}};
    assert(ans == merge(intervals));

    intervals = {{1, 4}, {4, 5}};
    ans = {{1, 5}};
    assert(ans == merge(intervals));

    return 0;
}