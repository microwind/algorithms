/**
 * Copyright https://github.com/microwind
 * Multiplication Table
 */

class TimesTable {
    public static void printTable(int max) {
        for (int i = 1; i <= max; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.printf("%d×%d=%2d  ", j, i, i * j);
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        System.out.println("Multiplication Table (9x9):");
        printTable(9);
    }
}
