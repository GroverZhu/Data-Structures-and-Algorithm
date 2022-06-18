#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<bool>> graph;
bool knows(int a, int b) { return graph[a][b]; }

//  https://leetcode-cn.com/problems/find-the-celebrity/
int findCelebrity(int n) {
#if 0
    queue<int> q;
    for (int i = 0; i < n; i++) {
        q.push(i);
    }

    while (q.size() >= 2) {
        auto cand = q.front();
        q.pop();
        auto other = q.front();
        q.pop();

        if (knows(cand, other) || !knows(other, cand)) {
            q.push(other);
        } else {
            q.push(cand);
        }
    }

    int cand = q.front();
    q.pop();
    for (int other = 0;  other < n; other++) {
        if (cand == other) continue;
        if (!knows(other, cand) || knows(cand, other)) return -1;
    }
    return cand;
#endif
#if 1

    int cand = 0;
    for (int other = 1; other < n; other++) {
        if (knows(cand, other) || !knows(other, cand)) {
            cand = other;
        }
    }
    for (int other = 0; other < n; other++) {
        if (cand == other) continue;
        if (knows(cand, other) || !knows(other, cand)) {
            return -1;
        }
    }
    return cand;

#endif
}

int main(int argc, char* argv[]) {
    int n = 3;
    graph = {{1, 1, 0}, {0, 1, 0}, {1, 1, 1}};
    assert(1 == findCelebrity(n));

    graph = {{1, 0, 1}, {1, 1, 0}, {0, 1, 1}};
    assert(-1 == findCelebrity(n));

    return 0;
}