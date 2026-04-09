/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 素数判定与生成 (Prime Numbers)
 * 判断素数并生成素数表
 * 时间复杂度: O(√n) - 试除法, O(n log log n) - 筛法
 */

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Prime {
    
    /**
     * 试除法判断素数
     * 
     * 时间复杂度: O(√n)
     */
    public static boolean isPrime(int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    /**
     * 优化的素数判断（6k±1形式）
     */
    public static boolean isPrimeOptimized(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }
    
    /**
     * 埃拉托斯特尼筛法
     * 
     * 时间复杂度: O(n log log n)
     */
    public static boolean[] sieveOfEratosthenes(int limit) {
        boolean[] isPrime = new boolean[limit + 1];
        for (int i = 2; i <= limit; i++) {
            isPrime[i] = true;
        }
        
        for (int p = 2; p * p <= limit; p++) {
            if (isPrime[p]) {
                for (int multiple = p * p; multiple <= limit; multiple += p) {
                    isPrime[multiple] = false;
                }
            }
        }
        
        return isPrime;
    }
    
    /**
     * 获取素数列表
     */
    public static List<Integer> getPrimes(int limit) {
        boolean[] sieve = sieveOfEratosthenes(limit);
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= limit; i++) {
            if (sieve[i]) primes.add(i);
        }
        return primes;
    }
    
    /**
     * 素因数分解
     */
    public static List<Integer> primeFactorization(int n) {
        List<Integer> factors = new ArrayList<>();
        int d = 2;
        while (d * d <= n) {
            while (n % d == 0) {
                factors.add(d);
                n /= d;
            }
            d++;
        }
        if (n > 1) factors.add(n);
        return factors;
    }
    
    /**
     * Miller-Rabin素性测试（概率算法）
     */
    public static boolean isProbablePrime(long n, int k) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;
        
        // 写成 n-1 = d * 2^r
        long d = n - 1;
        int r = 0;
        while (d % 2 == 0) {
            d /= 2;
            r++;
        }
        
        Random rand = new Random();
        for (int i = 0; i < k; i++) {
            long a = rand.nextLong() % (n - 3) + 2;
            long x = modPow(a, d, n);
            
            if (x == 1 || x == n - 1) continue;
            
            boolean continueOuter = false;
            for (int j = 0; j < r - 1; j++) {
                x = modPow(x, 2, n);
                if (x == n - 1) {
                    continueOuter = true;
                    break;
                }
            }
            
            if (continueOuter) continue;
            return false;
        }
        
        return true;
    }
    
    /**
     * 模幂运算
     */
    private static long modPow(long base, long exp, long mod) {
        long result = 1 % mod;
        base = base % mod;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
    
    /**
     * 素数计数 π(n)
     */
    public static int countPrimes(int n) {
        if (n < 2) return 0;
        boolean[] sieve = sieveOfEratosthenes(n);
        int count = 0;
        for (boolean b : sieve) {
            if (b) count++;
        }
        return count;
    }
    
    public static void main(String[] args) {
        System.out.println("========================================");
        System.out.println("    素数判定与生成 (Prime Numbers)");
        System.out.println("========================================\n");
        
        // 100以内的素数
        System.out.println("100以内的素数:");
        System.out.println("----------------------------------------");
        List<Integer> primes100 = getPrimes(100);
        for (int i = 0; i < primes100.size(); i++) {
            System.out.printf("%3d ", primes100.get(i));
            if ((i + 1) % 10 == 0) System.out.println();
        }
        System.out.println("\n共 " + primes100.size() + " 个素数\n");
        
        // 素数判定
        System.out.println("素数判定测试:");
        System.out.println("----------------------------------------");
        int[] testNumbers = {1, 2, 3, 4, 17, 18, 97, 541, 1009};
        for (int n : testNumbers) {
            String result = isPrimeOptimized(n) ? "是素数" : "不是素数";
            System.out.printf("%6d %s%n", n, result);
        }
        
        // 素因数分解
        System.out.println("\n========================================");
        System.out.println("素因数分解:");
        System.out.println("========================================");
        int[] numbersToFactor = {12, 100, 360, 1001, 2024};
        for (int n : numbersToFactor) {
            List<Integer> factors = primeFactorization(n);
            System.out.printf("%6d = ", n);
            for (int i = 0; i < factors.size(); i++) {
                System.out.print(factors.get(i));
                if (i < factors.size() - 1) System.out.print(" × ");
            }
            System.out.println();
        }
        
        // 素数计数
        System.out.println("\n========================================");
        System.out.println("素数计数 π(n):");
        System.out.println("========================================");
        for (int n : new int[]{10, 100, 1000, 10000}) {
            int count = countPrimes(n);
            double approx = n / Math.log(n);
            System.out.printf("π(%6d) = %6d (近似: %.1f)%n", n, count, approx);
        }
        
        // 数学性质
        System.out.println("\n========================================");
        System.out.println("数学性质:");
        System.out.println("========================================");
        System.out.println("• 素数定理: π(n) ~ n/ln(n)");
        System.out.println("• 欧几里得定理: 素数有无穷多个");
        System.out.println("• 唯一分解定理: 每个整数可唯一表示为素数乘积");
    }
}
