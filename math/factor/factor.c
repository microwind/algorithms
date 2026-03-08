/*
 * 数学算法 - 质因数分解 (Prime Factorization)
 * 将一个正整数分解为质因数的乘积
 * 时间复杂度: O(√n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * 质因数分解函数
 * 
 * 算法原理：
 * 1. 从最小的质数2开始尝试除法
 * 2. 如果能被整除，记录该质因数，继续用该质因数除
 * 3. 如果不能整除，尝试下一个可能的因数
 * 4. 直到因数的平方超过剩余的数
 * 5. 如果最后剩余的数大于1，它本身就是一个质因数
 * 
 * 参数：
 *     num: 要分解的正整数
 *     len: 结果数组的最大长度（通常设为num/2）
 * 返回：
 *     包含所有质因数的动态数组，需要调用者释放内存
 * 
 * 时间复杂度: O(√n) - 最坏情况下需要检查到√n
 * 空间复杂度: O(log n) - 质因数的个数
 * 
 * 注意事项：
 * - 返回的数组需要调用者手动free()
 * - 数组末尾可能包含0值，需要检查
 * - 输入必须为正整数
 */
int *factorize(int num, int len);

/**
 * 打印质因数分解结果
 * 
 * 参数：
 *     factors: 质因数数组
 *     len: 数组长度
 *     original_num: 原始数字
 */
void print_factors(int *factors, int len, int original_num);

/**
 * 验证分解结果的正确性
 * 
 * 参数：
 *     factors: 质因数数组
 *     len: 数组长度
 *     original_num: 原始数字
 * 返回：
 *     1表示正确，0表示错误
 */
int verify_factorization(int *factors, int len, int original_num);

/**
 * 质因数分解演示程序
 * 
 * 功能：
 * - 演示质因数分解算法
 * - 打印分解结果
 * - 验证分解正确性
 * 
 * 测试用例：20 = 2 * 2 * 5
 */
int main()
{
    printf("质因数分解演示\n");
    printf("===============\n\n");
    
    int num = 20;
    
    // 分配足够大的数组（最坏情况：2的幂次，如2^k）
    int len = num / 2;  // 保守估计
    
    printf("分解数字: %d\n", num);
    printf("分解过程:\n");
    
    // 执行质因数分解
    int *result = factorize(num, len);
    
    if (result == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }
    
    // 打印分解结果
    print_factors(result, len, num);
    
    // 验证分解结果
    if (verify_factorization(result, len, num)) {
        printf("\n✓ 分解结果验证正确\n");
    } else {
        printf("\n✗ 分解结果验证错误\n");
    }
    
    // 释放内存
    free(result);
    
    printf("\n算法说明:\n");
    printf("• 时间复杂度: O(√n)\n");
    printf("• 适用于中小规模数字\n");
    printf("• 大数字需要更高效的算法（如Pollard's Rho）\n");
    
    return 0;
}

/**
 * 质因数分解实现
 * 使用试除法进行分解
 */
int *factorize(int num, int len)
{
    // 分配结果数组
    int *result = (int *)malloc(len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    // 初始化数组
    memset(result, 0, len * sizeof(int));
    
    int divisor = 2;           // 从最小的质数开始
    int result_idx = 0;        // 结果数组索引
    int remaining = num;       // 剩余待分解的数
    
    // 试除法：当除数的平方不超过剩余数时继续
    while (divisor * divisor <= remaining)
    {
        // 如果当前除数能整除剩余数
        while (remaining % divisor == 0)
        {
            // 记录该质因数
            if (result_idx < len) {
                result[result_idx] = divisor;
                result_idx++;
            }
            
            // 更新剩余数
            remaining /= divisor;
        }
        
        // 尝试下一个可能的因数
        divisor++;
    }
    
    // 如果最后剩余的数大于1，它本身就是一个质因数
    if (remaining > 1 && result_idx < len)
    {
        result[result_idx] = remaining;
    }
    
    return result;
}

/**
 * 打印质因数分解结果
 * 格式：2 * 2 * 5 = 20
 */
void print_factors(int *factors, int len, int original_num)
{
    printf("分解结果: ");
    
    int first = 1;  // 标记是否为第一个因数
    
    for (int i = 0; i < len; i++)
    {
        // 跳过0值（数组未使用的部分）
        if (factors[i] <= 0) {
            break;
        }
        
        // 打印乘号（除了第一个因数）
        if (!first) {
            printf(" *");
        } else {
            first = 0;
        }
        
        printf(" %d", factors[i]);
    }
    
    printf(" = %d\n", original_num);
}

/**
 * 验证分解结果的正确性
 * 将所有质因数相乘，看是否等于原数
 */
int verify_factorization(int *factors, int len, int original_num)
{
    int product = 1;
    
    for (int i = 0; i < len; i++)
    {
        if (factors[i] <= 0) {
            break;
        }
        
        product *= factors[i];
        
        // 防止溢出
        if (product > original_num) {
            return 0;  // 乘积已经超过原数，肯定错误
        }
    }
    
    return product == original_num;
}