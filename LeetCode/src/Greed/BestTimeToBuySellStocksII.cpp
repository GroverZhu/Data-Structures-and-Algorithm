#include <iostream>
#include <vector>


#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
int maxProfit(vector<int>& prices) {
    int size = static_cast<int>(prices.size());
    int profit = 0;
    for (int i = 1; i < size; i++) {
        profit += max(0, prices[i] - prices[i - 1]);
    }
    return profit;
}

int main(int argc, char* argv[]) {
    vector<int> prices;

    prices = {7,1,5,3,6,4};
    assert(7 == maxProfit(prices));

    prices = {1, 2, 3, 4, 5};
    assert(4 == maxProfit(prices));

    prices = {7,6,4,3,1};
    assert(0 == maxProfit(prices));

    return 0;
}