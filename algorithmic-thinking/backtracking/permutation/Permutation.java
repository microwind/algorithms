import java.util.*;

/*
使用回溯生成排列 (Java Implementation)

算法说明:
- 使用回溯生成列表的所有排列
- 使用 ArrayList 实现动态大小调整和灵活性
- 在每个递归级别，尝试每个未使用的元素
- 通过从当前排列中移除元素来回溯

时间复杂度：O(n! * n) - n! 个排列，每个需要 O(n) 时间复制
空间复杂度：O(n) - 递归深度（不计算输出）

示例:
    permute([1, 2, 3]) 返回 [[1,2,3], [1,3,2], [2,1,3], ...]
*/

public class Permutation {

    /*
     * 使用回溯生成列表的所有排列。
     *
     * @param nums 要排列的整数列表
     * @return 所有排列的列表
     */
    public static List<List<Integer>> permute(List<Integer> nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), nums);
        return result;
    }

    /*
     * 回溯的辅助方法。
     *
     * @param result 存储所有排列的列表
     * @param current 正在构建的当前排列
     * @param remaining 未使用的元素
     */
    private static void backtrack(List<List<Integer>> result,
                                   List<Integer> current,
                                   List<Integer> remaining) {
        // 基础情况：所有元素都已使用，添加到结果中
        if (remaining.isEmpty()) {
            result.add(new ArrayList<>(current));
            return;
        }

        // 尝试每个剩余元素作为下一个元素
        for (int i = 0; i < remaining.size(); i++) {
            // 选择：将 remaining.get(i) 添加到当前排列
            int num = remaining.get(i);
            current.add(num);

            // 探索：递归构建排列的其余部分
            List<Integer> newRemaining = new ArrayList<>(remaining);
            newRemaining.remove(i);
            backtrack(result, current, newRemaining);

            // 撤销：移除元素以进行回溯
            current.remove(current.size() - 1);
        }
    }

    /*
     * 使用数组原位置交换的优化排列。
     *
     * 时间复杂度：O(n! * n)
     * 空间复杂度：O(n)
     */
    public static List<List<Integer>> permuteOptimized(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrackSwap(result, nums, 0);
        return result;
    }

    /*
     * 原位置交换回溯的辅助方法。
     *
     * @param result 存储所有排列的列表
     * @param nums 要排列的数组
     * @param index 当前排列的位置
     */
    private static void backtrackSwap(List<List<Integer>> result, int[] nums, int index) {
        // 基础情况：到了数组的末举
        if (index == nums.length) {
            List<Integer> perm = new ArrayList<>();
            for (int num : nums) {
                perm.add(num);
            }
            result.add(perm);
            return;
        }

        // 尝试从 index 开始的每个元素作为下一个元素
        for (int i = index; i < nums.length; i++) {
            // 选择：交换元素
            int temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;

            // 探索：排列余下部分
            backtrackSwap(result, nums, index + 1);

            // 撤销：交换回师
            temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;
        }
    }

    /*
     * 排列生成的测试用例
     */
    public static void main(String[] args) {
        System.out.println("=== 排列回溯测试用例 ===");

        // 测试用例 1: [1, 2, 3]
        System.out.println("测试 1: permute([1, 2, 3])");
        List<Integer> test1 = Arrays.asList(1, 2, 3);
        List<List<Integer>> result1 = permute(test1);
        System.out.println("结果（共 " + result1.size() + " 个）:");
        for (List<Integer> perm : result1) {
            System.out.println("  " + perm);
        }
        System.out.println();

        // 测试用例 2: [1, 2]
        System.out.println("测试 2: permute([1, 2])");
        List<Integer> test2 = Arrays.asList(1, 2);
        List<List<Integer>> result2 = permute(test2);
        System.out.println("结果（共 " + result2.size() + " 个）:");
        for (List<Integer> perm : result2) {
            System.out.println("  " + perm);
        }
        System.out.println();

        // 测试用例 3: [1]
        System.out.println("测试 3: permute([1])");
        List<Integer> test3 = Arrays.asList(1);
        List<List<Integer>> result3 = permute(test3);
        System.out.println("结果（共 " + result3.size() + " 个）:");
        for (List<Integer> perm : result3) {
            System.out.println("  " + perm);
        }
        System.out.println();

        // 测试用例 4: 新优化版本 [1, 2, 3, 4]
        System.out.println("测试 4: permuteOptimized([1, 2, 3, 4])");
        int[] test4 = {1, 2, 3, 4};
        List<List<Integer>> result4 = permuteOptimized(test4);
        System.out.println("结果（共 " + result4.size() + " 个）:");
        System.out.println("前 3 个排列:");
        for (int i = 0; i < 3; i++) {
            System.out.println("  " + result4.get(i));
        }
        System.out.println("后 3 个排列:");
        for (int i = result4.size() - 3; i < result4.size(); i++) {
            System.out.println("  " + result4.get(i));
        }
        System.out.println();

        // 测试用例 5: 优化版本
        System.out.println("测试 5: permuteOptimized([10, 20, 30])");
        int[] test5 = {10, 20, 30};
        List<List<Integer>> result5 = permuteOptimized(test5);
        System.out.println("结果（共 " + result5.size() + " 个）:");
        for (List<Integer> perm : result5) {
            System.out.println("  " + perm);
        }
    }
}
