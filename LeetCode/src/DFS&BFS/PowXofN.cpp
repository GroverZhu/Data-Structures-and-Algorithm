#include <iostream>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/powx-n/
double myPow(double x, int n) {
    if (n == 0) return 1.0;
    double epsilon = 1e-5;
    if (abs(x - 1.0) < epsilon || n == 1) return x;

    long long nLong = static_cast<long long>(n);
    bool flag = true; // n正数true，n负数false
    if (n < 0) {
        flag = false;
        nLong = -nLong;
    }
    double tmp = myPow(x, nLong / 2);

    double result = tmp * tmp;
    if (n & 1) {
        result *= x;
    }

    return flag ? result : 1.0 / result;
}

int main(int argc, char* argv[]) {
    double epsilon = 1e-6;
    double x;
    int n;
    double ans, result;

    x = 2.0;
    n = 10;
    ans = 1024.0;
    result = myPow(x, n);
    assert(abs(ans - result) < epsilon);


    x = 2.1;
    n = 3;
    ans = 9.261;
    result = myPow(x, n);
    assert(abs(ans - result) < epsilon);

    x = 2.0;
    n = -2;
    ans = 0.25;
    result = myPow(x, n);
    assert(abs(ans - result) < epsilon);

    x = 0.0;
    n = 1;
    ans = 0.0;
    result = myPow(x, n);
    assert(abs(ans - result) < epsilon);

    x = 2.0;
    n = -2147483648;
    ans = 0.0;
    result = myPow(x, n);
    assert(abs(ans - result) < epsilon);

    x = 1.0;
    n = -2147483648;
    ans = 1.0;
    result = myPow(x, n);
    assert(abs(ans - result) < epsilon);
    return 0;
}