import java.util.*;

/*
*
 * 最长递增子序列 (LIS) - 动态规划应用
 *
 * 问题描述：
 * 给定一个无序整数数组，找出其中最长递增子序列的长度
 *
 * 动态规划方程：
 * dp[i] = 1 + max(dp[j]) for all j < i and arr[j] < arr[i]
 *
 * 时间复杂度: O(n²) 基础DP
 * 空间复杂度: O(n)
*/
public class Lis {
    /*
*
     * 最长递增子序列 - 基础DP方案
*/
    public static int longestIncreasingSubsequence(int[] arr) {
        if (arr.length == 0) return 0;

        int n = arr.length;

        // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
        int[] dp = new int[n];
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
        }

        // 构建 DP 表
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // 如果 arr[j] < arr[i]，可以扩展以 arr[j] 结尾的 LIS
                if (arr[j] < arr[i]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
        }

        // 找到最大值
        int maxLength = 0;
        for (int val : dp) {
            maxLength = Math.max(maxLength, val);
        }
        return maxLength;
    }

    /*
*
     * 最长递增子序列 - 优化方案 (O(n log n))
     * 使用二分查找和 tails 数组
*/
    public static int longestIncreasingSubsequenceOptimized(int[] arr) {
        if (arr.length == 0) return 0;

        List<Integer> tails = new ArrayList<>();

        for (int num : arr) {
            // 使用二分查找找到应该替换的位置
            int pos = Collections.binarySearch(tails, num);
            if (pos < 0) {
                pos = -(pos + 1);
            }

            if (pos == tails.size()) {
                // 找到了更长的递增子序列
                tails.add(num);
            } else {
                // 替换较大的元素，保持 tails 的最小性
                tails.set(pos, num);
            }
        }

        return tails.size();
    }

    /*
*
     * 最长递增子序列 - 返回子序列本身
*/
    public static Object[] longestIncreasingSubsequenceWithSequence(int[] arr) {
        if (arr.length == 0) return new Object[]{0, new ArrayList<>()};

        int n = arr.length;

        // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
        int[] dp = new int[n];
        // parent[i] 表示以 arr[i] 结尾的 LIS 中，前一个元素的索引
        int[] parent = new int[n];

        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            parent[i] = -1;
        }

        // 构建 DP 表
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }

        // 找到最长序列的结尾位置
        int maxLength = 0;
        int maxIndex = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] > maxLength) {
                maxLength = dp[i];
                maxIndex = i;
            }
        }

        // 反向追踪构建最长子序列
        List<Integer> lis = new ArrayList<>();
        int idx = maxIndex;
        while (idx != -1) {
            lis.add(0, arr[idx]);
            idx = parent[idx];
        }

        return new Object[]{maxLength, lis};
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 最长递增子序列 ===\n");

        // 测试用例1：基本数组
        System.out.println("1. 基本数组");
        int[] arr1 = {10, 9, 2, 5, 3, 7, 101, 18};
        System.out.println("数组: " + Arrays.toString(arr1));
        System.out.println("LIS 长度（DP）: " + longestIncreasingSubsequence(arr1));
        System.out.println("LIS 长度（优化）: " + longestIncreasingSubsequenceOptimized(arr1));
        System.out.println();

        // 测试用例2：已排序数组
        System.out.println("2. 已排序数组");
        int[] arr2 = {1, 3, 6, 7, 9, 4, 10, 5, 8};
        System.out.println("数组: " + Arrays.toString(arr2));
        Object[] result = longestIncreasingSubsequenceWithSequence(arr2);
        System.out.println("LIS 长度: " + result[0]);
        System.out.println("一个 LIS: " + result[1]);
        System.out.println();

        // 测试用例3：包含重复元素
        System.out.println("3. 包含重复元素");
        int[] arr3 = {1, 3, 3, 4, 5};
        System.out.println("数组: " + Arrays.toString(arr3));
        System.out.println("LIS 长度: " + longestIncreasingSubsequence(arr3));
        System.out.println();

        // 测试用例4：单调递减
        System.out.println("4. 单调递减");
        int[] arr4 = {5, 4, 3, 2, 1};
        System.out.println("数组: " + Arrays.toString(arr4));
        System.out.println("LIS 长度: " + longestIncreasingSubsequence(arr4));
    }
}
