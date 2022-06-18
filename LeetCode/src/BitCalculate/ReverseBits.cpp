#include <cassert>
#include <iostream>

using namespace std;

// https://leetcode-cn.com/problems/reverse-bits/
uint32_t reverseBits(uint32_t n) {
    n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    return n;
}

int main(int argc, char* argv[]) {
    uint32_t n = 0b00000010100101000001111010011100;
    uint32_t ans = 0b00111001011110000010100101000000;
    uint32_t result = reverseBits(n);
    assert(ans == result);

    n = 0b11111111111111111111111111111101;
    ans = 0b10111111111111111111111111111111;
    result = reverseBits(n);
    assert(ans == result);

    return 0;
}