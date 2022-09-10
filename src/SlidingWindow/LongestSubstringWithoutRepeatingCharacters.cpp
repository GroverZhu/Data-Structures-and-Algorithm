#include <iostream>
#include <map>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s) {
    int size = static_cast<int>(s.size());
    if (size <= 1) return size;

    int left = 0;
    int right = 0;
    map<char, int> cnt;
    int result = 0;
    while (right < size) {
        auto add = s[right];
        right++;
        cnt[add]++;

        while (cnt[add] > 1) {
            auto del = s[left];
            left++;
            cnt[del]--;
        }

        result = max(result, right - left);
    }
    return result;
}

int main(int argc, char* argv[]) {
    string s;
    int result, ans;

    s = "abcabcbb";
    ans = 3;
    result = lengthOfLongestSubstring(s);
    assert(result == ans);

    s = "bbbbb";
    ans = 1;
    result = lengthOfLongestSubstring(s);
    assert(result == ans);

    s = "pwwkew";
    ans = 3;
    result = lengthOfLongestSubstring(s);
    assert(result == ans);

    s = "";
    ans = 0;
    result = lengthOfLongestSubstring(s);
    assert(result == ans);
    return 0;
}
