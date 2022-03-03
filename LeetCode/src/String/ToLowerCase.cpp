#include <iostream>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/to-lower-case/
string toLowerCase(string s) {
    for (auto& c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = (c - 'A') + 'a';
        }
    }
    return s;
}
int main(int argc, char* argv[]) {
    string s;

    s = "Hello";
    assert("hello" == toLowerCase(s));

    s = "here";
    assert("here" == toLowerCase(s));

    s = "LOVELY";
    assert("lovely" == toLowerCase(s));
    return 0;
}
