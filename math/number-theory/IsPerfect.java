/**
 * Copyright https://github.com/microwind
 * Perfect Number Check
 */

class IsPerfect {
    public static boolean isPerfect(int n) {
        if (n <= 1) return false;
        int sum = 1;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                sum += i;
                if (i != n / i) sum += n / i;
            }
        }
        return sum == n;
    }
    
    public static void main(String[] args) {
        System.out.print("Perfect numbers up to 1000: ");
        for (int i = 1; i <= 1000; i++) {
            if (isPerfect(i)) System.out.print(i + " ");
        }
        System.out.println();
    }
}
