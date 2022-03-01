#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/triangle/description/
int minimumTotal(vector<vector<int>>& triangle) {
    int rows = static_cast<int>(triangle.size());
    if (rows == 1) return triangle[0][0];
    for (int i = rows - 2; i >= 0; i--) {
        int cols = static_cast<int>(triangle[i].size());
        for (int j = 0; j < cols; j++) {
            triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];

}


int main(int argc, char* argv[]) {
    vector<vector<int>> triangle;
    triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    assert(11 == minimumTotal(triangle));

    triangle = {{-10}};
    assert(-10 == minimumTotal(triangle));

    return 0;
}