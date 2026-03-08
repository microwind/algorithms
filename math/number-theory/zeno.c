/*
 * 数论算法 - 芝诺悖论 (Zeno's Paradox)
 * 演示无限级数收敛的概念
 * 时间复杂度: O(n) - 直到浮点精度极限
 */

#include <stdio.h>

/**
 * 芝诺悖论演示程序
 * 
 * 算法原理：
 * 芝诺悖论中的二分法：1/2 + 1/4 + 1/8 + 1/16 + ...
 * 这是一个几何级数，首项a=1/2，公比r=1/2
 * 无穷级数和：S = a/(1-r) = (1/2)/(1-1/2) = 1
 * 
 * 功能：
 * - 演示芝诺悖论的收敛过程
 * - 显示每次累加的结果
 * - 直到浮点精度极限
 * 
 * 输出样例：
 * 0.8
 * 1.2
 * 1.4
 * 1.5
 * ...
 * The sum of Zeno's series is 1.6
 */
int main()
{
    printf("芝诺悖论演示\n");
    printf("============\n\n");
    printf("芝诺悖论：无限分割的收敛\n");
    printf("级数：1/2 + 1/4 + 1/8 + 1/16 + ...\n\n");
    
    double sum = 0.0;
    double term = 0.8;  // 初始项（可以设为任意值）
    int count = 0;
    
    printf("收敛过程:\n");
    printf("---------\n");
    
    // 循环直到浮点精度极限
    // 当term相对于sum太小时，sum + term == sum
    while (sum != sum + term)
    {
        sum += term;
        count++;
        printf("第%d项: %g\n", count, sum);
        term /= 2;  // 每次减半
    }
    
    printf("\n最终结果:\n");
    printf("---------\n");
    printf("项数: %d\n", count);
    printf("级数和: %g\n", sum);
    
    // 数学解释
    printf("\n数学解释:\n");
    printf("---------\n");
    printf("这是一个几何级数：\n");
    printf("• 首项 a = %.1f\n", 0.8);
    printf("• 公比 r = 1/2\n");
    printf("• 无穷级数和 S = a/(1-r) = %.1f/(1-0.5) = %.1f\n", 0.8, 0.8 * 2);
    
    printf("\n芝诺悖论原理解释:\n");
    printf("• 阿喀琉斯追乌龟：每次追到乌龟上次的位置\n");
    printf("• 虽然有无限个步骤，但总距离是有限的\n");
    printf("• 这体现了极限和收敛的概念\n");
    
    printf("\n实际应用:\n");
    printf("• 微积分基础\n");
    printf("• 极限理论\n");
    printf("• 级数求和\n");
    printf("• 数值分析\n");
    
    return 0;
}
