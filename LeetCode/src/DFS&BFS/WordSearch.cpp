#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

bool dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, string word, int index, int x, int y) {
    if (index == static_cast<int>(word.size()) - 1) {
        return true;
    }

    constexpr int size = 4;
    constexpr int dx[size] = {0, -1, 0, 1};
    constexpr int dy[size] = {1, 0, -1, 0};
    int rows = static_cast<int>(board.size());
    int cols = static_cast<int>(board[0].size());

    for (int i = 0; i < size; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && !visited[nextX][nextY] &&
            board[nextX][nextY] == word[index + 1]) {
            visited[nextX][nextY] = true;
            auto result = dfs(board, visited, word, index + 1, nextX, nextY);
            if (result) return true;
            visited[nextX][nextY] = false;
        }
    }

    return false;
}

// https://leetcode-cn.com/problems/word-search/
bool exist(vector<vector<char>>& board, string word) {
    int rows = static_cast<int>(board.size());
    int cols = static_cast<int>(board[0].size());

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == word[0]) {
                vector<vector<bool>> visited(rows, vector<bool>(cols, false));
                visited[i][j] = true;
                auto result = dfs(board, visited, word, 0, i, j);
                if (result) return result;
            }
        }
    }

    return false;
}

int main() {
    vector<vector<char>> board;
    string word;

    board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    word = "ABCCED";
    assert(true == exist(board, word));

    board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    word = "SEE";
    assert(true == exist(board, word));

    board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    word = "ABCB";
    assert(false == exist(board, word));

    return 0;
}