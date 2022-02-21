#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

void dfs(vector<vector<int>>& graph, vector<int>& visited, vector<int>& colors, int cur, bool& result) {
    if (!result) return;

    visited[cur] = true;
    for (auto next : graph[cur]) {
        if (!visited[next]) {
            visited[next] = true;
            colors[next] = !colors[cur];
            dfs(graph, visited, colors, next, result);
        } else {
            if (colors[cur] == colors[next]) {
                result = false;
                return;
            }
        }
    }

}
// https://leetcode-cn.com/problems/is-graph-bipartite/
bool isBipartite(vector<vector<int>>& graph) {
    int size = static_cast<int>(graph.size());
    vector<int> visited(size, false);
    vector<int> colors(size, false);
    bool result = true;
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            dfs(graph, visited, colors, i, result);
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> graph = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
    assert(false == isBipartite(graph));

    graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    assert(true == isBipartite(graph));
    return 0;
}