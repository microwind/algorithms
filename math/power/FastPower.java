/**
 * Copyright https://github.com/microwind
 * Fast Power (Binary Exponentiation)
 */

class FastPower {
    public static long fastPower(long base, long exponent, long mod) {
        long result = 1;
        base = base % mod;
        while (exponent > 0) {
            if ((exponent & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exponent >>= 1;
        }
        return result;
    }
    
    public static void main(String[] args) {
        System.out.println("2^10 = " + fastPower(2, 10, 1000000007));
        System.out.println("3^5 = " + fastPower(3, 5, 1000000007));
    }
}
