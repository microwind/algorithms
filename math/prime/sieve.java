/**
数学算法 - 素数筛 (Sieve of Eratosthenes)
高效找出一定范围内的所有素数
 */

class Sieve {
    public static void sieve(int n) {
        boolean[] isPrime = new boolean[n + 1];
        for (int i = 2; i <= n; i++) isPrime[i] = true;
        
        for (int p = 2; p * p <= n; p++) {
            if (isPrime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    isPrime[i] = false;
                }
            }
        }
        
        System.out.print("Primes up to " + n + ": ");
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) System.out.print(i + " ");
        }
        System.out.println();
    }
    
    public static void main(String[] args) {
        sieve(50);
    }
}
