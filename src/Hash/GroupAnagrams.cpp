#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> result;
    map<string, vector<string>> cache;
    for (auto str : strs) {
        auto tmp = str;
        sort(tmp.begin(), tmp.end());
        cache[tmp].push_back(str);
    }

    for (auto node : cache) {
        result.push_back(node.second);
    }

    return result;
}

int main(int argc, char* argv[]) {
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto result = groupAnagrams(strs);
    auto ans = vector<vector<string>>({{"bat"}, {"ate", "eat", "tea"}, {"nat", "tan"}});

    multiset<multiset<string>> ans_ref;
    for (auto strs : ans) {
        multiset<string> tmp;
        for (auto str : strs) {
            tmp.insert(str);
        }
        ans_ref.insert(tmp);
    }

    multiset<multiset<string>> result_ref;
    for (auto strs : result) {
        multiset<string> tmp;
        for (auto str : strs) {
            tmp.insert(str);
        }
        result_ref.insert(tmp);
    }

    assert(ans_ref == result_ref);

    // {""} -> {{""}}

    strs = {""};
    result = groupAnagrams(strs);
    ans = vector<vector<string>>({{""}});
    ans_ref.clear();
    result_ref.clear();

    for (auto strs : ans) {
        multiset<string> tmp;
        for (auto str : strs) {
            tmp.insert(str);
        }
        ans_ref.insert(tmp);
    }

    for (auto strs : result) {
        multiset<string> tmp;
        for (auto str : strs) {
            tmp.insert(str);
        }
        result_ref.insert(tmp);
    }

    assert(ans_ref == result_ref);

    // {"a"} -> {{"a"}}
    strs = {"a"};
    result = groupAnagrams(strs);
    ans = vector<vector<string>>({{"a"}});
    ans_ref.clear();
    result_ref.clear();

    for (auto strs : ans) {
        multiset<string> tmp;
        for (auto str : strs) {
            tmp.insert(str);
        }
        ans_ref.insert(tmp);
    }

    for (auto strs : result) {
        multiset<string> tmp;
        for (auto str : strs) {
            tmp.insert(str);
        }
        result_ref.insert(tmp);
    }

    assert(ans_ref == result_ref);

    return 0;
}