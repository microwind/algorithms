import java.util.*;

/*
*
 * 硬币兑换问题 (Coin Change) - 动态规划应用
 *
 * 问题描述：
 * 给定不同面值的硬币和一个金额，找出使用最少数量的硬币凑出该金额
 *
 * 动态规划方程：
 * dp[i] = min(dp[i], dp[i-coin] + 1) for each coin
 *
 * 时间复杂度: O(n * amount)
 * 空间复杂度: O(amount)
*/
public class CoinChange {
    /*
*
     * 硬币兑换 - 求最少硬币数量
*/
    public static int coinChange(int[] coins, int amount) {
        if (amount == 0) return 0;

        // dp[i] 表示凑出金额 i 需要的最少硬币数
        // 初始化为 amount + 1，表示无法凑出
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;

        // 对每个金额进行处理
        for (int i = 1; i <= amount; i++) {
            // 尝试使用每枚硬币
            for (int coin : coins) {
                if (coin <= i) {
                    // 如果可以使用该硬币，更新最少数量
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        // 如果 dp[amount] > amount，说明无法凑出
        return dp[amount] > amount ? -1 : dp[amount];
    }

    /*
*
     * 硬币兑换 - 返回具体的硬币组合
*/
    public static Object[] coinChangeWithCoins(int[] coins, int amount) {
        if (amount == 0) return new Object[]{0, new ArrayList<>()};

        // dp[i] 表示凑出金额 i 需要的最少硬币数
        int[] dp = new int[amount + 1];
        // parent[i] 表示凑出金额 i 时使用的硬币面值
        int[] parent = new int[amount + 1];

        Arrays.fill(dp, amount + 1);
        Arrays.fill(parent, -1);
        dp[0] = 0;

        // 对每个金额进行处理
        for (int i = 1; i <= amount; i++) {
            // 尝试使用每枚硬币
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    parent[i] = coin;
                }
            }
        }

        // 如果无法凑出
        if (dp[amount] > amount) {
            return new Object[]{-1, new ArrayList<>()};
        }

        // 反向追踪构建硬币组合
        List<Integer> result = new ArrayList<>();
        int idx = amount;
        while (idx > 0) {
            int coin = parent[idx];
            result.add(coin);
            idx -= coin;
        }

        return new Object[]{dp[amount], result};
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 硬币兑换问题 ===\n");

        // 测试用例1：基本硬币兑换
        System.out.println("1. 基本硬币兑换");
        int[] coins1 = {1, 2, 5};
        int amount1 = 5;
        System.out.println("硬币面值: " + Arrays.toString(coins1));
        System.out.println("需要凑出的金额: " + amount1);
        System.out.println("最少硬币数: " + coinChange(coins1, amount1) + "\n");

        // 测试用例2：返回具体的硬币组合
        System.out.println("2. 返回具体的硬币组合");
        int[] coins2 = {1, 2, 5};
        int amount2 = 7;
        System.out.println("硬币面值: " + Arrays.toString(coins2));
        System.out.println("需要凑出的金额: " + amount2);
        Object[] result2 = coinChangeWithCoins(coins2, amount2);
        System.out.println("最少硬币数: " + result2[0]);
        System.out.println("硬币组合: " + result2[1] + "\n");

        // 测试用例3：无法凑出的金额
        System.out.println("3. 无法凑出的金额");
        int[] coins3 = {2, 5};
        int amount3 = 3;
        System.out.println("硬币面值: " + Arrays.toString(coins3));
        System.out.println("需要凑出的金额: " + amount3);
        System.out.println("最少硬币数: " + coinChange(coins3, amount3) + "\n");

        // 测试用例4：更大的金额
        System.out.println("4. 更大的金额");
        int[] coins4 = {1, 3, 4};
        int amount4 = 10;
        System.out.println("硬币面值: " + Arrays.toString(coins4));
        System.out.println("需要凑出的金额: " + amount4);
        Object[] result4 = coinChangeWithCoins(coins4, amount4);
        System.out.println("最少硬币数: " + result4[0]);
        System.out.println("硬币组合: " + result4[1]);
    }
}
