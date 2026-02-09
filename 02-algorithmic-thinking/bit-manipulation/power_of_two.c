/**
 * 2的幂 - 位运算和数字性质
 *
 * 问题：
 * 1. 检查一个数是否是2的幂
 * 2. 计算2的幂相关的位操作
 *
 * 核心思想：
 * - 2的幂在二进制表示中只有一个1（1, 2, 4, 8, 16, ...）
 * - n & (n-1) == 0 可以判断是否为2的幂
 * - 利用位运算的性质进行快速计算
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * 判断一个数是否是2的幂
 *
 * 原理：
 * - 2的幂的二进制表示只有一个1，其余为0
 * - 例如：8 = 1000 (二进制)
 * - n-1 = 0111 (二进制)
 * - n & (n-1) = 0
 *
 * @param n 待检查的数
 * @return true 如果是2的幂，否则 false
 */
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/**
 * 使用位计数判断（备选方案）
 *
 * 统计二进制表示中1的个数，如果只有一个1则是2的幂
 *
 * @param n 待检查的数
 * @return true 如果是2的幂，否则 false
 */
bool isPowerOfTwoBuiltin(int n) {
    if (n <= 0) return false;

    int count = 0;
    while (n > 0) {
        count += n & 1;
        n >>= 1;
    }
    return count == 1;
}

/**
 * 计算2的幂中的位置（幂的指数）
 *
 * 例如：
 * - 8 (1000) 的位置是 3 (2^3 = 8)
 * - 16 (10000) 的位置是 4 (2^4 = 16)
 *
 * @param n 2的幂
 * @return 指数，如果不是2的幂返回 -1
 */
int powerOfTwoExponent(int n) {
    if (!isPowerOfTwo(n)) {
        return -1;
    }

    int exp = 0;
    while ((n & 1) == 0) {
        n >>= 1;
        exp++;
    }
    return exp;
}

/**
 * 找到大于等于n的最小2的幂
 *
 * 例如：
 * - n=5 -> 8 (2^3)
 * - n=8 -> 8 (2^3)
 * - n=10 -> 16 (2^4)
 *
 * @param n 输入数
 * @return 大于等于n的最小2的幂
 */
int nextPowerOfTwo(int n) {
    if (n <= 1) return 1;

    // 如果已经是2的幂，直接返回
    if (isPowerOfTwo(n)) {
        return n;
    }

    // 找到下一个2的幂
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

/**
 * 获取一个2的幂是2的几次方
 *
 * @param n 2的幂
 * @return 幂的指数
 */
int getExponent(int n) {
    if (!isPowerOfTwo(n)) return -1;

    int exp = 0;
    while ((n & 1) == 0) {
        exp++;
        n >>= 1;
    }
    return exp;
}

/**
 * 打印二进制表示
 */
void printBinary(int n) {
    printf("0b");
    for (int i = 15; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

/**
 * 测试函数
 */
int main() {
    printf("=== 2的幂 ===\n\n");

    // 测试用例1：判断是否为2的幂
    printf("1. 判断是否为2的幂:\n");
    int testNums[] = {1, 2, 3, 4, 5, 8, 16, 17, 32, 100};
    int numCount = sizeof(testNums) / sizeof(testNums[0]);

    for (int i = 0; i < numCount; i++) {
        int num = testNums[i];
        printf("  %3d: %s\n", num, isPowerOfTwo(num) ? "是2的幂" : "不是2的幂");
    }
    printf("\n");

    // 测试用例2：获取幂的指数
    printf("2. 获取2的幂中的指数:\n");
    int powerNums[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    int powerCount = sizeof(powerNums) / sizeof(powerNums[0]);

    for (int i = 0; i < powerCount; i++) {
        int num = powerNums[i];
        int exp = getExponent(num);
        printf("  2^%d = %d\n", exp, num);
    }
    printf("\n");

    // 测试用例3：找下一个2的幂
    printf("3. 找大于等于n的最小2的幂:\n");
    int testNums2[] = {1, 3, 5, 7, 8, 9, 15, 16, 17, 100};
    int numCount2 = sizeof(testNums2) / sizeof(testNums2[0]);

    for (int i = 0; i < numCount2; i++) {
        int num = testNums2[i];
        int next = nextPowerOfTwo(num);
        printf("  n=%3d -> %d\n", num, next);
    }
    printf("\n");

    // 测试用例4：边界情况
    printf("4. 边界情况:\n");
    printf("  0 是2的幂: %s\n", isPowerOfTwo(0) ? "是" : "否");
    printf("  1 是2的幂: %s\n", isPowerOfTwo(1) ? "是" : "否");
    printf("  -8 是2的幂: %s\n", isPowerOfTwo(-8) ? "是" : "否");
    printf("\n");

    // 测试用例5：二进制表示
    printf("5. 2的幂的二进制表示:\n");
    for (int i = 0; i <= 4; i++) {
        int num = 1 << i;
        printf("  2^%d = %2d = ", i, num);
        printBinary(num);
        printf("\n");
    }

    return 0;
}
