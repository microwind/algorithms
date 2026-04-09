/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 组合计算 (Combination)
 * 计算从n个元素中选取k个元素的组合数
 * 公式: C(n,k) = n! / (k! * (n-k)!)
 */

class Combine {
    
    /**
     * 计算阶乘
     */
    public static long factorial(int n) {
        long product = 1;
        for (int i = 1; i <= n; i++) {
            product *= i;
        }
        return product;
    }
    
    /**
     * 计算组合数 C(n,k)
     */
    public static long combine(int n, int k) {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }
    
    public static void main(String[] args) {
        int n = 5;
        System.out.println("组合计算 C(n,k)");
        System.out.println("===============");
        
        for (int k = 1; k <= n; k++) {
            long result = combine(n, k);
            System.out.printf("C(%d,%d) = %d%n", n, k, result);
        }
    }
}
