/*
 * 蒙特卡洛算法实现 (C语言)
 * 
 * 特点：
 * - 运行时间固定
 * - 给出正确答案的概率很高
 * - 可能会返回错误答案，但概率可控
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// 生成 [0, 1] 范围内的随机数
double random_double() {
    return (double)rand() / RAND_MAX;
}

// 蒙特卡洛方法估算 π
double monte_carlo_pi(int num_samples) {
    int inside_circle = 0;
    
    for (int i = 0; i < num_samples; i++) {
        // 在 [0, 1] × [0, 1] 内随机生成点
        double x = random_double();
        double y = random_double();
        
        // 判断是否在原点为中心、半径为 1 的圆内
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }
    
    // 圆的面积 / 正方形面积 = π/4
    // 所以 π ≈ 4 * (圆内的点数 / 总点数)
    return 4.0 * inside_circle / num_samples;
}

// 蒙特卡洛方法计算积分
double monte_carlo_integration(double (*func)(double), double a, double b, int num_samples) {
    double sum_values = 0.0;
    
    for (int i = 0; i < num_samples; i++) {
        // 在 [a, b] 内随机生成 x
        double x = a + (b - a) * random_double();
        sum_values += func(x);
    }
    
    // 积分 ≈ (b - a) * (平均函数值)
    return (b - a) * sum_values / num_samples;
}

// 测试函数：x²
double func_x_squared(double x) {
    return x * x;
}

// 测试函数：sin(x)
double func_sin(double x) {
    return sin(x);
}

// 蒙特卡洛方法估算概率
double monte_carlo_probability(int num_trials, int success_threshold) {
    int successes = 0;
    
    for (int i = 0; i < num_trials; i++) {
        // 模拟随机事件：掷骰子
        int dice_roll = (int)(random_double() * 6) + 1;
        
        // 假设成功条件是掷出大于等于 success_threshold 的点数
        if (dice_roll >= success_threshold) {
            successes++;
        }
    }
    
    return (double)successes / num_trials;
}

// 蒙特卡洛方法求解Buffon's针问题估算π
double monte_carlo_buffon_needle(int num_trials, double needle_length, double line_spacing) {
    int intersections = 0;
    
    for (int i = 0; i < num_trials; i++) {
        // 随机生成针的中心位置和角度
        double center_y = random_double() * line_spacing;
        double angle = random_double() * M_PI; // [0, π]
        
        // 计算针的两端到最近线的距离
        double half_length = needle_length / 2.0;
        double y1 = center_y - half_length * sin(angle);
        double y2 = center_y + half_length * sin(angle);
        
        // 检查是否与线相交
        if ((int)(y1 / line_spacing) != (int)(y2 / line_spacing)) {
            intersections++;
        }
    }
    
    // Buffon's针公式：π ≈ (2 * needle_length * num_trials) / (line_spacing * intersections)
    if (intersections == 0) return 0.0; // 避免除零
    return (2.0 * needle_length * num_trials) / (line_spacing * intersections);
}

// 蒙特卡洛方法估算圆周率（改进版：使用拒绝采样）
double monte_carlo_pi_rejection_sampling(int num_samples) {
    int inside_circle = 0;
    int total_points = 0;
    
    while (total_points < num_samples) {
        // 在 [-1, 1] × [-1, 1] 内随机生成点
        double x = 2.0 * random_double() - 1.0;
        double y = 2.0 * random_double() - 1.0;
        
        // 只考虑在单位圆内的点（拒绝采样）
        if (x * x + y * y <= 1.0) {
            inside_circle++;
            total_points++;
        }
    }
    
    // 由于我们只统计圆内的点，这里用另一种方法估算π
    // 通过计算点到原点的平均距离来估算π
    double sum_distance = 0.0;
    for (int i = 0; i < num_samples; i++) {
        double x = 2.0 * random_double() - 1.0;
        double y = 2.0 * random_double() - 1.0;
        if (x * x + y * y <= 1.0) {
            sum_distance += sqrt(x * x + y * y);
        }
    }
    
    // 平均距离 ≈ 2/3，所以可以用来验证随机性
    return sum_distance / num_samples;
}

int main() {
    srand(time(NULL));
    
    printf("=== 蒙特卡洛算法演示 ===\n\n");
    
    // 测试π估算
    printf("1. 蒙特卡洛方法估算π\n");
    int samples = 1000000;
    double pi_estimate = monte_carlo_pi(samples);
    printf("采样数: %d\n", samples);
    printf("π估算值: %.6f\n", pi_estimate);
    printf("π真实值: %.6f\n", M_PI);
    printf("误差: %.6f\n\n", fabs(pi_estimate - M_PI));
    
    // 测试数值积分
    printf("2. 蒙特卡洛方法计算积分\n");
    printf("计算: ∫[0,1] x² dx\n");
    double integral_est = monte_carlo_integration(func_x_squared, 0.0, 1.0, 100000);
    printf("估算值: %.6f\n", integral_est);
    printf("真实值: %.6f\n", 1.0/3.0);
    printf("误差: %.6f\n\n", fabs(integral_est - 1.0/3.0));
    
    printf("计算: ∫[0,π] sin(x) dx\n");
    integral_est = monte_carlo_integration(func_sin, 0.0, M_PI, 100000);
    printf("估算值: %.6f\n", integral_est);
    printf("真实值: %.6f\n", 2.0);
    printf("误差: %.6f\n\n", fabs(integral_est - 2.0));
    
    // 测试概率估算
    printf("3. 蒙特卡洛方法估算概率\n");
    printf("模拟掷骰子，求掷出≥4点的概率\n");
    double prob_estimate = monte_carlo_probability(100000, 4);
    printf("估算概率: %.6f\n", prob_estimate);
    printf("理论概率: %.6f\n", 3.0/6.0);
    printf("误差: %.6f\n\n", fabs(prob_estimate - 3.0/6.0));
    
    // 测试Buffon's针问题
    printf("4. Buffon's针问题估算π\n");
    double needle_length = 1.0;
    double line_spacing = 2.0;
    double pi_buffon = monte_carlo_buffon_needle(100000, needle_length, line_spacing);
    printf("针长度: %.1f, 线间距: %.1f\n", needle_length, line_spacing);
    printf("π估算值: %.6f\n", pi_buffon);
    printf("π真实值: %.6f\n", M_PI);
    printf("误差: %.6f\n\n", fabs(pi_buffon - M_PI));
    
    // 测试拒绝采样
    printf("5. 蒙特卡洛拒绝采样\n");
    double avg_distance = monte_carlo_pi_rejection_sampling(100000);
    printf("单位圆内点到原点的平均距离: %.6f\n", avg_distance);
    printf("理论值: %.6f\n", 2.0/3.0);
    printf("误差: %.6f\n", fabs(avg_distance - 2.0/3.0));
    
    return 0;
}
