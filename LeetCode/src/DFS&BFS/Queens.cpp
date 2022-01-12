#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <ctime>

using namespace std;

// https://leetcode-cn.com/problems/n-queens-II/

void dfsBits(int& result, int n, int row, int col, int postiveDigonal, int negativeDigonal) {
    if (row == n) {
        ++result;
        return;
    }

    int bits = (~(col | postiveDigonal | negativeDigonal)) & ((1 << n) - 1);

    while (bits) {
        int pos = bits & (-bits);
        bits &= (bits - 1);
        dfsBits(result, n, row + 1, col | pos, (postiveDigonal | pos) << 1, (negativeDigonal | pos) >> 1);
    }
}

void dfs(int& result, int n, int row, set<int>& cols, set<int>& postiveDiagonal, set<int>& negativeDiagonal) {
    if (row == n) {
        ++result;
        return;
    }

    for (int j = 0; j < n; j++) {
        if (cols.find(j) != cols.end()) continue;
        if (postiveDiagonal.find(j - row) != postiveDiagonal.end()) continue;
        if (negativeDiagonal.find(j + row) != negativeDiagonal.end()) continue;

        cols.insert(j);
        postiveDiagonal.insert(j - row);
        negativeDiagonal.insert(j + row);

        dfs(result, n, row + 1, cols, postiveDiagonal, negativeDiagonal);

        cols.erase(j);
        postiveDiagonal.erase(j - row);
        negativeDiagonal.erase(j + row);

    }
}

int totalNQueens(int n) {
    if (n < 1) return 0;
    int result = 0;
    // dfsBits(result, n, 0, 0, 0, 0);
    
    set<int> cols;
    set<int> pos;
    set<int> neg;
    dfs(result, n, 0, cols, pos, neg);

    return result;
}




int main(int argc, char* argv[]) {

    auto begin = clock();

    assert(1 == totalNQueens(1));
    assert(0 == totalNQueens(2));
    assert(0 == totalNQueens(3));
    assert(2 == totalNQueens(4));
    assert(10 == totalNQueens(5));
    assert(4 == totalNQueens(6));
    assert(40 == totalNQueens(7));
    assert(92 == totalNQueens(8));
    assert(352 == totalNQueens(9));

    auto end = clock();

    cout << "All tests passed. Time cost: " << (1.0 * (end - begin) / CLOCKS_PER_SEC * 1000) << "ms." << endl;

    return 0;
}