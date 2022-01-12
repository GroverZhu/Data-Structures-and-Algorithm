#include <cstdio>

/**
 * 计算x^n
 */ 
double pow(double x, int n) {
    if (n == 0) return 1;
    double result = 1.0;

    // 快速幂求法
    for (int i = n; i != 0; i /= 2) {
        if (i % 2 != 0) {
            result *= x;
        }
        x *= x;
    }
    return n > 0 ? result : 1.0 / result;
}

// 迭代求法
double recursive_pow(double x, int n) {
    if (n == 0) return 1.0;
    double result = recursive_pow(x, n / 2);
    if (n % 2 != 0) {
        // 需要处理n<0的情况
        if (n > 0) {
            result = result * result * x;
        } else {
            result = (result * result) / x;
        }
    } else {
        result = result * result;
    }
    return result;
}

int main() {
    double x = 2;
    int n = -2;
    printf("%lf\n", recursive_pow(x, n));
    return 0;
}