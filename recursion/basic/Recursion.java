/**
 * 递归算法示例集合
 * 包含阶乘、递归计算、尾递归等示例
 */

public class Recursion {
    
    /**
     * 阶乘递归计算
     * @param x 输入数字
     * @return 阶乘结果
     */
    public static int factorial(int x) {
        System.out.println("\nx=" + x);
        if (x < 1) {
            return x;
        }
        if (x == 1) {
            return x;
        }
        // 递归调用：x * (x-1) * (x-2) * ... * 1
        return x * factorial(x - 1);
    }
    
    /**
     * 阶乘递归计算（改进版）
     * @param x 输入数字
     * @return 阶乘结果
     */
    public static int factorial2(int x) {
        System.out.println("\nx=" + x);
        if (x <= 1) {
            return x;
        }
        // 递归调用：x * (x-1) * (x-2) * ... * 1
        return x * factorial2(x - 1);
    }
    
    /**
     * 递归计算示例
     * @param n 输入数字
     * @return 计算结果
     */
    public static int recursion(int n) {
        System.out.println("\nbegin: n=" + n);
        if (n >= 15) {
            return n;
        }
        n *= 3;
        return recursion(n + 1) + recursion(n * 2);
    }
    
    /**
     * 尾递归示例（单一递归调用，无后续操作）
     * @param n 输入数字
     * @param accumulator 累加器
     * @return 计算结果
     */
    public static int tailRecursion(int n, int accumulator) {
        if (n >= 15) {
            return accumulator + n;                      // 终止时直接返回结果
        }
        return tailRecursion(n * 3 + 1, accumulator); // 最后一步仅递归调用
    }
    
    /**
     * 递归计算示例2
     * @param n 输入数字
     * @return 计算结果
     */
    public static int recursion2(int n) {
        System.out.println("\nbegin: n=" + n);
        if (n >= 15) {
            return n;
        }
        n *= 3;
        return recursion2(n + 1) - recursion2(n * 2);
    }
    
    public static void main(String[] args) {
        System.out.println("\r\nfactorial(5) " + factorial(5));
        System.out.println("\r\n===");
        System.out.println("\r\nfactorial2(5) " + factorial2(5));
        System.out.println("\r\n===");
        System.out.println("\r\nrecursion(1) " + recursion(1));
        System.out.println("\r\n===");
        System.out.println("\r\nrecursion2(1) " + recursion2(1));
    }
}
