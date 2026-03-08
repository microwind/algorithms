/*
 * 数论算法 - 数字各位操作 (Digit Operations)
 * 计算数字的各位数之和，以及数字的分解操作
 * 时间复杂度: O(log n)
 */

#include <stdio.h>

/**
 * 获取数字的最后一位（个位数）
 * 
 * 参数:
 *     n: 输入的整数
 * 返回:
 *     n的个位数
 */
int get_last_digit(int n);

/**
 * 去除数字的最后一位，返回前面的部分
 * 
 * 参数:
 *     n: 输入的整数
 * 返回:
 *     去掉个位数后的数字
 */
int get_front_digits(int n);

/**
 * 计算数字各位数之和
 * 
 * 算法原理：
 * 1. 不断取模10得到个位数
 * 2. 累加个位数到总和
 * 3. 整除10去掉个位数
 * 4. 重复直到数字为0
 * 
 * 参数:
 *     n: 输入的正整数
 * 返回:
 *     各位数之和
 * 
 * 时间复杂度: O(log n) - 位数次循环
 * 空间复杂度: O(1)
 */
int calculate_digit_sum(int n);

/**
 * 数字各位操作演示程序
 * 
 * 功能：
 * - 获取用户输入的数字
 * - 分解数字的各位
 * - 计算各位数之和
 * - 反向显示数字
 * 
 * 输入样例：
 * please input the number(int): 12345
 * 
 * 输出样例：
 * last digit: 5
 * front digits: 1234
 * reverse order: 5-4-3-2-1
 * sum of digits: 15
 */
int main()
{
    int num;
    
    printf("数字各位操作演示\n");
    printf("================\n\n");
    printf("请输入一个正整数: ");
    
    // 读取用户输入
    if (scanf("%d", &num) != 1 || num < 0) {
        printf("输入错误：请输入有效的正整数\n");
        return 1;
    }
    
    printf("\n数字分析: %d\n", num);
    printf("=============\n");
    
    // 获取个位数
    int last_digit = get_last_digit(num);
    printf("个位数: %d\n", last_digit);
    
    // 获取前面的数字
    int front_digits = get_front_digits(num);
    printf("前面的数字: %d\n", front_digits);
    
    // 计算各位数之和
    int digit_sum = calculate_digit_sum(num);
    printf("各位数之和: %d\n", digit_sum);
    
    // 反向显示数字
    printf("\n数字分解过程:\n");
    printf("-------------\n");
    printf("反向顺序: ");
    
    int temp = num;
    int count = 0;
    while (temp > 0)
    {
        int digit = temp % 10;
        printf("%d", digit);
        if (temp >= 10) {
            printf("-");
        }
        temp /= 10;
        count++;
    }
    
    printf("\n数字位数: %d\n", count);
    
    // 数学性质
    printf("\n数学性质:\n");
    printf("• 数字和模9性质: n mod 9 = (各位数之和) mod 9\n");
    printf("• 可被3整除: 各位数之和能被3整除\n");
    printf("• 可被9整除: 各位数之和能被9整除\n");
    
    // 应用场景
    printf("\n应用场景:\n");
    printf("• 数字根计算\n");
    printf("• 数值分析\n");
    printf("• 校验位计算\n");
    printf("• 数字游戏\n");
    
    return 0;
}

/**
 * 获取数字的最后一位实现
 * 使用模10运算
 */
int get_last_digit(int n)
{
    return n % 10;
}

/**
 * 去除数字的最后一位实现
 * 使用整除10运算
 */
int get_front_digits(int n)
{
    return n / 10;
}

/**
 * 计算数字各位数之和实现
 * 使用循环分解数字并累加
 */
int calculate_digit_sum(int n)
{
    int sum = 0;
    int temp = n;
    
    while (temp > 0)
    {
        // 除10取模得到最后一位
        int digit = temp % 10;
        sum += digit;
        
        // 整除10得到去掉最后一位的数
        temp = temp / 10;
    }
    
    return sum;
}