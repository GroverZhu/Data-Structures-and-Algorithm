#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/car-pooling/
bool carPooling(vector<vector<int>>& trips, int capacity) {
    int size = 0;
    for (auto trip : trips) {
        size = max(size, trip[2]);
    }

    vector<int> diff(size + 1, 0);
    for (auto trip : trips) {
        auto num = trip[0];
        auto begin = trip[1];
        auto end = trip[2];
        diff[begin] += num;
        diff[end] -= num;
    }

    int num = diff[0];
    if (num > capacity) return false;
    for (int i = 1; i < size; i++) {
        num = num + diff[i];
        if (num > capacity) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> trips = {{2, 1, 5}, {3, 3, 7}};
    int capactity = 4;
    assert(false == carPooling(trips, capactity));

    trips = {{2, 1, 5}, {3, 3, 7}};
    capactity = 5;
    assert(true == carPooling(trips, capactity));

    trips = {{2, 1, 5}, {3, 5, 7}};
    capactity = 3;
    assert(true == carPooling(trips, capactity));

    trips = {{9, 0, 1}, {3, 3, 7}};
    capactity = 4;
    assert(false == carPooling(trips, capactity));

    trips = {{7, 5, 6}, {6, 7, 8}, {10, 1, 6}};
    capactity = 16;
    assert(false == carPooling(trips, capactity));

    return 0;
}