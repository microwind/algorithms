/**
 * Copyright https://github.com/microwind
 * GCD - Greatest Common Divisor
 */

class GCD {
    public static int gcd(int x, int y) {
        while (y != 0) {
            int temp = y;
            y = x % y;
            x = temp;
        }
        return x;
    }
    
    public static void main(String[] args) {
        System.out.println("GCD(48, 18) = " + gcd(48, 18));
        System.out.println("GCD(56, 98) = " + gcd(56, 98));
    }
}
