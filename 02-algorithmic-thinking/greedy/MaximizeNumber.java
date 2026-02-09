import java.util.*;

/**
 * Maximize Number - Remove k digits to get maximum value
 *
 * Algorithm:
 * - Given a digit string and k, remove k digits to maximize the resulting number
 * - Use a greedy stack-based approach:
 *   1. Iterate through digits
 *   2. If current digit is greater than the top of stack, pop smaller digits
 *   3. Add current digit to stack
 *   4. If we still need to delete digits, remove from the end
 *
 * Time Complexity: O(n) - each digit is pushed/popped at most once
 * Space Complexity: O(n) - for the stack
 */

class MaximizeNumberResult {
    String result;
    List<Integer> deletedPositions;

    MaximizeNumberResult(String result, List<Integer> deletedPositions) {
        this.result = result;
        this.deletedPositions = deletedPositions;
    }

    @Override
    public String toString() {
        return "Result: '" + result + "', Deleted positions: " + deletedPositions;
    }
}

public class MaximizeNumber {
    /**
     * Remove k digits from the string to get maximum resulting number
     *
     * @param numStr String of digits
     * @param k Number of digits to remove
     * @return String representing the maximum number
     */
    static String removeKDigits(String numStr, int k) {
        int n = numStr.length();

        if (k >= n) {
            return "0";
        }

        if (k == 0) {
            return numStr;
        }

        // Stack-based greedy approach
        Deque<Character> stack = new LinkedList<>();
        int toDelete = k;

        for (char digit : numStr.toCharArray()) {
            // Remove smaller digits from stack when we encounter a larger digit
            while (toDelete > 0 && !stack.isEmpty() && stack.peekLast() < digit) {
                stack.removeLast();
                toDelete--;
            }
            stack.addLast(digit);
        }

        // If we still have digits to delete, remove from the end
        while (toDelete > 0 && !stack.isEmpty()) {
            stack.removeLast();
            toDelete--;
        }

        // Build result
        StringBuilder sb = new StringBuilder();
        for (char c : stack) {
            sb.append(c);
        }

        String result = sb.toString();

        // Handle leading zeros
        int i = 0;
        while (i < result.length() && result.charAt(i) == '0') {
            i++;
        }

        return (i == result.length()) ? "0" : result.substring(i);
    }

    /**
     * Remove k digits with position tracking
     *
     * @param numStr String of digits
     * @param k Number of digits to remove
     * @return MaximizeNumberResult with result and deleted positions
     */
    static MaximizeNumberResult removeKDigitsWithTracking(String numStr, int k) {
        int n = numStr.length();

        if (k >= n) {
            return new MaximizeNumberResult("0", new ArrayList<>());
        }

        if (k == 0) {
            return new MaximizeNumberResult(numStr, new ArrayList<>());
        }

        Deque<int[]> stack = new LinkedList<>();
        List<Integer> deletedPositions = new ArrayList<>();
        int toDelete = k;

        for (int i = 0; i < n; i++) {
            char digit = numStr.charAt(i);
            while (toDelete > 0 && !stack.isEmpty() && stack.peekLast()[0] < digit) {
                int[] removed = stack.removeLast();
                deletedPositions.add(removed[1]);
                toDelete--;
            }
            stack.addLast(new int[]{digit, i});
        }

        // Delete remaining from end if needed
        while (toDelete > 0 && !stack.isEmpty()) {
            int[] removed = stack.removeLast();
            deletedPositions.add(removed[1]);
            toDelete--;
        }

        // Build result
        StringBuilder sb = new StringBuilder();
        for (int[] item : stack) {
            sb.append((char) item[0]);
        }

        String result = sb.toString();

        // Handle leading zeros
        int i = 0;
        while (i < result.length() && result.charAt(i) == '0') {
            i++;
        }

        String finalResult = (i == result.length()) ? "0" : result.substring(i);
        Collections.sort(deletedPositions);

        return new MaximizeNumberResult(finalResult, deletedPositions);
    }

    static void testStandardExample() {
        System.out.println("\n[Test 1] Standard example from problem");
        String result = removeKDigits("1432219", 3);
        System.out.println("Input: '1432219', k=3");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '4321'");
    }

    static void testLeadingZeros() {
        System.out.println("\n[Test 2] Remove leading zeros");
        String result = removeKDigits("10200", 1);
        System.out.println("Input: '10200', k=1");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '200'");
    }

    static void testSameDigits() {
        System.out.println("\n[Test 3] All same digits");
        String result = removeKDigits("1111", 2);
        System.out.println("Input: '1111', k=2");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '11'");
    }

    static void testDescendingOrder() {
        System.out.println("\n[Test 4] Descending digits - remove from end");
        String result = removeKDigits("54321", 2);
        System.out.println("Input: '54321', k=2");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '321'");
    }

    static void testAscendingOrder() {
        System.out.println("\n[Test 5] Ascending digits - remove from front");
        String result = removeKDigits("12345", 2);
        System.out.println("Input: '12345', k=2");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '345'");
    }

    static void testRemoveAll() {
        System.out.println("\n[Test 6] Remove all digits");
        String result = removeKDigits("123", 3);
        System.out.println("Input: '123', k=3");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '0'");
    }

    static void testRemoveZero() {
        System.out.println("\n[Test 7] Remove zero digits");
        String result = removeKDigits("1234", 0);
        System.out.println("Input: '1234', k=0");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '1234'");
    }

    static void testMultipleZeros() {
        System.out.println("\n[Test 8] Multiple zeros in middle");
        String result = removeKDigits("100200", 2);
        System.out.println("Input: '100200', k=2");
        System.out.println("Output: '" + result + "'");
    }

    static void testMixed() {
        System.out.println("\n[Test 9] Mixed digits");
        String result = removeKDigits("112", 1);
        System.out.println("Input: '112', k=1");
        System.out.println("Output: '" + result + "'");
        System.out.println("Expected: '12'");
    }

    static void testLargeNumber() {
        System.out.println("\n[Test 10] With deletion position tracking");
        MaximizeNumberResult result = removeKDigitsWithTracking("987654321", 4);
        System.out.println("Input: '987654321', k=4");
        System.out.println("Output: " + result);
    }

    public static void main(String[] args) {
        System.out.println("==================================================");
        System.out.println("MAXIMIZE NUMBER - Remove k Digits (Java)");
        System.out.println("==================================================");

        testStandardExample();
        testLeadingZeros();
        testSameDigits();
        testDescendingOrder();
        testAscendingOrder();
        testRemoveAll();
        testRemoveZero();
        testMultipleZeros();
        testMixed();
        testLargeNumber();
    }
}
