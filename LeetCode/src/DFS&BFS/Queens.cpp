#include <cassert>
#include <ctime>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/n-queens-II/

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

vector<string> genBoard(vector<int>& rows) {
    int size = static_cast<int>(rows.size());
    vector<string> board(size);
    for (int i = 0; i < size; i++) {
        board[i] = string(size, '.');
        board[i][rows[i]] = 'Q';
    }
    return board;
}

void dfs(vector<vector<string>>& result, int n, int row, vector<int>& rows, set<int>& cols, set<int>& pos,
         set<int>& neg) {
    if (row == n) {
        result.push_back(genBoard(rows));
        return;
    }

    for (int i = 0; i < n; i++) {
        if (cols.find(i) != cols.end()) continue;
        if (pos.find(i - row) != pos.end()) continue;
        if (neg.find(i + row) != neg.end()) continue;

        cols.insert(i);
        pos.insert(i - row);
        neg.insert(i + row);
        rows[row] = i;

        dfs(result, n, row + 1, rows, cols, pos, neg);

        cols.erase(i);
        pos.erase(i - row);
        neg.erase(i + row);
    }
}

// https://leetcode-cn.com/problems/n-queens/
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<int> rows(n);
    set<int> cols;
    set<int> pos;
    set<int> neg;
    dfs(result, n, 0, rows, cols, pos, neg);
    return result;
}

int main(int argc, char* argv[]) {
    assert(1 == totalNQueens(1));
    assert(0 == totalNQueens(2));
    assert(0 == totalNQueens(3));
    assert(2 == totalNQueens(4));
    assert(10 == totalNQueens(5));
    assert(4 == totalNQueens(6));
    assert(40 == totalNQueens(7));
    assert(92 == totalNQueens(8));
    assert(352 == totalNQueens(9));

    set<vector<string>> ans = {{"Q"}};
    auto result = solveNQueens(1);
    set<vector<string>> result_set = set<vector<string>>(result.begin(), result.end());
    assert(ans == result_set);

    ans = {{".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}};
    result = solveNQueens(4);
    result_set = set<vector<string>>(result.begin(), result.end());
    assert(ans == result_set);

    return 0;
}