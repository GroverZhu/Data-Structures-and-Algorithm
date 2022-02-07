#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/h-index-ii/
int hIndex(vector<int>& citations) {
    int size = static_cast<int>(citations.size());

    int left = 0;
    int right = size;
    int mid;
    while (left < right) {
        mid = (right - left) / 2 + left;
        int num = size - mid;
        if (citations[mid] < num) {
            left = mid + 1;
        } else if (citations[mid] > num) {
            right = mid;
        } else if (citations[mid] == num) {
            right = mid;
        }

    }

    return size - left;

}

int main(int argc, char* argv[]) {
    vector<int> citations;
    int ans, result;

    citations = {0, 1, 3, 5, 6};
    ans = 3;
    result = hIndex(citations);
    assert(ans == result);

    citations = {1, 2, 100};
    ans = 2;
    result = hIndex(citations);
    assert(ans == result);

    citations = {1, 1};
    ans = 1;
    result = hIndex(citations);
    assert(ans == result);

    citations = {1, 1};
    ans = 1;
    result = hIndex(citations);
    assert(ans == result);

    return 0;
}
