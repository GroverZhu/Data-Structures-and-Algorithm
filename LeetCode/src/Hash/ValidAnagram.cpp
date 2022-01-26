#include <iostream>
#include <string>
#include <map>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/valid-anagram/
bool isAnagram(string s, string t) {
    int s_size = static_cast<int>(s.size());
    int t_size = static_cast<int>(t.size());

    if (s_size != t_size) return false;
    map<char, int> count;
    for (int i = 0; i < s_size; i++) {
        count[s[i]]++;
        count[t[i]]--;
    }

    for (auto node : count) {
        if (node.second != 0) return false;
    }
    return true;

}

int main(int argc, char* argv[]) {
    string s = "anagram";
    string t = "nagaram";
    assert(true == isAnagram(s, t));

    s = "rat";
    t = "car";
    assert(false == isAnagram(s, t));

    return 0;
}