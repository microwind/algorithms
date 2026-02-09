import java.util.*;

/*
Combination Generator using Backtracking (Java Implementation)

Algorithm Explanation:
- Generate all combinations of k elements from 1 to n (C(n,k))
- Use backtracking to systematically explore all choices
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

Time Complexity: O(C(n,k) * k) where C(n,k) is the number of combinations
Space Complexity: O(k) for recursion depth and current combination

Example:
    combine(4, 2) returns [[1,2], [1,3], [1,4], [2,3], [2,4], [3,4]]
*/

public class Combination {

    /**
     * Generate all combinations of k elements from 1 to n.
     *
     * @param n Total number of elements (1 to n)
     * @param k Size of each combination
     * @return List of all combinations
     */
    public static List<List<Integer>> combine(int n, int k) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), 1, n, k);
        return result;
    }

    /**
     * Helper method for backtracking.
     *
     * @param result List to store all combinations
     * @param current Current combination being built
     * @param start Starting number to consider
     * @param n Total number of elements
     * @param k Target combination size
     */
    private static void backtrack(List<List<Integer>> result,
                                   List<Integer> current,
                                   int start,
                                   int n,
                                   int k) {
        // Base case: combination is complete
        if (current.size() == k) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Try each number from start to n
        for (int num = start; num <= n; num++) {
            // Choose: add num to current combination
            current.add(num);

            // Explore: build rest of combination
            // Only numbers >= num+1 to avoid duplicates
            backtrack(result, current, num + 1, n, k);

            // Unchoose: remove num for backtracking
            current.remove(current.size() - 1);
        }
    }

    /**
     * Optimized combination with early termination.
     * Prunes branches that can't possibly yield k elements.
     *
     * Time Complexity: O(C(n,k) * k)
     * Space Complexity: O(k)
     */
    public static List<List<Integer>> combineOptimized(int n, int k) {
        List<List<Integer>> result = new ArrayList<>();
        backtrackOptimized(result, new ArrayList<>(), 1, n, k);
        return result;
    }

    /**
     * Helper method for optimized backtracking with pruning.
     */
    private static void backtrackOptimized(List<List<Integer>> result,
                                            List<Integer> current,
                                            int start,
                                            int n,
                                            int k) {
        // Base case: combination is complete
        if (current.size() == k) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Optimization: early termination
        // Remaining slots needed: k - current.size()
        // Elements available: n - start + 1
        // If not enough elements available, stop
        int remaining = k - current.size();
        int available = n - start + 1;
        if (available < remaining) {
            return;
        }

        // Try each number from start to n
        for (int num = start; num <= n; num++) {
            current.add(num);
            backtrackOptimized(result, current, num + 1, n, k);
            current.remove(current.size() - 1);
        }
    }

    /**
     * Test cases for combination generation
     */
    public static void main(String[] args) {
        System.out.println("=== Combination Backtracking Test Cases ===\n");

        // Test Case 1: combine(4, 2)
        System.out.println("Test 1: combine(4, 2)");
        List<List<Integer>> result1 = combine(4, 2);
        System.out.println("Result (count=" + result1.size() + "):");
        for (List<Integer> combo : result1) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // Test Case 2: combine(3, 1)
        System.out.println("Test 2: combine(3, 1)");
        List<List<Integer>> result2 = combine(3, 1);
        System.out.println("Result (count=" + result2.size() + "):");
        for (List<Integer> combo : result2) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // Test Case 3: combine(3, 3)
        System.out.println("Test 3: combine(3, 3)");
        List<List<Integer>> result3 = combine(3, 3);
        System.out.println("Result (count=" + result3.size() + "):");
        for (List<Integer> combo : result3) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // Test Case 4: combine(5, 3)
        System.out.println("Test 4: combine(5, 3)");
        List<List<Integer>> result4 = combine(5, 3);
        System.out.println("Result (count=" + result4.size() + "):");
        for (List<Integer> combo : result4) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // Test Case 5: combineOptimized(6, 2)
        System.out.println("Test 5: combineOptimized(6, 2)");
        List<List<Integer>> result5 = combineOptimized(6, 2);
        System.out.println("Result (count=" + result5.size() + "):");
        for (List<Integer> combo : result5) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // Test Case 6: combineOptimized(5, 4)
        System.out.println("Test 6: combineOptimized(5, 4)");
        List<List<Integer>> result6 = combineOptimized(5, 4);
        System.out.println("Result (count=" + result6.size() + "):");
        for (List<Integer> combo : result6) {
            System.out.println("  " + combo);
        }
    }
}
