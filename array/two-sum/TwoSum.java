import java.util.HashMap;
import java.util.Map;

/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 两数之和算法 - Java实现
 * 
 * 算法原理：
 * 使用哈希表辅助查找。遍历数组时，对于每个元素，计算目标值与当前元素的差值（补数），
 * 检查补数是否已在哈希表中。如果在，则找到答案；否则将当前元素存入哈希表。
 * 
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(n) - 哈希表存储
 */
public class TwoSum {
    
    /**
     * 两数之和
     * @param nums - 输入数组
     * @param target - 目标和
     * @return 返回两个数的索引数组
     */
    public static int[] twoSum(int[] nums, int target) {
        // 使用HashMap存储已遍历的元素及其索引
        Map<Integer, Integer> map = new HashMap<>();
        
        for (int i = 0; i < nums.length; i++) {
            // 计算补数
            int complement = target - nums[i];
            
            // 检查补数是否已在哈希表中
            if (map.containsKey(complement)) {
                // 找到答案，返回两个索引
                return new int[]{map.get(complement), i};
            }
            
            // 将当前元素及其索引存入哈希表
            map.put(nums[i], i);
        }
        
        // 未找到答案
        return new int[0];
    }
    
    public static void main(String[] args) {
        int[] nums = {2, 7, 11, 15};
        int target = 9;
        
        int[] result = twoSum(nums, target);
        
        if (result.length > 0) {
            System.out.println("目标值: " + target);
            System.out.println("结果索引: [" + result[0] + ", " + result[1] + "]");
            System.out.println("对应数值: " + nums[result[0]] + " + " + nums[result[1]] + " = " + target);
        } else {
            System.out.println("未找到答案");
        }
    }
}

/*
 * 输出结果：
 * 目标值: 9
 * 结果索引: [0, 1]
 * 对应数值: 2 + 7 = 9
 */
