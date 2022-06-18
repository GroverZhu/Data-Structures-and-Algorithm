
#include <iostream>
#include <string>
#include <vector>

#include <cassert>

#include <Tree/BinaryTreeNode.h>

using namespace std;

// https://leetcode-cn.com/problems/reverse-string
void reverseString(vector<char>& s) {
    int size = static_cast<int>(s.size());
    int left = 0, right = size - 1;
    while (left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        ++left;
        --right;
    }
}

// https://leetcode-cn.com/problems/reverse-string-ii/
string reverseStr(string s, int k) {
    auto reverse = [&s](int begin, int end) {
        while (begin < end) {
            swap(s[begin], s[end]);
            ++begin;
            --end;
        }
    };

    int left = 0;
    int right = 0;
    int size = static_cast<int>(s.size());

    while (right < size) {
        int i = 0;
        for (i = 0; i < 2 * k && right < size; i++) {
            right++;
        }

        if (i >= k) {
            reverse(left, left + k - 1);
            left = right;
        } else if (i < k) {
            reverse(left, size - 1);
        }
    }

    return s;
}

// https://leetcode-cn.com/problems/reverse-words-in-a-string/
string reverseWord(string s) {
    auto reverse = [&s](int begin, int end) {
        while (begin < end) {
            swap(s[begin], s[end]);
            ++begin;
            --end;
        }
    };

    int left = 0;
    int right = 0;
    int size = static_cast<int>(s.size());

    while (right < size) {
        while (left < size && s[left] == ' ') ++left;
        right = left;
        while (right < size && !(s[right] == ' ')) ++right;

        if (right > size) break;

        reverse(left, right - 1);
        left = right;
    }
    return s;
}

// https://leetcode-cn.com/problems/reverse-words-in-a-string-iii
string reverseWords(string s) {
    int size = static_cast<int>(s.size());
    int fast = 0;
    int slow = 0;
    // 先去除左边的空格
    while (fast < size && s[fast] == ' ') ++fast;

    while (fast < size) {
        // 去除连续的空格
        if (fast - 1 >= 0 && s[fast - 1] == ' ' && s[fast] == s[fast - 1]) {
            ++fast;
        } else {  // 将字符往前移动
            s[slow++] = s[fast++];
        }
    }

    if (slow - 1 >= 0 && s[slow - 1] == ' ') {  // 末尾有多个空格的，会保留一个要去除
        s.resize(slow - 1);
        size = slow - 1;
    } else {
        s.resize(slow);
        size = slow;
    }
    // [left, right]
    auto reverse = [&s](int left, int right) {
        while (left < right) {
            swap(s[left], s[right]);
            ++left;
            --right;
        }
    };
    reverse(0, size - 1);
    int begin = 0, end = 0;
    while (end < size) {
        while (end < size && s[end] != ' ') ++end;
        reverse(begin, end - 1);
        end++;
        begin = end;
    }
    return s;
}

// https://leetcode-cn.com/problems/reverse-only-letters/
string reverseOnlyLetters(string s) {
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        while (left <= right && !isalpha(s[left])) ++left;
        while (right >= 0 && !isalpha(s[right])) --right;
        if (left >= right) break;
        swap(s[left], s[right]);
        ++left;
        --right;
    }
    return s;
}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/reverse-string
    vector<char> s, ans;
    s = {'h', 'e', 'l', 'l', 'o'};
    ans = {'o', 'l', 'l', 'e', 'h'};
    reverseString(s);
    assert(s == ans);

    s = {'H', 'a', 'n', 'n', 'a', 'h'};
    ans = {'h', 'a', 'n', 'n', 'a', 'H'};
    reverseString(s);
    assert(s == ans);

    // https://leetcode-cn.com/problems/reverse-string-ii/
    string s1 = "abcdefg";
    int k = 2;
    string ans1 = "bacdfeg";
    assert(ans1 == reverseStr(s1, k));

    s1 = "abcd";
    k = 2;
    ans1 = "bacd";
    assert(ans1 == reverseStr(s1, k));

    // https://leetcode-cn.com/problems/reverse-words-in-a-string/
    s1 = "Let's take LeetCode contest";
    ans1 = "s'teL ekat edoCteeL tsetnoc";
    assert(ans1 == reverseWord(s1));

    s1 = "God Ding";
    ans1 = "doG gniD";
    assert(ans1 == reverseWord(s1));

    // https://leetcode-cn.com/problems/reverse-words-in-a-string-iii
    s1 = "the sky is blue";
    ans1 = "blue is sky the";
    // assert(ans1 == reverseWords(s1));

    s1 = "  hello world  ";
    ans1 = "world hello";
    assert(ans1 == reverseWords(s1));

    s1 = "a good   example";
    ans1 = "example good a";
    assert(ans1 == reverseWords(s1));

    s1 = "  Bob    Loves  Alice   ";
    ans1 = "Alice Loves Bob";
    assert(ans1 == reverseWords(s1));

    s1 = "Alice does not even like bob";
    ans1 = "bob like even not does Alice";
    assert(ans1 == reverseWords(s1));

    // https://leetcode-cn.com/problems/reverse-only-letters/
    s1 = "ab-cd";
    ans1 = "dc-ba";
    assert(ans1 == reverseOnlyLetters(s1));

    s1 = "a-bC-dEf-ghIj";
    ans1 = "j-Ih-gfE-dCba";
    assert(ans1 == reverseOnlyLetters(s1));

    s1 = "Test1ng-Leet=code-Q!";
    ans1 = "Qedo1ct-eeLg=ntse-T!";
    assert(ans1 == reverseOnlyLetters(s1));
    return 0;
}