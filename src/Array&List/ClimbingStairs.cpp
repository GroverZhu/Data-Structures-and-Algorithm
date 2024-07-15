#include <iostream>
#include <vector>

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

// https://leetcode-cn.com/problems/climbing-stairs/

int climbStairsRecursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

int climbStairsIteration(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int climbStairs(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    int first = 1;
    int second = 2;

    n -= 1;
    while (--n) {
        int tmp = second;
        second = first + second;
        first = tmp;
    }

    return second;
}

// 进阶版，可以一次走一步，两步，三步，但是当前的选择不能跟前一次一样，比如不能连续两次都是走一步或者连续都走两步
int climbStairsInDiff(int n) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    if (n == 3) return 3;

    vector<vector<int>> steps(n + 1, vector<int>(4, 0));

    steps[1][1] = 1;
    steps[2][2] = 1;
    steps[3][1] = 1;
    steps[3][2] = 1;
    steps[3][3] = 1;

    for (int i = 4; i <= n; i++) {
        steps[i][1] = steps[i - 1][2] + steps[i - 1][3];
        steps[i][2] = steps[i - 2][1] + steps[i - 2][3];
        steps[i][3] = steps[i - 3][1] + steps[i - 3][2];
    }

    return steps[n][1] + steps[n][2] + steps[n][3];
}

// 更进阶版，给你一个数组，问有多少可能，这个就是组合，需要用到dfs，或者说是找零钱的解法

int main(int argc, char* argv[]) {
    int n = 1;
    int ans1 = climbStairsRecursive(n);
    int ans2 = climbStairsIteration(n);
    int ans3 = climbStairs(n);

    assert(ans1 == ans2);
    assert(ans2 == ans3);

    clock_t begin, end;

    n = 20;
    begin = clock();
    ans1 = climbStairsRecursive(n);
    end = clock();
    cout << "Recursive time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans2 = climbStairsIteration(n);
    end = clock();
    cout << "Iteration time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans3 = climbStairs(n);
    end = clock();
    cout << "Climb Stairs time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;

    assert(ans1 == ans2);
    assert(ans2 == ans3);

    n = 45;
    begin = clock();
    ans1 = climbStairsRecursive(n);
    end = clock();
    cout << "Recursive time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans2 = climbStairsIteration(n);
    end = clock();
    cout << "Iteration time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans3 = climbStairs(n);
    end = clock();
    cout << "Climb Stairs time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;

    assert(ans1 == ans2);
    assert(ans2 == ans3);

    assert(1 == climbStairsInDiff(1));
    assert(1 == climbStairsInDiff(2));
    assert(3 == climbStairsInDiff(3));
    assert(3 == climbStairsInDiff(4));
    assert(8 == climbStairsInDiff(6));
    assert(9 == climbStairsInDiff(7));

    return 0;
}