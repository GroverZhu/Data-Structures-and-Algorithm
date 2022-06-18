#include <climits>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/perfect-squares/
int numSquares(int n) {
    vector<int> count(n + 1, INT_MAX);
    count[0] = 0;
    count[1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int k = 1; k * k <= i; k++) {
            if (i - (k * k) >= 0) {
                count[i] = min(count[i], count[i - k * k] + 1);
            }
        }
    }
    return count[n] == INT_MAX ? 0 : count[n];
}

int main(int argc, char* argv[]) {
    int n = 12;
    assert(3 == numSquares(n));

    n = 13;
    assert(2 == numSquares(n));

    return 0;
}