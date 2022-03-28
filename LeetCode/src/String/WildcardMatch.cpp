#include <iostream>
#include <string>
#include <map>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/wildcard-matching/

// 记忆化搜索
bool matchHelper(string& s, int s_index, string& p, int p_index, map<pair<int, int>, bool>& memo) {
    if (memo.find({s_index, p_index}) != memo.end()) return memo[{s_index, p_index}];

    int s_size = static_cast<int>(s.size());
    int p_size = static_cast<int>(p.size());

    if (p_index == p_size) {
        return s_index == s_size;
    }

    if (s_index == s_size) {
        for (int i = p_index; i < p_size; i++) {
            if (p[i] != '*') return false;
        }
        return true;
    }

    bool ans = false;
    if (p[p_index] != '*') {
        ans = (s[s_index] == p[p_index] || p[p_index] == '?') && matchHelper(s, s_index + 1, p, p_index + 1, memo);
    } else {
        ans = matchHelper(s, s_index, p, p_index + 1, memo) || matchHelper(s, s_index + 1, p, p_index, memo);
    }
    memo[{s_index, p_index}] = ans;
    return ans;
}

bool isMatch(string s, string p) {

#if 0  // 采用递归调用
    if (p.size() == 0) return s.size() == 0;
    if (s.size() == 0) {
        for (auto& c : p) {
            if (c != '*') return false;
        }
        return true;
    }


    if (p[0] != '*') {
        return (s[0] == p[0] || p[0] == '?') && isMatch(s.substr(1), p.substr(1));
    }

    // 匹配0次跟1次
    return isMatch(s, p.substr(1)) || isMatch(s.substr(1), p);
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
    p = "*";
    assert(true == isMatch(s, p));

    s = "cb";
    p = "?a";
    assert(false == isMatch(s, p));


    s = "adceb";
    p = "*a*b";
    assert(true == isMatch(s, p));

    s = "acdcb";
    p = "a*c?b";
    assert(false == isMatch(s, p));


    s = "aaaabaaaabbbbaabbbaabbaababbabbaaaababaaabbbbbbaabbbabababbaaabaabaaaaaabbaabbbbaababbababaabbbaababbbba";
    p = "*****b*aba***babaa*bbaba***a*aaba*b*aa**a*b**ba***a*a*";
    assert(true == isMatch(s, p));

    s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
    p = "a*******b";
    assert(false == isMatch(s, p));

    return 0;
}