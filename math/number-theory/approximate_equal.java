/**
 * Copyright https://github.com/microwind
 * Approximate Equality Check
 */

class ApproximateEqual {
    public static boolean approxEqual(double a, double b, double epsilon) {
        return Math.abs(a - b) < epsilon;
    }
    
    public static void main(String[] args) {
        System.out.println("Approximate Equality Check:");
        System.out.println("0.1 + 0.2 ≈ 0.3: " + approxEqual(0.1 + 0.2, 0.3, 1e-10));
    }
}
