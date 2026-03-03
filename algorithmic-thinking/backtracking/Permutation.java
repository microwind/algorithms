import java.util.*;

/*
使用回溯生成排列 (Java Implementation)

算法说明:
- Generate all permutations of a list using backtracking
- Use ArrayList for dynamic sizing and flexibility
- At each recursion level, try each unused element
- Backtrack by removing the element from current permutation

Time Complexity: O(n! * n) - n! permutations, each taking O(n) to copy
Space Complexity: O(n) - recursion depth (not counting output)

示例:
    permute([1, 2, 3]) returns [[1,2,3], [1,3,2], [2,1,3], ...]
*/

public class Permutation {

    /*
*
     * Generate all permutations of a list using backtracking.
     *
     * @param nums List of integers to permute
     * @return List of all permutations
*/
    public static List<List<Integer>> permute(List<Integer> nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), nums);
        return result;
    }

    /*
*
     * Helper method for backtracking.
     *
     * @param result List to store all permutations
     * @param current Current permutation being built
     * @param remaining Unused elements to choose from
*/
    private static void backtrack(List<List<Integer>> result,
                                   List<Integer> current,
                                   List<Integer> remaining) {
        // Base case: all elements used, add to result
        if (remaining.isEmpty()) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Try each remaining element as the next element
        for (int i = 0; i < remaining.size(); i++) {
            // Choose: add remaining.get(i) to current permutation
            int num = remaining.get(i);
            current.add(num);

            // Explore: recursively build rest of permutation
            List<Integer> newRemaining = new ArrayList<>(remaining);
            newRemaining.remove(i);
            backtrack(result, current, newRemaining);

            // Unchoose: remove the element for backtracking
            current.remove(current.size() - 1);
        }
    }

    /*
*
     * Optimized permutation using in-place swapping with array.
     *
     * Time Complexity: O(n! * n)
     * Space Complexity: O(n)
*/
    public static List<List<Integer>> permuteOptimized(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrackSwap(result, nums, 0);
        return result;
    }

    /*
*
     * Helper method for in-place swap backtracking.
     *
     * @param result List to store all permutations
     * @param nums Array to permute
     * @param index Current position to permute from
*/
    private static void backtrackSwap(List<List<Integer>> result, int[] nums, int index) {
        // Base case: reached end of array
        if (index == nums.length) {
            List<Integer> perm = new ArrayList<>();
            for (int num : nums) {
                perm.add(num);
            }
            result.add(perm);
            return;
        }

        // Try each element from index onwards as the next element
        for (int i = index; i < nums.length; i++) {
            // Choose: swap elements
            int temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;

            // Explore: permute the rest
            backtrackSwap(result, nums, index + 1);

            // Unchoose: swap back
            temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;
        }
    }

    /*
*
     * Test cases for permutation generation
*/
    public static void main(String[] args) {
        System.out.println("=== Permutation Backtracking Test Cases ===\n");

        // 测试用例 1: [1, 2, 3]
        System.out.println("Test 1: permute([1, 2, 3])");
        List<Integer> test1 = Arrays.asList(1, 2, 3);
        List<List<Integer>> result1 = permute(test1);
        System.out.println("Result (count=" + result1.size() + "):");
        for (List<Integer> perm : result1) {
            System.out.println("  " + perm);
        }
        System.out.println();

        // 测试用例 2: [1, 2]
        System.out.println("Test 2: permute([1, 2])");
        List<Integer> test2 = Arrays.asList(1, 2);
        List<List<Integer>> result2 = permute(test2);
        System.out.println("Result (count=" + result2.size() + "):");
        for (List<Integer> perm : result2) {
            System.out.println("  " + perm);
        }
        System.out.println();

        // 测试用例 3: [1]
        System.out.println("Test 3: permute([1])");
        List<Integer> test3 = Arrays.asList(1);
        List<List<Integer>> result3 = permute(test3);
        System.out.println("Result (count=" + result3.size() + "):");
        for (List<Integer> perm : result3) {
            System.out.println("  " + perm);
        }
        System.out.println();

        // 测试用例 4: Optimized version with [1, 2, 3, 4]
        System.out.println("Test 4: permuteOptimized([1, 2, 3, 4])");
        int[] test4 = {1, 2, 3, 4};
        List<List<Integer>> result4 = permuteOptimized(test4);
        System.out.println("Result (count=" + result4.size() + "):");
        System.out.println("First 3 permutations:");
        for (int i = 0; i < 3; i++) {
            System.out.println("  " + result4.get(i));
        }
        System.out.println("Last 3 permutations:");
        for (int i = result4.size() - 3; i < result4.size(); i++) {
            System.out.println("  " + result4.get(i));
        }
        System.out.println();

        // 测试用例 5: String characters via optimized
        System.out.println("Test 5: permuteOptimized([10, 20, 30])");
        int[] test5 = {10, 20, 30};
        List<List<Integer>> result5 = permuteOptimized(test5);
        System.out.println("Result (count=" + result5.size() + "):");
        for (List<Integer> perm : result5) {
            System.out.println("  " + perm);
        }
    }
}
