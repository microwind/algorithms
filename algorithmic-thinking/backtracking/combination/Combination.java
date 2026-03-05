import java.util.*;

/*
使用回溯生成组合 (Java Implementation)

算法说明:
- 生成从1到n中选取k个元素的所有组合 (C(n,k))
- 使用回溯系统地探索所有选择
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

时间复杂度：O(C(n,k) * k)，其中C(n,k)是组合数
空间复杂度：O(k)，用于递归深度和当前组合

示例:
    combine(4, 2) 返回 [[1,2], [1,3], [1,4], [2,3], [2,4], [3,4]]
*/

public class Combination {

    /*
     *
     * 生成从1到n中选取k个元素的所有组合.
     *
     * @param n 元素的总数（1到n）
     * 
     * @param k 每个组合的大小
     * 
     * @return List of all combinations
     */
    public static List<List<Integer>> combine(int n, int k) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), 1, n, k);
        return result;
    }

    /*
     *
     * Helper method for backtracking.
     *
     * @param result List to store all combinations
     * 
     * @param current 当前要构建的组合
     * 
     * @param start Starting number to consider
     * 
     * @param n Total number of elements
     * 
     * @param k Target combination size
     */
    private static void backtrack(List<List<Integer>> result,
            List<Integer> current,
            int start,
            int n,
            int k) {
        // 基本情况：组合已完成
        if (current.size() == k) {
            result.add(new ArrayList<>(current));
            return;
        }

        // 尝试从start到n的每个数字
        for (int num = start; num <= n; num++) {
            // 选择：将num添加到当前组合
            current.add(num);

            // 探索：构建组合的其余部分
            // 仅数字 >= num+1 以避免重复
            backtrack(result, current, num + 1, n, k);

            // 取消选择：移除num以进行回溯
            current.remove(current.size() - 1);
        }
    }

    /*
     *
     * Optimized combination with early termination.
     * 剪枝不可能产生k个元素的分支.
     *
     * Time Complexity: O(C(n,k) * k)
     * Space Complexity: O(k)
     */
    public static List<List<Integer>> combineOptimized(int n, int k) {
        List<List<Integer>> result = new ArrayList<>();
        backtrackOptimized(result, new ArrayList<>(), 1, n, k);
        return result;
    }

    /*
     *
     * Helper method for optimized backtracking with pruning.
     */
    private static void backtrackOptimized(List<List<Integer>> result,
            List<Integer> current,
            int start,
            int n,
            int k) {
        // 基本情况：组合已完成
        if (current.size() == k) {
            result.add(new ArrayList<>(current));
            return;
        }

        // 优化：提前终止
        // Remaining slots needed: k - current.size()
        // 可用的元素：n - start + 1
        // 如果没有足够的可用元素，则停止
        int remaining = k - current.size();
        int available = n - start + 1;
        if (available < remaining) {
            return;
        }

        // 尝试从start到n的每个数字
        for (int num = start; num <= n; num++) {
            current.add(num);
            backtrackOptimized(result, current, num + 1, n, k);
            current.remove(current.size() - 1);
        }
    }

    /*
     *
     * Test cases for combination generation
     */
    public static void main(String[] args) {
        System.out.println("=== Combination Backtracking Test Cases ===\n");

        // 测试用例 1: combine(4, 2)
        System.out.println("Test 1: combine(4, 2)");
        List<List<Integer>> result1 = combine(4, 2);
        System.out.println("Result (count=" + result1.size() + "):");
        for (List<Integer> combo : result1) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // 测试用例 2: combine(3, 1)
        System.out.println("Test 2: combine(3, 1)");
        List<List<Integer>> result2 = combine(3, 1);
        System.out.println("Result (count=" + result2.size() + "):");
        for (List<Integer> combo : result2) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // 测试用例 3: combine(3, 3)
        System.out.println("Test 3: combine(3, 3)");
        List<List<Integer>> result3 = combine(3, 3);
        System.out.println("Result (count=" + result3.size() + "):");
        for (List<Integer> combo : result3) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // 测试用例 4: combine(5, 3)
        System.out.println("Test 4: combine(5, 3)");
        List<List<Integer>> result4 = combine(5, 3);
        System.out.println("Result (count=" + result4.size() + "):");
        for (List<Integer> combo : result4) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // 测试用例 5: combineOptimized(6, 2)
        System.out.println("Test 5: combineOptimized(6, 2)");
        List<List<Integer>> result5 = combineOptimized(6, 2);
        System.out.println("Result (count=" + result5.size() + "):");
        for (List<Integer> combo : result5) {
            System.out.println("  " + combo);
        }
        System.out.println();

        // 测试用例 6: combineOptimized(5, 4)
        System.out.println("Test 6: combineOptimized(5, 4)");
        List<List<Integer>> result6 = combineOptimized(5, 4);
        System.out.println("Result (count=" + result6.size() + "):");
        for (List<Integer> combo : result6) {
            System.out.println("  " + combo);
        }
    }
}
