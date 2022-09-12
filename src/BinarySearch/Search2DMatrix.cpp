#include <pthread.h>
#include <climits>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/search-a-2d-matrix/
bool searchMatrix(vector<vector<int>>& matrix, int target) {
#if 0  // 缩小范围
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());

    int x = 0;
    int y = cols - 1;

    while (x < rows && y >= 0) {
        if (matrix[x][y] < target) {
            x++;
        } else if (matrix[x][y] > target) {
            y--;
        } else if (matrix[x][y] == target) {
            return true;
        }
    }

    return false;
#endif

#if 1  // 二分搜索，该二维矩阵按行展开后是一个有序列表
    int rows = static_cast<int>(matrix.size());
    if (rows == 0) {
        return false;
    }
    int cols = static_cast<int>(matrix[0].size());
    if (cols == 0) {
        return false;
    }

    int left = 0;
    int right = rows * cols;
    int mid;

    while (left < right) {
        mid = (right - left) / 2 + left;
        int x = mid / cols;
        int y = mid % cols;

        if (matrix[x][y] == target) {
            return true;
        } else if (matrix[x][y] < target) {
            left = mid + 1;
        } else if (matrix[x][y] > target) {
            right = mid;
        }
    }

    return false;

#endif
}

// https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/
int lessEqualThanCount(vector<vector<int>>& matrix, int val) {
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());
    int cnt = 0;

    int i = 0;
    int j = cols - 1;

    while (i < rows && j >= 0) {
        if (matrix[i][j] <= val) {
            cnt += j + 1;
            i += 1;
        } else {
            j -= 1;
        }
    }

    return cnt;
}

int kthSmallest(vector<vector<int>>& matrix, int k) {
    int rows = static_cast<int>(matrix.size());
    if (rows == 0) {
        return INT_MIN;
    }
    int cols = static_cast<int>(matrix[0].size());
    if (k >= rows * cols) {
        return matrix[rows - 1][cols - 1];
    }

    int left = matrix[0][0];
    int right = matrix[rows - 1][cols - 1];
    int mid;
    while (left < right) {
        mid = (right - left) / 2 + left;
        int cnt = lessEqualThanCount(matrix, mid);
        if (cnt < k) {
            left = mid + 1;
        } else if (cnt > k) {
            right = mid;
        } else if (cnt == k) {
            right = mid;
        }
    }
    return left;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> matrix;
    int target;
    int k;

    matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};

    target = 3;
    assert(true == searchMatrix(matrix, target));

    target = 13;
    assert(false == searchMatrix(matrix, target));

    k = 1;
    assert(1 == kthSmallest(matrix, k));
    k = 2;
    assert(3 == kthSmallest(matrix, k));
    k = 3;
    assert(5 == kthSmallest(matrix, k));
    k = 4;
    assert(7 == kthSmallest(matrix, k));
    k = 5;
    assert(10 == kthSmallest(matrix, k));

    matrix = {{1, 1, 3, 8, 13}, {4, 4, 4, 8, 18}, {9, 14, 18, 19, 20}, {14, 19, 23, 25, 25}, {18, 21, 26, 28, 29}};
    k = 13;
    assert(18 == kthSmallest(matrix, k));
    return 0;
}
