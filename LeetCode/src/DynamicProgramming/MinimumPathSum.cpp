#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/minimum-path-sum/
int minPathSum(vector<vector<int>>& grid) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());
    for (int i = 1; i < rows; i++) {
        grid[i][0] = grid[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < cols; j++) {
        grid[0][j] = grid[0][j - 1] + grid[0][j];
    }

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
        }
    }

    return grid[rows - 1][cols - 1];
}


int main(int argc, char* argv[]) {
    vector<vector<int>> grid;
    
    grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    assert(7 == minPathSum(grid));

    grid = {{1, 2, 3}, {4, 5, 6}};
    assert(12 == minPathSum(grid));
    return 0;
}