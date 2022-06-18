#include <algorithm>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/assign-cookies/
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int gSize = static_cast<int>(g.size());
    int sSize = static_cast<int>(s.size());

    int gIndex = 0;
    int sIndex = 0;

    while (gIndex < gSize && sIndex < sSize) {
        if (g[gIndex] <= s[sIndex]) {
            gIndex++;
            sIndex++;
        } else {
            while (sIndex < sSize && g[gIndex] > s[sIndex]) sIndex++;
        }
    }

    return gIndex;
}

int main(int argc, char* argv[]) {
    vector<int> g, s;

    g = {1, 2, 3};
    s = {1, 1};
    assert(1 == findContentChildren(g, s));

    g = {1, 2};
    s = {1, 2, 3};
    assert(2 == findContentChildren(g, s));

    return 0;
}