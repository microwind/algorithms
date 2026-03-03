import java.util.*;

/*
*
 * 0-1 背包问题 - 动态规划的经典应用
 *
 * 时间复杂度: O(n * W)
 * 空间复杂度: O(n * W) 或 O(W)
*/
public class Knapsack {
    /*
*
     * 0-1 背包问题 - 二维 DP
*/
    public static int knapsack(int[] weights, int[] values, int capacity) {
        int n = weights.length;

        // dp[i][w] 表示前 i 件物品，容量为 w 时的最大价值
        int[][] dp = new int[n + 1][capacity + 1];

        // 填充 dp 表
        for (int i = 1; i <= n; i++) {
            int weight = weights[i - 1];
            int value = values[i - 1];

            for (int w = 0; w <= capacity; w++) {
                if (weight <= w) {
                    // 选择或不选择
                    dp[i][w] = Math.max(
                        dp[i - 1][w],
                        dp[i - 1][w - weight] + value
                    );
                } else {
                    // 物品太重
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        return dp[n][capacity];
    }

    /*
*
     * 0-1 背包问题 - 空间优化版本
*/
    public static int knapsackOptimized(int[] weights, int[] values, int capacity) {
        int n = weights.length;

        // dp[w] 表示容量为 w 时的最大价值
        int[] dp = new int[capacity + 1];

        // 处理每件物品
        for (int i = 0; i < n; i++) {
            int weight = weights[i];
            int value = values[i];

            // 从后向前遍历容量
            for (int w = capacity; w >= weight; w--) {
                dp[w] = Math.max(dp[w], dp[w - weight] + value);
            }
        }

        return dp[capacity];
    }

    /*
*
     * 0-1 背包问题 - 返回选中物品
*/
    public static Object[] knapsackWithItems(int[] weights, int[] values, int capacity) {
        int n = weights.length;

        // 构建 dp 表
        int[][] dp = new int[n + 1][capacity + 1];

        for (int i = 1; i <= n; i++) {
            int weight = weights[i - 1];
            int value = values[i - 1];

            for (int w = 0; w <= capacity; w++) {
                if (weight <= w) {
                    dp[i][w] = Math.max(
                        dp[i - 1][w],
                        dp[i - 1][w - weight] + value
                    );
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // 反向追踪选中的物品
        List<Integer> selected = new ArrayList<>();
        int w = capacity;
        for (int i = n; i > 0; i--) {
            if (dp[i][w] != dp[i - 1][w]) {
                selected.add(i - 1);
                w -= weights[i - 1];
            }
        }

        Collections.reverse(selected);

        return new Object[]{dp[n][capacity], selected};
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 0-1 背包问题 ===\n");

        // 测试用例1：基本背包问题
        System.out.println("1. 基本背包问题");
        int[] weights = {2, 3, 4, 5};
        int[] values = {3, 4, 5, 6};
        int capacity = 8;

        System.out.println("物品重量: " + Arrays.toString(weights));
        System.out.println("物品价值: " + Arrays.toString(values));
        System.out.println("背包容量: " + capacity);

        int maxValue = knapsack(weights, values, capacity);
        System.out.println("最大价值: " + maxValue + "\n");

        // 测试用例2：空间优化版本
        System.out.println("2. 空间优化版本");
        int maxValueOpt = knapsackOptimized(weights, values, capacity);
        System.out.println("最大价值（优化）: " + maxValueOpt + "\n");

        // 测试用例3：返回选中物品
        System.out.println("3. 返回选中物品");
        Object[] result = knapsackWithItems(weights, values, capacity);
        System.out.println("最大价值: " + result[0]);
        System.out.println("选中物品索引: " + result[1] + "\n");

        // 测试用例4：容量较大
        System.out.println("4. 容量较大的背包");
        int[] weights2 = {1, 2, 3, 4, 5};
        int[] values2 = {1, 3, 5, 7, 9};
        int capacity2 = 10;

        System.out.println("物品重量: " + Arrays.toString(weights2));
        System.out.println("物品价值: " + Arrays.toString(values2));
        System.out.println("背包容量: " + capacity2);

        int maxValue2 = knapsack(weights2, values2, capacity2);
        System.out.println("最大价值: " + maxValue2);
    }
}
