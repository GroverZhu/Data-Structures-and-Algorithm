#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

// 并查集两个通用函数
int Find(vector<int>& nums, int i) {
    int root = i;
    while (nums[root] != root) root = nums[root];

    while (nums[i] != i) {
        int temp = i;
        i = nums[i];
        nums[temp] = root;
    }
    return root;
}

void Union(vector<int>& nums, int i, int j) {
    int root_i = Find(nums, i);
    int root_j = Find(nums, j);
    nums[root_i] = root_j;
}

// 省份数量
// https://leetcode-cn.com/problems/number-of-provinces/ 
int findCircleNum(vector<vector<int>>& isConnected) {
    int size = isConnected.size();
    if (size <= 1) return size;

    vector<int> disjoint(size, 0);
    iota(disjoint.begin(), disjoint.end(), 0);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (isConnected[i][j] == 1) {
                Union(disjoint, i, j);
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < size; i++) {
        if (disjoint[i] == i) ++cnt;
    }

    return cnt;
}

// 岛屿数量
// https://leetcode-cn.com/problems/number-of-islands/

int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int total = rows * cols;
    vector<int> disjoint(total, 0);
    iota(disjoint.begin(), disjoint.end(), 0);

    const int LEN = 4;
    constexpr int dx[LEN] = {0, -1, 0, 1};
    constexpr int dy[LEN] = {1, 0, -1, 0};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '1') {
                for (int k = 0; k < LEN; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < rows && y >=0 && y < cols && grid[x][y] == '1') {
                        Union(disjoint, i * cols + j, x * cols + y);
                    }
                }
            }
        }
    }

    int cnt = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '1' && disjoint[i * cols + j] == (i * cols + j)) {
                ++cnt;
            }
        }
    }

    return cnt;
}

// 被围绕的区域
// https://leetcode-cn.com/problems/surrounded-regions/

void solve(vector<vector<char>>& board) {
    int rows = board.size();
    int cols = board[0].size();
    if (rows <= 1 || cols <= 1) return;

    int total = rows * cols + 1;
    int dummy = rows * cols; // 哑节点，用来连接外部'O'的位置

    vector<int> disjoint(total, 0);
    iota(disjoint.begin(), disjoint.end(), 0);

    for (int i = 0; i < rows; i++) {
        if (board[i][0] == 'O') Union(disjoint, i * cols, dummy);
        if (board[i][cols - 1] == 'O') Union(disjoint, i * cols + cols - 1, dummy);
    }

    for (int j = 1; j < cols - 1; j++) {
        if (board[0][j] == 'O') Union(disjoint, j, dummy);
        if (board[rows - 1][j] == 'O') Union(disjoint, (rows - 1) * cols + j, dummy);
    }

    const int LEN = 4;
    constexpr int dx[LEN] = {0, -1, 0, 1};
    constexpr int dy[LEN] = {1, 0, -1, 0};
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (board[i][j] == 'O') {
                for (int k = 0; k < LEN; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] == 'O') {
                        Union(disjoint, i * cols + j, x * cols + y);
                    }
                }
            }
        }
    }

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (board[i][j] == 'O' && Find(disjoint, i * cols + j) != Find(disjoint, dummy)) {
                board[i][j] = 'X';
            }
        }
    }
}


int main(int argc, char* argv[]) {
    // 省份数量
    vector<vector<int>> graph = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    assert(2 == findCircleNum(graph));
    graph = {{1,0,0},{0,1,0},{0,0,1}};
    assert(3 == findCircleNum(graph));

    // 岛屿数量
    vector<vector<char>> grid = {{'1','1','1','1','0'}, {'1','1','0','1','0'}, {'1','1','0','0','0'}, {'0','0','0','0','0'}};
    assert(1 == numIslands(grid));
    grid = {{'1','1','0','0','0'}, {'1','1','0','0','0'}, {'0','0','1','0','0'}, {'0','0','0','1','1'}};
    assert(3 == numIslands(grid));

    // 被围绕的区域
    vector<vector<char>> board = {{'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}};
    vector<vector<char>> ans = {{'X','X','X','X'},{'X','X','X','X'},{'X','X','X','X'},{'X','O','X','X'}};
    solve(board);
    assert(board == ans);
    board = {{'X'}};
    ans = {{'X'}};
    solve(board);
    assert(board == ans);
    return 0;
}