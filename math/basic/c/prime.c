/*
 * 数学基础 - 素数判定 (Prime Number Check)
 * 判断一个正整数是否为素数，并生成素数表
 * 支持试除法和埃拉托斯特尼筛法
 * 时间复杂度: O(√n) - 试除法, O(n log log n) - 筛法
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**
 * 试除法判断素数
 * 
 * 算法原理：
 * - 若 n 为合数，则必有一个小于等于 √n 的因子
 * - 只需检查 2 到 √n 的整数
 * 
 * 优化：
 * - 先检查2，然后只检查奇数
 * - 跳过偶数可减少一半计算
 * 
 * 参数:
 *     n: 正整数
 * 返回:
 *     true - 是素数, false - 不是素数
 * 
 * 时间复杂度: O(√n)
 * 空间复杂度: O(1)
 */
bool is_prime_basic(int n);

/**
 * 优化的试除法判断素数
 * 
 * 进一步优化：
 * - 检查 2 和 3
 * - 然后检查形如 6k±1 的数（所有素数>3都符合此形式）
 * 
 * 参数:
 *     n: 正整数
 * 返回:
 *     true - 是素数, false - 不是素数
 */
bool is_prime_optimized(int n);

/**
 * 埃拉托斯特尼筛法生成素数表
 * 
 * 算法原理：
 * - 从2开始，将每个素数的倍数标记为合数
 * - 剩余未标记的数即为素数
 * 
 * 参数:
 *     limit: 上限范围
 * 返回:
 *     布尔数组，is_prime[i]表示i是否为素数
 */
bool *sieve_of_eratosthenes(int limit);

/**
 * 计算小于n的素数个数（素数计数函数π(n)）
 */
int count_primes(int n);

/**
 * 主函数 - 素数演示程序
 */
int main()
{
    int n;
    
    printf("========================================\n");
    printf("    素数判定与生成 (Prime Numbers)\n");
    printf("========================================\n\n");
    
    // 显示素数表
    printf("100以内的素数:\n");
    printf("----------------------------------------\n");
    
    bool *prime_table = sieve_of_eratosthenes(100);
    int count = 0;
    for (int i = 2; i <= 100; i++) {
        if (prime_table[i]) {
            printf("%3d ", i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }
    printf("\n----------------------------------------\n");
    printf("共 %d 个素数\n\n", count);
    
    free(prime_table);
    
    // 用户输入
    printf("请输入一个正整数进行素数判定: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("错误：请输入正整数\n");
        return 1;
    }
    
    printf("\n----------------------------------------\n");
    printf("判定结果:\n");
    printf("----------------------------------------\n");
    
    // 基本算法判定
    bool result_basic = is_prime_basic(n);
    printf("基本算法: %d %s素数\n", n, result_basic ? "是" : "不是");
    
    // 优化算法判定
    bool result_opt = is_prime_optimized(n);
    printf("优化算法: %d %s素数\n", n, result_opt ? "是" : "不是");
    
    // 如果是合数，显示因子
    if (!result_basic && n > 1) {
        printf("\n因子分解:\n");
        int temp = n;
        printf("%d = ", n);
        for (int i = 2; i <= temp; i++) {
            while (temp % i == 0) {
                printf("%d", i);
                temp /= i;
                if (temp > 1) printf(" × ");
            }
        }
        printf("\n");
    }
    
    // 素数计数
    printf("\n----------------------------------------\n");
    printf("素数计数（π函数）:\n");
    printf("----------------------------------------\n");
    printf("π(%d) = %d\n", n, count_primes(n));
    printf("（小于等于%d的素数个数）\n", n);
    
    // 数学性质
    printf("\n========================================\n");
    printf("素数的数学性质:\n");
    printf("========================================\n");
    printf("• 定义: 大于1的自然数，只有1和自身两个因子\n");
    printf("• 唯一分解定理: 每个整数可唯一表示为素数乘积\n");
    printf("• 素数无限性: 素数有无穷多个（欧几里得证明）\n");
    printf("• 素数定理: π(n) ~ n/ln(n)\n");
    printf("• 孪生素数: 相差2的素数对（如3,5和11,13）\n");
    printf("• 梅森素数: 形如2^p-1的素数\n");
    
    // 应用场景
    printf("\n========================================\n");
    printf("应用场景:\n");
    printf("========================================\n");
    printf("• 密码学: RSA加密基于大素数分解\n");
    printf("• 哈希表: 素数大小的表减少冲突\n");
    printf("• 随机数生成: 梅森旋转算法\n");
    printf("• 校验和: ISBN、信用卡号码验证\n");
    printf("• 数论研究: 黎曼猜想、哥德巴赫猜想\n");
    
    return 0;
}

/**
 * 基本试除法
 */
bool is_prime_basic(int n)
{
    // 小于2不是素数
    if (n < 2) return false;
    
    // 2是素数
    if (n == 2) return true;
    
    // 偶数不是素数
    if (n % 2 == 0) return false;
    
    // 检查奇数因子
    for (int i = 3; i <= (int)sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    
    return true;
}

/**
 * 优化试除法（6k±1形式）
 */
bool is_prime_optimized(int n)
{
    // 处理小数值
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // 检查形如6k±1的数
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    
    return true;
}

/**
 * 埃拉托斯特尼筛法
 */
bool *sieve_of_eratosthenes(int limit)
{
    // 分配内存
    bool *is_prime = (bool *)malloc((limit + 1) * sizeof(bool));
    
    // 初始化：假设都是素数
    for (int i = 0; i <= limit; i++) {
        is_prime[i] = true;
    }
    
    // 0和1不是素数
    is_prime[0] = false;
    is_prime[1] = false;
    
    // 筛法核心
    for (int p = 2; p * p <= limit; p++) {
        // 如果p是素数，标记其倍数为合数
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= limit; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }
    
    return is_prime;
}

/**
 * 计算小于等于n的素数个数
 */
int count_primes(int n)
{
    if (n < 2) return 0;
    
    bool *prime_table = sieve_of_eratosthenes(n);
    int count = 0;
    
    for (int i = 2; i <= n; i++) {
        if (prime_table[i]) count++;
    }
    
    free(prime_table);
    return count;
}
