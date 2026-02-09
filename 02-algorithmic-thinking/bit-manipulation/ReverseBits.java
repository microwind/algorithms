import java.util.*;

/**
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
public class ReverseBits {
    /**
     * 逐位反转：从右到左提取，从左到右重建
     *
     * @param n 输入的32位整数
     * @return 反转后的32位整数
     */
    public static long reverseBitsIterative(long n) {
        long result = 0;
        for (int i = 0; i < 32; i++) {
            // 提取n的最右边一位
            long bit = n & 1;
            // 右移n，处理下一位
            n >>>= 1;
            // result左移，为新位腾出空间
            result <<= 1;
            // 将bit加到result
            result |= bit;
        }
        return result;
    }

    /**
     * 手动位操作：逐位反转
     *
     * @param n 输入的32位整数
     * @return 反转后的32位整数
     */
    public static long reverseBitsManual(long n) {
        long result = 0;
        // 处理32位
        for (int i = 0; i < 32; i++) {
            // 从n中提取第i位
            if (((n >>> i) & 1) == 1) {
                // 在result中设置第(31-i)位
                result |= (1L << (31 - i));
            }
        }
        return result;
    }

    /**
     * 按字节反转（4个字节的整数）
     *
     * @param n 输入的32位整数
     * @return 反转后的32位整数
     */
    public static long reverseBitsByteByByte(long n) {
        long result = 0;

        // 处理4个字节
        for (int i = 0; i < 4; i++) {
            // 提取第i个字节
            int byteVal = (int)((n >>> (i * 8)) & 0xFF);

            // 反转字节内的位
            int reversedByte = 0;
            for (int j = 0; j < 8; j++) {
                if (((byteVal >>> j) & 1) == 1) {
                    reversedByte |= (1 << (7 - j));
                }
            }

            // 将反转后的字节放在结果的正确位置
            result |= ((long)reversedByte << ((3 - i) * 8));
        }

        return result;
    }

    /**
     * 使用查表法反转（针对频繁调用优化）
     *
     * @param n 输入的32位整数
     * @return 反转后的32位整数
     */
    public static long reverseBitsLookup(long n) {
        int[] lookup = new int[256];

        // 预计算0-255的位反转
        for (int i = 0; i < 256; i++) {
            int byte_val = i;
            int reversed = 0;
            for (int j = 0; j < 8; j++) {
                if (((byte_val >>> j) & 1) == 1) {
                    reversed |= (1 << (7 - j));
                }
            }
            lookup[i] = reversed;
        }

        long result = 0;
        for (int i = 0; i < 4; i++) {
            int byteVal = (int)((n >>> (i * 8)) & 0xFF);
            int reversedByte = lookup[byteVal];
            result |= ((long)reversedByte << ((3 - i) * 8));
        }

        return result;
    }

    /**
     * 打印32位二进制表示
     */
    private static void printBinary32(long n) {
        System.out.print("0b");
        for (int i = 31; i >= 0; i--) {
            System.out.print(((n >>> i) & 1));
        }
    }

    /**
     * 测试函数
     */
    public static void main(String[] args) {
        System.out.println("=== 反转二进制位 ===\n");

        // 测试用例1：基本用例
        System.out.println("1. 基本用例:");
        long[] testCases = {
                1L,           // 最右位为1
                2L,           // 倒数第二位为1
                3L,           // 最右两位为1
                43261596L,    // 复杂用例
        };

        for (long num : testCases) {
            long result = reverseBitsIterative(num);

            System.out.print("  输入:   ");
            printBinary32(num);
            System.out.println(" (" + num + ")");
            System.out.print("  输出:   ");
            printBinary32(result);
            System.out.println(" (" + result + ")\n");
        }

        // 测试用例2：比较不同算法
        System.out.println("2. 不同算法的结果比较:");
        long[] testNums = {0, 1, 2, 7, 15, 255, 43261596, 2147483647};

        for (long num : testNums) {
            long iter = reverseBitsIterative(num);
            long manual = reverseBitsManual(num);
            long byte_by_byte = reverseBitsByteByByte(num);
            long lookup = reverseBitsLookup(num);

            boolean allMatch = (iter == manual) && (manual == byte_by_byte)
                    && (byte_by_byte == lookup);
            System.out.printf("  n=%u: 所有算法一致 = %s\n", num,
                    allMatch ? "是" : "否");
        }
        System.out.println();

        // 测试用例3：特殊值
        System.out.println("3. 特殊值:");
        Object[][] special = {
                {0x00000000L, "全0"},
                {0xFFFFFFFFL, "全1"},
                {0x80000000L, "仅最左位为1"},
                {0x00000001L, "仅最右位为1"},
                {0x12345678L, "任意值"},
        };

        for (Object[] obj : special) {
            long num = (long) obj[0];
            String desc = (String) obj[1];
            long result = reverseBitsIterative(num);
            System.out.printf("  %-15s: 0x%08X -> 0x%08X\n",
                    desc, num, result);
        }
        System.out.println();

        // 测试用例4：验证对称性（反转两次应该恢复）
        System.out.println("4. 验证反转的对称性（反转两次应该恢复）:");
        long[] symmetryNums = {1, 7, 255, 43261596};

        for (long num : symmetryNums) {
            long once = reverseBitsIterative(num);
            long twice = reverseBitsIterative(once);
            boolean symmetric = (num == twice);
            System.out.printf("  %u: 反转两次后恢复 = %s\n", num,
                    symmetric ? "是" : "否");
        }
    }
}
