
#include <cassert>

// x = x - f(x)/f'(x), f(x) = x^2 - a
// x = x / 2  + a / 2x
int newtonIter(int x) {
    if (x <= 1) return x;
    double epsilon = 1e-5;
    double cur = x;
    double next = cur / 2.0 + x / (2.0 * cur);
    while (abs(next - cur) > epsilon) {
        cur = next;
        next = cur / 2.0 + x / (2.0 * cur);
    }
    return next;
}
// https://leetcode-cn.com/problems/sqrtx/
int mySqrt(int x) {
#if 0
    if (x <= 1) return x;
    double left = 0;
    double right = x;
    double mid;
    double epsilon = 1e-5;
    while (left <= right) {
        mid = (right - left) / 2.0 + left;
        double tmp = mid * mid;
        if (abs(tmp - x) < epsilon) {
            return static_cast<int>(mid);
        } else if (tmp > x) {
            right = mid;
        } else if (tmp < x) {
            left = mid;
        }
    }
    return mid;
#endif

#if 1
    return newtonIter(x);
#endif
}

int main(int argc, char* argv[]) {
    assert(2 == mySqrt(4));
    assert(2 == mySqrt(8));
    assert(1 == mySqrt(1));
    assert(0 == mySqrt(0));
    return 0;
}
