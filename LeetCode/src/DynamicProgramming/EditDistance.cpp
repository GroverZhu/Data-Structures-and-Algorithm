#include <iostream>
#include <vector>
#include <string>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/edit-distance/
int minDistance(string word1, string word2) {
    int size1 = static_cast<int>(word1.size());
    int size2 = static_cast<int>(word2.size());

    vector<vector<int>> edits(size1 + 1, vector<int>(size2 + 1, 0));

    for (int i = 1; i <= size1; i++) edits[i][0] = i;
    for (int j = 1; j <= size2; j++) edits[0][j] = j;

    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                edits[i][j] = edits[i - 1][j - 1];
            } else {
                edits[i][j] = min(edits[i - 1][j], min(edits[i][j - 1], edits[i - 1][j - 1])) + 1;
            }
        }
    }
    return edits[size1][size2];
}

int main(int argc, char* argv[]) {
    string word1, word2;

    word1 = "horse";
    word2 = "ros";
    assert(3 == minDistance(word1, word2));

    word1 = "intention";
    word2 = "execution";
    assert(5 == minDistance(word1, word2));
    return 0;
}