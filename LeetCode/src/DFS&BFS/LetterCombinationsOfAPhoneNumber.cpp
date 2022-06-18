#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<char, string> refs = {
    {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
};

void dfs(vector<string>& result, string& digits, int index, string& tmp) {
    if (tmp.size() == digits.size()) {
        result.push_back(tmp);
        return;
    }

    for (auto c : refs[digits[index]]) {
        tmp.push_back(c);
        dfs(result, digits, index + 1, tmp);
        tmp.pop_back();
    }
}

// https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
vector<string> letterCombinations(string digits) {
    int size = static_cast<int>(digits.size());
    vector<string> result;

    if (size <= 0) return result;
    string tmp;
    dfs(result, digits, 0, tmp);

    return result;
}

int main(int argc, char* argv[]) {
    string digits;
    set<string> ans, result;
    vector<string> tmp;

    digits = "23";
    ans = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    tmp = letterCombinations(digits);
    result = set<string>(tmp.begin(), tmp.end());
    assert(ans == result);

    digits = "2";
    ans = {"a", "b", "c"};
    tmp = letterCombinations(digits);
    result = set<string>(tmp.begin(), tmp.end());
    assert(ans == result);

    digits = "223";
    ans = {"aad", "aae", "aaf", "abd", "abe", "abf", "acd", "ace", "acf", "bad", "bae", "baf", "bbd", "bbe",
           "bbf", "bcd", "bce", "bcf", "cad", "cae", "caf", "cbd", "cbe", "cbf", "ccd", "cce", "ccf"};
    tmp = letterCombinations(digits);
    result = set<string>(tmp.begin(), tmp.end());
    assert(ans == result);
    return 0;
}