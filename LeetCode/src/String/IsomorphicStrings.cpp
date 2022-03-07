#include <iostream>
#include <map>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/isomorphic-strings/
bool isIsomorphic(string s, string t) {
    int sSize = static_cast<int>(s.size());

    map<char, char> s2t;
    map<char, char> t2s;

    for (int i = 0; i < sSize; i++) {
        auto iter1 = s2t.find(s[i]);
        auto iter2 = t2s.find(t[i]);
        if (iter1 == s2t.end() && iter2 == t2s.end()) {
            s2t[s[i]] = t[i];
            t2s[t[i]] = s[i];
        } else if (iter1 == s2t.end() || iter2 == t2s.end()) {
            return false;
        } else {
            if (iter1->second != t[i] || iter2->second != s[i]) return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    string s, t;
    
    s = "egg";
    t = "add";
    assert(true == isIsomorphic(s, t));

    s = "foo";
    t = "bar";
    assert(false == isIsomorphic(s, t));

    s = "paper";
    t = "title";
    assert(true == isIsomorphic(s, t));
    return 0;
}