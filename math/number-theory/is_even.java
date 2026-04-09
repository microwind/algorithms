/**
 * Check if number is even/odd
 */

class IsEven {
    public static boolean isEven(int n) {
        return n % 2 == 0;
    }
    
    public static void main(String[] args) {
        int[] testNumbers = {2, 3, 4, 5, 10, 15};
        for (int n : testNumbers) {
            System.out.println(n + " is " + (isEven(n) ? "even" : "odd"));
        }
    }
}
