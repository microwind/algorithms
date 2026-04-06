/**
 * 递归算法示例集合（基于JavaScript版本）
 * 包含阶乘、递归计算等示例
 */

public class RecursionJs {
    
    /**
     * 阶乘递归计算（版本1）
     * @param x 输入数字
     * @return 阶乘结果
     */
    public static int factorial(int x) {
        System.out.println("x= " + x);
        if (x < 1) return 0;
        if (x == 1) return 1;
        // 递归调用：x * (x-1) * (x-2) * ... * 1
        return x * factorial(x - 1);
    }
    
    /**
     * 阶乘递归计算（版本2）
     * @param x 输入数字
     * @return 阶乘结果
     */
    public static int factorial2(int x) {
        System.out.println("x= " + x);
        if (x <= 1) return x;
        // 递归调用：x * (x-1) * (x-2) * ... * 1
        return x * factorial2(x - 1);
    }
    
    /**
     * 递归计算示例
     * @param n 输入数字
     * @return 计算结果
     */
    public static int recursion(int n) {
        System.out.println("begin: n= " + n);
        if (n >= 15) return n;
        n *= 3;
        // 递归调用：recursion(n + 1) + recursion(n * 2)
        return recursion(n + 1) + recursion(n * 2);
    }
    
    /**
     * 递归计算示例2
     * @param n 输入数字
     * @return 计算结果
     */
    public static int recursion2(int n) {
        System.out.println("begin: n= " + n);
        if (n >= 15) return n;
        n *= 3;
        return recursion2(n + 1) - recursion2(n * 2);
    }
    
    public static void main(String[] args) {
        System.out.println("factorial(5) " + factorial(5));
        
        System.out.println("recursion(1)= " + recursion(1));
        System.out.println("recursion2(1)= " + recursion2(1));
    }
}
