#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/plus-one/
vector<int> plusOne(vector<int>& digits) {
    int size = static_cast<int>(digits.size());

    int index = size - 1;
    int carry = 0;
    int tmp = digits[index] + 1;
    digits[index] = tmp % 10;
    carry = tmp / 10;
    index--;
    while (index >= 0 && carry != 0) {
        tmp = digits[index] + carry;
        digits[index] = tmp % 10;
        carry = tmp / 10;
        index--;
    }
    if (carry != 0) digits.insert(digits.begin(), carry);

    return digits;
}

int main(int argc, char* argv[]) {
    vector<int> digits;
    vector<int> ans;

    digits = {1, 2, 3};
    ans = {1, 2, 4};
    plusOne(digits);
    assert(digits == ans);

    digits = {4, 3, 2, 1};
    ans = {4, 3, 2, 2};
    plusOne(digits);
    assert(digits == ans);

    digits = {9};
    ans = {1, 0};
    plusOne(digits);
    assert(digits == ans);
    return 0;
}