#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/koko-eating-bananas/
int costTime(vector<int>& piles, int eat) {
    int size = static_cast<int>(piles.size());
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        cnt += (static_cast<long long>(piles[i]) + eat - 1) / eat;
    }
    return cnt;
}

int minEatingSpeed(vector<int>& piles, int h) {
    long long left = 1;
    long long right = 0;
    for (auto num : piles) {
        right += num;
    }
    right += 1;
    long long mid = 0;
    while (left < right) {
        mid = (right - left) / 2 + left;
        int time = costTime(piles, mid);
        if (time < h) {
            right = mid;
        } else if (time > h) {
            left = mid + 1;
        } else if (time == h) {
            right = mid;
        }
    }
    return left;
}

// https://leetcode.cn/problems/minimize-max-distance-to-gas-station/
int gasDistance(vector<double_t>& intervals, double dist) {
    int size = static_cast<int>(intervals.size());
    int cnt = 0;

    for (int i = 0; i < size; i++) {
        cnt += intervals[i] / dist;
    }

    return cnt;
}

double minmaxGasDist(vector<int>& stations, int k) {
    double epsilon = 1e-6;
    double left = 0.0;
    double right = 0.0;
    int size = static_cast<int>(stations.size());
    vector<double> intervals(size - 1);
    for (int i = 1; i < size; i++) {
        intervals[i - 1] = static_cast<double>(stations[i] - stations[i - 1]);
        right = max(right, intervals[i - 1]);
    }
    double mid = 0.0;

    while (right - left > epsilon) {
        mid = (right - left) / 2.0 + left;
        int cnt = gasDistance(intervals, mid);
        if (cnt < k) {
            right = mid;
        } else if (cnt > k) {
            left = mid;
        } else if (cnt == k) {
            right = mid;
        }
    }

    return left;
}

int main() {
    vector<int> piles;
    int h;

    piles = {3, 6, 7, 11};
    h = 8;
    assert(4 == minEatingSpeed(piles, h));

    piles = {30, 11, 23, 4, 20};
    h = 5;
    assert(30 == minEatingSpeed(piles, h));

    piles = {30, 11, 23, 4, 20};
    h = 6;
    assert(23 == minEatingSpeed(piles, h));

    double epsilon = 1e-6;
    vector<int> stations;
    int k;

    stations = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    k = 9;
    assert(abs(0.500 - minmaxGasDist(stations, k)) < epsilon);

    stations = {23, 24, 36, 39, 46, 56, 57, 65, 84, 98};
    k = 1;
    assert(abs(14.00 - minmaxGasDist(stations, k)) < epsilon);

    return 0;
}