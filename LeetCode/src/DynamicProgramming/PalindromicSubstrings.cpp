#include <iostream>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/palindromic-substrings/ 
int countSubstrings(string s) {
    int size = static_cast<int>(s.size());
    vector<vector<bool>> isPalindromic(size, vector<bool>(size, false));
    int count = 0;
    for (int i = 0; i < size; i++) {
        isPalindromic[i][i] = true; // 单个字符组成
        ++count;
    }

    for (int offset = 1; offset < size; offset++) {
        for (int i = 0; i < size - offset; i++) {
            int j = i + offset;
            
            if (s[i] == s[j]) {
                if (j - i + 1 <= 2) { // 两个字符组成
                    isPalindromic[i][j] = true;
                } else {
                    isPalindromic[i][j] = isPalindromic[i + 1][j - 1];
                }
            }
            if (isPalindromic[i][j]) ++count;
        }
    }

    return count;

}

// todo manacher算法 https://leetcode-cn.com/problems/palindromic-substrings/solution/hui-wen-zi-chuan-by-leetcode-solution/

int main(int argc, char* argv[]) {
    string s;
    s = "abc";
    assert(3 == countSubstrings(s));

    s = "aaa";
    // cout << countSubstrings(s) << endl;
    assert(6 == countSubstrings(s));

    return 0;
}