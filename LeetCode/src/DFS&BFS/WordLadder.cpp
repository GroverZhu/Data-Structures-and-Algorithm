#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/word-ladder/
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    set<string> cache(wordList.begin(), wordList.end());
    if (cache.find(endWord) == cache.end()) return 0;

    set<string> begin;
    set<string> end;
    set<string> visited;

    begin.insert(beginWord);
    end.insert(endWord);
    visited.insert(beginWord);
    visited.insert(endWord);

    int step = 1;

    while (!begin.empty() && !end.empty()) {
        set<string> tmp;
        for (auto str : begin) {
            for (auto& c : str) {
                auto reversed = c;
                for (char t = 'a'; t <= 'z'; t++) {
                    if (t == c) continue;
                    c = t;
                    if (end.find(str) != end.end()) return step + 1;
                    if (visited.find(str) == visited.end() && cache.find(str) != cache.end()) {
                        tmp.insert(str);
                        visited.insert(str);
                    }
                }
                c = reversed;
            }
        }
        swap(begin, tmp);
        if (begin.size() > end.size()) swap(begin, end);
        ++step;
    }

    return 0;
}

// https://leetcode-cn.com/problems/word-ladder-ii/
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    set<string> cache(wordList.begin(), wordList.end());
    vector<vector<string>> result;
    if (cache.find(endWord) == cache.end()) return result;

    queue<vector<string>> q;
    q.push({beginWord});
    set<string> visited;
    int level = 1;
    int minStep = INT_MAX;

    while (!q.empty()) {
        auto path = q.front();
        q.pop();

        if (static_cast<int>(path.size()) > level) {
            for (auto str : visited) cache.erase(str);
            visited.clear();

            if (static_cast<int>(path.size()) > minStep) {
                break;
            } else {
                level = static_cast<int>(path.size());
            }
        }

        auto str = path.back();
        for (auto& base : str) {
            auto reversed = base;
            for (int c = 'a'; c <= 'z'; c++) {
                if (base == c) continue;
                base = c;
                if (cache.find(str) != cache.end()) {
                    auto newPath = path;
                    newPath.emplace_back(str);
                    if (str == endWord) {
                        result.push_back(newPath);
                        minStep = level;
                    } else {
                        q.push(newPath);
                        visited.insert(str);
                    }
                }
            }
            base = reversed;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    string beginWord, endWord;
    vector<string> wordList;
    vector<vector<string>> lists;
    set<vector<string>> ans_set;
    set<vector<string>> result_set;

    beginWord = "hit";
    endWord = "cog";
    wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    assert(5 == ladderLength(beginWord, endWord, wordList));
    lists = findLadders(beginWord, endWord, wordList);
    result_set = set<vector<string>>(lists.begin(), lists.end());
    ans_set = {{"hit", "hot", "dot", "dog", "cog"}, {"hit", "hot", "lot", "log", "cog"}};
    assert(ans_set == result_set);

    beginWord = "hit";
    endWord = "cog";
    wordList = {"hot", "dot", "dog", "lot", "log"};
    assert(0 == ladderLength(beginWord, endWord, wordList));
    lists = findLadders(beginWord, endWord, wordList);
    result_set = set<vector<string>>(lists.begin(), lists.end());
    ans_set = {};
    assert(ans_set == result_set);

    beginWord = "hot";
    endWord = "dog";
    wordList = {"hot", "dog"};
    assert(0 == ladderLength(beginWord, endWord, wordList));
    lists = findLadders(beginWord, endWord, wordList);
    result_set = set<vector<string>>(lists.begin(), lists.end());
    ans_set = {};
    assert(ans_set == result_set);

    beginWord = "red";
    endWord = "tax";
    wordList = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
    assert(4 == ladderLength(beginWord, endWord, wordList));
    lists = findLadders(beginWord, endWord, wordList);
    result_set = set<vector<string>>(lists.begin(), lists.end());
    ans_set = {{"red", "ted", "tad", "tax"}, {"red", "ted", "tex", "tax"}, {"red", "rex", "tex", "tax"}};
    assert(ans_set == result_set);

    return 0;
}