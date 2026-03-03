/*
*
 * 硬币兑换问题 (Coin Change) - 动态规划应用
 *
 * 问题描述：
 * 给定不同面值的硬币和一个金额，找出使用最少数量的硬币凑出该金额的方法
 *
 * 动态规划方程：
 * dp[i] = min(dp[i], dp[i-coin] + 1) for each coin
 *
 * 时间复杂度: O(n * amount)
 * 空间复杂度: O(amount)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
*
 * 硬币兑换 - 求最少硬币数量
 *
 * @param coins 硬币面值数组
 * @param coinsSize 硬币数量
 * @param amount 需要凑出的金额
 * @return 最少需要的硬币数量，如果无法凑出返回 -1
*/
int coinChange(int *coins, int coinsSize, int amount) {
    if (amount == 0) return 0;

    // dp[i] 表示凑出金额 i 需要的最少硬币数
    // 初始化为 INT_MAX，表示无法凑出
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }

    // 对每个金额进行处理
    for (int i = 1; i <= amount; i++) {
        // 尝试使用每枚硬币
        for (int j = 0; j < coinsSize; j++) {
            int coin = coins[j];
            if (coin <= i && dp[i - coin] != INT_MAX) {
                // 如果可以使用该硬币，更新最少数量
                dp[i] = MIN(dp[i], dp[i - coin] + 1);
            }
        }
    }

    int result = (dp[amount] == INT_MAX) ? -1 : dp[amount];
    free(dp);
    return result;
}

/*
*
 * 硬币兑换 - 返回具体的硬币组合
 *
 * @param coins 硬币面值数组
 * @param coinsSize 硬币数量
 * @param amount 需要凑出的金额
 * @param out_coins 输出数组，存储硬币组合
 * @return 最少需要的硬币数量，如果无法凑出返回 -1
*/
int coinChangeWithCoins(int *coins, int coinsSize, int amount, int *out_coins) {
    if (amount == 0) return 0;

    // dp[i] 表示凑出金额 i 需要的最少硬币数
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    // parent[i] 表示凑出金额 i 时使用的硬币面值
    int *parent = (int *)malloc((amount + 1) * sizeof(int));

    dp[0] = 0;
    parent[0] = -1;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
        parent[i] = -1;
    }

    // 对每个金额进行处理
    for (int i = 1; i <= amount; i++) {
        // 尝试使用每枚硬币
        for (int j = 0; j < coinsSize; j++) {
            int coin = coins[j];
            if (coin <= i && dp[i - coin] != INT_MAX && dp[i - coin] + 1 < dp[i]) {
                dp[i] = dp[i - coin] + 1;
                parent[i] = coin;
            }
        }
    }

    int result = -1;
    if (dp[amount] != INT_MAX) {
        result = dp[amount];
        // 反向追踪构建硬币组合
        int idx = amount;
        int pos = 0;
        while (idx > 0) {
            int coin = parent[idx];
            out_coins[pos++] = coin;
            idx -= coin;
        }
    }

    free(dp);
    free(parent);
    return result;
}

/*
*
 * 测试函数
*/
int main() {
    printf("=== 硬币兑换问题 ===\n\n");

    // 测试用例1：基本硬币兑换
    printf("1. 基本硬币兑换\n");
    int coins1[] = {1, 2, 5};
    int coinsSize1 = 3;
    int amount1 = 5;
    printf("硬币面值: ");
    for (int i = 0; i < coinsSize1; i++) printf("%d ", coins1[i]);
    printf("\n需要凑出的金额: %d\n", amount1);
    printf("最少硬币数: %d\n\n", coinChange(coins1, coinsSize1, amount1));

    // 测试用例2：返回具体的硬币组合
    printf("2. 返回具体的硬币组合\n");
    int coins2[] = {1, 2, 5};
    int coinsSize2 = 3;
    int amount2 = 7;
    printf("硬币面值: ");
    for (int i = 0; i < coinsSize2; i++) printf("%d ", coins2[i]);
    printf("\n需要凑出的金额: %d\n", amount2);

    int out_coins[100];
    int count = coinChangeWithCoins(coins2, coinsSize2, amount2, out_coins);
    printf("最少硬币数: %d\n", count);
    if (count > 0) {
        printf("硬币组合: ");
        for (int i = 0; i < count; i++) printf("%d ", out_coins[i]);
        printf("\n\n");
    } else {
        printf("\n\n");
    }

    // 测试用例3：无法凑出的金额
    printf("3. 无法凑出的金额\n");
    int coins3[] = {2, 5};
    int coinsSize3 = 2;
    int amount3 = 3;
    printf("硬币面值: ");
    for (int i = 0; i < coinsSize3; i++) printf("%d ", coins3[i]);
    printf("\n需要凑出的金额: %d\n", amount3);
    printf("最少硬币数: %d\n\n", coinChange(coins3, coinsSize3, amount3));

    // 测试用例4：更大的金额
    printf("4. 更大的金额\n");
    int coins4[] = {1, 3, 4};
    int coinsSize4 = 3;
    int amount4 = 10;
    printf("硬币面值: ");
    for (int i = 0; i < coinsSize4; i++) printf("%d ", coins4[i]);
    printf("\n需要凑出的金额: %d\n", amount4);

    int out_coins4[100];
    int count4 = coinChangeWithCoins(coins4, coinsSize4, amount4, out_coins4);
    printf("最少硬币数: %d\n", count4);
    if (count4 > 0) {
        printf("硬币组合: ");
        for (int i = 0; i < count4; i++) printf("%d ", out_coins4[i]);
        printf("\n");
    }

    return 0;
}
