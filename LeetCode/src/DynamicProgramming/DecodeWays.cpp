#include <iostream>
#include <vector>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/decode-ways/
int numDecodings(string s) {
    int size = static_cast<int>(s.size());
    if (size <= 0) return 0;
    if (s[0] == '0') return 0;
    vector<int> ways(size, 0);
    ways[0] = 1;
    for (int i = 1; i < size; i++) {
        int cur = s[i] - '0';
        int prev = s[i - 1] - '0';
        if (1 <= cur && cur <= 9) {
            ways[i] = ways[i - 1];
        }
        int aggr = prev * 10 + cur;
        if (10 <= aggr && aggr <= 26) {
            ways[i] += ((i - 2) >= 0 ? ways[i - 2] : 1);
        }
    }
    return ways[size - 1];
}
int main(int argc, char* argv[]) {
    string s;

    s = "12";
    // cout << numDecodings(s) << endl;
    assert(2 == numDecodings(s));

    s = "226";
    assert(3 == numDecodings(s));

    s = "0";
    assert(0 == numDecodings(s));
    return 0;
}