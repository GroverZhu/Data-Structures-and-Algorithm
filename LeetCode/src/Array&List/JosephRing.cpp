// g++ joseph_ring.cpp  -o joseph_ring -D FORCE
#include <iostream>
#include <cstdio>
#include <cstdio>
#include <vector>
#include <cassert>
#include <ctime>

using namespace std;

// https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
int josephRing(int n, int m) {

#ifdef FORCE
    // 失业解法
    vector<int> circle(n, 0);
    for (int i = 0; i < n; i++) circle[i] = i;

    int index = 0;
    while (n > 1) {
        index = (index + m - 1) % n;
        circle.erase(circle.begin() + index);
        --n;
    }
    return circle[0];
#else

   int ans = 0;
   for (int i = 2; i <= n; i++) {
       ans = (ans + m) % i;
   }
   return ans;

#endif
}

int main(int argc, char* argv[]) {
    int n, m;
    clock_t start, end;

    // Test 1
    n = 10, m = 17;
    start = clock();
    assert(2 == josephRing(n, m));
    end = clock();
    printf("Test1 costs time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    //Test 2
    n = 5, m = 3;
    start = clock();
    assert(3 == josephRing(n, m));
    end = clock();
    printf("Test2 costs time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Test 3
    start = clock();
    n = 71989, m = 111059;
    assert(34203 == josephRing(n, m));
    end = clock();
    printf("Test3 costs time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Test 4
    start = clock();
    n = 100000, m = 2;
    assert(68928 == josephRing(n, m));
    end = clock();
    printf("Test4 costs time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Test 5
    start = clock();
    n = 100000, m = 1;
    assert(99999 == josephRing(n, m));
    end = clock();
    printf("Test5 costs time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}