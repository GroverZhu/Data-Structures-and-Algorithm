#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    int pSize = static_cast<int>(p.size());
    int sSize = static_cast<int>(s.size());

    map<char, int> need;
    map<char, int> window;

    for (int i = 0; i < pSize; i++) {
        need[p[i]]++;
    }

    int left = 0;
    int right = 0;
    vector<int> result;

    while (right < sSize) {
        auto add = s[right];
        ++right;

        if (need.find(add) != need.end()) {
            window[add]++;

            while (window[add] > need[add]) {
                auto del = s[left];
                left++;
                window[del]--;
            }

            if (window == need) {
                result.push_back(left);
            }
        } else {
            window.clear();
            left = right;
        }
    }

    return result;
}


int main(int argc, char* argv[]) {
    string s = "cbaebabacd";
    string p = "abc";
    vector<int> ans = {0, 6};
    vector<int> result = findAnagrams(s, p);
    assert(ans == result);


    s = "abab";
    p = "ab";
    ans = {0, 1, 2};
    result = findAnagrams(s, p);
    assert(ans == result);

    return 0;
}
