#include <iostream>
#include <vector>
#include <set>
#include <cassert>
using namespace std;


bool dfs(vector<vector<char>>& board, vector<set<char>>& rows, vector<set<char>>& cols, vector<set<char>>& boxes) {
    int m = static_cast<int>(board.size());
    int n = static_cast<int>(board[0].size());

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            auto c = board[i][j];
            if (c == '.') {
                for (char k = '1'; k <= '9'; k++) {
                    if (rows[i].find(k) != rows[i].end()) continue;
                    if (cols[j].find(k) != cols[j].end()) continue;
                    int index = (i / 3) * 3 + (j / 3);
                    if (boxes[index].find(k) != boxes[index].end()) continue;

                    board[i][j] = k;
                    rows[i].insert(k);
                    cols[j].insert(k);
                    boxes[index].insert(k);
                    
                    bool result = dfs(board, rows, cols, boxes);
                    if (result) return true;
                    board[i][j] = '.';  
                    rows[i].erase(k);
                    cols[j].erase(k);
                    boxes[index].erase(k);
                    
                }
                return false; // 9个数全部试过不能用
            }
        }
    }
    return true;
}

// https://leetcode-cn.com/problems/sudoku-solver/
void solveSudoKu(vector<vector<char>>& board) {
    int size = static_cast<int>(board.size());
    vector<set<char>> rows(size, set<char>());
    vector<set<char>> cols(size, set<char>());
    vector<set<char>> boxes(size, set<char>());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != '.') {
                rows[i].insert(board[i][j]);
                cols[j].insert(board[i][j]);
                boxes[(i / 3) * 3 + (j / 3)].insert(board[i][j]);
            }
        }
    }
    dfs(board, rows, cols, boxes);
}

int main(int argc, char* argv[]) {
    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    vector<vector<char>> ans = {{'5','3','4','6','7','8','9','1','2'},{'6','7','2','1','9','5','3','4','8'},{'1','9','8','3','4','2','5','6','7'},{'8','5','9','7','6','1','4','2','3'},{'4','2','6','8','5','3','7','9','1'},{'7','1','3','9','2','4','8','5','6'},{'9','6','1','5','3','7','2','8','4'},{'2','8','7','4','1','9','6','3','5'},{'3','4','5','2','8','6','1','7','9'}};
    solveSudoKu(board);
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         cout << board[i][j] << ",";
    //     }
    //     cout << endl;
    // }
    assert(board == ans);
    return 0;
}