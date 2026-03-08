/*
 * 数论算法 - 完全数判断 (Perfect Number Detection)
 * 判断一个数是否为完全数（真约数之和等于本身）
 * 时间复杂度: O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 布尔类型定义（兼容性考虑）
typedef int bool;
#define true 1
#define false 0

/**
 * 判断一个数是否为完全数
 * 
 * 算法原理：
 * 完全数：所有真约数（能被整除且小于自身的数）之和等于本身
 * 例如：6 = 1 + 2 + 3，28 = 1 + 2 + 4 + 7 + 14
 * 
 * 参数:
 *     n: 要判断的正整数
 * 返回:
 *     true表示是完全数，false表示不是
 * 
 * 时间复杂度: O(n) - 需要检查1到n-1的所有数
 * 空间复杂度: O(1)
 */
bool is_perfect(int n);

/**
 * 完全数判断演示程序
 * 
 * 功能：
 * - 查找指定范围内的完全数
 * - 显示完全数的约数分解
 * - 展示已知的完全数
 * 
 * 输出样例：
 * 6 is perfect.
 * 28 is perfect.
 * 496 is perfect.
 * 8128 is perfect.
 */
int main()
{
    printf("完全数判断演示\n");
    printf("================\n\n");
    
    printf("查找1-10000范围内的完全数:\n");
    printf("=============================\n");
    
    int perfect_count = 0;
    
    // 查找完全数
    for (int i = 1; i < 10000; i++)
    {
        if (is_perfect(i))
        {
            printf("%d 是完全数 ✓\n", i);
            perfect_count++;
            
            // 显示约数分解
            printf("  约数分解: ");
            int sum = 0;
            for (int j = 1; j < i; j++) {
                if (i % j == 0) {
                    printf("%d", j);
                    sum += j;
                    if (j < i / 2) printf(" + ");
                }
            }
            printf(" = %d\n", sum);
        }
    }
    
    printf("\n找到 %d 个完全数\n", perfect_count);
    
    // 已知的完全数
    printf("\n已知的完全数:\n");
    printf("=============\n");
    int known_perfects[] = {6, 28, 496, 8128, 33550336};
    int known_count = sizeof(known_perfects) / sizeof(known_perfects[0]);
    
    for (int i = 0; i < known_count; i++) {
        printf("• %d", known_perfects[i]);
        if (i < known_count - 1) printf(", ");
    }
    printf("\n");
    
    // 数学性质
    printf("\n数学性质:\n");
    printf("• 所有已知的完全数都是偶数\n");
    printf("• 完全数可以表示为 2^(p-1) × (2^p - 1)\n");
    printf("• 其中 2^p - 1 是梅森素数\n");
    printf("• 目前尚未发现奇完全数\n");
    
    // 应用场景
    printf("\n应用场景:\n");
    printf("• 数论研究\n");
    printf("• 素数探索\n");
    printf("• 数学竞赛\n");
    printf("• 算法练习\n");
    
    return 0;
}

/**
 * 完全数判断实现
 * 遍历所有可能的约数并求和
 */
bool is_perfect(int n)
{
    // 排除1以下的数
    if (n <= 1) return false;
    
    int sum = 0;
    
    // 遍历所有可能的真约数
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)  // 如果i是n的约数
        {
            sum += i;
        }
    }
    
    // 判断约数之和是否等于原数
    return (sum == n);
}
