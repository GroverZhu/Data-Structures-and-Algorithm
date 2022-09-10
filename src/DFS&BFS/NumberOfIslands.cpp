#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void floodFill(vector<vector<char>>& grid, int x, int y) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    constexpr int LEN = 4;
    constexpr int dx[LEN] = {0, -1, 0, 1};
    constexpr int dy[LEN] = {1, 0, -1, 0};

    grid[x][y] = '#';
    for (int i = 0; i < LEN; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && grid[nextX][nextY] == '1') {
            floodFill(grid, nextX, nextY);
        }
    }
}

// https://leetcode-cn.com/problems/number-of-islands/
int numIslands(vector<vector<char>>& grid) {
    int cnt = 0;
    int row = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid.size());

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '1') {
                ++cnt;
                floodFill(grid, i, j);
            }
        }
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    vector<vector<char>> grid;
    int ans, result;

    grid = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};
    ans = 1;
    result = numIslands(grid);
    assert(ans == result);

    grid = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
    ans = 3;
    result = numIslands(grid);
    assert(ans == result);
    return 0;
}