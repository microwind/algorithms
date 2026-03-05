import java.util.*;

/*
*
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
public class PowerOfTwo {
    /*
*
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
    public static boolean isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

    /*
*
     * 使用位计数判断（备选方案）
     *
     * @param n 待检查的数
     * @return true 如果是2的幂，否则 false
*/
    public static boolean isPowerOfTwoBuiltin(int n) {
        if (n <= 0) return false;
        return Integer.bitCount(n) == 1;
    }

    /*
*
     * 计算2的幂中的位置（幂的指数）
     *
     * @param n 2的幂
     * @return 指数，如果不是2的幂返回 -1
*/
    public static int powerOfTwoExponent(int n) {
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

    /*
*
     * 找到大于等于n的最小2的幂
     *
     * @param n 输入数
     * @return 大于等于n的最小2的幂
*/
    public static int nextPowerOfTwo(int n) {
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

    /*
*
     * 获取一个2的幂是2的几次方
     *
     * @param n 2的幂
     * @return 幂的指数
*/
    public static int getExponent(int n) {
        if (!isPowerOfTwo(n)) return -1;
        return Integer.numberOfTrailingZeros(n);
    }

    /*
*
     * 打印二进制表示
*/
    private static void printBinary(int n) {
        System.out.print("0b");
        System.out.print(Integer.toBinaryString(n));
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 2的幂 ===\n");

        // 测试用例1：判断是否为2的幂
        System.out.println("1. 判断是否为2的幂:");
        int[] testNums = {1, 2, 3, 4, 5, 8, 16, 17, 32, 100};

        for (int num : testNums) {
            System.out.printf("  %3d: %s\n", num,
                    isPowerOfTwo(num) ? "是2的幂" : "不是2的幂");
        }
        System.out.println();

        // 测试用例2：获取幂的指数
        System.out.println("2. 获取2的幂中的指数:");
        int[] powerNums = {1, 2, 4, 8, 16, 32, 64, 128, 256};

        for (int num : powerNums) {
            int exp = getExponent(num);
            System.out.printf("  2^%d = %d\n", exp, num);
        }
        System.out.println();

        // 测试用例3：找下一个2的幂
        System.out.println("3. 找大于等于n的最小2的幂:");
        int[] testNums2 = {1, 3, 5, 7, 8, 9, 15, 16, 17, 100};

        for (int num : testNums2) {
            int next = nextPowerOfTwo(num);
            System.out.printf("  n=%3d -> %d\n", num, next);
        }
        System.out.println();

        // 测试用例4：边界情况
        System.out.println("4. 边界情况:");
        System.out.println("  0 是2的幂: " + (isPowerOfTwo(0) ? "是" : "否"));
        System.out.println("  1 是2的幂: " + (isPowerOfTwo(1) ? "是" : "否"));
        System.out.println("  -8 是2的幂: " + (isPowerOfTwo(-8) ? "是" : "否"));
        System.out.println();

        // 测试用例5：二进制表示
        System.out.println("5. 2的幂的二进制表示:");
        for (int i = 0; i <= 4; i++) {
            int num = 1 << i;
            System.out.printf("  2^%d = %2d = ", i, num);
            printBinary(num);
            System.out.println();
        }
    }
}
