#include <iostream>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/longest-common-subsequence/
int longestCommonSubsequence(string text1, string text2) {
    int size1 = static_cast<int>(text1.size());
    int size2 = static_cast<int>(text2.size());
    vector<vector<int>> count(size1 + 1, vector<int>(size2 + 1, 0));

    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                count[i][j] = count[i - 1][j - 1] + 1;
            } else {
                count[i][j] = max(count[i - 1][j], count[i][j - 1]);
            }
        }
    }
    return count[size1][size2];
}

int main(int argc, char* argv[]) {
    string text1, text2;

    text1 = "abcde";
    text2 = "ace";
    assert(3 == longestCommonSubsequence(text1, text2));

    text1 = "abc";
    text2 = "abc";
    assert(3 == longestCommonSubsequence(text1, text2));

    text1 = "abc";
    text2 = "def";
    assert(0 == longestCommonSubsequence(text1, text2));

    return 0;
}