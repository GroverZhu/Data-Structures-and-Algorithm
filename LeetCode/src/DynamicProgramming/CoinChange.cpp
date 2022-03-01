#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/coin-change/
int coinChange(vector<int>& coins, int amount) {
    vector<int> count(amount + 1, amount + 1);
    count[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (auto coin : coins) {
            if (i >= coin) {
                count[i] = min(count[i], count[i - coin] + 1);
            }
        }
    }

    return count[amount] == amount + 1 ? -1 : count[amount];
}

// https://leetcode-cn.com/problems/coin-change-2/
int change(int amount, vector<int>& coins) {
    int size = static_cast<int>(coins.size());
    vector<vector<int>> count(size + 1, vector<int>(amount + 1, 0));
    for (int i = 0; i <= size; i++) {
        count[i][0] = 1;
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= amount; j++) {
            count[i][j] = count[i - 1][j];
            if (j >= coins[i - 1]) {
                count[i][j] += count[i][j - coins[i - 1]];
            }
        }
    }

    return count[size][amount];
}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/coin-change/
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

    // https://leetcode-cn.com/problems/coin-change-2/
    amount = 5;
    coins = {1, 2, 5};
    assert(4 == change(amount, coins));

    amount = 3;
    coins = {2};
    assert(0 == change(amount, coins));

    amount = 10;
    coins = {10};
    assert(1 == change(amount, coins));
    return 0;
}