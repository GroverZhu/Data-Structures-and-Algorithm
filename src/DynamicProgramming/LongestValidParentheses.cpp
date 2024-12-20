#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/longest-valid-parentheses/
int longestValidParentheses(string s) {
#if 1
    int size = static_cast<int>(s.size());
    stack<int> stk;

    stk.push(-1);
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (s[i] == '(') {
            stk.push(i);
        } else {
            stk.pop();
            if (stk.empty()) {
                stk.push(i);
            } else {
                result = max(result, i - stk.top());
            }
        }
    }

    return result;

#endif
#if 0
    int size = static_cast<int>(s.size());
    if (size < 2) return 0;
    vector<int> lens(size, 0);
    int result = 0;
    for (int i = 1; i < size; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                lens[i] = (i - 2 >= 0 ? lens[i - 2] : 0) + 2;
            } else if ((i - lens[i - 1] - 1) >= 0 && s[i - lens[i - 1] - 1] == '(') {
                lens[i] += lens[i - 1] + (i - lens[i - 1] - 2 >= 0 ? lens[i - lens[i - 1] - 2] : 0) + 2;
            }
        }
        result = max(result, lens[i]);
    }

    return result;
#endif
}

int main(int argc, char* argv[]) {
    string s;

    s = "(()";
    assert(2 == longestValidParentheses(s));

    s = ")()())";
    assert(4 == longestValidParentheses(s));

    s = "";
    assert(0 == longestValidParentheses(s));

    s = "(";
    assert(0 == longestValidParentheses(s));

    s = ")";
    assert(0 == longestValidParentheses(s));
    return 0;
}