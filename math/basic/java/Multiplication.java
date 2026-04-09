/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 乘法运算 (Multiplication)
 * 安全乘法，溢出检测
 */

public class Multiplication {
    
    public static long safeMultiply(int a, int b) {
        long result = (long) a * (long) b;
        if (result > Integer.MAX_VALUE || result < Integer.MIN_VALUE) {
            throw new ArithmeticException("乘法溢出");
        }
        return result;
    }
    
    public static long multiply(int a, int b) {
        return (long) a * b;
    }
    
    public static long powerOfTwoMultiply(int a, int power) {
        return (long) a << power;
    }
    
    public static void main(String[] args) {
        System.out.println("乘法运算演示:");
        System.out.printf("12 × 8 = %d%n", multiply(12, 8));
        System.out.printf("100 × 25 = %d%n", multiply(100, 25));
        System.out.printf("7 << 3 (7 × 8) = %d%n", powerOfTwoMultiply(7, 3));
    }
}
