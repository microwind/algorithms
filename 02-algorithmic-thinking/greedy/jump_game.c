#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Jump Game - Can reach the last index with greedy jumps
 *
 * Algorithm:
 * - Given an array where each element is the maximum jump length from that position
 * - Determine if you can reach the last index
 * - Greedy approach: track the maximum index we can reach so far
 * - If at any point current index exceeds max reachable, return false
 *
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(1) - only using variables
 *
 * Key Insight:
 * At each position i, we can reach up to position i + nums[i].
 * We maintain the maximum position we can reach (max_reach).
 * If we encounter a position we can't reach, it's impossible.
 */

/*
 * Determine if we can reach the last index of the array
 *
 * Args:
 *   nums: Array where each element is max jump length from that position
 *   n: Length of the array
 *
 * Returns:
 *   true if we can reach the last index, false otherwise
 */
bool can_jump(int *nums, int n) {
    if (n == 0 || n == 1) {
        return true;
    }

    int max_reach = 0;

    for (int i = 0; i < n; i++) {
        /* If current position is beyond what we can reach, return false */
        if (i > max_reach) {
            return false;
        }

        /* Update the maximum position we can reach */
        if (i + nums[i] > max_reach) {
            max_reach = i + nums[i];
        }

        /* Early termination: if we can reach the end, return true */
        if (max_reach >= n - 1) {
            return true;
        }
    }

    return max_reach >= n - 1;
}

/*
 * Find the minimum number of jumps needed to reach the last index
 *
 * Args:
 *   nums: Array where each element is max jump length from that position
 *   n: Length of the array
 *   jumps: Pointer to store the number of jumps
 *
 * Returns:
 *   true if reachable, false otherwise
 */
bool min_jumps(int *nums, int n, int *jumps) {
    if (n == 0 || n == 1) {
        *jumps = 0;
        return true;
    }

    /* First check if reachable */
    int max_reach = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i > max_reach) {
            *jumps = -1;
            return false;
        }
        if (i + nums[i] > max_reach) {
            max_reach = i + nums[i];
        }
    }

    if (max_reach < n - 1) {
        *jumps = -1;
        return false;
    }

    /* Find minimum jumps using greedy */
    int jump_count = 0;
    int current_end = 0;
    int farthest = 0;

    for (int i = 0; i < n - 1; i++) {
        if (i + nums[i] > farthest) {
            farthest = i + nums[i];
        }

        if (i == current_end) {
            jump_count++;
            current_end = farthest;
        }
    }

    *jumps = jump_count;
    return true;
}

/*
 * Find a path from start to end
 *
 * Args:
 *   nums: Array where each element is max jump length from that position
 *   n: Length of the array
 *   path: Array to store the path
 *   path_size: Pointer to store the path length
 *
 * Returns:
 *   true if path found, false otherwise
 */
bool jump_path(int *nums, int n, int *path, int *path_size) {
    if (n == 0) {
        return false;
    }

    if (n == 1) {
        path[0] = 0;
        *path_size = 1;
        return true;
    }

    /* Check if reachable */
    int max_reach = 0;
    for (int i = 0; i < n; i++) {
        if (i > max_reach) {
            return false;
        }
        if (i + nums[i] > max_reach) {
            max_reach = i + nums[i];
        }
        if (max_reach >= n - 1) {
            break;
        }
    }

    if (max_reach < n - 1) {
        return false;
    }

    /* Greedy path construction */
    path[0] = 0;
    int path_len = 1;
    int current_pos = 0;

    while (current_pos < n - 1) {
        int next_pos = current_pos;
        int max_next_reach = current_pos + nums[current_pos];

        for (int i = current_pos + 1; i <= current_pos + nums[current_pos] && i < n; i++) {
            if (i + nums[i] > max_next_reach) {
                max_next_reach = i + nums[i];
                next_pos = i;
            }
        }

        if (next_pos == current_pos) {
            return false;
        }

        path[path_len] = next_pos;
        path_len++;
        current_pos = next_pos;
    }

    *path_size = path_len;
    return true;
}

void print_array(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void test_basic_reachable() {
    printf("\n[Test 1] Reachable - should return true\n");

    int nums[] = {2, 3, 1, 1, 4};
    int n = 5;

    bool result = can_jump(nums, n);
    int jump_count = -1;
    min_jumps(nums, n, &jump_count);
    int path[n];
    int path_size = 0;
    jump_path(nums, n, path, &path_size);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
    printf("Min jumps: %d\n", jump_count);
    printf("Path: ");
    print_array(path, path_size);
}

void test_not_reachable() {
    printf("\n[Test 2] Not reachable - should return false\n");

    int nums[] = {3, 2, 1, 0, 4};
    int n = 5;

    bool result = can_jump(nums, n);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
}

void test_single_element() {
    printf("\n[Test 3] Single element\n");

    int nums[] = {0};
    int n = 1;

    bool result = can_jump(nums, n);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
}

void test_zero_jump() {
    printf("\n[Test 4] All zeros except last\n");

    int nums[] = {0, 1};
    int n = 2;

    bool result = can_jump(nums, n);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
}

void test_large_jumps() {
    printf("\n[Test 5] Large jumps available\n");

    int nums[] = {10, 0, 0, 0, 0};
    int n = 5;

    bool result = can_jump(nums, n);
    int jump_count = -1;
    min_jumps(nums, n, &jump_count);
    int path[n];
    int path_size = 0;
    jump_path(nums, n, path, &path_size);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
    printf("Min jumps: %d\n", jump_count);
    printf("Path: ");
    print_array(path, path_size);
}

void test_multiple_jumps() {
    printf("\n[Test 6] Requires multiple jumps\n");

    int nums[] = {2, 3, 1, 1, 1};
    int n = 5;

    bool result = can_jump(nums, n);
    int jump_count = -1;
    min_jumps(nums, n, &jump_count);
    int path[n];
    int path_size = 0;
    jump_path(nums, n, path, &path_size);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
    printf("Min jumps: %d\n", jump_count);
    printf("Path: ");
    print_array(path, path_size);
}

void test_blocked() {
    printf("\n[Test 7] Blocked at second-to-last\n");

    int nums[] = {1, 0, 1, 0};
    int n = 4;

    bool result = can_jump(nums, n);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
}

void test_two_element() {
    printf("\n[Test 8] Two element array\n");

    int nums[] = {2, 3};
    int n = 2;

    bool result = can_jump(nums, n);
    int jump_count = -1;
    min_jumps(nums, n, &jump_count);
    int path[n];
    int path_size = 0;
    jump_path(nums, n, path, &path_size);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
    printf("Min jumps: %d\n", jump_count);
    printf("Path: ");
    print_array(path, path_size);
}

void test_decreasing() {
    printf("\n[Test 9] Large array with decreasing values\n");

    int nums[] = {5, 4, 3, 2, 1, 0};
    int n = 6;

    bool result = can_jump(nums, n);
    int jump_count = -1;
    min_jumps(nums, n, &jump_count);
    int path[n];
    int path_size = 0;
    jump_path(nums, n, path, &path_size);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
    printf("Min jumps: %d\n", jump_count);
    printf("Path: ");
    print_array(path, path_size);
}

void test_complex() {
    printf("\n[Test 10] Complex reachable scenario\n");

    int nums[] = {2, 5, 0, 0};
    int n = 4;

    bool result = can_jump(nums, n);
    int jump_count = -1;
    min_jumps(nums, n, &jump_count);
    int path[n];
    int path_size = 0;
    jump_path(nums, n, path, &path_size);

    printf("Input: ");
    print_array(nums, n);
    printf("Can reach end: %s\n", result ? "true" : "false");
    printf("Min jumps: %d\n", jump_count);
    printf("Path: ");
    print_array(path, path_size);
}

int main() {
    printf("==================================================\n");
    printf("JUMP GAME - Greedy Approach (C)\n");
    printf("==================================================\n");

    test_basic_reachable();
    test_not_reachable();
    test_single_element();
    test_zero_jump();
    test_large_jumps();
    test_multiple_jumps();
    test_blocked();
    test_two_element();
    test_decreasing();
    test_complex();

    return 0;
}
