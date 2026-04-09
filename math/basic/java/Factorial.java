/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 阶乘计算 (Factorial)
 * 计算非负整数的阶乘 n!
 * 支持递归、迭代和大数计算
 * 时间复杂度: O(n)
 */

import java.math.BigInteger;

public class Factorial {
    
    /**
     * 迭代计算阶乘
     * 
     * 算法原理：
     * - n! = 1 × 2 × 3 × ... × n
     * - 0! = 1（空积的定义）
     * 
     * 参数:
     *     n: 非负整数（n ≤ 20，避免long溢出）
     * 返回:
     *     n! 的结果
     * 
     * 时间复杂度: O(n)
     * 空间复杂度: O(1)
     */
    public static long factorialIterative(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        if (n > 20) throw new IllegalArgumentException("n太大，会导致long溢出");
        
        long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
    
    /**
     * 递归计算阶乘
     * 
     * 时间复杂度: O(n)
     * 空间复杂度: O(n) - 递归栈
     */
    public static long factorialRecursive(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        if (n > 20) throw new IllegalArgumentException("n太大，会导致long溢出");
        if (n <= 1) return 1;
        return n * factorialRecursive(n - 1);
    }
    
    /**
     * 尾递归优化版本
     */
    public static long factorialTailRecursive(int n, long accumulator) {
        if (n <= 1) return accumulator;
        return factorialTailRecursive(n - 1, n * accumulator);
    }
    
    /**
     * 大数阶乘计算（使用BigInteger）
     * 
     * 可以计算任意大的阶乘（受限于内存）
     * 1000! 有 2568 位数字
     * 10000! 有 35660 位数字
     */
    public static BigInteger factorialBig(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        
        BigInteger result = BigInteger.ONE;
        for (int i = 2; i <= n; i++) {
            result = result.multiply(BigInteger.valueOf(i));
        }
        return result;
    }
    
    /**
     * 使用Stream API计算阶乘（函数式风格）
     */
    public static long factorialStream(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        if (n > 20) throw new IllegalArgumentException("n太大");
        
        return java.util.stream.LongStream.rangeClosed(1, n)
                .reduce(1, (a, b) -> a * b);
    }
    
    /**
     * 双阶乘 n!! = n × (n-2) × (n-4) × ...
     */
    public static long doubleFactorial(int n) {
        if (n < 0) throw new IllegalArgumentException("n必须非负");
        if (n > 30) throw new IllegalArgumentException("n太大，会导致溢出");
        
        long result = 1;
        for (int i = n; i > 0; i -= 2) {
            result *= i;
        }
        return result;
    }
    
    /**
     * 排列数 P(n, k) = n! / (n-k)!
     * 从n个不同元素中取出k个元素的排列数
     */
    public static long permutation(int n, int k) {
        if (k > n || k < 0) throw new IllegalArgumentException("k必须在0到n之间");
        if (n > 20) throw new IllegalArgumentException("n太大");
        
        long result = 1;
        for (int i = n; i > n - k; i--) {
            result *= i;
        }
        return result;
    }
    
    /**
     * 组合数 C(n, k) = n! / (k! × (n-k)!)
     * 从n个不同元素中取出k个元素的组合数
     */
    public static long combination(int n, int k) {
        if (k > n || k < 0) throw new IllegalArgumentException("k必须在0到n之间");
        if (k > n / 2) k = n - k;  // 利用对称性减少计算
        if (n > 20) throw new IllegalArgumentException("n太大");
        
        long result = 1;
        for (int i = 1; i <= k; i++) {
            result = result * (n - k + i) / i;
        }
        return result;
    }
    
    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("    阶乘计算演示 (Factorial n!)");
        System.out.println("========================================\n");
        
        // 阶乘表
        System.out.println("阶乘表 (0! 到 20!):");
        System.out.println("----------------------------------------");
        for (int i = 0; i <= 20; i++) {
            System.out.printf("%2d! = %20d%n", i, factorialIterative(i));
        }
        
        // 大数阶乘
        System.out.println("\n大数阶乘 (使用BigInteger):");
        System.out.println("----------------------------------------");
        System.out.println("50! 的位数: " + factorialBig(50).toString().length());
        System.out.println("100! 的位数: " + factorialBig(100).toString().length());
        System.out.println("1000! 的位数: " + factorialBig(1000).toString().length());
        
        // 显示100!的前50位和后20位
        String fact100 = factorialBig(100).toString();
        System.out.println("\n100! = " + fact100.substring(0, 50) + "..." + 
                          fact100.substring(fact100.length() - 20));
        
        // 排列组合
        System.out.println("\n========================================");
        System.out.println("排列组合计算:");
        System.out.println("========================================");
        System.out.printf("P(10, 3) = %d (从10个中取3个排列)%n", permutation(10, 3));
        System.out.printf("C(10, 3) = %d (从10个中取3个组合)%n", combination(10, 3));
        System.out.printf("C(52, 5) = %d (扑克牌5张组合数)%n", combination(52, 5));
        
        // 杨辉三角（帕斯卡三角）
        System.out.println("\n杨辉三角（前8行）:");
        System.out.println("----------------------------------------");
        for (int n = 0; n < 8; n++) {
            for (int k = 0; k <= n; k++) {
                System.out.printf("%4d", combination(n, k));
            }
            System.out.println();
        }
        
        // 数学性质
        System.out.println("\n========================================");
        System.out.println("阶乘的数学性质:");
        System.out.println("========================================");
        System.out.println("• 定义: n! = n × (n-1) × ... × 2 × 1");
        System.out.println("• 递推: n! = n × (n-1)!");
        System.out.println("• 0! = 1（空积的定义）");
        System.out.println("• 增长: 阶乘比指数增长更快");
        System.out.println("• 斯特林近似: n! ≈ √(2πn) × (n/e)^n");
        
        // 应用场景
        System.out.println("\n========================================");
        System.out.println("应用场景:");
        System.out.println("========================================");
        System.out.println("• 排列组合: 计算可能性的总数");
        System.out.println("• 概率论: 生日问题、洗牌算法");
        System.out.println("• 泰勒级数: e^x = Σ x^n/n!");
        System.out.println("• 图论: 计算不同图的数量");
        System.out.println("• 信息论: 编码理论");
    }
}
