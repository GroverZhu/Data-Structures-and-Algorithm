#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/shortest-path-in-binary-matrix/
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1) return -1;

    constexpr int size = 8;
    constexpr int dx[size] = {0, -1, -1, -1, 0, 1, 1, 1};
    constexpr int dy[size] = {1, 1, 0, -1, -1, -1, 0, 1};

#if defined(BFS)
    queue<pair<pair<int, int>, int>> q;
    q.push({{0, 0}, 1});
    int step = INT_MAX;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        auto x = node.first.first;
        auto y = node.first.second;
        grid[x][y] = 1;
        auto tmp = node.second;
        if (x == rows - 1 && y == cols - 1) {
            step = min(step, tmp);
        }
        for (int i = 0; i < size; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && grid[nextX][nextY] == 0) {
                grid[nextX][nextY] = 1;
                q.push({{nextX, nextY}, tmp + 1});
            }
        }
    }
    return step == INT_MAX ? - 1 : step;

#elif defined(BIBFS)
    set<pair<int, int>> begin;
    set<pair<int, int>> end;

    begin.insert({0, 0});
    end.insert({rows - 1, cols - 1});
    grid[0][0] = 1;
    grid[rows - 1][cols - 1] = 1;
    int step = 1;

    while (!begin.empty() && !end.empty()) {
        set<pair<int, int>> tmp;
        for (auto node : begin) {
            int x = node.first;
            int y = node.second;
            if (end.find({x, y}) != end.end()) return step;
            for (int i = 0; i < size; i++) {
                int next_x = x + dx[i];
                int next_y = y + dy[i];
                if (next_x >= 0 && next_x < rows && next_y >= 0 && next_y < cols) {
                    if (end.find({next_x, next_y}) != end.end()) return step + 1;
                    if (grid[next_x][next_y] == 0) {
                        grid[next_x][next_y] = 1;
                        tmp.insert({next_x, next_y});
                    }
                }
            }
        }
        ++step;
        swap(begin, tmp);
        if (begin.size() > end.size()) {
            swap(begin, end);
        }
    }

    return -1;

#else

    auto cmp = [&](const pair<pair<int, int>, int>& lhs, const pair<pair<int, int>, int>& rhs) {
        int manhattenLhs = (rows - 1 - lhs.first.first) + (cols - 1 - lhs.first.second);
        int manhattenRhs = (rows - 1 - rhs.first.second) + (cols - 1 - rhs.first.second);
        return manhattenLhs < manhattenRhs;
    };

    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(cmp)> q(cmp);
    q.push({{0, 0}, 1});
    grid[0][0] = 1;
    
    while (!q.empty()) {
        auto node = q.top();
        int x = node.first.first;
        int y = node.first.second;
        int step = node.second;
        q.pop();

        if (x == rows - 1 && y == cols - 1) return step;

        for (int i = 0; i < size; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];

            if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols && grid[nextX][nextY] == 0) {
                if (nextX == rows - 1 && nextY == cols - 1) {
                    return step + 1;
                }
                grid[nextX][nextY] = 1;
                q.push({{nextX, nextY}, step + 1});
            }
        }
    }
    return -1;
#endif

}

int main(int argc, char* argv[]) {
    vector<vector<int>> grid;
    int ans, result;

    grid = {{0, 1}, {1, 0}};
    ans = 2;
    result = shortestPathBinaryMatrix(grid);
    assert(ans == result);


    grid = {{0, 0, 0}, {1, 1, 0}, {1, 1, 0}};
    ans = 4;
    result = shortestPathBinaryMatrix(grid);
    assert(ans == result);

    grid = {{1, 0, 0}, {1, 1, 0}, {1, 1, 0}};
    ans = -1;
    result = shortestPathBinaryMatrix(grid);
    assert(ans == result);
    
    grid = {{0}};
    ans = 1;
    result = shortestPathBinaryMatrix(grid);
    assert(ans == result);

    grid = {{0,1,0,0,0,0},{0,1,1,1,1,1},{0,0,0,0,1,1},{0,1,0,0,0,1},{1,0,0,1,0,1},{0,0,1,0,1,0}};
    ans = 7;
    result = shortestPathBinaryMatrix(grid);
    assert(ans == result);

    grid = {{0,1,1,1,1,1,1,1},{0,1,1,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},{0,1,1,0,0,1,1,0},{0,1,1,1,1,0,1,0},{0,0,0,0,0,1,1,0},{1,1,1,1,1,1,1,0}};
    ans = 25;
    result = shortestPathBinaryMatrix(grid);
    assert(ans == result);
    return 0;
}