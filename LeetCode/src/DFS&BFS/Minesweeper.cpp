#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void dfs(vector<vector<char>>& board, int x, int y) {
    constexpr int size = 8;
    constexpr int dx[size] = {0, -1, -1, -1, 0, 1, 1, 1};
    constexpr int dy[size] = {1, 1, 0, -1, -1, -1, 0, 1};
    int rows = static_cast<int>(board.size());
    int cols = static_cast<int>(board[0].size());
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && board[nextX][nextY] == 'M') {
            ++cnt;
        }
    }

    if (cnt > 0) {
        board[x][y] = cnt + '0';
    } else {
        board[x][y] = 'B';
        for (int i = 0; i < size; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && board[nextX][nextY] == 'E') {
                dfs(board, nextX, nextY);
        }
    }
    }
}

// https://leetcode-cn.com/problems/minesweeper/
vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
    int x = click[0];
    int y = click[1];

    if (board[x][y] == 'M') {
        board[x][y] = 'X';
    } else if (board[x][y] == 'E') {
        dfs(board, x, y);
    }

    return board;
}

int main(int argc, char* argv[]) {
    vector<vector<char>> board, ans;
    vector<int> click;

    board = {{'E','E','E','E','E'},{'E','E','M','E','E'},{'E','E','E','E','E'},{'E','E','E','E','E'}};
    ans = {{'B','1','E','1','B'},{'B','1','M','1','B'},{'B','1','1','1','B'},{'B','B','B','B','B'}};
    click = {3, 0};
    updateBoard(board, click);
    assert(board == ans);


    board = {{'B','1','E','1','B'},{'B','1','M','1','B'},{'B','1','1','1','B'},{'B','B','B','B','B'}};
    ans = {{'B','1','E','1','B'},{'B','1','X','1','B'},{'B','1','1','1','B'},{'B','B','B','B','B'}};
    click = {1, 2};
    updateBoard(board, click);
    assert(board == ans);

}