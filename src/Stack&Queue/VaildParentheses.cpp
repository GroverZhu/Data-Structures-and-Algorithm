#include <cassert>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// https://leetcode-cn.com/problems/valid-parentheses/
bool isValid(string s) {
    int size = static_cast<int>(s.size());
    if (size == 0) return true;
    if (size % 2 == 1) return false;

    stack<char> stk;

    for (int i = 0; i < size; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stk.push(s[i]);
        } else if (s[i] == ')') {
            if (stk.empty() || stk.top() != '(') return false;
            stk.pop();
        } else if (s[i] == ']') {
            if (stk.empty() || stk.top() != '[') return false;
            stk.pop();
        } else if (s[i] == '}') {
            if (stk.empty() || stk.top() != '{') return false;
            stk.pop();
        }
    }

    return stk.empty();
}

int main(int argc, char* argv[]) {
    string s = "()";
    assert(true == isValid(s));

    s = "()[]{}";
    assert(true == isValid(s));

    s = "(]";
    assert(false == isValid(s));

    s = "([)]";
    assert(false == isValid(s));

    s = "{[()]}";
    assert(true == isValid(s));
    return 0;
}