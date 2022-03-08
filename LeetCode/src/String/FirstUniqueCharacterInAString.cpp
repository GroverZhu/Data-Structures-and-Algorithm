#include <iostream>
#include <string>
#include <map>
#include <queue>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/first-unique-character-in-a-string/
int firstUniqChar(string s) {
#if 0
    map<char, int> ref;
    for (auto c : s) {
        ref[c]++;
    }
    int size = static_cast<int>(s.size());
    for (int i = 0; i < size; i++) {
        if (ref[s[i]] == 1) {
            return i;
        }
    }
    return -1;
#endif

#if 1
    map<char, int> ref;
    queue<pair<char, int>> q;
    int size = static_cast<int>(s.size());
    for (int i = 0; i < size; i++) {
        if (ref.find(s[i]) == ref.end()) {
            ref[s[i]] = i;
            q.push({s[i], i});
        } else {
            ref[s[i]] = -1;
            while (!q.empty() && ref[q.front().first] == -1) {
                q.pop();
            }
        }
    }

    return q.empty() ? -1 : q.front().second;

#endif
}

int main(int argc, char* argv[]) {
    string s;

    s = "leetcode";
    assert(0 == firstUniqChar(s));
    
    s = "loveleetcode";
    assert(2 == firstUniqChar(s));

    s = "aabb";
    assert(-1 == firstUniqChar(s));
    return 0;
}