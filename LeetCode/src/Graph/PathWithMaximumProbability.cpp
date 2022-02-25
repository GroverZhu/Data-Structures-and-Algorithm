#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cassert>

using namespace std;

struct State {
    int cur;
    double probility;

    State(int _cur, double _probility) : cur(_cur), probility(_probility) {}
};

// https://leetcode-cn.com/problems/path-with-maximum-probability/
double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    // 建图
    map<int, vector<State>> graph;
    int size = static_cast<int>(edges.size());
    for (int i = 0; i < size; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        auto prob = succProb[i];
        graph[from].push_back(State(to, prob));
        graph[to].push_back(State(from, prob));
    }

    // dijkdtra算法
    vector<double> probs(n, -1.0);
    probs[start] = 1.0;

    auto cmp = [](const State& lhs, const State& rhs) {
        return lhs.probility < rhs.probility;
    };

    priority_queue<State, vector<State>, decltype(cmp)> q(cmp);
    q.push(State(start, 1));

    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        if (cur.cur == end) {
            return cur.probility;
        }
        if (cur.probility < probs[cur.cur]) {
            continue;
        }
        for (auto next : graph[cur.cur]) {
            double tmp = cur.probility * next.probility;
            if (tmp > probs[next.cur]) {
                probs[next.cur] = tmp;
                q.push(State(next.cur, tmp));
            }
        }
    }

    return 0.0;
}

int main(int argc, char* argv[]) {
    int n, start, end;
    vector<vector<int>> edges;
    vector<double> succProb;
    double epsilon = 1e-5;

    n = 3;
    edges = {{0, 1}, {1, 2}, {0, 2}};
    succProb = {0.5, 0.5, 0.2};
    start = 0;
    end = 2;
    assert(abs(maxProbability(n, edges, succProb, start, end) - 0.2500) < epsilon);

    n = 3;
    edges = {{0, 1}, {1, 2}, {0, 2}};
    succProb = {0.5, 0.5, 0.3};
    start = 0;
    end = 2;
    assert(abs(maxProbability(n, edges, succProb, start, end) - 0.30000) < epsilon);

    n = 3;
    edges = {{0, 1}};
    succProb = {0.5};
    start = 0;
    end = 2;
    assert(abs(maxProbability(n, edges, succProb, start, end) - 0.00000) < epsilon);
    return 0;
}