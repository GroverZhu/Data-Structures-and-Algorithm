#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/maximal-square/
int maximalSquare(vector<vector<char>>& matrix) {
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());
    vector<vector<int>> edges(rows, vector<int>(cols, 0));
    int result = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i][0] == '1') {
            edges[i][0] = 1;
            result = 1;
        }
    }
    for (int j = 0; j < cols; j++) {
        if (matrix[0][j] == '1') {
            edges[0][j] = 1;
            result = 1;
        }
    }

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] == '1') {
                edges[i][j] = min(edges[i - 1][j], min(edges[i - 1][j - 1], edges[i][j - 1])) + 1;
                result = max(result, edges[i][j]);
            }
        }
    }

    return result * result;
}

int main(int argc, char* argv[]) {
    vector<vector<char>> matrix;

    matrix = {
        {'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    assert(4 == maximalSquare(matrix));

    matrix = {{'0', '1'}, {'1', '0'}};
    assert(1 == maximalSquare(matrix));

    matrix = {{'0'}};
    assert(0 == maximalSquare(matrix));

    matrix = {{'1', '0', '1', '0'}, {'1', '0', '1', '1'}, {'1', '0', '1', '1'}, {'1', '1', '1', '1'}};
    assert(4 == maximalSquare(matrix));

    return 0;
}