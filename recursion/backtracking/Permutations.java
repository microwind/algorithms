import java.util.ArrayList;
import java.util.List;

/**
 * 回溯算法 - 全排列 (Permutations)
 * 使用递归生成数组的所有排列
 */
public class Permutations {
    
    /**
     * 生成数组的所有排列
     * @param nums 输入数组
     * @return 所有排列的列表
     */
    public List<List<Integer>> permutations(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, new ArrayList<>(), result);
        return result;
    }
    
    /**
     * 回溯生成排列
     * @param nums 输入数组
     * @param current 当前排列
     * @param result 结果列表
     */
    private void backtrack(int[] nums, List<Integer> current, List<List<Integer>> result) {
        // 基础情况：当前排列长度等于输入数组长度
        if (current.size() == nums.length) {
            result.add(new ArrayList<>(current));
            return;
        }
        
        // 递归情况：尝试每个元素
        for (int i = 0; i < nums.length; i++) {
            // 如果元素已经在当前排列中，跳过
            if (current.contains(nums[i])) {
                continue;
            }
            
            // 选择元素
            current.add(nums[i]);
            
            // 递归：继续处理
            backtrack(nums, current, result);
            
            // 回溯：撤销选择
            current.remove(current.size() - 1);
        }
    }
    
    public static void main(String[] args) {
        Permutations solution = new Permutations();
        int[] nums = {1, 2, 3};
        
        List<List<Integer>> result = solution.permutations(nums);
        
        System.out.println("数组 [1, 2, 3] 的所有排列:");
        
        int count = 1;
        for (List<Integer> permutation : result) {
            System.out.println("  " + count + ". " + permutation);
            count++;
        }
        
        System.out.println("\n共 " + result.size() + " 种排列");
    }
}
