/*
*
 * 计数1位 - Hamming权重
 *
 * 问题：计算整数二进制表示中1的个数
 *
 * 核心思想：
 * - 逐位检查：与1进行AND操作
 * - Brian Kernighan算法：n & (n-1) 移除最右边的1
 * - 预计算查表法（对于频繁调用优化）
 *
 * 时间复杂度: O(log n) 或 O(1) 取决于实现方式
 * 空间复杂度: O(1)
*/

#include <stdio.h>
#include <string.h>

/*
*
 * 逐位检查：循环检查每一位
 *
 * 原理：
 * - 将n与1进行AND操作，检查最右边的位
 * - 右移n，继续检查下一位
 * - 重复直到n为0
 *
 * @param n 输入数
 * @return 1的个数
*/
int countOnesLoop(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/*
*
 * Brian Kernighan算法：移除最右边的1
 *
 * 原理：
 * - n & (n-1) 移除n的最右边的1
 * - 重复这个操作直到n为0
 * - 操作次数就是1的个数
 * - 只需O(k)的时间，k是1的个数
 *
 * @param n 输入数
 * @return 1的个数
*/
int countOnesKernighan(unsigned int n) {
    int count = 0;
    while (n) {
        n &= n - 1;  // 移除最右边的1
        count++;
    }
    return count;
}

/*
*
 * 使用查表法（用于频繁调用的优化）
 *
 * @param n 输入数
 * @return 1的个数
*/
int countOnesTable(unsigned int n) {
    // 预计算0-255中1的个数
    static int lookup[256];
    static int initialized = 0;

    if (!initialized) {
        for (int i = 0; i < 256; i++) {
            int count = 0;
            int temp = i;
            while (temp) {
                count += temp & 1;
                temp >>= 1;
            }
            lookup[i] = count;
        }
        initialized = 1;
    }

    int count = 0;
    while (n) {
        count += lookup[n & 0xFF];
        n >>= 8;
    }
    return count;
}

/*
*
 * 并行计数法（位操作优化）
 *
 * 对于32位整数
*/
int countOnesParallel(unsigned int n) {
    n = ((n & 0xaaaaaaaa) >> 1) + (n & 0x55555555);
    n = ((n & 0xcccccccc) >> 2) + (n & 0x33333333);
    n = ((n & 0xf0f0f0f0) >> 4) + (n & 0x0f0f0f0f);
    n = ((n & 0xff00ff00) >> 8) + (n & 0x00ff00ff);
    n = ((n & 0xffff0000) >> 16) + (n & 0x0000ffff);
    return n;
}

/*
*
 * 打印二进制表示
*/
void printBinary(unsigned int n) {
    printf("0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

/*
*
 * 测试函数
*/
int main() {
    printf("=== 计数1位 (Hamming权重) ===\n\n");

    // 测试用例1：基本用例
    printf("1. 基本用例:\n");
    unsigned int testNums[] = {0, 1, 3, 5, 7, 15, 31, 63, 127, 255};
    int numCount = sizeof(testNums) / sizeof(testNums[0]);

    for (int i = 0; i < numCount; i++) {
        unsigned int num = testNums[i];
        int count = countOnesLoop(num);
        printf("  %3u ", num);
        printBinary(num);
        printf(": %d个1\n", count);
    }
    printf("\n");

    // 测试用例2：比较不同算法
    printf("2. 不同算法的结果比较:\n");
    unsigned int testNums2[] = {1, 7, 15, 127, 255, 1023};
    int numCount2 = sizeof(testNums2) / sizeof(testNums2[0]);

    for (int i = 0; i < numCount2; i++) {
        unsigned int num = testNums2[i];
        int loop = countOnesLoop(num);
        int kern = countOnesKernighan(num);
        int table = countOnesTable(num);
        int parallel = countOnesParallel(num);

        printf("  n=%4u: loop=%d, kernighan=%d, table=%d, parallel=%d\n",
               num, loop, kern, table, parallel);
    }
    printf("\n");

    // 测试用例3：大数值
    printf("3. 大数值:\n");
    unsigned int largeNums[] = {
        0xFFFF,      // 2^16 - 1
        0xFFFFF,     // 2^20 - 1
        0x3FFFFFFF   // 2^30 - 1
    };
    int largeCount = sizeof(largeNums) / sizeof(largeNums[0]);

    for (int i = 0; i < largeCount; i++) {
        unsigned int num = largeNums[i];
        int count = countOnesKernighan(num);
        printf("  0x%08X: %d个1\n", num, count);
    }
    printf("\n");

    // 测试用例4：稀疏1的情况（Kernighan优势明显）
    printf("4. 稀疏1的情况（Kernighan优势明显）:\n");
    unsigned int sparseNums[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    int sparseCount = sizeof(sparseNums) / sizeof(sparseNums[0]);

    for (int i = 0; i < sparseCount; i++) {
        unsigned int num = sparseNums[i];
        int count = countOnesKernighan(num);
        printf("  %3u (2^?): %d个1\n", num, count);
    }
    printf("\n");

    // 测试用例5：特殊值
    printf("5. 特殊值:\n");
    printf("  0x00000000: %d个1\n", countOnesLoop(0x00000000));
    printf("  0xFFFFFFFF: %d个1\n", countOnesLoop(0xFFFFFFFF));
    printf("  0x80000000: %d个1\n", countOnesLoop(0x80000000));
    printf("  0x00000001: %d个1\n", countOnesLoop(0x00000001));

    return 0;
}
