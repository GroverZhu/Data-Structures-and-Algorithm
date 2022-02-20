
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/course-schedule/
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> indegree(numCourses, 0);
    map<int, vector<int>> graph;
    for (auto list : prerequisites) {
        int to = list[0];
        int from = list[1];
        graph[from].push_back(to);
        indegree[to]++;
    }

    int visited = 0;
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            q.push(i);
            ++visited;
        }
    }

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        for (auto next : graph[node]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                q.push(next);
                ++visited;
            }
        }
    }
    
    return visited == numCourses;


}

// https://leetcode-cn.com/problems/course-schedule-ii/
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> result;
    int visited = 0;

    map<int, vector<int>> graph;
    vector<int> indegree(numCourses, 0);

    for (auto list : prerequisites) {
        int to = list[0];
        int from = list[1];
        graph[from].emplace_back(to);
        indegree[to]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            q.push(i);
            ++visited;
        }
    }

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        result.emplace_back(node);
        
        for (auto next : graph[node]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                ++visited;
                q.push(next);
            }
        }
    }

    return visited == numCourses ? result : vector<int>();

}

int main(int argc, char* argv[]) {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}};
    assert(true == canFinish(numCourses, prerequisites));
    vector<int> order = findOrder(numCourses, prerequisites);
    vector<int> orderResult = {0, 1};
    assert(order == orderResult);

    numCourses = 4;
    prerequisites = {{1, 0}, {2, 0}};
    assert(true == canFinish(numCourses, prerequisites));

    numCourses = 2;
    prerequisites = {{1, 0}, {0, 1}};
    assert(false == canFinish(numCourses, prerequisites));
    order = findOrder(numCourses, prerequisites);
    orderResult = {};
    assert(order == orderResult);

    
    numCourses = 1;
    prerequisites = {};
    assert(true == canFinish(numCourses, prerequisites));
    order = findOrder(numCourses, prerequisites);
    orderResult = {0};
    assert(order == orderResult);
    return 0;
}