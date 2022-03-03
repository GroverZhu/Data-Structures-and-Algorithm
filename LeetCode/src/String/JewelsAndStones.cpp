#include <iostream>
#include <vector>
#include <set>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/jewels-and-stones/
int numJewIsInStones(string jewels, string stones) {
    set<char> jewelsSet;
    for (auto c : jewels) {
        jewelsSet.insert(c);
    }
    int count = 0;
    for (auto c : stones) {
        if (jewelsSet.find(c) != jewelsSet.end()) ++count;
    }
    return count;
}

int main(int argc, char* argv[]) {
    string jewels, stones;
    jewels = "aA";
    stones = "aAAbbbb";
    assert(3 == numJewIsInStones(jewels, stones));
    
    jewels = "z";
    stones = "ZZ";
    assert(0 == numJewIsInStones(jewels, stones));;


    return 0;
}