#include <iostream>
#include <map>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/car-pooling/
bool carPooling(vector<vector<int>>& trips, int capacity) {
#if 1
    int size = static_cast<int>(trips.size());
    map<int, int> diff;

    for (int i = 0; i < size; i++) {
        int begin = trips[i][1];
        int end = trips[i][2];
        int passenger = trips[i][0];
        diff[begin] += passenger;
        diff[end] -= passenger;
    }

    int sum = 0;
    for (auto& iter : diff) {
        sum += iter.second;
        iter.second = sum;
        if (sum > capacity) {
            return false;
        }
    }

    return true;
#endif

#if 0
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
#endif
}

// https://leetcode.cn/problems/number-of-flowers-in-full-bloom/
vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
    int len = static_cast<int>(flowers.size());
    map<int, int> diff;

    for (int i = 0; i < len; i++) {
        assert(flowers[i].size() == 2);
        diff[flowers[i][0]] += 1;
        diff[flowers[i][1] + 1] -= 1;
    }

    int size = static_cast<int>(persons.size());

    for (int i = 0; i < size; i++) {
        diff[persons[i]] += 0;  // 将 persons[i] 到达的位置记录下来
    }

    int sum = 0;
    for (auto& iter : diff) {
        sum += iter.second;
        iter.second = sum;
    }

    vector<int> ans(size, 0);
    for (int i = 0; i < size; i++) {
        ans[i] = diff[persons[i]];
    }

    return ans;
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

    vector<vector<int>> flowers = {{1, 6}, {3, 7}, {9, 12}, {4, 13}};
    vector<int> persons = {2, 3, 7, 11};
    vector<int> answer = {1, 2, 2, 2};
    assert(answer == fullBloomFlowers(flowers, persons));

    return 0;
}