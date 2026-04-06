import java.util.ArrayList;
import java.util.List;

/**
 * 回溯算法 - 子集生成 (Subsets)
 * 使用递归生成数组的所有子集
 */
public class Subsets {
    
    /**
     * 生成数组的所有子集
     * @param nums 输入数组
     * @return 所有子集的列表
     */
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, 0, new ArrayList<>(), result);
        return result;
    }
    
    /**
     * 回溯生成子集
     * @param nums 输入数组
     * @param start 开始位置
     * @param current 当前子集
     * @param result 结果列表
     */
    private void backtrack(int[] nums, int start, List<Integer> current, List<List<Integer>> result) {
        // 每次递归都将当前子集加入结果
        result.add(new ArrayList<>(current));
        
        // 从start开始尝试每个元素
        for (int i = start; i < nums.length; i++) {
            // 选择元素
            current.add(nums[i]);
            
            // 递归：继续处理后面的元素
            backtrack(nums, i + 1, current, result);
            
            // 回溯：撤销选择
            current.remove(current.size() - 1);
        }
    }
    
    public static void main(String[] args) {
        Subsets solution = new Subsets();
        int[] nums = {1, 2, 3};
        
        List<List<Integer>> result = solution.subsets(nums);
        
        System.out.println("数组 [1, 2, 3] 的所有子集:");
        System.out.println("共 " + result.size() + " 个子集\n");
        
        int count = 1;
        for (List<Integer> subset : result) {
            System.out.println("  " + count + ". " + subset);
            count++;
        }
        
        System.out.println("\n递归过程可视化:");
        System.out.println("        []");
        System.out.println("       / | \\");
        System.out.println("     [1] [2] [3]");
        System.out.println("    /  \\      |");
        System.out.println("  [1,2] [1,3] [2,3]");
        System.out.println("   /");
        System.out.println("[1,2,3]");
    }
}
