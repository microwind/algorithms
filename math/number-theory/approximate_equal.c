/*
 * 数论算法 - 浮点数近似相等判断 (Floating Point Approximate Equality)
 * 使用相对误差判断两个浮点数是否近似相等
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <math.h>

// 精度控制：相对误差阈值
#define PRECISION 0.00001

// 布尔类型定义（兼容性考虑）
typedef int bool;
#define true 1
#define false 0

/**
 * 检查两个浮点数是否近似相等
 * 
 * 算法原理：
 * 使用相对误差判断：|x - y| / min(|x|, |y|) < precision
 * 避免了直接比较浮点数的不精确性问题
 * 
 * 参数:
 *     x: 第一个浮点数
 *     y: 第二个浮点数
 * 返回:
 *     true: 近似相等，false: 不相等
 * 
 * 注意事项：
 * - 当两个数都接近0时，使用绝对误差判断
 * - 避免除零错误
 * - 适用于科学计算中的精度比较
 */
bool approximateEqual(double x, double y);

/**
 * 浮点数近似相等判断演示
 * 
 * 功能：
 * - 演示近似相等判断的实际应用
 * - 对比不同精度下的判断结果
 * 
 * 输出样例：
 * 1.1110102000 and 1.1110001000 is not approximate
 * 2.3330102000 and 2.3330101000 is approximate
 */
int main()
{
    printf("浮点数近似相等判断演示\n");
    printf("========================\n\n");
    
    double x, y;
    
    // 测试用例1：精度差异较大
    x = 1.1110102;
    y = 1.1110001;
    printf("测试1: %.10f vs %.10f\n", x, y);
    printf("绝对差值: %.10f\n", fabs(x - y));
    printf("相对误差: %.10f\n", fabs(x - y) / fmin(fabs(x), fabs(y)));
    
    if (approximateEqual(x, y))
    {
        printf("结果: 近似相等 ✓\n");
    }
    else
    {
        printf("结果: 不近似相等 ✗\n");
    }

    printf("\n");

    // 测试用例2：精度差异较小
    x = 2.3330102;
    y = 2.3330101;
    printf("测试2: %.10f vs %.10f\n", x, y);
    printf("绝对差值: %.10f\n", fabs(x - y));
    printf("相对误差: %.10f\n", fabs(x - y) / fmin(fabs(x), fabs(y)));
    
    if (approximateEqual(x, y))
    {
        printf("结果: 近似相等 ✓\n");
    }
    else
    {
        printf("结果: 不近似相等 ✗\n");
    }
    
    // 边界情况测试
    printf("\n边界情况测试:\n");
    
    // 测试接近0的数
    x = 0.000001;
    y = 0.000002;
    printf("接近0: %.10f vs %.10f\n", x, y);
    if (approximateEqual(x, y)) {
        printf("结果: 近似相等 ✓\n");
    } else {
        printf("结果: 不近似相等 ✗\n");
    }
    
    // 测试0值
    x = 0.0;
    y = 0.0;
    printf("零值比较: %.10f vs %.10f\n", x, y);
    if (approximateEqual(x, y)) {
        printf("结果: 近似相等 ✓\n");
    } else {
        printf("结果: 不近似相等 ✗\n");
    }
    
    printf("\n算法说明:\n");
    printf("• 精度阈值: %.10f\n", PRECISION);
    printf("• 使用相对误差避免大数问题\n");
    printf("• 适用于科学计算和数值分析\n");
    
    return 0;
}

/**
 * 浮点数近似相等判断实现
 * 使用相对误差进行判断，处理边界情况
 */
bool approximateEqual(double x, double y)
{
    // 处理特殊情况：两个数都接近0
    if (fabs(x) < PRECISION && fabs(y) < PRECISION) {
        return true;  // 都接近0，认为相等
    }
    
    // 计算绝对值的最小值
    double min_val = fabs(x) < fabs(y) ? fabs(x) : fabs(y);
    
    // 防止除零：如果min_val为0，使用绝对误差
    if (min_val == 0) {
        return fabs(x - y) < PRECISION;
    }
    
    // 相对误差判断：|x - y| / min(|x|, |y|) < precision
    // 两个数相减的绝对值除以较小的那个数，小于设定的精度即近似相等
    return fabs(x - y) / min_val < PRECISION;
}