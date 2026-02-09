import java.util.*;

/**
 * Coin Change - Greedy Approach
 *
 * Algorithm:
 * - Use greedy approach: always select the largest coin possible
 * - Keep subtracting the largest coin until amount is 0
 * - Does NOT always give optimal solution
 *
 * Time Complexity: O(n log n) - sorting + O(n) for the loop
 * Space Complexity: O(n) - for storing coins used
 *
 * Important: This greedy approach is NOT optimal for all coin systems!
 *
 * Example where greedy fails:
 * - coins = [1, 3, 4], amount = 6
 * - Greedy: 4 + 1 + 1 = 3 coins
 * - Optimal: 3 + 3 = 2 coins
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
    /**
     * Find minimum coins using greedy approach (not always optimal)
     *
     * @param coins Array of coin denominations
     * @param amount Target amount to make
     * @return CoinChangeResult with count and coins used
     */
    static CoinChangeResult coinChangeGreedy(int[] coins, int amount) {
        if (amount == 0) {
            return new CoinChangeResult(0, new ArrayList<>());
        }

        // Sort coins in descending order
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

        // If we couldn't make exact amount
        if (remaining != 0) {
            return new CoinChangeResult(-1, new ArrayList<>());
        }

        return new CoinChangeResult(count, coinsUsed);
    }

    /**
     * Find minimum coins using Dynamic Programming (always optimal)
     * Provided for comparison with greedy approach
     *
     * @param coins Array of coin denominations
     * @param amount Target amount
     * @return CoinChangeResult with count and coins used
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

        for (int currAmount = 1; currAmount <= amount; currAmount++) {
            for (int coin : coins) {
                if (coin <= currAmount && dp[currAmount - coin] != Integer.MAX_VALUE) {
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

        // Reconstruct the solution
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
