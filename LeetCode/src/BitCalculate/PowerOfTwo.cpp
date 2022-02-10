#include <iostream>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/power-of-two/
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int main(int argc, char* argv[]) {
    assert(true == isPowerOfTwo(1));
    assert(true == isPowerOfTwo(16));
    assert(true == isPowerOfTwo(8));
    assert(false == isPowerOfTwo(3));
    assert(false == isPowerOfTwo(-1));
}