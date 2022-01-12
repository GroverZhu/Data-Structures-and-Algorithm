#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// https://leetcode-cn.com/problems/minimum-genetic-mutation/

int minMutation(string start, string end, vector<string>& bank) {
    set<string> cache(bank.begin(), bank.end());
    if (cache.find(end) == cache.end()) return -1;
    string gens = "ACGT";

    set<string> begin;
    set<string> finish;

    begin.insert(start);
    finish.insert(end);
    
    cache.erase(start);
    cache.erase(end);

    int step = 0;

    while (!begin.empty() && !finish.empty()) {
        set<string> temp;
        for(auto s : begin) {
            for (int i = 0; i < static_cast<int>(s.size()); i++) {
                char base = s[i];
                
                for (auto c : gens) {
                    if (base == c) continue;
                    s[i] = c;
                    if (finish.find(s) != finish.end()) return step + 1;
                    if (cache.find(s) != cache.end()) {
                        temp.insert(s);
                        cache.erase(s);
                    }
                }

                s[i] = base;
            }
        }
        begin = temp;
        if (begin.size() > finish.size()) swap(begin, finish);
        ++step;
    }

    return -1;
}

int main(int argc, char* argv[]) {
    string start = "AACCGGTT";
    string end = "AACCGGTA";
    vector<string> bank = {"AACCGGTA"};
    int result = minMutation(start, end, bank);
    int ans = 1;
    assert(ans == result);

    start = "AACCGGTT";
    end = "AAACGGTA";
    bank = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    result = minMutation(start, end, bank);
    ans = 2;
    assert(ans == result);

    start = "AAAAACCC";
    end = "AACCCCCC";
    bank = {"AAAACCCC", "AAACCCCC", "AACCCCCC"};
    result = minMutation(start, end, bank);
    ans = 3;
    assert(ans == result);

    return 0;
}