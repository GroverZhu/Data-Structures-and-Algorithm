#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/range-sum-query-2d-immutable/

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());

        prefix = vector<vector<int>>(rows + 1, vector<int>(cols + 1, 0));

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] + matrix[i - 1][j - 1] - prefix[i - 1][j - 1];
            }
        }

        // for (int i = 0; i <= rows; i++) {
        //     for (int j = 0; j <= cols; j++) {
        //         cout << prefix[i][j] << "\t";
        //     }
        //     cout << endl;
        // }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefix[row2 + 1][col2 + 1] - prefix[row1][col2 + 1] - prefix[row2 + 1][col1] + prefix[row1][col1];
    }

private:
    vector<vector<int>> prefix;
};

int main(int argc, char* argv[]) {
    vector<vector<int>> nums = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    NumMatrix test(nums);

    assert(8 == test.sumRegion(2, 1, 4, 3));
    assert(11 == test.sumRegion(1, 1, 2, 2));
    assert(12 == test.sumRegion(1, 2, 2, 4));
    return 0;
}