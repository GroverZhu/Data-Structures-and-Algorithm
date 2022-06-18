#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Node {
    vector<vector<int>> board;
    int x;
    int y;
    int step;

    Node(vector<vector<int>> _board, int _x, int _y, int _step) : board(_board), x(_x), y(_y), step(_step) {}
};

// https://leetcode-cn.com/problems/sliding-puzzle/
int slidingPuzzle(vector<vector<int>>& board) {
    vector<vector<int>> ans = {{1, 2, 3}, {4, 5, 0}};
    if (board == ans) return 0;

    int rows = 2;
    int cols = 3;
    int index = 0;
    for (index = 0; index < rows * cols; index++) {
        if (board[index / cols][index % cols] == 0) break;
    }
    int x = index / cols;
    int y = index % cols;

    constexpr int size = 4;
    constexpr int dx[size] = {0, -1, 0, 1};
    constexpr int dy[size] = {1, 0, -1, 0};

    queue<Node> q;
    q.push({board, x, y, 0});
    set<vector<vector<int>>> visited;
    visited.insert(board);

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        // if (node.board == ans) return node.step;
        int x = node.x;
        int y = node.y;
        for (int i = 0; i < size; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols) {
                swap(node.board[x][y], node.board[nextX][nextY]);
                if (node.board == ans) return node.step + 1;
                if (visited.find(node.board) == visited.end()) {
                    q.push({node.board, nextX, nextY, node.step + 1});
                    visited.insert(node.board);
                }
                swap(node.board[x][y], node.board[nextX][nextY]);
            }
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> board;
    int ans, result;

    board = {{1, 2, 3}, {4, 0, 5}};
    ans = 1;
    result = slidingPuzzle(board);
    assert(ans == result);

    board = {{1, 2, 3}, {5, 4, 0}};
    ans = -1;
    result = slidingPuzzle(board);
    assert(ans == result);

    board = {{4, 1, 2}, {5, 0, 3}};
    ans = 5;
    result = slidingPuzzle(board);
    assert(ans == result);

    board = {{3, 2, 4}, {1, 5, 0}};
    ans = 14;
    result = slidingPuzzle(board);
    assert(ans == result);

    return 0;
}