/**
 * Copyright https://github.com/microwind
 * Zeno's Paradox - Dichotomy Paradox
 */

class Zeno {
    public static void zenoParadox(double totalDistance, int steps) {
        double remaining = totalDistance;
        System.out.println("Zeno's Dichotomy Paradox:");
        for (int i = 1; i <= steps; i++) {
            remaining /= 2;
            System.out.printf("Step %d: remaining distance = %.6f%n", i, remaining);
        }
    }
    
    public static void main(String[] args) {
        zenoParadox(1.0, 10);
    }
}
