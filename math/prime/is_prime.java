/**
 * Copyright https://github.com/microwind
 * Prime Number Check
 */

class IsPrime {
    public static boolean isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }
    
    public static void main(String[] args) {
        System.out.print("Primes up to 50: ");
        for (int i = 1; i <= 50; i++) {
            if (isPrime(i)) System.out.print(i + " ");
        }
        System.out.println();
    }
}
