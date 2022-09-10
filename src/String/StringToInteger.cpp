#include <cassert>
#include <climits>
#include <iostream>
#include <string>

using namespace std;

// https://leetcode-cn.com/problems/string-to-integer-atoi/
int myAtoi(string s) {
    int size = static_cast<int>(s.size());
    if (size <= 0) return 0;
    int index = 0;
    // 去除空格
    while (index < size && s[index] == ' ') ++index;
    if (index == size) return 0;

    bool flag = true;  // 标记正负 true为正，false为负
    if (s[index] == '+') {
        ++index;
    } else if (s[index] == '-') {
        flag = false;
        ++index;
    }

    if (index == size) return 0;  // 仅有符号或全是空格

    int value = 0;

    while (index < size && isdigit(s[index])) {
        int cur = s[index] - '0';
        if (flag && ((value > INT_MAX / 10) || (value == INT_MAX / 10 && cur > INT_MAX % 10))) return INT_MAX;
        if (!flag && ((value > INT_MAX / 10) || (value == INT_MAX / 10 && cur >= INT_MAX % 10 + 1)))
            return INT_MIN;  // INT_MIN 最小值比 INT_MAX 多1，不能等到最后去转化，否则会溢出
        value = value * 10 + cur;
        ++index;
    }

    return flag ? value : -value;
}

int main(int argc, char* argv[]) {
    string s;

    s = "42";
    assert(42 == myAtoi(s));

    s = "   -42";
    assert(-42 == myAtoi(s));

    s = "4193 with words";
    assert(4193 == myAtoi(s));

    s = "099999999999999999999";
    assert(2147483647 == myAtoi(s));

    s = "-099999999999999999999";
    assert(-2147483648 == myAtoi(s));

    s = "asc123";
    assert(0 == myAtoi(s));

    s = "+-12";
    assert(0 == myAtoi(s));

    s = "-2147483648";
    assert(-2147483648 == myAtoi(s));

    return 0;
}