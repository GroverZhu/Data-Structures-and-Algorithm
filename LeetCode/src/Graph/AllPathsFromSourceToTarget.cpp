#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/all-paths-from-source-to-target/
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    int size = graph.size();
    vector<vector<int>> result;
    queue<vector<int>> q;
    q.push({0});
    while (!q.empty()) {
        auto path = q.front();
        q.pop();
        int node = path.back();
        for (auto next : graph[node]) {
            auto tmp = path;
            tmp.push_back(next);
            if (next == size - 1) {
                result.push_back(tmp);
            } else {
                q.push(tmp);
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
    set<vector<int>> ans = {{0, 1, 3}, {0, 2, 3}};
    vector<vector<int>> result = allPathsSourceTarget(graph);
    set<vector<int>> result_set(result.begin(), result.end());
    assert(ans == result_set);

    graph = {{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
    ans = {{0, 4}, {0, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 4}};
    result = allPathsSourceTarget(graph);
    result_set = set<vector<int>>(result.begin(), result.end());
    assert(ans == result_set);

    return 0;
}