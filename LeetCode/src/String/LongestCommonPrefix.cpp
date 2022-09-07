#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

struct TrieNode {
    char c;
    bool isEnd;
    map<char, TrieNode*> children;

    TrieNode() {
        c = '\0';
        isEnd = false;
        children = {};
    }

    TrieNode(char _c) {
        c = _c;
        isEnd = false;
        children = {};
    }

    ~TrieNode() {
        for (auto child : children) {
            delete child.second;
        }
    }
};

class Trie {
public:
    Trie() { root = new TrieNode(); }

    ~Trie() {
        if (root) {
            delete root;
        }
    }

    void insert(string s) {
        auto cur = root;
        for (auto c : s) {
            auto node = cur->children.find(c);
            if (node == cur->children.end()) {
                cur->children[c] = new TrieNode(c);
            }
            cur = cur->children[c];
        }
        cur->isEnd = true;
    }

    string longestCommonPrefix() {
        string result;
        queue<pair<char, TrieNode*>> q;
        q.push({'#', root});
        while (!q.empty()) {
            auto now = q.front();
            auto c = now.first;
            auto cur = now.second;
            q.pop();
            if (c != '#') result.push_back(c);
            if (cur->children.size() == 1 && !cur->isEnd) {
                auto node = cur->children.begin();
                q.push({node->first, node->second});
            }
        }
        return result;
    }

private:
    TrieNode* root;
};

// https://leetcode-cn.com/problems/longest-common-prefix/description/
string longestCommonPrefix(vector<string>& strs) {
    Trie trie = Trie();
    for (auto& str : strs) {
        trie.insert(str);
    }
    return trie.longestCommonPrefix();
}

int main(int argc, char* argv[]) {
    vector<string> strs;
    string ans;

    strs = {"flower", "flow", "flight"};
    ans = "fl";
    assert(ans == longestCommonPrefix(strs));

    strs = {"dog", "racecar", "car"};
    ans = "";
    assert(ans == longestCommonPrefix(strs));

    strs = {"", "b"};
    ans = "";
    assert(ans == longestCommonPrefix(strs));

    strs = {"ab", "a"};
    ans = "a";
    assert(ans == longestCommonPrefix(strs));

    return 0;
}