#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/corporate-flight-bookings/
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n + 1, 0);
    for (auto node : bookings) {
        int begin = node[0];
        int end = node[1];
        int num = node[2];
        diff[begin - 1] += num;
        diff[end] -= num;
    }

    vector<int> result(n, 0);
    result[0] = diff[0];
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] + diff[i];
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> bookings = {{1, 2, 10}, {2, 3, 20}, {2, 5, 25}};
    int n = 5;
    vector<int> ans = {10, 55, 45, 25, 25};
    assert(ans == corpFlightBookings(bookings, n));

    bookings = {{1, 2, 10}, {2, 2, 15}};
    n = 2;
    ans = {10, 25};
    assert(ans == corpFlightBookings(bookings, n));

    return 0;
}