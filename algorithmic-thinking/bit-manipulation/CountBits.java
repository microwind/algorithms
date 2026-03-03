import java.util.*;

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
public class CountBits {
    /*
*
     * 使用Java内置函数计数1位
     *
     * @param n 输入数
     * @return 1的个数
*/
    public static int countOnesBuiltin(int n) {
        return Integer.bitCount(n);
    }

    /*
*
     * 逐位检查：循环检查每一位
     *
     * @param n 输入数
     * @return 1的个数
*/
    public static int countOnesLoop(int n) {
        int count = 0;
        while (n > 0) {
            count += n & 1;
            n >>>= 1;  // 无符号右移
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
    public static int countOnesKernighan(int n) {
        int count = 0;
        while (n > 0) {
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
    public static int countOnesTable(int n) {
        int[] lookup = new int[256];
        for (int i = 0; i < 256; i++) {
            lookup[i] = Integer.bitCount(i);
        }

        int count = 0;
        while (n > 0) {
            count += lookup[n & 0xFF];
            n >>>= 8;
        }
        return count;
    }

    /*
*
     * 并行计数法（位操作优化）
     *
     * @param n 输入数
     * @return 1的个数
*/
    public static int countOnesParallel(int n) {
        n = ((n & 0xaaaaaaaa) >>> 1) + (n & 0x55555555);
        n = ((n & 0xcccccccc) >>> 2) + (n & 0x33333333);
        n = ((n & 0xf0f0f0f0) >>> 4) + (n & 0x0f0f0f0f);
        n = ((n & 0xff00ff00) >>> 8) + (n & 0x00ff00ff);
        n = ((n & 0xffff0000) >>> 16) + (n & 0x0000ffff);
        return n;
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 计数1位 (Hamming权重) ===\n");

        // 测试用例1：基本用例
        System.out.println("1. 基本用例:");
        int[] testNums = {0, 1, 3, 5, 7, 15, 31, 63, 127, 255};

        for (int num : testNums) {
            int count = countOnesBuiltin(num);
            String binary = String.format("%8s",
                    Integer.toBinaryString(num)).replace(' ', '0');
            System.out.printf("  %3d (%s): %d个1\n", num, binary, count);
        }
        System.out.println();

        // 测试用例2：比较不同算法
        System.out.println("2. 不同算法的结果比较:");
        int[] testNums2 = {1, 7, 15, 127, 255, 1023};

        for (int num : testNums2) {
            int builtin = countOnesBuiltin(num);
            int loop = countOnesLoop(num);
            int kernighan = countOnesKernighan(num);
            int table = countOnesTable(num);

            System.out.printf("  n=%4d: builtin=%d, loop=%d, " +
                    "kernighan=%d, table=%d\n",
                    num, builtin, loop, kernighan, table);
        }
        System.out.println();

        // 测试用例3：大数值
        System.out.println("3. 大数值:");
        int[] largeNums = {
                0xFFFF,      // 2^16 - 1
                0xFFFFF,     // 2^20 - 1
                0x3FFFFFFF   // 2^30 - 1
        };

        for (int num : largeNums) {
            int count = countOnesKernighan(num);
            System.out.printf("  0x%08X: %d个1\n", num, count);
        }
        System.out.println();

        // 测试用例4：稀疏1的情况（Kernighan优势明显）
        System.out.println("4. 稀疏1的情况（Kernighan优势明显）:");
        int[] sparseNums = {1, 2, 4, 8, 16, 32, 64, 128, 256};

        for (int num : sparseNums) {
            int count = countOnesKernighan(num);
            System.out.printf("  %3d (2^?): %d个1\n", num, count);
        }
        System.out.println();

        // 测试用例5：特殊值
        System.out.println("5. 特殊值:");
        System.out.println("  0x00000000: " + countOnesLoop(0x00000000) + "个1");
        System.out.println("  0xFFFFFFFF: " + countOnesLoop(0xFFFFFFFF) + "个1");
        System.out.println("  0x80000000: " + countOnesLoop(0x80000000) + "个1");
        System.out.println("  0x00000001: " + countOnesLoop(0x00000001) + "个1");
    }
}
