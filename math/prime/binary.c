/*
 * 数学算法 - 二进制转换 (Binary Conversion)
 * 演示十进制与二进制之间的相互转换
 * 时间复杂度: O(log n)
 */

#include <stdio.h>
#include <math.h>

/**
 * 十进制转二进制（直接打印法）
 * 
 * 算法原理：
 * 1. 不断除2取余数
 * 2. 余数的逆序就是二进制表示
 * 
 * 参数：
 *     num: 要转换的十进制正整数
 * 
 * 注意：
 * - 直接按计算顺序打印，结果是逆序的
 * - 适用于快速查看转换过程
 */
void decimalToBinary(int num);

/**
 * 十进制转二进制（数值构建法）
 * 
 * 算法原理：
 * 1. 除2取余，但将余数构建为数值
 * 2. 通过乘10累加余数
 * 
 * 参数：
 *     num: 要转换的十进制正整数
 * 
 * 注意：
 * - 构建的二进制数值可能溢出
 * - 仅适用于较小的数字
 */
void decimal2Binary(int num);

/**
 * 二进制转十进制
 * 
 * 算法原理：
 * 1. 从右到左，每位乘以2的相应次方
 * 2. 次方从0开始递增
 * 
 * 参数：
 *     num: 要转换的二进制数（以十进制形式存储）
 */
void binaryToDecimal(long num);

/**
 * 计算数字的位数（辅助函数）
 * 
 * 参数：
 *     n: 要计算位数的数字
 * 返回：
 *     数字的位数
 */
int length(double n);

/**
 * 二进制转换演示程序
 * 
 * 功能：
 * - 演示十进制转二进制的两种方法
 * - 演示二进制转十进制
 * - 比较不同转换方法的结果
 * 
 * 测试用例：20 → 10100 → 20
 */
int main()
{
    printf("二进制转换演示\n");
    printf("===============\n");
    
    int test_num = 20;
    
    // 方法1：直接打印余数（逆序）
    printf("\n方法1：直接打印余数法");
    decimalToBinary(test_num);
    
    // 方法2：构建二进制数值
    printf("\n方法2：数值构建法");
    decimal2Binary(test_num);
    
    // 反向转换验证
    printf("\n反向转换验证");
    binaryToDecimal(10100L);  // 20的二进制是10100
    
    printf("\n\n转换原理说明：");
    printf("\n• 十进制→二进制：不断除2取余，余数逆序排列");
    printf("\n• 二进制→十进制：每位乘以2的相应次方后相加");
    
    return 0;
}

/**
 * 计算数字的位数
 */
int length(double n)
{
    if (n == 0) return 1;
    return (int)log10(fabs(n)) + 1;
}

/**
 * 十进制转二进制（直接打印法）
 * 按计算顺序直接打印余数，结果是逆序的
 */
void decimalToBinary(int num)
{
    int remainder;
    int divisor = 2;
    
    printf("\n %d 转换为二进制（直接打印）: ", num);
    
    if (num == 0) {
        printf("0");
        return;
    }
    
    // 不断除2取余，倒序打印余数
    while (num != 0)
    {
        remainder = num % divisor;
        num /= divisor;
        printf("%d", remainder);  // 直接打印，结果是逆序的
    }
}

/**
 * 十进制转二进制（数值构建法）
 * 尝试构建一个表示二进制的十进制数值
 */
void decimal2Binary(int num)
{
    long binary = 0L;
    int remainder;
    int multiplier = 1;
    int step = 1;
    int divisor = 2;
    int original_num = num;
    
    printf("\n %d 转换为二进制（数值构建）: ", original_num);
    
    if (num == 0) {
        printf("0");
        return;
    }
    
    while (num != 0)
    {
        remainder = num % divisor;
        num /= divisor;
        
        // 以余数乘以位数相加（注意：这里构建的是十进制数）
        binary += remainder * multiplier;
        multiplier *= 10;
        
        step++;
    }
    
    printf("%ld", binary);
    printf(" (注意：这是以十进制形式存储的二进制)");
}

/**
 * 二进制转十进制
 * 将以十进制形式存储的二进制数转换为真正的十进制数
 */
void binaryToDecimal(long num)
{
    long original_num = num;
    int decimal = 0;
    int position = 0;
    int remainder;
    int divisor = 10;
    
    printf("\n %ld 转换为十进制: ", original_num);
    
    if (num == 0) {
        printf("0");
        return;
    }
    
    while (num != 0)
    {
        remainder = num % divisor;  // 取最低位
        num /= divisor;             // 去掉最低位
        
        // 从右往左用二进制的每个位去乘以2的相应次方
        // 次方是数字的位置，从0开始，从右往左递增
        decimal += remainder * (int)pow(2, position);
        position++;
    }
    
    printf("%d", decimal);
}