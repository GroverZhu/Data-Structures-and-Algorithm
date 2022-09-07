#include <cassert>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

// 实现 Trie (前缀树) https://leetcode-cn.com/problems/implement-trie-prefix-tree/
struct TrieNode {
    bool is_end;
    map<char, TrieNode*> next;

    TrieNode() {
        is_end = false;
        next = {};
    }

    ~TrieNode() {
        for (auto node : next) {
            if (node.second) delete node.second;
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

    void insert(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->next.find(c) == node->next.end()) {
                node->next[c] = new TrieNode();
            }
            node = node->next[c];
        }
        node->is_end = true;
    }

    bool search(string word) {
        auto node = root;
        for (auto c : word) {
            if (node->next.find(c) == node->next.end()) {
                return false;
            }
            node = node->next[c];
        }
        return node->is_end;
    }

    bool startsWith(string prefix) {
        auto node = root;
        for (auto c : prefix) {
            if (node->next.find(c) == node->next.end()) {
                return false;
            }
            node = node->next[c];
        }
        return true;
    }

    // 最长公共前缀 https://leetcode-cn.com/problems/longest-common-prefix/description/
    string longestCommonPrefix() {
        if (!root || root->next.size() != 1) return "";
        string prefix;
        queue<pair<char, TrieNode*>> q;
        q.push({'#', root});

        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            if (node.first != '#') prefix.push_back(node.first);
            if (node.second->next.size() == 1 && !node.second->is_end) {
                for (auto n : node.second->next) {
                    q.push({n.first, n.second});
                }
            }
        }
        return prefix;
    }

private:
    TrieNode* root;
};

// 最长公共前缀 https://leetcode-cn.com/problems/longest-common-prefix/description/
string longestCommonPrefix(vector<string>& strs) {
    Trie trie;
    for (auto str : strs) {
        trie.insert(str);
    }
    return trie.longestCommonPrefix();
}

// 单词搜索 II https://leetcode-cn.com/problems/word-search-ii/ 在该Trie结构下，leetcode会超时
void dfs(vector<vector<char>>& board, Trie& trie, set<string>& result, string& temp, int x, int y, int level) {
    if (board[x][y] < 'a') return;
    if (trie.search(temp)) {
        result.insert(temp);
    }

    board[x][y] -= 'a';

    const int LEN = 4;
    constexpr int dx[LEN] = {0, -1, 0, 1};
    constexpr int dy[LEN] = {1, 0, -1, 0};
    int rows = board.size();
    int cols = board[0].size();
    for (int k = 0; k < LEN; k++) {
        int next_x = x + dx[k];
        int next_y = y + dy[k];

        if (next_x >= 0 && next_x < rows && next_y >= 0 && next_y < cols && board[next_x][next_y] >= 'a' &&
            level < 10) {
            temp.push_back(board[next_x][next_y]);
            dfs(board, trie, result, temp, next_x, next_y, level + 1);
            temp.pop_back();
        }
    }

    board[x][y] += 'a';
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    Trie trie;
    for (auto str : words) {
        trie.insert(str);
    }

    set<string> result;
    int rows = board.size();
    int cols = board[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            string temp = "";
            dfs(board, trie, result, temp, i, j, 0);
        }
    }
    return vector<string>(result.begin(), result.end());
}

int main(int argc, char* argv[]) {
    auto begin = clock();

    Trie trie1;
    trie1.insert("apple");
    assert(true == trie1.search("apple"));
    assert(false == trie1.search("app"));
    assert(true == trie1.startsWith("app"));
    trie1.insert("app");
    assert(true == trie1.search("app"));

    vector<string> strs = {"flower", "flow", "flight"};
    string ans = "fl";
    assert(ans == longestCommonPrefix(strs));
    strs = {"dog", "racecar", "car"};
    ans = "";
    assert(ans == longestCommonPrefix(strs));
    strs = {"", "b"};
    ans = "";
    assert(ans == longestCommonPrefix(strs));
    strs = {"abc", "abc", "abc"};
    ans = "abc";
    assert(ans == longestCommonPrefix(strs));

    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};
    vector<string> words = {"oath", "pea", "eat", "rain"};
    vector<string> results = {"eat", "oath"};
    auto tmp = findWords(board, words);
    assert(results == tmp);

    board = {{'b', 'd', 'a', 'a', 'c', 'c', 'b', 'e'}, {'d', 'c', 'e', 'b', 'b', 'e', 'e', 'b'},
             {'b', 'd', 'b', 'e', 'b', 'a', 'a', 'e'}, {'b', 'c', 'd', 'a', 'd', 'd', 'a', 'c'},
             {'e', 'd', 'b', 'c', 'a', 'd', 'a', 'c'}, {'e', 'b', 'a', 'a', 'c', 'd', 'c', 'd'},
             {'d', 'e', 'c', 'c', 'b', 'd', 'd', 'c'}, {'c', 'a', 'c', 'e', 'c', 'b', 'd', 'c'},
             {'a', 'e', 'd', 'b', 'c', 'b', 'a', 'a'}, {'e', 'a', 'a', 'a', 'a', 'c', 'c', 'b'},
             {'d', 'e', 'e', 'e', 'c', 'b', 'c', 'e'}};
    words = {"cbcccec"};
    results = {"cbcccec"};
    tmp = findWords(board, words);
    assert(results == tmp);

    auto end = clock();
    cout << "All tests passed. Time cost: " << (1.0 * (end - begin) / CLOCKS_PER_SEC * 1000) << "ms." << endl;

    return 0;
}