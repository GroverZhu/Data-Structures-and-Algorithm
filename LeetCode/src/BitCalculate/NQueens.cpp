#include <iostream>
#include <vector>
#include <string>
#include <set>

#include <cassert>

using namespace std;

void bitsDFS(int& result, int n, int cols, int post, int neg, int row) {
    if (row == n) {
        ++result;
        return;
    }

    int bits = ((~(cols | post | neg)) & ((1 << n) - 1));
    while (bits) {
        int pos = bits & (-bits); // 保留从右至左的第一位1
        bits &= (bits - 1); // 将从右至左的第一位置0
        bitsDFS(result, n, cols | pos, (post | pos) >> 1, (neg | pos) << 1, row + 1);
    }

}



// https://leetcode-cn.com/problems/n-queens-ii/description/
int totalNQueens(int n) {
    int result = 0;
    bitsDFS(result, n, 0, 0, 0, 0);
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

int countTrailingZero(int n) {
    if (n == 0) return -1;
    int cnt = 0;
    while ((n & 1) == 0) {
        n = n >> 1;
        cnt++;
    }
    return cnt;
}

void dfs(vector<vector<string>>& result, int n, vector<int>& rows, int row, int cols, int neg, int pos) {
    if (row == n) {
        result.emplace_back(genBoard(rows));
        return;
    }

    int bits = (~(cols | neg | pos)) & ((1 << n) - 1);
    while (bits) {
        int index = bits & (-bits);
        bits &= (bits - 1);
        rows[row] = countTrailingZero(index);
        dfs(result, n, rows, row + 1, cols | index, (neg | index) >> 1, (pos | index) << 1);
    }

}

// https://leetcode-cn.com/problems/n-queens/
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<int> rows(n);
    dfs(result, n, rows, 0, 0, 0, 0);
    return result;
}


int main(int argc, char* argv[]) {
    int n, ans, result;
    n = 4;
    ans = 2;
    result = totalNQueens(n);
    assert(ans == result);
    vector<vector<string>> board = solveNQueens(n);
    set<vector<string>> board_set(board.begin(), board.end());
    set<vector<string>> board_ans = {{".Q..","...Q","Q...","..Q."}, {"..Q.","Q...","...Q",".Q.."}};
    assert(board_ans == board_set);

    n = 1;
    ans = 1;
    result = totalNQueens(n);
    assert(ans == result);
    board = solveNQueens(n);
    board_set = set<vector<string>>(board.begin(), board.end());
    board_ans = {{"Q"}};
    assert(board_ans == board_set);

    return 0;
}