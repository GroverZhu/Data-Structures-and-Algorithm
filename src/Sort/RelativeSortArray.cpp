#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/relative-sort-array/
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    map<int, int> value2index;
    for (int i = 0; i < static_cast<int>(arr2.size()); i++) {
        value2index[arr2[i]] = i;
    }

    auto cmp = [&value2index](const int& lhs, const int& rhs) {
        auto leftIter = value2index.find(lhs);
        auto rightIter = value2index.find(rhs);
        if (leftIter != value2index.end() && rightIter != value2index.end()) {
            return leftIter->second < rightIter->second;
        } else if (leftIter == value2index.end() && rightIter == value2index.end()) {
            return lhs < rhs;
        } else if (leftIter != value2index.end() && rightIter == value2index.end()) {
            return true;
        } else if (leftIter == value2index.end() && rightIter != value2index.end()) {
            return false;
        }
        return false;
    };

    // todo: 自己写排序函数
    sort(arr1.begin(), arr1.end(), cmp);

    return arr1;
}

int main(int argc, char* argv[]) {
    vector<int> arr1, arr2;
    vector<int> ans;

    arr1 = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
    arr2 = {2, 1, 4, 3, 9, 6};
    ans = {2, 2, 2, 1, 4, 3, 3, 9, 6, 7, 19};
    assert(ans == relativeSortArray(arr1, arr2));

    arr1 = {28, 6, 22, 8, 44, 17};
    arr2 = {22, 28, 8, 6};
    ans = {22, 28, 8, 6, 17, 44};
    assert(ans == relativeSortArray(arr1, arr2));
    return 0;
}