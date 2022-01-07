/**
 * @file palindrome.cpp
 * @author zry (groverzhu@gmail.com)
 * @brief 给定一个字符串，仅有大小写字母或?组成，其中?可以表示任意的字母，
 * 判断对于给定的字符串，能够组成一个回文字符串
 * @version 0.1
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool palindrome(string s) {
    int left = 0;
    int right = s.size() - 1;
    while (left <= right) {
        if (s[left] == '?' || s[right] == '?') {
            ++left;
            --right;
        } else if (s[left] == s[right]) {
            ++left;
            --right;
        } else if (s[left] != s[right]) {
            return false;
        }
    }

    return left > right;
}

int main(int argc, char* argv[]) {
    assert(palindrome("a") == true);
    assert(palindrome("zxcvbnmnbvcxz") == true);
    assert(palindrome("") == true);
    assert(palindrome("?a?") == true);
    assert(palindrome("?a??") == true);
    assert(palindrome("?abc") == false);
    assert(palindrome("?z?cvb") == false);
    assert(palindrome("?ab??a") == true);
    assert(palindrome("bab??a") == false);
    assert(palindrome("?") == true);
    assert(palindrome("b?b") == true);
    return 0;
}

