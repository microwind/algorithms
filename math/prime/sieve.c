/*
 * 数学算法 - 埃拉托斯特尼筛法 (Sieve of Eratosthenes)
 * 高效地找出指定范围内的所有素数
 * 时间复杂度: O(n log log n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1000000

/**
 * 基础筛法实现
 * 找出小于等于n的所有素数
 * 
 * 参数:
 *     n: 上界
 *     is_prime: 存储素数标记的数组
 * 返回:
 *     素数个数
 */
int sieve_basic(int n, char is_prime[]) {
    // 初始化：假设所有数都是素数
    memset(is_prime, 1, (n + 1) * sizeof(char));
    is_prime[0] = is_prime[1] = 0;  // 0和1不是素数
    
    int count = 0;
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            count++;
            // 标记i的所有倍数为非素数
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    
    return count;
}

/**
 * 优化筛法实现
 * 只标记奇数，减少一半的内存和计算
 */
int sieve_optimized(int n, char is_prime[]) {
    if (n < 2) return 0;
    
    // 初始化
    memset(is_prime, 1, (n + 1) * sizeof(char));
    is_prime[0] = is_prime[1] = 0;
    
    // 标记偶数（除了2）
    for (int i = 4; i <= n; i += 2) {
        is_prime[i] = 0;
    }
    
    int count = 1;  // 2是素数
    
    // 只检查奇数
    for (int i = 3; i <= n; i += 2) {
        if (is_prime[i]) {
            count++;
            // 从i*i开始，步长为2*i（只标记奇数倍数）
            for (int j = i * i; j <= n; j += 2 * i) {
                is_prime[j] = 0;
            }
        }
    }
    
    return count;
}

/**
 * 分段筛法
 * 用于处理大范围的素数查找
 */
int sieve_segmented(int l, int r, char is_prime[]) {
    if (r < 2) return 0;
    
    // 先用基础筛法找出sqrt(r)以内的素数
    int limit = (int)sqrt(r) + 1;
    char* base_primes = (char*)malloc((limit + 1) * sizeof(char));
    
    int base_count = sieve_optimized(limit, base_primes);
    
    // 初始化分段数组
    memset(is_prime, 1, (r - l + 1) * sizeof(char));
    
    // 用基础素数标记分段中的合数
    for (int p = 2; p <= limit; p++) {
        if (base_primes[p]) {
            // 找到第一个>=l的p的倍数
            int start = (l / p) * p;
            if (start < l) start += p;
            if (start == p) start += p;  // 避免标记p本身
            
            for (int j = start; j <= r; j += p) {
                is_prime[j - l] = 0;
            }
        }
    }
    
    // 处理边界情况
    if (l == 1) is_prime[0] = 0;
    if (l == 0) {
        is_prime[0] = 0;
        if (r >= 1) is_prime[1] = 0;
    }
    
    // 统计素数个数
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (is_prime[i - l]) count++;
    }
    
    free(base_primes);
    return count;
}

/**
 * 获取素数列表
 */
void get_primes(int n, const char is_prime[], int primes[], int* count) {
    *count = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[(*count)++] = i;
        }
    }
}

/**
 * 打印素数
 */
void print_primes(int l, int r, const char is_prime[]) {
    printf("  素数范围 [%d, %d]:\n    ", l, r);
    int printed = 0;
    for (int i = l; i <= r; i++) {
        if (i >= 2 && is_prime[i - l]) {
            printf("%d ", i);
            if (++printed % 10 == 0) printf("\n    ");
        }
    }
    if (printed % 10 != 0) printf("\n");
}

/**
 * 验证筛法正确性
 */
void verify_sieve() {
    printf("\n验证筛法正确性:\n");
    
    int n = 100;
    char is_prime[MAX_SIZE + 1];
    int count = sieve_optimized(n, is_prime);
    
    // 手动验证一些已知素数
    int known_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    int known_count = sizeof(known_primes) / sizeof(known_primes[0]);
    
    printf("  已知素数验证: ");
    int all_correct = 1;
    for (int i = 0; i < known_count; i++) {
        if (!is_prime[known_primes[i]]) {
            all_correct = 0;
            break;
        }
    }
    printf("%s\n", all_correct ? "✓" : "✗");
    
    // 验证一些已知合数
    int known_composites[] = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27, 28, 30};
    int composite_count = sizeof(known_composites) / sizeof(known_composites[0]);
    
    printf("  已知合数验证: ");
    for (int i = 0; i < composite_count; i++) {
        if (is_prime[known_composites[i]]) {
            all_correct = 0;
            break;
        }
    }
    printf("%s\n", all_correct ? "✓" : "✗");
}

/**
 * 性能比较
 */
void performance_comparison() {
    printf("\n性能比较 (n=1000000):\n");
    
    char is_prime1[MAX_SIZE + 1];
    char is_prime2[MAX_SIZE + 1];
    
    // 基础筛法
    printf("  基础筛法: ");
    int count1 = sieve_basic(1000000, is_prime1);
    printf("%d个素数\n", count1);
    
    // 优化筛法
    printf("  优化筛法: ");
    int count2 = sieve_optimized(1000000, is_prime2);
    printf("%d个素数\n", count2);
    
    printf("  结果一致: %s\n", (count1 == count2) ? "✓" : "✗");
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("埃拉托斯特尼筛法 (Sieve of Eratosthenes)\n");
    printf("==================================================\n");
    
    char is_prime[MAX_SIZE + 1];
    
    // 基础测试
    printf("\n基础筛法测试 (n=50):");
    int count = sieve_optimized(50, is_prime);
    print_primes(2, 50, is_prime);
    printf("  总计: %d个素数\n", count);
    
    // 分段筛法测试
    printf("\n分段筛法测试 ([100, 150]):");
    char segmented_primes[51];
    int seg_count = sieve_segmented(100, 150, segmented_primes);
    print_primes(100, 150, segmented_primes);
    printf("  总计: %d个素数\n", seg_count);
    
    // 验证正确性
    verify_sieve();
    
    // 性能比较
    performance_comparison();
    
    printf("\n应用场景:\n");
    printf("  • 密码学 (大素数生成)\n");
    printf("  • 数论研究\n");
    printf("  • 哈希表设计\n");
    printf("  • 随机数生成\n");
    printf("  • 算法竞赛预处理\n");
    
    printf("\n算法特点:\n");
    printf("  • 时间复杂度: O(n log log n)\n");
    printf("  • 空间复杂度: O(n)\n");
    printf("  • 可以优化到O(n)时间复杂度\n");
    printf("  • 分段筛法可处理大范围\n");
    printf("  • 是素数相关算法的基础\n");
    
    return 0;
}
