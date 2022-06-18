#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/search-a-2d-matrix/
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());

    int x = 0;
    int y = cols - 1;

    while (x < rows && y >= 0) {
        if (matrix[x][y] < target) {
            x++;
        } else if (matrix[x][y] > target) {
            y--;
        } else if (matrix[x][y] == target) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> matrix;
    int target;

    matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    target = 3;
    assert(true == searchMatrix(matrix, target));

    matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    target = 13;
    assert(false == searchMatrix(matrix, target));

    return 0;
}
