#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/coin-change/
// 贪心bfs/dfs都会超时 最优解为动态规划，背包问题
int coinChange(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    sort(coins.rbegin(), coins.rend());
    int steps = INT_MAX;
    auto cmp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
        // 弄个小顶堆
        return lhs.first > rhs.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    q.push({amount, 0});

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        int num = node.first;
        int step = node.second;
        if (num == 0) {  // 不能提前返回
            steps = min(steps, step);
        }
        for (auto coin : coins) {
            if (num >= coin) {
                q.push({num - coin, step + 1});
            }
        }
    }

    return steps == INT_MAX ? -1 : steps;
}

int main(int argc, char* argv[]) {
    vector<int> coins;
    int amount;

    coins = {1, 2, 5};
    amount = 11;
    assert(3 == coinChange(coins, amount));

    coins = {2};
    amount = 3;
    assert(-1 == coinChange(coins, amount));

    coins = {1};
    amount = 0;
    assert(0 == coinChange(coins, amount));

    // 超时测例
    coins = {1, 2, 5};
    amount = 100;
    assert(20 == coinChange(coins, amount));

    coins = {186, 419, 83, 408};
    amount = 6249;
    assert(20 == coinChange(coins, amount));

    return 0;
}