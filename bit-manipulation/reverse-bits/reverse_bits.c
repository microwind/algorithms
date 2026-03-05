/*
*
 * 反转二进制位
 *
 * 问题：反转一个32位整数的二进制表示
 *
 * 核心思想：
 * - 逐位提取和重建
 * - 位操作实现高效反转
 *
 * 时间复杂度: O(32)
 * 空间复杂度: O(1)
*/

#include <stdio.h>
#include <stdint.h>

/*
*
 * 逐位反转：从右到左提取，从左到右重建
 *
 * 原理：
 * - 从n的最右边提取一位
 * - 将其放在result的最左边
 * - 继续处理n的其他位
 *
 * @param n 输入的32位整数
 * @return 反转后的32位整数
*/
uint32_t reverseBitsIterative(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        // 提取n的最右边一位
        uint32_t bit = n & 1;
        // 右移n，处理下一位
        n >>= 1;
        // result左移，为新位腾出空间
        result <<= 1;
        // 将bit加到result
        result |= bit;
    }
    return result;
}

/*
*
 * 手动位操作：逐位反转
 *
 * @param n 输入的32位整数
 * @return 反转后的32位整数
*/
uint32_t reverseBitsManual(uint32_t n) {
    uint32_t result = 0;
    // 处理32位
    for (int i = 0; i < 32; i++) {
        // 从n中提取第i位
        if ((n >> i) & 1) {
            // 在result中设置第(31-i)位
            result |= (1U << (31 - i));
        }
    }
    return result;
}

/*
*
 * 按字节反转（4个字节的整数）
 *
 * @param n 输入的32位整数
 * @return 反转后的32位整数
*/
uint32_t reverseBitsByteByByte(uint32_t n) {
    uint32_t result = 0;

    // 处理4个字节
    for (int i = 0; i < 4; i++) {
        // 提取第i个字节
        uint8_t byte = (n >> (i * 8)) & 0xFF;

        // 反转字节内的位
        uint8_t reversed_byte = 0;
        for (int j = 0; j < 8; j++) {
            if ((byte >> j) & 1) {
                reversed_byte |= (1 << (7 - j));
            }
        }

        // 将反转后的字节放在结果的正确位置
        result |= ((uint32_t)reversed_byte << ((3 - i) * 8));
    }

    return result;
}

/*
*
 * 使用查表法反转（针对频繁调用优化）
 *
 * @param n 输入的32位整数
 * @return 反转后的32位整数
*/
uint32_t reverseBitsLookup(uint32_t n) {
    // 预计算0-255的位反转
    static uint8_t lookup[256];
    static int initialized = 0;

    if (!initialized) {
        for (int i = 0; i < 256; i++) {
            uint8_t byte = i;
            uint8_t reversed = 0;
            for (int j = 0; j < 8; j++) {
                if ((byte >> j) & 1) {
                    reversed |= (1 << (7 - j));
                }
            }
            lookup[i] = reversed;
        }
        initialized = 1;
    }

    uint32_t result = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t byte = (n >> (i * 8)) & 0xFF;
        uint8_t reversed_byte = lookup[byte];
        result |= ((uint32_t)reversed_byte << ((3 - i) * 8));
    }

    return result;
}

/*
*
 * 打印32位二进制表示
*/
void printBinary32(uint32_t n) {
    printf("0b");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

/*
*
 * 测试函数
*/
int main() {
    printf("=== 反转二进制位 ===\n\n");

    // 测试用例1：基本用例
    printf("1. 基本用例:\n");
    uint32_t testCases[] = {
        1,           // 最右位为1
        2,           // 倒数第二位为1
        3,           // 最右两位为1
        43261596,    // 复杂用例
    };
    int caseCount = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < caseCount; i++) {
        uint32_t num = testCases[i];
        uint32_t result = reverseBitsIterative(num);

        printf("  输入:   ");
        printBinary32(num);
        printf(" (%u)\n", num);
        printf("  输出:   ");
        printBinary32(result);
        printf(" (%u)\n\n", result);
    }

    // 测试用例2：比较不同算法
    printf("2. 不同算法的结果比较:\n");
    uint32_t testNums[] = {0, 1, 2, 7, 15, 255, 43261596, 2147483647};
    int numCount = sizeof(testNums) / sizeof(testNums[0]);

    for (int i = 0; i < numCount; i++) {
        uint32_t num = testNums[i];
        uint32_t iter = reverseBitsIterative(num);
        uint32_t manual = reverseBitsManual(num);
        uint32_t byte_by_byte = reverseBitsByteByByte(num);
        uint32_t lookup = reverseBitsLookup(num);

        int all_match = (iter == manual) && (manual == byte_by_byte) &&
                        (byte_by_byte == lookup);
        printf("  n=%u: 所有算法一致 = %s\n", num,
               all_match ? "是" : "否");
    }
    printf("\n");

    // 测试用例3：特殊值
    printf("3. 特殊值:\n");
    struct {
        uint32_t value;
        const char *desc;
    } special[] = {
        {0x00000000, "全0"},
        {0xFFFFFFFF, "全1"},
        {0x80000000, "仅最左位为1"},
        {0x00000001, "仅最右位为1"},
        {0x12345678, "任意值"},
    };

    for (int i = 0; i < 5; i++) {
        uint32_t num = special[i].value;
        uint32_t result = reverseBitsIterative(num);
        printf("  %-15s: 0x%08X -> 0x%08X\n",
               special[i].desc, num, result);
    }
    printf("\n");

    // 测试用例4：验证对称性（反转两次应该回到原值）
    printf("4. 验证反转的对称性（反转两次应该恢复）:\n");
    uint32_t symmetryNums[] = {1, 7, 255, 43261596};
    int symCount = sizeof(symmetryNums) / sizeof(symmetryNums[0]);

    for (int i = 0; i < symCount; i++) {
        uint32_t num = symmetryNums[i];
        uint32_t once = reverseBitsIterative(num);
        uint32_t twice = reverseBitsIterative(once);
        int symmetric = (num == twice);
        printf("  %u: 反转两次后恢复 = %s\n", num,
               symmetric ? "是" : "否");
    }

    return 0;
}
