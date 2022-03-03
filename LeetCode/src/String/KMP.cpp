#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

void getNext(vector<int>& next, string& pat) {
    int size = static_cast<int>(pat.size());
    int j = 0;
    next[0] = j;

    for (int i = 1; i < size; i++) {
        while (j > 0 && pat[i] != pat[j]) { // 前后缀不相等
            j = next[j - 1];
        }

        if (pat[i] == pat[j]) { // 前后缀相等
            j++;
        }
        next[i] = j;
    }
}

// https://leetcode-cn.com/problems/implement-strstr/
int strStr(string& txt, string& pat) {
    int txt_size = static_cast<int>(txt.size());
    int pat_size = static_cast<int>(pat.size());

    if (pat_size < 1) return 0;

    vector<int> next(pat_size, 0);
    getNext(next, pat);

    int j = 0;
    for (int i = 0; i < txt_size; i++) {
        while (j > 0 && txt[i] != pat[j]) {
            j = next[j - 1];
        }

        if (txt[i] == pat[j]) {
            j++;
        }

        if (j == pat_size) {
            return i - pat_size + 1;
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    string txt = "hello";
    string pat = "ll";
    assert(2 == strStr(txt, pat));

    txt = "aaaaa";
    pat = "bba";
    assert(-1 == strStr(txt, pat));

    txt = "";
    pat = "";
    assert(0 == strStr(txt, pat));

    txt = "hello world";
    pat = "";
    assert(0 == strStr(txt, pat));

    txt = "mississippi";
    pat = "issip";
    assert(4 == strStr(txt, pat));
    return 0;
}