/*
 * 数学基础 - 平均值计算 (Average Calculation)
 * 演示算术平均值的计算方法
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <limits.h>

/**
 * 计算两个整数的算术平均值
 * 
 * 算术平均值公式：avg = (a + b) / 2
 * 
 * 注意事项：
 * - 整数除法会截断小数部分
 * - 可能存在精度损失
 * - 大数相加可能溢出
 * 
 * 输入样例：
 * please input the first number(int):12
 * please input the second number(int):15
 * 
 * 输出样例：
 * 12 + 15 average = 13
 * 
 * 改进建议：
 * - 使用浮点数避免精度损失
 * - 检查整数溢出
 * - 添加输入验证
 */
int main()
{
    int first_num, second_num, average;
    
    // 获取第一个整数
    printf("please input the first number(int):");
    if (scanf("%d", &first_num) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;
    }
    
    // 获取第二个整数
    printf("please input the second number(int):");
    if (scanf("%d", &second_num) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;
    }
    
    // 计算算术平均值
    average = (first_num + second_num) / 2;
    
    // 检查可能的溢出情况
    if ((second_num > 0 && first_num > INT_MAX - second_num) ||
        (second_num < 0 && first_num < INT_MIN - second_num)) {
        printf("警告：整数相加可能溢出\n");
    }
    
    // 输出结果
    printf("%d + %d average = %d\n", first_num, second_num, average);
    
    // 提示精度限制
    if ((first_num + second_num) % 2 != 0) {
        printf("注意：由于整数除法，结果已截断小数部分\n");
        printf("精确平均值应为 %.1f\n", (first_num + second_num) / 2.0);
    }
    
    return 0;
}