#include <iostream>
#include <vector>
#include <queue>
#include <cassert>


using namespace std;

// https://leetcode-cn.com/problems/possible-bipartition/
bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    vector<vector<int>> graph(n, vector<int>());
    for (auto dislike : dislikes) {
        int from = dislike[0] - 1;
        int to = dislike[1] - 1;
        graph[from].emplace_back(to);
        graph[to].emplace_back(from);
    }
    vector<bool> visited(n, false);
    vector<bool> colors(n, false);
    bool result = true;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            while (!q.empty() && result) {
                auto cur = q.front();
                q.pop();
                visited[cur] = true;
                for (auto next : graph[cur]) {
                    if (!visited[next]) {
                        colors[next] = !colors[cur];
                        q.push(next);
                    } else {
                        if (colors[cur] == colors[next]) {
                            result = false;
                            return result;
                        }
                    }
                }
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    int n = 4;
    vector<vector<int>> dislikes = {{1, 2}, {1, 3}, {2, 4}};
    assert(true == possibleBipartition(n, dislikes));
    
    n = 3;
    dislikes = {{1, 2}, {1, 3}, {2, 3}};
    assert(false == possibleBipartition(n, dislikes));

    n = 5;
    dislikes = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}};
    assert(false == possibleBipartition(n, dislikes));
    return 0;
}