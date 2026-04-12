/**
 * Copyright https://github.com/microwind
 * Digit Sum
 */

class DigitSum {
    public static int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }
    
    public static void main(String[] args) {
        int n = 12345;
        System.out.println("Digit sum of " + n + " = " + digitSum(n));
    }
}
