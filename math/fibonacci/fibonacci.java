/**
 * Copyright https://github.com/microwind
 * Fibonacci Sequence
 */

class Fibonacci {
    public static long fibonacci(int n) {
        if (n <= 1) return n;
        long first = 0, second = 1, result = 0;
        for (int i = 1; i < n; i++) {
            result = first + second;
            first = second;
            second = result;
        }
        return result;
    }
    
    public static void main(String[] args) {
        System.out.println("Fibonacci Sequence:");
        for (int i = 0; i <= 10; i++) {
            System.out.println("F(" + i + ") = " + fibonacci(i));
        }
    }
}
