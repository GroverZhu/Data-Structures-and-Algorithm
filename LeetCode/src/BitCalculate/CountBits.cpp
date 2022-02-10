#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/counting-bits/description/
vector<int> countBits(int n) {
    vector<int> result(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        result[i] = result[i & (i - 1)] + 1;
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<int> ans, result;
    int n;

    n = 2;
    ans = {0, 1, 1};
    result =  countBits(n);
    assert(ans == result);


    n = 5;
    ans = {0, 1, 1, 2, 1, 2};
    result =  countBits(n);
    assert(ans == result);
}