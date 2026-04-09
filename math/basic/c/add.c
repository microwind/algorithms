/*
 * 数学基础 - 整数加法运算 (Integer Addition)
 * 演示基本的输入输出和算术运算
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <limits.h>

/**
 * 简单的整数加法计算器
 * 
 * 功能：
 * - 从用户输入获取两个整数
 * - 计算它们的和
 * - 输出结果
 * 
 * 输入样例：
 * please input the first number(int):12
 * please input the second number(int):14
 * 
 * 输出样例：
 * 12 + 14 = 26
 * 
 * 注意事项：
 * - 使用scanf读取输入，需要检查返回值
 * - 整数溢出问题（32位int范围：-2^31 到 2^31-1）
 * - 输入验证（非数字输入的处理）
 */
int main()
{
    int first_num, second_num, sum;
    
    // 获取第一个整数
    printf("please input the first number(int):");
    if (scanf("%d", &first_num) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;  // 错误退出
    }
    
    // 获取第二个整数
    printf("please input the second number(int):");
    if (scanf("%d", &second_num) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;  // 错误退出
    }
    
    // 执行加法运算
    sum = first_num + second_num;
    
    // 检查整数溢出
    if ((second_num > 0 && first_num > INT_MAX - second_num) ||
        (second_num < 0 && first_num < INT_MIN - second_num)) {
        printf("警告：整数溢出！结果可能不正确\n");
    }
    
    // 输出结果
    printf("%d + %d = %d\n", first_num, second_num, sum);
    
    return 0;
}