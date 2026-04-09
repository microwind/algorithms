/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 幂运算 (Power/Exponentiation)
 * 计算基数的指数次幂
 * 支持快速幂算法
 * 时间复杂度: O(log n)
 */

public class Power {
    
    public static double power(double base, int exp) {
        if (exp < 0) return 1.0 / power(base, -exp);
        if (exp == 0) return 1.0;
        
        double result = 1.0;
        double current = base;
        int e = exp;
        
        while (e > 0) {
            if ((e & 1) == 1) result *= current;
            current *= current;
            e >>= 1;
        }
        return result;
    }
    
    public static long powerMod(long base, long exp, long mod) {
        long result = 1 % mod;
        base = base % mod;
        long e = exp;
        
        while (e > 0) {
            if ((e & 1) == 1) result = (result * base) % mod;
            base = (base * base) % mod;
            e >>= 1;
        }
        return result;
    }
    
    public static void main(String[] args) {
        System.out.println("幂运算演示:");
        for (int i = 0; i <= 10; i++) {
            System.out.printf("2^%d = %.0f%n", i, power(2, i));
        }
        System.out.println("\n模幂运算:");
        System.out.printf("3^100 mod 1000 = %d%n", powerMod(3, 100, 1000));
    }
}
