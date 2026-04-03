#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double trapezoidal_rule(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return sum * h;
}

double simpsons_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) n++; // 确保n为偶数
    
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x);
        } else {
            sum += 4 * f(x);
        }
    }
    
    return sum * h / 3;
}

double monte_carlo_integration(double (*f)(double), double a, double b, int samples) {
    double sum = 0;
    
    // 初始化随机数种子
    srand(time(NULL));
    
    for (int i = 0; i < samples; i++) {
        double x = a + (b - a) * (double)rand() / RAND_MAX;
        sum += f(x);
    }
    
    return (b - a) * sum / samples;
}

// 测试函数：f(x) = x^2
double test_function(double x) {
    return x * x;
}

int main() {
    double a = 0, b = 1;
    int n = 1000;
    
    printf("数值积分测试 (f(x) = x^2, [0,1]):\n");
    
    double trapezoidal = trapezoidal_rule(test_function, a, b, n);
    printf("梯形法则: %.6f\n", trapezoidal);
    
    double simpson = simpsons_rule(test_function, a, b, n);
    printf("辛普森法则: %.6f\n", simpson);
    
    double monte_carlo = monte_carlo_integration(test_function, a, b, 10000);
    printf("蒙特卡洛积分: %.6f\n", monte_carlo);
    
    printf("精确值: %.6f\n", 1.0/3.0);
    
    return 0;
}
