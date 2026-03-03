import java.util.*;

/*
*
 * 单数问题 - 使用XOR技巧找到单个数字
 *
 * 问题：给定一个整数数组，其中除了一个元素出现一次外，
 * 其他元素都出现两次。找到只出现一次的那个元素。
 *
 * 核心思想：
 * - XOR 的性质：a ^ a = 0, a ^ 0 = a
 * - 对所有元素进行XOR操作，两个相同的数会相消，留下单个数字
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/
public class SingleNumber {
    /*
*
     * 使用XOR技巧找到单个数字
     *
     * 原理：
     * - 0 ^ x = x
     * - x ^ x = 0
     * - XOR满足交换律和结合律
     * - 对所有数字XOR，重复数字相消，留下单个数字
     *
     * @param nums 输入数组
     * @return 单个数字
*/
    public static int singleNumberXor(int[] nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }

    /*
*
     * 使用哈希表统计频数（备选方案）
     *
     * @param nums 输入数组
     * @return 单个数字
*/
    public static int singleNumberHash(int[] nums) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }

        for (Map.Entry<Integer, Integer> entry : count.entrySet()) {
            if (entry.getValue() == 1) {
                return entry.getKey();
            }
        }

        return -1;
    }

    /*
*
     * 排序后相邻比较（备选方案）
     *
     * @param nums 输入数组
     * @return 单个数字
*/
    public static int singleNumberSort(int[] nums) {
        Arrays.sort(nums);

        for (int i = 0; i < nums.length - 1; i += 2) {
            if (nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }

        return nums[nums.length - 1];
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 单数问题 ===\n");

        // 测试用例1：基本用例
        System.out.println("1. 基本用例:");
        int[] nums1 = {2, 2, 1};
        System.out.println("  数组: " + Arrays.toString(nums1));
        System.out.println("  单数: " + singleNumberXor(nums1));
        System.out.println();

        // 测试用例2：较大数组
        System.out.println("2. 较大数组:");
        int[] nums2 = {4, 1, 2, 1, 2};
        System.out.println("  数组: " + Arrays.toString(nums2));
        System.out.println("  单数: " + singleNumberXor(nums2));
        System.out.println();

        // 测试用例3：负数
        System.out.println("3. 包含负数:");
        int[] nums3 = {-1, -1, 5, 5, 3};
        System.out.println("  数组: " + Arrays.toString(nums3));
        System.out.println("  单数: " + singleNumberXor(nums3));
        System.out.println();

        // 测试用例4：单个元素
        System.out.println("4. 单个元素:");
        int[] nums4 = {42};
        System.out.println("  数组: " + Arrays.toString(nums4));
        System.out.println("  单数: " + singleNumberXor(nums4));
        System.out.println();

        // 性能对比
        System.out.println("5. 不同方法的结果比较:");
        int[] nums5 = {7, 7, 8, 8, 9};
        System.out.println("  数组: " + Arrays.toString(nums5));
        System.out.println("  XOR方法: " + singleNumberXor(nums5));
        System.out.println("  哈希方法: " + singleNumberHash(nums5));
        System.out.println("  排序方法: " + singleNumberSort(nums5));
    }
}
