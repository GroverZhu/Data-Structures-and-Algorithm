#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/palindrome-removal/
int minimumMoves(vector<int>& arr) {
    int size = static_cast<int>(arr.size());
    vector<vector<int>> operations(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) operations[i][i] = 1;

    for (int offset = 1; offset < size; offset++) {
        for (int i = 0; i < size - offset; i++) {
            int j = i + offset;
            operations[i][j] = offset + 1; // 初始化最大值，i->j 的长度
            if (j - i < 2) {
                if (arr[i] == arr[j]) operations[i][j] = 1;

            } else {
                for (int k = 0; k < offset; k++) {
                    operations[i][j] = min(operations[i][j], operations[i][i + k] + operations[i + k + 1][j]);
                }

                if (arr[i] == arr[j]) {
                    operations[i][j] = min(operations[i + 1][j - 1], operations[i][j]);
                }

            }
        }
    }

// #ifndef NDEBUG
//     for (auto& lst : operations) {
//         for (auto& num : lst) {
//             cout << num << "\t";
//         }
//         cout << endl;
//     }
// #endif

    return operations[0][size - 1];
}

int main(int argc, char* argv[]) {
    vector<int> arr;

    arr = {1, 2};
    assert(2 == minimumMoves(arr));

    arr = {1, 3, 4, 1, 5};
    assert(3 == minimumMoves(arr));
    return 0;
}