#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
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

typedef struct {
    int coin;
    int count;
} CoinResult;

/* Comparator for sorting coins in descending order */
int compare_descending(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

/*
 * Find minimum coins using greedy approach (not always optimal)
 *
 * Args:
 *   coins: Array of coin denominations
 *   coin_count: Number of coin types
 *   amount: Target amount to make
 *   used_coins: Array to store coins used
 *
 * Returns:
 *   Number of coins used, or -1 if impossible
 */
int coin_change_greedy(int *coins, int coin_count, int amount, int *used_coins) {
    if (amount == 0) {
        return 0;
    }

    /* Sort coins in descending order */
    qsort(coins, coin_count, sizeof(int), compare_descending);

    int total_coins = 0;
    int remaining = amount;

    for (int i = 0; i < coin_count; i++) {
        while (remaining >= coins[i]) {
            remaining -= coins[i];
            if (used_coins != NULL) {
                used_coins[total_coins] = coins[i];
            }
            total_coins++;
        }
    }

    /* If we couldn't make exact amount */
    if (remaining != 0) {
        return -1;
    }

    return total_coins;
}

void test_standard_coins() {
    printf("\n[Test 1] US Coins (greedy optimal)\n");

    int coins[] = {1, 5, 10, 25};
    int coin_count = 4;
    int amount = 41;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [1, 5, 10, 25], Amount: %d\n", amount);
    printf("Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

void test_greedy_fails() {
    printf("\n[Test 2] Case where greedy fails\n");

    int coins[] = {1, 3, 4};
    int coin_count = 3;
    int amount = 6;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [1, 3, 4], Amount: %d\n", amount);
    printf("Greedy Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
        printf("Note: Optimal would be 2 coins (3+3)\n");
    }
}

void test_another_greedy_fails() {
    printf("\n[Test 3] Another greedy fails case\n");

    int coins[] = {1, 7, 10};
    int coin_count = 3;
    int amount = 11;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [1, 7, 10], Amount: %d\n", amount);
    printf("Greedy Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

void test_greedy_optimal() {
    printf("\n[Test 4] Greedy optimal case\n");

    int coins[] = {1, 5, 10, 25};
    int coin_count = 4;
    int amount = 30;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [1, 5, 10, 25], Amount: %d\n", amount);
    printf("Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

void test_impossible_amount() {
    printf("\n[Test 5] Impossible amount (no 1-cent coin)\n");

    int coins[] = {5, 10, 25};
    int coin_count = 3;
    int amount = 11;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [5, 10, 25], Amount: %d\n", amount);
    printf("Result: %d (impossible)\n", count);
}

void test_zero_amount() {
    printf("\n[Test 6] Zero amount\n");

    int coins[] = {1, 5, 10};
    int coin_count = 3;
    int amount = 0;

    int count = coin_change_greedy(coins, coin_count, amount, NULL);

    printf("Coins: [1, 5, 10], Amount: %d\n", amount);
    printf("Result: %d coins\n", count);
}

void test_single_coin_type() {
    printf("\n[Test 7] Single coin type\n");

    int coins[] = {7};
    int coin_count = 1;
    int amount = 21;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [7], Amount: %d\n", amount);
    printf("Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

void test_large_amount() {
    printf("\n[Test 8] Large amount\n");

    int coins[] = {1, 5, 10, 25, 50};
    int coin_count = 5;
    int amount = 158;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [1, 5, 10, 25, 50], Amount: %d\n", amount);
    printf("Result: %d coins\n", count);
    if (count > 0 && count <= 10) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

void test_non_standard_coins() {
    printf("\n[Test 9] Non-standard coins where greedy fails\n");

    int coins[] = {1, 3, 4, 5};
    int coin_count = 4;
    int amount = 13;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [1, 3, 4, 5], Amount: %d\n", amount);
    printf("Greedy Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

void test_edge_case() {
    printf("\n[Test 10] Larger denomination problem\n");

    int coins[] = {2, 5, 10};
    int coin_count = 3;
    int amount = 11;
    int used_coins[amount];

    int count = coin_change_greedy(coins, coin_count, amount, used_coins);

    printf("Coins: [2, 5, 10], Amount: %d\n", amount);
    printf("Result: %d coins\n", count);
    if (count > 0) {
        printf("Coins used: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", used_coins[i]);
        }
        printf("\n");
    }
}

int main() {
    printf("==================================================\n");
    printf("COIN CHANGE - Greedy Approach (C)\n");
    printf("==================================================\n");

    test_standard_coins();
    test_greedy_fails();
    test_another_greedy_fails();
    test_greedy_optimal();
    test_impossible_amount();
    test_zero_amount();
    test_single_coin_type();
    test_large_amount();
    test_non_standard_coins();
    test_edge_case();

    return 0;
}
