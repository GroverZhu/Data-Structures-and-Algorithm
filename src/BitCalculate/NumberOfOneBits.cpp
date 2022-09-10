#include <cassert>
#include <cstdint>

using namespace std;

// https://leetcode-cn.com/problems/number-of-1-bits/
int hammingWeight(uint32_t n) {
    int cnt = 0;
    while (n) {
        n &= (n - 1);
        cnt++;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    uint32_t n;
    int ans;
    int result;

    n = 0b1011;
    ans = 3;
    result = hammingWeight(n);
    assert(ans == result);

    n = 0b10000000;
    ans = 1;
    result = hammingWeight(n);
    assert(ans == result);

    n = 0b11111111111111111111111111111101;
    ans = 31;
    result = hammingWeight(n);
    assert(ans == result);
}