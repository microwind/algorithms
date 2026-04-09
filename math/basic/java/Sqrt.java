/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 平方根计算 (Square Root)
 * 使用牛顿迭代法求平方根
 * 时间复杂度: O(log n)
 */

public class Sqrt {
    
    public static double sqrtNewton(double n, double epsilon) {
        if (n < 0) throw new IllegalArgumentException("不能计算负数的平方根");
        if (n == 0) return 0.0;
        
        double x = n;
        while (Math.abs(x * x - n) > epsilon) {
            x = (x + n / x) / 2.0;
        }
        return x;
    }
    
    public static void main(String[] args) {
        System.out.println("牛顿迭代法求平方根:");
        double[] testValues = {1, 2, 4, 9, 16, 25, 100, 10000};
        for (double n : testValues) {
            double result = sqrtNewton(n, 1e-10);
            System.out.printf("sqrt(%.0f) = %.10f (Math.sqrt: %.10f)%n", 
                            n, result, Math.sqrt(n));
        }
    }
}
