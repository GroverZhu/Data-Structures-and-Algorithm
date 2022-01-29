#include <iostream>
#include <string>
#include <stack>
#include <deque>
#include <ctype.h>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/basic-calculator/
// https://leetcode-cn.com/problems/basic-calculator-ii/
// https://leetcode-cn.com/problems/basic-calculator-iii/
int calculateHelper(deque<char>& s) {
    stack<int> stk;
    int num = 0;
    char sign = '+';

    while (s.size() > 0) {
        char cur = s.front();
        s.pop_front();

        if (isdigit(cur)) {
            num = num * 10 + (cur - '0');
        }

        if (cur == '(') {
            num = calculateHelper(s);
        }

        if ((!isdigit(cur) && cur != ' ') || s.size() == 0) {
            int prev;
            switch (sign) {
                case '+':
                    stk.push(num);
                    break;
                case '-':
                    stk.push(-num);
                    break;
                case '*':
                    prev = stk.top();
                    stk.pop();
                    stk.push(prev * num);
                    break;
                case '/':
                    prev = stk.top();
                    stk.pop();
                    stk.push(prev / num);
                    break;
                default:
                    break;
            }
            sign = cur;
            num = 0;
        }
    
        if (cur == ')') break;
    }

    int result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }

    return result;
}

int calculate(string s) {
    deque<char> q(s.begin(), s.end());
    return calculateHelper(q);
}

int main(int argc, char* argv[]) {
    string s = "1 + 1";
    int ans = 2;
    assert(calculate(s) == ans);

    s = " 2 - 1 + 2 ";
    ans = 3;
    assert(calculate(s) == ans);

    s = "(1+(4+5+2)-3)+(6+8)";
    ans = 23;
    assert(calculate(s) == ans);

    s = " 1 + 2 * 3 - 5 ";
    ans = 2;
    assert(calculate(s) == ans);
    return 0;
}