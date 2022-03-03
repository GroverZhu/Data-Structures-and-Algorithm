#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/length-of-last-word/
int lengthOfLastWord(string s) {
    int size = static_cast<int>(s.size());
    int index = size - 1;
    while (index >= 0 && s[index] == ' ') --index;
    int end = index;
    while (index >= 0 && s[index] != ' ') --index;
    return end - index;

}

int main(int argc, char* argv[]) {
    string s = "Hello World";
    assert(5 == lengthOfLastWord(s));

    s = "   fly me   to   the moon  ";
    assert(4 == lengthOfLastWord(s));

    s = "luffy is still joyboy";
    assert(6 == lengthOfLastWord(s));

    s = " ";
    assert(0 == lengthOfLastWord(s));

    s = "";
    assert(0 == lengthOfLastWord(s));
    return 0;
}