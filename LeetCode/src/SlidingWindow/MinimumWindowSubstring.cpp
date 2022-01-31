#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/minimum-window-substring/
string minWindow(string s, string t) {
    int sSize = static_cast<int>(s.size());
    int tSize = static_cast<int>(t.size());

    if (tSize > sSize) return "";

    map<char, int> need;
    for (int i = 0; i < tSize; i++){
        need[t[i]]++;
    }

    int left = 0;
    int right = 0;
    map<char, int> window;
    int len = sSize + 1;
    int count = 0;
    string result;

    while (right < sSize) {
        auto add = s[right];
        right++;

        if (need.find(add) != need.end()) {
            window[add]++;
            if (window[add] == need[add]) {
                ++count;
            }
        }

        while (count == static_cast<int>(need.size())) {
            int size = right - left;
            if (size < len) {
                len = size;
                result = s.substr(left, len);
            }

            auto del = s[left];
            ++left;
            if (need.find(del) != need.end()) {
                if (window[del] == need[del]) {
                    --count;
                }
                window[del]--;
            }
        }
    }

    return result;


}

int main(int argc, char* argv[]) {
    string s;
    string t;
    string result;
    string ans;

    s = "ADOBECODEBANC";
    t = "ABC";
    ans = "BANC";
    assert(ans == minWindow(s, t));

    s = "a";
    t = "a";
    ans = "a";
    assert(ans == minWindow(s, t));

    s = "a";
    t = "aa";
    ans = "";
    assert(ans == minWindow(s, t));

    return 0;
}
