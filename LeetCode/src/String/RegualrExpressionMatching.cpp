#include <iostream>
#include <map>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/regular-expression-matching/

bool matchHelper(string s, int s_index, string p, int p_index, map<pair<int, int>, bool>& memo) {
    if (memo.find({s_index, p_index}) != memo.end()) return memo[{s_index, p_index}];

    int s_size = static_cast<int>(s.size());
    int p_size = static_cast<int>(p.size());

    if (p_index == p_size) {
        memo[{s_index, p_index}] = (s_index == s_size);
        return memo[{s_index, p_index}];
    }

    bool first = (s_index < s_size) && (s[s_index] == p[p_index] || p[p_index] == '.');

    bool ans = false;

    if (p_index <= p_size - 2 && p[p_index + 1] == '*') {
        ans = (first && matchHelper(s, s_index + 1, p, p_index, memo)) || matchHelper(s, s_index, p, p_index + 2, memo);
    } else {
        ans = first && matchHelper(s, s_index + 1, p, p_index + 1, memo);
    }

    memo[{s_index, p_index}] = ans;

    return ans;
}

bool isMatch(string s, string p) {
#if 0
    if (p.size() == 0) return s.size() == 0;

    bool first = (s.size() > 0) && (s[0] == p[0] || p[0] == '.');

    if (p.size() > 1 && p[1] == '*') {
        return (first && isMatch(s.substr(1), p)) || isMatch(s, p.substr(2));
    }

    return first && isMatch(s.substr(1), p.substr(1));
#endif

    map<pair<int, int>, bool> memo;

    return matchHelper(s, 0, p, 0, memo);
}

int main(int argc, char* argv[]) {
    string s, p;

    s = "aa";
    p = "a";
    assert(false == isMatch(s, p));

    s = "aa";
    p = "a*";
    assert(true == isMatch(s, p));

    s = "ab";
    p = ".*";
    assert(true == isMatch(s, p));

    return 0;
}