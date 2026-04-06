/**
 * 阶乘递归示例
 * n! = n × (n-1) × (n-2) × ... × 1
 */
public class FactorialPy {
    
    /**
     * 方法1: 递归版本
     * @param n 输入数字
     * @return 阶乘结果
     */
    public static long factorialRecursive(int n) {
        /* 递归计算阶乘，O(n) 时间复杂度，O(n) 空间复杂度 */
        if (n <= 1) {
            return 1;
        }
        return n * factorialRecursive(n - 1);
    }
    
    /**
     * 方法2: 迭代版本
     * @param n 输入数字
     * @return 阶乘结果
     */
    public static long factorialIterative(int n) {
        /* 迭代计算阶乘，O(n) 时间复杂度，O(1) 空间复杂度 */
        long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
    
    /**
     * 方法3: 尾递归
     * @param n 输入数字
     * @param acc 累加器
     * @return 阶乘结果
     */
    private static long factorialTail(int n, long acc) {
        /* 尾递归版本 */
        if (n <= 1) {
            return acc;
        }
        return factorialTail(n - 1, n * acc);
    }
    
    public static long factorialTail(int n) {
        return factorialTail(n, 1);
    }
    
    public static void main(String[] args) {
        System.out.println("=== 阶乘计算 ===\n");
        
        int[] testValues = {5, 10, 20};
        
        for (int n : testValues) {
            System.out.printf("%d! = %d\n", n, factorialRecursive(n));
            System.out.printf("迭代版本: %d! = %d\n", n, factorialIterative(n));
            System.out.printf("尾递归版本: %d! = %d\n", n, factorialTail(n));
            System.out.println();
        }
    }
}
