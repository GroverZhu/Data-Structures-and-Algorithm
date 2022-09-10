
#include <iostream>
#include <map>
#include <queue>
#include <set>
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

// follow up 所有可能的上课顺序
bool allTopologySortOrdersHelper(vector<vector<int>>& orders, vector<int>& order, map<int, vector<int>>& graph,
                                 vector<int>& indegree, vector<bool>& visited, int verticeNum) {
    if (static_cast<int>(order.size()) == verticeNum) {
        orders.emplace_back(order);
        return true;
    }
    bool flag = false;
    for (int i = 0; i < verticeNum; i++) {
        if (indegree[i] == 0 && !visited[i]) {
            order.emplace_back(i);
            visited[i] = true;
            for (auto& next : graph[i]) {
                indegree[next] -= 1;
            }

            allTopologySortOrdersHelper(orders, order, graph, indegree, visited, verticeNum);

            order.pop_back();
            visited[i] = false;
            for (auto& next : graph[i]) {
                indegree[next] += 1;
            }

            flag = true;
        }
    }

    return flag;
}

vector<vector<int>> allTopologySortOrders(int numCourses, vector<vector<int>>& prerequisites) {
    if (numCourses == 0) {
        return vector<vector<int>>();
    }
    if (numCourses == 1) {
        return vector<vector<int>>{{0}};
    }
    vector<vector<int>> result;
    vector<int> order;
    vector<int> indegree(numCourses, 0);
    vector<bool> visited(numCourses, false);
    map<int, vector<int>> graph;
    for (auto& link : prerequisites) {
        auto to = link[0];
        auto from = link[1];
        graph[from].emplace_back(to);
        indegree[to] += 1;
    }
    allTopologySortOrdersHelper(result, order, graph, indegree, visited, numCourses);
    return result;
}

int main(int argc, char* argv[]) {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}};
    assert(true == canFinish(numCourses, prerequisites));
    vector<int> order = findOrder(numCourses, prerequisites);
    vector<int> orderResult = {0, 1};
    assert(order == orderResult);
    vector<vector<int>> topologyOrders = allTopologySortOrders(numCourses, prerequisites);
    assert(1 == topologyOrders.size());

    numCourses = 4;
    prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    assert(true == canFinish(numCourses, prerequisites));
    topologyOrders = allTopologySortOrders(numCourses, prerequisites);
    assert(2 == topologyOrders.size());

    numCourses = 2;
    prerequisites = {{1, 0}, {0, 1}};
    assert(false == canFinish(numCourses, prerequisites));
    order = findOrder(numCourses, prerequisites);
    orderResult = {};
    assert(order == orderResult);
    topologyOrders = allTopologySortOrders(numCourses, prerequisites);
    assert(0 == topologyOrders.size());

    numCourses = 1;
    prerequisites = {};
    assert(true == canFinish(numCourses, prerequisites));
    order = findOrder(numCourses, prerequisites);
    orderResult = {0};
    assert(order == orderResult);
    topologyOrders = allTopologySortOrders(numCourses, prerequisites);
    assert(1 == topologyOrders.size());
    return 0;
}