#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;


// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/ 

int maxProfitI(vector<int>& prices) {
    int size = static_cast<int>(prices.size());
    if (size <= 1) return 0;
    vector<vector<int>> profits(size, vector<int>(2, 0));

    profits[0][0] = 0;
    profits[0][1] = -prices[0];

    for (int i = 1; i < size; i++) {
        profits[i][0] = max(profits[i - 1][0], profits[i - 1][1] + prices[i]);
        profits[i][1] = max(profits[i - 1][1], -prices[i]);
    }

    return profits[size - 1][0];
}

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
int maxProfitII(vector<int>& prices) {
    int size = static_cast<int>(prices.size());
    if (size <= 1) return 0;
    
    vector<vector<int>> profits(size, vector<int>(2, 0));

    profits[0][0] = 0;
    profits[0][1] = -prices[0];

    for (int i = 1; i < size; i++) {
        profits[i][0] = max(profits[i - 1][0], profits[i - 1][1] + prices[i]);
        profits[i][1] = max(profits[i - 1][1], profits[i - 1][0] - prices[i]);
    }

    return profits[size - 1][0];
}

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/ 
int maxProfitIII(vector<int>& prices) {
    int size = static_cast<int>(prices.size());
    if (size <= 1) return 0;
    int trade = 3;
    vector<vector<vector<int>>> profits(size, vector<vector<int>>(trade, vector<int>(2, 0)));

    for (int j = 0; j < trade; j++) {
        profits[0][j][1] = -prices[0];
    }

    for (int i = 0; i < size; i++) {
        profits[i][0][1] = INT_MIN;
    }

    for (int i = 1; i < size; i++) {
        for (int j = 1; j < trade; j++) {
            profits[i][j][0] = max(profits[i - 1][j][0], profits[i - 1][j][1] + prices[i]);
            profits[i][j][1] = max(profits[i - 1][j][1], profits[i - 1][j - 1][0] - prices[i]);
        }
    }

    return profits[size - 1][trade - 1][0];

}

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/ 
int maxProfitWithCooldown(vector<int>& prices) {
    int size = static_cast<int>(prices.size());
    if (size <= 1) return 0;
    vector<vector<int>> profits(size, vector<int>(2, 0));
    profits[0][1] = -prices[0];
    profits[1][0] = max(0, profits[0][1] + prices[1]);
    profits[1][1] = max(profits[0][1], -prices[1]);

    for (int i = 2; i < size; i++) {
        profits[i][0] = max(profits[i - 1][0], profits[i - 1][1] + prices[i]);
        profits[i][1] = max(profits[i - 1][1], profits[i - 2][0] - prices[i]);
    }

    return profits[size - 1][0];
}

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
int maxProfitWithTransactionFee(vector<int>& prices, int fee) {
    int size = static_cast<int>(prices.size());
    if (size <= 1) return 0;

    vector<vector<int>> profits(size, vector<int>(2, 0));
    profits[0][1] = -prices[0] - fee;

    for (int i = 1; i < size; i++) {
        profits[i][0] = max(profits[i - 1][0], profits[i - 1][1] + prices[i]);
        profits[i][1] = max(profits[i - 1][1], profits[i - 1][0] - prices[i] - fee);
    }

    return profits[size - 1][0];
}

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/ 
int maxProfitIV(vector<int>& prices, int k) {
    int size = static_cast<int>(prices.size());
    if (size <= 1) return 0;

    int trade = k + 1;
    vector<vector<vector<int>>> profits(size, vector<vector<int>>(trade, vector<int>(2, 0)));

    for (int j = 0; j < trade; j++) {
        profits[0][j][1] = -prices[0];
    }

    for (int i = 0; i < size; i++) {
        profits[i][0][1] = INT_MIN;
    }

    for (int i = 1; i < size; i++) {
        for (int j = 1; j < trade; j++) {
            profits[i][j][0] = max(profits[i - 1][j][0], profits[i - 1][j][1] + prices[i]);
            profits[i][j][1] = max(profits[i - 1][j][1], profits[i - 1][j - 1][0] - prices[i]);
        }
    }

    return profits[size - 1][trade - 1][0];

}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int ans = 5;
    assert(ans == maxProfitI(prices));

    prices = {7, 6, 4, 3, 1};
    ans = 0;
    assert(ans == maxProfitI(prices));


    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
    prices = {7, 1, 5, 3, 6, 4};
    ans = 7;
    assert(ans == maxProfitII(prices));

    prices = {1, 2, 3, 4, 5};
    ans = 4;
    assert(ans == maxProfitII(prices));


    prices = {7, 6, 4, 3, 1};
    ans = 0;
    assert(ans == maxProfitII(prices));

    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/ 
    prices = {3, 3, 5, 0, 0, 3, 1, 4};
    ans = 6;
    assert(ans == maxProfitIII(prices));

    prices = {1, 2, 3, 4, 5};
    ans = 4;
    assert(ans == maxProfitIII(prices));


    prices = {7, 6, 4, 3, 1};
    ans = 0;
    assert(ans == maxProfitIII(prices));
    
    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/ 
    prices = {1, 2, 3, 0, 2};
    ans = 3;
    assert(ans == maxProfitWithCooldown(prices));

    prices = {2, 1, 4};
    ans = 3;
    assert(ans == maxProfitWithCooldown(prices));

    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
    prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    ans = 8;
    assert(ans == maxProfitWithTransactionFee(prices, fee));

    prices = {1, 3, 7, 5, 10, 3};
    fee = 3;
    ans = 6;
    assert(ans == maxProfitWithTransactionFee(prices, fee));

    // https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/
    int k = 2;
    prices = {2, 4, 1};
    ans = 2;
    assert(ans == maxProfitIV(prices, k));

    k = 2;
    prices = {3, 2, 6, 5, 0, 3};
    ans = 7;
    assert(ans == maxProfitIV(prices, k));
    
    return 0;
}