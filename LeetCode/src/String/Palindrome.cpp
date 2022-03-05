#include <iostream>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/valid-palindrome/ 
bool isPalindrome(string s) {
    int size = static_cast<int>(s.size());
    int left = 0;
    int right = size - 1;
    while (left < right) {
        while ((left < size) && !(isalpha(s[left]) || isdigit(s[left]))) ++left;
        while ((right >= 0) && !(isalpha(s[right]) || isdigit(s[right]))) --right;
        if (left >= right) break;

        if (isalpha(s[left]) && isalpha(s[right])) {
            if (tolower(s[left]) != tolower(s[right])) return false;
        } else if (isdigit(s[left]) && isdigit(s[right])) {
            if (s[left] != s[right]) return false;
        } else {
            return false;
        }
        ++left;
        --right;
    }
    return true;

}

// https://leetcode-cn.com/problems/valid-palindrome-ii/
bool validPalindrome(string s) {
    // [begin, end]
    auto isPalindrome = [&s](int begin, int end) {
        while (begin < end) {
            if (s[begin] != s[end]) return false;
            ++begin;
            --end;
        }
        return true;
    };

    int size = static_cast<int>(s.size());
    int left = 0;
    int right = size - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return isPalindrome(left + 1, right) || isPalindrome(left, right - 1);
        }
        ++left;
        --right;
    }

    return true;
}

// https://leetcode-cn.com/problems/longest-palindromic-substring/
string longestPalindrome(string s) {
    int size = static_cast<int>(s.size());
    if (size <= 1) return s;
    vector<vector<int>> lens(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) lens[i][i] = 1; // base case
    int maxLen = 1;
    int begin = 0;

    for (int offset = 1; offset < size; offset++) {
        for (int i = 0; i < size - offset; i++) {
            int j = i + offset;
            if (s[i] == s[j]) {
                if (j - i < 2) { // base case 长度为2的回文串
                    lens[i][j] = 2;
                } else if (lens[i + 1][j - 1] != 0) {
                    lens[i][j] = lens[i + 1][j - 1] + 2;
                }
                if (lens[i][j] > maxLen) {
                    begin = i;
                    maxLen = j - i + 1;
                }
            } else {
                lens[i][j] = 0;
            }
        }
    }

    return s.substr(begin, maxLen);

}

// https://leetcode-cn.com/problems/longest-palindromic-subsequence/
int longestPalindromeSubseq(string s) {
    int size = static_cast<int>(s.size());
    vector<vector<int>> lens(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        lens[i][i] = 1;
    }

    for (int offset = 1; offset < size; offset++) {
        for (int i = 0; i < size - offset; i++) {
            int j = i + offset;

            if (s[i] == s[j]) {
                if (j - i < 2) {
                    lens[i][j] = 2;
                } else {
                    lens[i][j] = lens[i + 1][j - 1] + 2; 
                }
            } else {
                lens[i][j] = max(lens[i + 1][j], lens[i][j - 1]);
            }
        }
    }

    return lens[0][size - 1];
}

int main(int argc, char* argv[]) {

    // https://leetcode-cn.com/problems/valid-palindrome/
    string s = "A man, a plan, a canal: Panama";
    assert(true == isPalindrome(s));

    s = "race a car";
    assert(false == isPalindrome(s));

    s = "OP";
    assert(false == isPalindrome(s));

    // https://leetcode-cn.com/problems/valid-palindrome-ii/
    s = "aba";
    assert(true == validPalindrome(s));

    s = "abca";
    assert(true == validPalindrome(s));

    s = "abc";
    assert(false == validPalindrome(s));

    s = "deeee";
    assert(true == validPalindrome(s));

    // https://leetcode-cn.com/problems/longest-palindromic-substring/
    s = "babad";
    string ans = longestPalindrome(s);
    assert(3 == ans.size() && isPalindrome(ans));

    s = "cbbd";
    ans = longestPalindrome(s);
    assert(2 == ans.size() && isPalindrome(ans));

    s = "ccc";
    ans = longestPalindrome(s);
    assert(3 == ans.size() && isPalindrome(ans));

    s = "aacabdkacaa";
    ans = longestPalindrome(s);
    assert(3 == ans.size() && isPalindrome(ans));


    // https://leetcode-cn.com/problems/longest-palindromic-subsequence/
    s = "bbbab";
    assert(4 == longestPalindromeSubseq(s));

    s = "cbbd";
    assert(2 == longestPalindromeSubseq(s));

    return 0;
}