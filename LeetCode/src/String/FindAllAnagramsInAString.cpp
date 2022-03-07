#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    int size1 = static_cast<int>(s.size());
    int size2 = static_cast<int>(p.size());

    map<char, int> need;
    for (int i = 0; i < size2; i++) {
        need[p[i]]++;
    }

    map<char, int> window;
    int left = 0;
    int right = 0;

    vector<int> result;
    
    while (right < size1) {
        auto add = s[right];
        right++;
        if (need.find(add) != need.end()) {
            window[add]++;
            while (window[add] > need[add]) {
                auto del = s[left];
                left++;
                window[del]--;
            }
            if (window == need) {
                result.push_back(left);
                window[s[left]]--;
                left++;
            }

        } else {
            window.clear();
            left = right;
        }
    }

    // for (auto num : result) {
    //     cout << num << "\t";
    // }
    // cout << endl;
    return result;
}

int main(int argc, char* argv[]) {
    string s, p;
    vector<int> ans;

    s = "cbaebabacd";
    p = "abc";
    ans = {0, 6};
    assert(ans == findAnagrams(s, p));


    s = "abab";
    p = "ab";
    ans = {0, 1, 2};
    assert(ans == findAnagrams(s, p));

    return 0;
}