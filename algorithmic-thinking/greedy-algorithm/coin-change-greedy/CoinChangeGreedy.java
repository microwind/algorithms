import java.util.*;

/*
 *
 * 零钱兑换问题 - 贪心算法
 *
 * 算法：
 * - 使用贪心策略：每次选择不超过剩余金额的最大面值硬币
 * - 持续用最大面值硬币去抵扣，直到金额为 0
 * - 注意：这种贪心解并不总是最优
 *
 * 时间复杂度：O(n log n)（排序）+ O(n)（循环）
 * 空间复杂度：O(n)（存储使用的硬币）
 *
 * 重要说明：该贪心算法并不适用于所有硬币体系！
 *
 * 贪心失败示例：
 * - coins = [1, 3, 4], amount = 6
 * - 贪心：4 + 1 + 1 = 3 枚硬币
 * - 最优：3 + 3 = 2 枚硬币
 */

class CoinChangeResult {
    int count;
    List<Integer> coins;

    CoinChangeResult(int count, List<Integer> coins) {
        this.count = count;
        this.coins = coins;
    }

    @Override
    public String toString() {
        if (count == -1) {
            return "Impossible";
        }
        return count + " coins: " + coins;
    }
}

public class CoinChangeGreedy {
    /*
     * 使用贪心算法求最少硬币数（不一定最优）
     *
     * @param coins 硬币面值数组
     * @param amount 目标金额
     * @return 包含硬币数量和具体硬币列表的结果
     */
    static CoinChangeResult coinChangeGreedy(int[] coins, int amount) {
        if (amount == 0) {
            return new CoinChangeResult(0, new ArrayList<>());
        }

        // 将硬币面值按降序排序
        Integer[] boxedCoins = Arrays.stream(coins).boxed().toArray(Integer[]::new);
        Arrays.sort(boxedCoins, Collections.reverseOrder());

        int count = 0;
        List<Integer> coinsUsed = new ArrayList<>();
        int remaining = amount;

        for (int coin : boxedCoins) {
            while (remaining >= coin) {
                remaining -= coin;
                coinsUsed.add(coin);
                count++;
            }
        }

        // 如果无法刚好凑成目标金额
        if (remaining != 0) {
            return new CoinChangeResult(-1, new ArrayList<>());
        }

        return new CoinChangeResult(count, coinsUsed);
    }

    /*
     * 使用动态规划求最少硬币数（一定最优，用于和贪心对比）
     *
     * @param coins 硬币面值数组
     * @param amount 目标金额
     * @return 包含硬币数量和具体硬币列表的结果
     */
    static CoinChangeResult coinChangeDP(int[] coins, int amount) {
        if (amount == 0) {
            return new CoinChangeResult(0, new ArrayList<>());
        }

        int[] dp = new int[amount + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        int[] parent = new int[amount + 1];
        Arrays.fill(parent, -1);
        // 对每个金额进行处理, 尝试使用每枚硬币
        for (int currAmount = 1; currAmount <= amount; currAmount++) {
            for (int coin : coins) {
                if (coin <= currAmount && dp[currAmount - coin] != Integer.MAX_VALUE) {
                    // 如果当前金额减去当前硬币面额的值的最少硬币数加1小于当前金额的最少硬币数，则更新当前金额的最少硬币数
                    if (dp[currAmount - coin] + 1 < dp[currAmount]) {
                        dp[currAmount] = dp[currAmount - coin] + 1;
                        parent[currAmount] = coin;
                    }
                }
            }
        }

        if (dp[amount] == Integer.MAX_VALUE) {
            return new CoinChangeResult(-1, new ArrayList<>());
        }

        // 还原一组最优解中使用的硬币
        List<Integer> coinsUsed = new ArrayList<>();
        int curr = amount;
        while (curr > 0) {
            int coin = parent[curr];
            coinsUsed.add(coin);
            curr -= coin;
        }

        return new CoinChangeResult(dp[amount], coinsUsed);
    }

    static void compareGreedyVsDP(int[] coins, int amount) {
        CoinChangeResult greedy = coinChangeGreedy(coins, amount);
        CoinChangeResult dp = coinChangeDP(coins, amount);

        System.out.println("Coins: " + Arrays.toString(coins) + ", Amount: " + amount);
        System.out.println("Greedy: " + greedy);
        System.out.println("DP:     " + dp);
        if (greedy.count != -1 && dp.count != -1) {
            if (greedy.count == dp.count) {
                System.out.println("✓ Greedy is optimal for this input");
            } else {
                System.out.println("✗ Greedy is suboptimal (difference: " + (greedy.count - dp.count) + ")");
            }
        }
        System.out.println();
    }

    static void testStandardCoins() {
        System.out.println("\n[Test 1] US Coins (greedy optimal)");
        CoinChangeResult result = coinChangeGreedy(new int[]{1, 5, 10, 25}, 41);
        System.out.println("Coins: [1, 5, 10, 25], Amount: 41");
        System.out.println("Result: " + result);
    }

    static void testGreedyFails1() {
        System.out.println("\n[Test 2] Greedy fails case");
        compareGreedyVsDP(new int[]{1, 3, 4}, 6);
    }

    static void testGreedyFails2() {
        System.out.println("\n[Test 3] Another greedy fails case");
        compareGreedyVsDP(new int[]{1, 7, 10}, 11);
    }

    static void testGreedyOptimal() {
        System.out.println("\n[Test 4] Greedy optimal case");
        compareGreedyVsDP(new int[]{1, 5, 10, 25}, 30);
    }

    static void testImpossibleAmount() {
        System.out.println("\n[Test 5] Impossible amount (no 1-cent coin)");
        CoinChangeResult result = coinChangeGreedy(new int[]{5, 10, 25}, 11);
        System.out.println("Coins: [5, 10, 25], Amount: 11");
        System.out.println("Result: " + result);
    }

    static void testZeroAmount() {
        System.out.println("\n[Test 6] Zero amount");
        CoinChangeResult result = coinChangeGreedy(new int[]{1, 5, 10}, 0);
        System.out.println("Coins: [1, 5, 10], Amount: 0");
        System.out.println("Result: " + result);
    }

    static void testSingleCoinType() {
        System.out.println("\n[Test 7] Single coin type");
        compareGreedyVsDP(new int[]{7}, 21);
    }

    static void testLargeAmount() {
        System.out.println("\n[Test 8] Large amount");
        CoinChangeResult result = coinChangeGreedy(new int[]{1, 5, 10, 25, 50}, 158);
        System.out.println("Coins: [1, 5, 10, 25, 50], Amount: 158");
        System.out.println("Result: " + result);
    }

    static void testNonStandardCoins() {
        System.out.println("\n[Test 9] Non-standard coins where greedy fails");
        compareGreedyVsDP(new int[]{1, 3, 4, 5}, 13);
    }

    static void testEdgeCase() {
        System.out.println("\n[Test 10] Larger denomination problem");
        compareGreedyVsDP(new int[]{2, 5, 10}, 11);
    }

    public static void main(String[] args) {
        System.out.println("==================================================");
        System.out.println("COIN CHANGE - Greedy vs DP Comparison (Java)");
        System.out.println("==================================================");

        testStandardCoins();
        testGreedyFails1();
        testGreedyFails2();
        testGreedyOptimal();
        testImpossibleAmount();
        testZeroAmount();
        testSingleCoinType();
        testLargeAmount();
        testNonStandardCoins();
        testEdgeCase();
    }
}
