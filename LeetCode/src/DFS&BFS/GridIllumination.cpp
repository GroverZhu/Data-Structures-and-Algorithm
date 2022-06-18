#include <cassert>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/grid-illumination/
vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
    auto hashPair = [](const pair<int, int>& lhs) -> size_t {
        static hash<long long> hashDoubleLong;
        return hashDoubleLong(static_cast<long long>(lhs.first) + (static_cast<long long>(lhs.second) << 32));
    };
    unordered_set<pair<int, int>, decltype(hashPair)> points(0, hashPair);
    map<int, int> rows;
    map<int, int> cols;
    map<int, int> neg;
    map<int, int> pos;

    for (auto&& lamp : lamps) {
        int x = lamp[0];
        int y = lamp[1];
        if (points.find({x, y}) != points.end()) continue;
        points.insert({x, y});
        rows[x]++;
        cols[y]++;
        neg[y + x]++;
        pos[y - x]++;
    }

    int size = static_cast<int>(queries.size());
    vector<int> result(size, 0);

    const int dir = 9;
    int dx[dir] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    int dy[dir] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

    for (int i = 0; i < size; i++) {
        int x = queries[i][0];
        int y = queries[i][1];

        if (rows.find(x) != rows.end() && rows[x] > 0) {
            result[i] = 1;
        } else if (cols.find(y) != cols.end() && cols[y] > 0) {
            result[i] = 1;
        } else if (neg.find(y + x) != neg.end() && neg[y + x] > 0) {
            result[i] = 1;
        } else if (pos.find(y - x) != pos.end() && pos[y - x] > 0) {
            result[i] = 1;
        }

        for (int j = 0; j < dir; j++) {
            int next_x = x + dx[j];
            int next_y = y + dy[j];

            if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= n) continue;

            if (points.find({next_x, next_y}) != points.end()) {
                points.erase({next_x, next_y});
                rows[next_x]--;
                cols[next_y]--;
                neg[next_y + next_x]--;
                pos[next_y - next_x]--;
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> lamps = {{0, 0}, {4, 4}};
    int n = 5;
    vector<vector<int>> queries = {{1, 1}, {1, 0}};
    vector<int> ans = {1, 0};
    auto result = gridIllumination(n, lamps, queries);
    assert(result == ans);
    return 0;
}