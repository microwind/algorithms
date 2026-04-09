/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 最大公约数与最小公倍数 (GCD and LCM)
 * 使用欧几里得算法计算两个整数的最大公约数
 * 时间复杂度: O(log min(a,b))
 */

import java.math.BigInteger;

public class GCD {
    
    /**
     * 欧几里得算法 - 迭代版
     * 
     * 算法原理：gcd(a, b) = gcd(b, a mod b)
     */
    public static int gcd(int a, int b) {
        a = Math.abs(a);
        b = Math.abs(b);
        
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    /**
     * 欧几里得算法 - 递归版
     */
    public static int gcdRecursive(int a, int b) {
        a = Math.abs(a);
        b = Math.abs(b);
        
        if (b == 0) return a;
        return gcdRecursive(b, a % b);
    }
    
    /**
     * 大数GCD（使用BigInteger）
     */
    public static BigInteger gcdBig(BigInteger a, BigInteger b) {
        return a.gcd(b);
    }
    
    /**
     * 最小公倍数 (LCM)
     * 
     * 公式: lcm(a, b) = |a × b| / gcd(a, b)
     */
    public static long lcm(int a, int b) {
        if (a == 0 || b == 0) return 0;
        long absA = Math.abs((long) a);
        long absB = Math.abs((long) b);
        return (absA / gcd(a, b)) * absB;
    }
    
    /**
     * 扩展欧几里得算法
     * 
     * 返回数组 [gcd, x, y] 使得 ax + by = gcd(a, b)
     */
    public static int[] gcdExtended(int a, int b) {
        if (b == 0) {
            return new int[]{a, 1, 0};
        }
        
        int[] vals = gcdExtended(b, a % b);
        int gcd = vals[0];
        int x1 = vals[1];
        int y1 = vals[2];
        
        int x = y1;
        int y = x1 - (a / b) * y1;
        
        return new int[]{gcd, x, y};
    }
    
    /**
     * 多个数的GCD
     */
    public static int gcdMultiple(int... numbers) {
        if (numbers.length == 0) return 0;
        
        int result = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            result = gcd(result, numbers[i]);
        }
        return result;
    }
    
    /**
     * 多个数的LCM
     */
    public static long lcmMultiple(int... numbers) {
        if (numbers.length == 0) return 0;
        
        long result = Math.abs(numbers[0]);
        for (int i = 1; i < numbers.length; i++) {
            result = lcm((int) result, numbers[i]);
        }
        return result;
    }
    
    /**
     * 判断两个数是否互质
     */
    public static boolean areCoprime(int a, int b) {
        return gcd(a, b) == 1;
    }
    
    /**
     * 欧拉函数 φ(n)
     * 
     * 计算小于等于n且与n互质的正整数的个数
     */
    public static int eulerTotient(int n) {
        if (n <= 0) return 0;
        
        int result = n;
        int temp = n;
        
        // 遍历所有可能的质因数
        for (int p = 2; p * p <= temp; p++) {
            if (temp % p == 0) {
                // p是质因数
                while (temp % p == 0) {
                    temp /= p;
                }
                result -= result / p;
            }
        }
        
        // 如果temp > 1，则temp是质因数
        if (temp > 1) {
            result -= result / temp;
        }
        
        return result;
    }
    
    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("  最大公约数计算 (GCD) - 欧几里得算法");
        System.out.println("========================================\n");
        
        // GCD测试
        int[][] testCases = {{48, 18}, {56, 98}, {100, 35}, {101, 103}};
        System.out.println("GCD测试:");
        System.out.println("----------------------------------------");
        for (int[] pair : testCases) {
            int a = pair[0], b = pair[1];
            int gcd = gcd(a, b);
            long lcm = lcm(a, b);
            System.out.printf("gcd(%d, %d) = %d, lcm(%d, %d) = %d%n", 
                            a, b, gcd, a, b, lcm);
        }
        
        // 扩展欧几里得
        System.out.println("\n========================================");
        System.out.println("扩展欧几里得算法:");
        System.out.println("========================================");
        int a = 240, b = 46;
        int[] result = gcdExtended(a, b);
        System.out.printf("%d × %d + %d × %d = %d%n", 
                         a, result[1], b, result[2], result[0]);
        
        // 多个数的GCD和LCM
        System.out.println("\n========================================");
        System.out.println("多个数的GCD和LCM:");
        System.out.println("========================================");
        int[] numbers = {12, 18, 24, 36};
        System.out.print("数字: ");
        for (int n : numbers) System.out.print(n + " ");
        System.out.println();
        System.out.println("gcd = " + gcdMultiple(numbers));
        System.out.println("lcm = " + lcmMultiple(numbers));
        
        // 欧拉函数
        System.out.println("\n========================================");
        System.out.println("欧拉函数 φ(n):");
        System.out.println("========================================");
        for (int i = 1; i <= 20; i++) {
            System.out.printf("φ(%2d) = %2d  ", i, eulerTotient(i));
            if (i % 5 == 0) System.out.println();
        }
        
        // 数学性质
        System.out.println("\n========================================");
        System.out.println("数学性质:");
        System.out.println("========================================");
        System.out.println("• gcd(a, b) = gcd(b, a mod b)");
        System.out.println("• gcd(a, b) × lcm(a, b) = |a × b|");
        System.out.println("• 贝祖定理: 存在x,y使得 ax + by = gcd(a,b)");
    }
}
