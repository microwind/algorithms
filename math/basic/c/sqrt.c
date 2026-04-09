/*
 * 数学算法 - 牛顿迭代法求平方根 (Newton's Method for Square Root)
 * 使用牛顿-拉弗森方法迭代逼近平方根
 * 时间复杂度: O(log n)，收敛速度快
 */

#include <stdio.h>
#include <math.h>

// 精度控制：迭代停止的误差阈值
#define PRECISION 0.00001

// 布尔类型定义（兼容性考虑）
typedef int bool;
#define true 1
#define false 0

/**
 * 使用牛顿迭代法计算平方根
 * 
 * 算法原理：
 * 1. 从初始猜测值开始（通常设为x本身）
 * 2. 迭代公式：g_new = (g_old + x/g_old) / 2
 * 3. 当 g^2 ≈ x 时停止迭代
 * 
 * 参数:
 *     x: 要求平方根的非负数
 * 返回:
 *     x的平方根近似值
 * 
 * 时间复杂度: O(log n) - 二次收敛
 * 空间复杂度: O(1)
 */
double sqrtN(double x);

/**
 * 检查两个浮点数是否近似相等
 * 
 * 使用相对误差判断：|x - y| / min(|x|, |y|) < precision
 * 避免除零：当min(x,y)接近0时使用绝对误差
 * 
 * 参数:
 *     x: 第一个数
 *     y: 第二个数
 * 返回:
 *     true: 近似相等，false: 不相等
 */
bool approximateEqual(double x, double y);
/**
 * 测试牛顿迭代法求平方根算法
 * 
 * 输出样例：
 * sqrtN(2) = 1.41422
 *  sqrt(2) = 1.41421
 * sqrtN(3) = 1.73205
 *  sqrt(3) = 1.73205
 * sqrtN(4) = 2.00000
 *   sqrt(4) = 2.00000
 */
int main()
{
    printf("牛顿迭代法求平方根测试 (1-49)\n");
    printf("格式: sqrtN(n) vs 标准sqrt(n)\n");
    printf("=====================================\n");
    
    // 测试1-49的平方根
    for (double i = 1; i < 50; i++)
    {
        double custom_result = sqrtN(i);
        double standard_result = sqrt(i);
        
        printf("sqrtN(%2.0f) = %.5f\n", i, custom_result);
        printf("  sqrt(%2.0f) = %.5f\n", i, standard_result);
        
        // 计算相对误差
        double error = fabs(custom_result - standard_result) / standard_result;
        if (error > 0.001) {  // 如果误差超过0.1%
            printf("  警告: 误差较大 %.6f\n", error);
        }
    }
    
    printf("\n算法特点:\n");
    printf("• 二次收敛，速度快\n");
    printf("• 精度可控\n");
    printf("• 适用于大数计算\n");
    
    return 0;
}

double sqrtN(double x)
{
    // 边界情况处理：0的平方根是0
    if (x == 0) return 0;
    
    // 负数处理：返回NaN（在标准库中，sqrt(-1)也是NaN）
    if (x < 0) return NAN;
    
    // 牛顿迭代法实现
    // 1. 初始猜测值：设为x本身（对于大数效率较低，可以优化为x/2）
    double guess = x;
    
    // 2. 迭代逼近：直到guess^2与x的误差在精度范围内
    while (!approximateEqual(guess * guess, x))
    {
        // 牛顿迭代公式：g_new = (g_old + x/g_old) / 2
        // 这个公式来自于求解 f(g) = g^2 - x = 0 的牛顿迭代
        guess = (guess + x / guess) / 2;
    }
    
    return guess;
}

bool approximateEqual(double x, double y)
{
    // 处理特殊情况：两个数都接近0
    if (fabs(x) < PRECISION && fabs(y) < PRECISION) {
        return true;
    }
    
    // 相对误差判断：|x - y| / min(|x|, |y|) < PRECISION
    // 避免除零：使用绝对值较小的数作为分母
    double min_val = fabs(x) < fabs(y) ? fabs(x) : fabs(y);
    
    // 防止除零：如果min_val为0，使用绝对误差
    if (min_val == 0) {
        return fabs(x - y) < PRECISION;
    }
    
    return fabs(x - y) / min_val < PRECISION;
}
