#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

struct TrieNode {
    bool is_end;
    map<char, TrieNode*> next;
    TrieNode() {
        is_end = false;
        next = {};
    }
    ~TrieNode() {
        for (auto node : next) {
            delete node.second;
        }
    }
};

class Trie {
public:

    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(string s) {
        auto node = this->root;
        for (auto c : s) {
            if (node->next.find(c) == node->next.end()) {
                node->next[c] = new TrieNode();
            }
            node = node->next[c];
        }
        node->is_end = true;
    }

    bool search(string s) {
        auto node = this->root;
        for (auto c: s) {
            if (node->next.find(c) == node->next.end()) return false;
            node = node->next[c];
        }
        return node->is_end;
    }

    bool startWith(string s) {
        auto node = this->root;
        for (auto c : s) {
            if (node->next.find(c) == node->next.end()) return false;
            node = node->next[c];
        }
        return true;
    }

    string longestCommonPrefix() {
        // bfs 查找最长公共前缀
        if (!root || root->next.size() != 1) return "";

        queue<pair<TrieNode*, char>> q;
        q.push({root, '#'});
        string result;
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            if (node.second != '#') {
                result.push_back(node.second);
            }

            for (auto n : node.first->next) {
                auto c = n.first;
                auto ptr = n.second;
                if (node.first->next.size() == 1 && !node.first->is_end) {
                    q.push({ptr, c});
                }
            }
        }

        return result;
    }

private:
    TrieNode* root;

};

string longestCommonPrefix(vector<string>& strs) {
    Trie trie;
    for (auto str : strs) {
        trie.insert(str);
    }
    return trie.longestCommonPrefix();
}

int main(int argc, char* argv[]) {
    vector<string> strs = {"d", "daa", "da"};
    cout << longestCommonPrefix(strs) << endl;
    return 0;
}