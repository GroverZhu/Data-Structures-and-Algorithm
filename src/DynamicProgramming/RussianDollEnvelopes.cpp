#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/russian-doll-envelopes/
int maxEnvelopes(vector<vector<int>>& envelopes) {
    int size = static_cast<int>(envelopes.size());
    if (size <= 1) return size;

    auto cmp = [](const vector<int>& lhs, const vector<int>& rhs) {
        if (lhs[0] == rhs[0]) {
            return lhs[1] > rhs[1];
        }

        return lhs[0] < rhs[0];
    };
    sort(envelopes.begin(), envelopes.end(), cmp);

    vector<int> nums(size);
    for (int i = 0; i < size; i++) {
        nums[i] = envelopes[i][1];
    }
    // 二分查找最长上升子序列
    vector<int> top(size, 0);
    int piles = 0;
    for (int i = 0; i < size; i++) {
        int poker = nums[i];
        int left = 0;
        int right = piles;
        while (left < right) {
            int mid = (right - left) / 2 + left;  // [left, right)
            if (poker < top[mid]) {
                right = mid;
            } else if (poker > top[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        if (left == piles) {
            piles++;
        }
        top[left] = poker;
    }
    return piles;
}

// 可以旋转的n维 https://people.cs.ksu.edu/~pradeep/paper_cis775.pdf
// 以二维为例
struct Envelope {
    int x;
    int y;

    Envelope() : x(0), y(0) {}

    Envelope(int _x, int _y) : x(_x), y(_y) {}

    // 判断当前 envelope 能否嵌入到 rhs 中
    bool canNest(const Envelope& rhs) {  // n 维的话，先将每个维度按照升序排序，逐个比较，所有维度满足条件才可以嵌套
        int lhs_x = min(this->x, this->y);
        int lhs_y = max(this->x, this->y);

        int rhs_x = min(rhs.x, rhs.y);
        int rhs_y = max(rhs.x, rhs.y);

        return lhs_x < rhs_x && lhs_y < rhs_y;
    }

    friend ostream& operator<<(ostream& output, const Envelope& envelope) {
        output << envelope.x << "," << envelope.y;
        return output;
    }
};

int maxRotateEnvelopes(vector<vector<int>>& inputs) {
    int size = static_cast<int>(inputs.size());
    if (size <= 1) {
        return size;
    }
    vector<Envelope> envelopes(size);
    for (int i = 0; i < size; i++) {
        envelopes[i] = Envelope(inputs[i][0], inputs[i][1]);
    }

    map<int, vector<int>> graph;
    vector<int> indgree(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                continue;
            }
            // envelope i 能否嵌套到 envelop j 中
            if (envelopes[i].canNest(envelopes[j])) {
                graph[i].push_back(j);
                indgree[j] += 1;
            }
        }
    }

#if 0  // 打印有向图的信息
    for (auto iter : graph) {
        cout << envelopes[iter.first] << "->";
        for (auto n : iter.second) {
            cout << envelopes[n] << ";";
        }
        cout << endl;
    }
    cout << endl;
#endif

    queue<int> q;
    for (int i = 0; i < size; i++) {
        if (indgree[i] == 0) {
            q.push(i);
        }
    }
    int result = 0;

    while (!q.empty()) {
        result += 1;
        int len = static_cast<int>(q.size());
        for (int i = 0; i < len; i++) {
            int cur = q.front();
            q.pop();
            for (int next : graph[cur]) {
                indgree[next] -= 1;
                if (indgree[next] == 0) {
                    q.push(next);
                }
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> envelopes;

    envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    assert(3 == maxEnvelopes(envelopes));
    assert(3 == maxRotateEnvelopes(envelopes));

    envelopes = {{1, 1}, {1, 1}, {1, 1}};
    assert(1 == maxEnvelopes(envelopes));
    assert(1 == maxRotateEnvelopes(envelopes));

    envelopes = {{1, 3}, {3, 5}, {6, 7}, {6, 8}, {8, 4}, {9, 5}};
    assert(3 == maxEnvelopes(envelopes));
    assert(4 == maxRotateEnvelopes(envelopes));

    envelopes = {{1, 15}, {7, 18}, {7, 6}, {7, 100}, {2, 200}, {17, 30}, {17, 45},
                 {3, 5},  {7, 8},  {3, 6}, {3, 10},  {7, 20},  {17, 3},  {17, 45}};
    assert(3 == maxEnvelopes(envelopes));
    assert(4 == maxRotateEnvelopes(envelopes));

    envelopes = {{7, 8}, {12, 16}, {12, 5}, {1, 8}, {4, 19}, {3, 15}, {4, 10}, {9, 16}};
    assert(3 == maxEnvelopes(envelopes));
    assert(4 == maxRotateEnvelopes(envelopes));

    return 0;
}