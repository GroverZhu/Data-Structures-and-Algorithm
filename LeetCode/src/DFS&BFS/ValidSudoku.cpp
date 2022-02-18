#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;


// https://leetcode-cn.com/problems/valid-sudoku/
bool isValidSudoku(vector<vector<char>>& board) {
    constexpr int size = 9;
    vector<set<char>> rows(size, set<char>());
    vector<set<char>> cols(size, set<char>());
    vector<set<char>> boxes(size, set<char>());

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            auto c = board[i][j];
            if (c != '.') {
                if (rows[i].find(c) != rows[i].end()) return false;
                if (cols[j].find(c) != cols[j].end()) return false;
                int index = (i / 3) * 3 + (j / 3);
                if (boxes[index].find(c) != boxes[index].end()) return false;
                rows[i].insert(c);
                cols[j].insert(c);
                boxes[index].insert(c);
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    vector<vector<char>> board;

    board = {{'5','3','.','.','7','.','.','.','.'} ,{'6','.','.','1','9','5','.','.','.'} ,{'.','9','8','.','.','.','.','6','.'} ,{'8','.','.','.','6','.','.','.','3'} ,{'4','.','.','8','.','3','.','.','1'} ,{'7','.','.','.','2','.','.','.','6'} ,{'.','6','.','.','.','.','2','8','.'} ,{'.','.','.','4','1','9','.','.','5'} ,{'.','.','.','.','8','.','.','7','9'}};
    assert(true == isValidSudoku(board));

    board = {{'8','3','.','.','7','.','.','.','.'} ,{'6','.','.','1','9','5','.','.','.'} ,{'.','9','8','.','.','.','.','6','.'} ,{'8','.','.','.','6','.','.','.','3'} ,{'4','.','.','8','.','3','.','.','1'} ,{'7','.','.','.','2','.','.','.','6'} ,{'.','6','.','.','.','.','2','8','.'} ,{'.','.','.','4','1','9','.','.','5'} ,{'.','.','.','.','8','.','.','7','9'}};
    assert(false == isValidSudoku(board));

    return 0;

}