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
    cout << "Recursive time cost: " << (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans2 = climbStairsIteration(n);
    end = clock();
    cout << "Iteration time cost: " << (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

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
    cout << "Recursive time cost: " << (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans2 = climbStairsIteration(n);
    end = clock();
    cout << "Iteration time cost: " << (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms\t";

    begin = clock();
    ans3 = climbStairs(n);
    end = clock();
    cout << "Climb Stairs time cost: " << 1.0 * (end - begin) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;

    assert(ans1 == ans2);
    assert(ans2 == ans3);

    return 0;
}