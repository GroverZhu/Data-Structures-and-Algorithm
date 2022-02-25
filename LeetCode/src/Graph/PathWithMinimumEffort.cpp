#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <queue>

#include <cassert>

using namespace std;

struct State {
    int x;
    int y;
    int effort;

    State(int _x, int _y, int _effort) : x(_x), y(_y), effort(_effort) {}
};

// https://leetcode-cn.com/problems/path-with-minimum-effort/
int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = static_cast<int>(heights.size());
    int cols = static_cast<int>(heights[0].size());

    vector<vector<int>> efforts(rows, vector<int>(cols, INT_MAX));
    efforts[0][0] = 0;

    auto cmp = [](const State& lhs, const State& rhs) {
        return lhs.effort > rhs.effort;
    };

    priority_queue<State, vector<State>, decltype(cmp)> q(cmp);
    q.push(State(0, 0, 0));
    constexpr int size = 4;
    constexpr int dx[size] = {0, -1, 0, 1};
    constexpr int dy[size] = {1, 0, -1, 0};
    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        if (node.x == rows - 1 && node.y == cols - 1) {
            return node.effort;
        }
        if (node.effort > efforts[node.x][node.y]) {
            continue;
        }

        for (int i = 0; i < size; i++) {
            int nextX = node.x + dx[i];
            int nextY = node.y + dy[i];
            if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols) {
                int effort = max(efforts[node.x][node.y], abs(heights[node.x][node.y] - heights[nextX][nextY]));
                if (effort < efforts[nextX][nextY]) {
                    efforts[nextX][nextY] = effort;
                    q.push(State(nextX, nextY, effort));
                }
            }
        }
        
    }

    return -1;

}

int main(int argc, char* argv[]) {
    vector<vector<int>> heights;

    heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    assert(2 == minimumEffortPath(heights));
    
    heights = {{1, 2, 3}, {3, 8, 4}, {5, 3, 5}};
    assert(1 == minimumEffortPath(heights));

    heights = {{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}};
    assert(0 == minimumEffortPath(heights));

    heights = {{1, 10, 6, 7, 9, 10, 4, 9}};
    assert(9 == minimumEffortPath(heights));

    return 0;
}