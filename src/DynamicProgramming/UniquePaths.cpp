#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/unique-paths/
int uniquePaths(int m, int n) {
#if 0
    vector<vector<int>> paths(m, vector<int>(n, 1));

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
        }
    }

    return paths[m - 1][n - 1];
#endif

#if 1  // 状态压缩
    vector<int> paths(n, 1);
    for (int i = 1; i < m; i++) {
        paths[0] = 1;
        for (int j = 1; j < n; j++) {
            paths[j] = paths[j - 1] + paths[j];
        }
    }
    return paths[n - 1];
#endif
}

// https://leetcode-cn.com/problems/unique-paths-ii/
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
#if 0
    int rows = static_cast<int>(obstacleGrid.size());
    int cols = static_cast<int>(obstacleGrid[0].size());

    vector<vector<int>> paths(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows && obstacleGrid[i][0] != 1; i++) {
        paths[i][0] = 1;
    }

    for (int j = 0; j < cols && obstacleGrid[0][j] != 1; j++) {
        paths[0][j] = 1;
    }

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (obstacleGrid[i][j] == 1) {
                paths[i][j] = 0;
            } else {
                paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
            }
        }
    }
    return paths[rows - 1][cols - 1];
#endif

#if 1
    int rows = static_cast<int>(obstacleGrid.size());
    if (rows == 0) {
        return 0;
    }
    int cols = static_cast<int>(obstacleGrid[0].size());
    if (cols == 0) {
        return 0;
    }

    vector<int> line(cols, 0);
    for (int j = 0; j < cols; j++) {
        if (obstacleGrid[0][j] == 1) {
            break;
        }
        line[j] = 1;
    }

    for (int i = 1; i < rows; i++) {
        if (obstacleGrid[i][0] == 1 || line[0] == 0) {
            line[0] = 0;
        } else {
            line[0] = 1;
        }

        for (int j = 1; j < cols; j++) {
            if (obstacleGrid[i][j] == 1) {
                line[j] = 0;
            } else {
                line[j] = line[j - 1] + line[j];
            }
        }
    }

    return line[cols - 1];
#endif
}

void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int& result, int steps, int x, int y) {
    if (grid[x][y] == 2 && steps == 0) {
        ++result;
        return;
    }
    if (grid[x][y] == -1) return;

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());
    constexpr int size = 4;
    constexpr int dx[size] = {0, -1, 0, 1};
    constexpr int dy[size] = {1, 0, -1, 0};

    for (int i = 0; i < size; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && !visited[nextX][nextY]) {
            if (grid[nextX][nextY] == 0) {
                --steps;
            }
            visited[nextX][nextY] = true;
            dfs(grid, visited, result, steps, nextX, nextY);
            visited[nextX][nextY] = false;
            if (grid[nextX][nextY] == 0) {
                ++steps;
            }
        }
    }
}

// https://leetcode-cn.com/problems/unique-paths-iii/
int uniquePathsIII(vector<vector<int>>& grid) {
    int result = 0;
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());
    int x = 0, y = 0;
    int steps = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                x = i;
                y = j;
            }
            if (grid[i][j] == 0) {
                ++steps;
            }
        }
    }
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[x][y] = true;
    dfs(grid, visited, result, steps, x, y);
    return result;
}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/unique-paths/
    int m, n;
    m = 3, n = 7;
    assert(28 == uniquePaths(m, n));

    m = 3, n = 2;
    assert(3 == uniquePaths(m, n));

    m = 7, n = 3;
    assert(28 == uniquePaths(m, n));

    m = 3, n = 3;
    assert(6 == uniquePaths(m, n));

    // https://leetcode-cn.com/problems/unique-paths-ii/
    vector<vector<int>> grid;
    grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    assert(2 == uniquePathsWithObstacles(grid));

    grid = {{0, 1}, {0, 0}};
    assert(1 == uniquePathsWithObstacles(grid));

    grid = {{1, 0}, {0, 0}};
    assert(0 == uniquePathsWithObstacles(grid));

    // https://leetcode-cn.com/problems/unique-paths-iii/
    grid = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}};
    assert(2 == uniquePathsIII(grid));

    grid = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}};
    assert(4 == uniquePathsIII(grid));

    grid = {{0, 1}, {2, 0}};
    assert(0 == uniquePathsIII(grid));
    return 0;
}