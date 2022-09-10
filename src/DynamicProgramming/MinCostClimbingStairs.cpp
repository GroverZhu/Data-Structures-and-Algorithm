#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/min-cost-climbing-stairs/
int minCostClimbingStairs(vector<int>& cost) {
    int size = static_cast<int>(cost.size());
    if (size < 2) return 0;
#if 0
    vector<int> fees(size + 1, 0);

    for (int i = 2; i <= size; i++) {
        fees[i] += min(fees[i - 2] + cost[i - 2], fees[i - 1] + cost[i - 1]);
    }
    return fees[size];
#endif

#if 1
    int first = 0, second = 0;
    for (int i = 2; i <= size; i++) {
        int tmp = second;
        second = min(first + cost[i - 2], second + cost[i - 1]);
        first = tmp;
    }
    return second;
#endif
}
int main(int argc, char* argv[]) {
    vector<int> cost;

    cost = {10, 15, 20};
    assert(15 == minCostClimbingStairs(cost));

    cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    assert(6 == minCostClimbingStairs(cost));

    cost = {1, 100};
    assert(1 == minCostClimbingStairs(cost));
    return 0;
}