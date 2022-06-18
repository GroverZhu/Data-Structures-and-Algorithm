#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

char rollUp(char c) {
    if (c == '9') return '0';
    return c + 1;
}

char rollDown(char c) {
    if (c == '0') return '9';
    return c - 1;
}

// https://leetcode-cn.com/problems/open-the-lock/
int openLock(vector<string>& deadends, string target) {
    set<string> visited(deadends.begin(), deadends.end());
    if (visited.find(target) != visited.end() || visited.find("0000") != visited.end()) return -1;
    if (target == "0000") return 0;

    set<string> begin;
    set<string> end;
    begin.insert("0000");
    end.insert(target);
    visited.insert(target);
    visited.insert("0000");
    int step = 0;
    while (!begin.empty() && !end.empty()) {
        set<string> temp;

        for (auto s : begin) {
            for (int i = 0; i < static_cast<int>(s.size()); i++) {
                char base = s[i];

                s[i] = rollUp(base);
                if (end.find(s) != end.end()) return step + 1;
                if (visited.find(s) == visited.end()) {
                    visited.insert(s);
                    temp.insert(s);
                }

                s[i] = rollDown(base);
                if (end.find(s) != end.end()) return step + 1;
                if (visited.find(s) == visited.end()) {
                    visited.insert(s);
                    temp.insert(s);
                }

                s[i] = base;
            }
        }

        begin = temp;
        if (end.size() < begin.size()) {
            swap(begin, end);
        }
        ++step;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    vector<string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    string target = "0202";
    int ans = 6;
    assert(ans == openLock(deadends, target));

    deadends = {"8888"};
    target = "0009";
    ans = 1;
    assert(ans == openLock(deadends, target));

    deadends = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    target = "8888";
    ans = -1;
    assert(ans == openLock(deadends, target));

    deadends = {"0000"};
    target = "8888";
    ans = -1;
    assert(ans == openLock(deadends, target));

    deadends = {"0201", "0101", "0102", "1212", "2002"};
    target = "0000";
    ans = 0;
    assert(ans == openLock(deadends, target));
    return 0;
}