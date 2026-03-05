package randomalgorithm.shuffle;

import java.util.Arrays;
import java.util.Random;

/**
 * 洗牌算法（Shuffle）- Java 版本
 *
 * 使用 Fisher–Yates 洗牌算法，保证所有排列等概率出现。
 * 提供两种形式：
 * 1. inPlaceShuffle：原地洗牌，直接修改数组
 * 2. shuffledCopy：返回打乱后的新数组，原数组不变
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1) 原地；O(n) 新数组版本
 */
public class Shuffle {

    private static final Random RANDOM = new Random();

    /**
     * 原地洗牌：直接修改 nums 数组
     *
     * @param nums 待打乱的数组
     */
    public static void inPlaceShuffle(int[] nums) {
        // 从数组末尾开始，逐个与前面随机位置交换
        for (int i = nums.length - 1; i > 0; i--) {
            // 在 [0, i] 范围内生成随机下标 j
            int j = RANDOM.nextInt(i + 1);
            // 交换 nums[i] 和 nums[j]
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }

    /**
     * 生成新数组的洗牌：原数组不变
     *
     * @param nums 原数组
     * @return 打乱后的新数组
     */
    public static int[] shuffledCopy(int[] nums) {
        int[] copy = Arrays.copyOf(nums, nums.length);
        inPlaceShuffle(copy);
        return copy;
    }

    public static void main(String[] args) {
        System.out.println("========== Shuffle (Java) ==========");
        int[] original = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        System.out.println("原数组: " + Arrays.toString(original));

        int[] arr1 = Arrays.copyOf(original, original.length);
        inPlaceShuffle(arr1);
        System.out.println("原地洗牌结果: " + Arrays.toString(arr1));

        int[] arr2 = shuffledCopy(original);
        System.out.println("新数组洗牌结果: " + Arrays.toString(arr2));
        System.out.println("原数组保持不变: " + Arrays.toString(original));
    }
}

