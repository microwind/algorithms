/*
 * 数论算法 - 奇偶数判断 (Even/Odd Number Detection)
 * 判断一个整数是奇数还是偶数
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 判断一个整数是否为偶数
 * 
 * 算法原理：
 * - 偶数：能被2整除的整数，即 n % 2 == 0
 * - 奇数：不能被2整除的整数，即 n % 2 == 1
 * 
 * 参数:
 *     n: 要判断的整数
 * 返回:
 *     1表示偶数，0表示奇数
 * 
 * 时间复杂度: O(1) - 常数时间
 * 空间复杂度: O(1) - 常数空间
 */
int is_even(int n);

/**
 * 奇偶数判断演示程序
 * 
 * 功能：
 * - 获取用户输入的数字
 * - 判断并显示其奇偶性
 * - 演示1-10的奇偶性
 * 
 * 输入样例：
 * please input the number: 4
 * 
 * 输出样例：
 * 4 is even
 * 
 * 1 is not even
 * 2 is even
 * 3 is not even
 * ...
 */
int main()
{
    int n;
    
    printf("奇偶数判断演示\n");
    printf("================\n\n");
    
    // 用户输入测试
    printf("请输入一个整数: ");
    if (scanf("%d", &n) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;
    }

    printf("\n单数测试: %d\n", n);
    printf("=============\n");
    
    if (is_even(n))
    {
        printf("%d 是偶数 (Even)\n", n);
    }
    else
    {
        printf("%d 是奇数 (Odd)\n", n);
    }
    
    // 显示判断原理
    printf("\n判断原理:\n");
    printf("%d ÷ 2 = %d 余 %d\n", n, n / 2, n % 2);
    printf("余数为 %d，所以 %d 是%s\n", n % 2, n, 
           (n % 2 == 0) ? "偶数" : "奇数");
    
    // 批量测试
    printf("\n批量测试 (1-10):\n");
    printf("================\n");
    
    int even_count = 0, odd_count = 0;
    
    for (int i = 1; i <= 10; i++)
    {
        if (is_even(i))
        {
            printf("%2d: 偶数 ✓\n", i);
            even_count++;
        }
        else
        {
            printf("%2d: 奇数  ○\n", i);
            odd_count++;
        }
    }
    
    // 统计结果
    printf("\n统计结果:\n");
    printf("偶数个数: %d\n", even_count);
    printf("奇数个数: %d\n", odd_count);
    
    // 数学性质
    printf("\n数学性质:\n");
    printf("• 偶数 + 偶数 = 偶数\n");
    printf("• 奇数 + 奇数 = 偶数\n");
    printf("• 偶数 + 奇数 = 奇数\n");
    printf("• 偶数 × 任意数 = 偶数\n");
    printf("• 奇数 × 奇数 = 奇数\n");
    
    // 应用场景
    printf("\n应用场景:\n");
    printf("• 数值分类\n");
    printf("• 算法优化（循环步长）\n");
    printf("• 数据结构设计\n");
    printf("• 数学证明\n");
    
    return 0;
}

/**
 * 奇偶数判断实现
 * 使用模2运算判断
 */
int is_even(int n)
{
    return (n % 2 == 0);
}