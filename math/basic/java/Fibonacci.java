/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 斐波那契数列 (Fibonacci Sequence)
 * 计算斐波那契数列的第n项
 * 时间复杂度: O(n) - 迭代, O(log n) - 矩阵快速幂
 */

import java.math.BigInteger;

public class Fibonacci {
    
    public static long fibonacciIterative(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        if (n <= 1) return n;
        long a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }
    
    public static BigInteger fibonacciBig(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        if (n <= 1) return BigInteger.valueOf(n);
        BigInteger a = BigInteger.ZERO, b = BigInteger.ONE;
        for (int i = 2; i <= n; i++) {
            BigInteger temp = a.add(b);
            a = b;
            b = temp;
        }
        return b;
    }
    
    public static void main(String[] args) {
        System.out.println("斐波那契数列前20项:");
        for (int i = 0; i < 20; i++) {
            System.out.printf("F(%2d) = %8d  ", i, fibonacciIterative(i));
            if ((i + 1) % 3 == 0) System.out.println();
        }
    }
}
