#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 跳跃游戏 - 使用贪心判断能否到达最后一个位置
 *
 * 算法：
 * - 给定一个数组，每个元素表示从当前位置最多能跳的步数
 * - 判断是否可以从起点跳到最后一个下标
 * - 贪心思路：维护当前能到达的最远下标 max_reach
 * - 一旦当前位置超过 max_reach，则说明无法继续前进，返回 false
 *
 * 时间复杂度：O(n)（单次遍历数组）
 * 空间复杂度：O(1)（只使用常数额外变量）
 *
 * 关键思想：
 * 在位置 i 处，最多可以到达 i + nums[i]。
 * 始终维护我们能到达的最远位置 max_reach。
 * 如果出现某个位置无法到达，则整体不可达。
 */

/*
* 判断是否能到达数组的最后一个下标
 *
 * 参数:
 *   nums: 数组，每个元素表示当前位置最大可跳跃步数
 *   n: 数组长度
 *
 * 返回:
 *   若能到达最后一个下标返回 true，否则返回 false
*/
bool can_jump(int *nums, int n) {
    if (n == 0 || n == 1) {
        return true;
    }

    int max_reach = 0;

    for (int i = 0; i < n; i++) {
        /*
         * 如果当前位置已经超过最远可达位置，则无法继续前进，返回 false
         */
        if (i > max_reach) {
            return false;
        }

        /*
         * 更新当前能到达的最远位置
         */
        if (i + nums[i] > max_reach) {
            max_reach = i + nums[i];
        }

        /*
         * 提前结束：一旦最远可达位置已经到达或超过末尾，直接返回 true
         */
        if (max_reach >= n - 1) {
            return true;
        }
    }

    return max_reach >= n - 1;
}

/*
* 计算到达数组最后一个下标所需的最少跳跃次数
 *
 * 参数:
 *   nums: 数组，每个元素表示当前位置最大可跳跃步数
 *   n: 数组长度
 *   jumps: 用于存储最少跳跃次数的指针
 *
 * 返回:
 *   若可达返回 true 并在 jumps 中写入次数；否则返回 false，jumps 置为 -1
*/
bool min_jumps(int *nums, int n, int *jumps) {
    if (n == 0 || n == 1) {
        *jumps = 0;
        return true;
    }

    /*
     * 首先检查是否可以到达终点
     */
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

    /*
     * 使用贪心策略计算最少跳跃次数
     */
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
* 构造从起点到终点的一条跳跃路径
 *
 * 参数:
 *   nums: 数组，每个元素表示当前位置最大可跳跃步数
 *   n: 数组长度
 *   path: 用于存储路径下标序列的数组
 *   path_size: 用于存储路径长度的指针
 *
 * 返回:
 *   若找到路径返回 true，否则返回 false
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

    /*
     * 先检查是否可以到达终点
     */
    int max_reach = 0;
    // 遍历数组，更新当前能到达的最远位置
    for (int i = 0; i < n; i++) {
        // 如果当前位置已经超过最远可达位置，则无法继续前进，返回 false
        if (i > max_reach) {
            return false;
        }
        // 更新当前能到达的最远位置
        if (i + nums[i] > max_reach) {
            max_reach = i + nums[i];
        }
        // 如果已经能到达最后一位，提前返回 true
        if (max_reach >= n - 1) {
            break;
        }
    }

    if (max_reach < n - 1) {
        return false;
    }

    /*
     * 使用贪心策略构造一条跳跃路径
     */
    path[0] = 0;
    int path_len = 1;
    int current_pos = 0;

    // 遍历数组，构造跳跃路径
    while (current_pos < n - 1) {
        int next_pos = current_pos;
        int max_next_reach = current_pos + nums[current_pos];
        // 遍历当前位置能到达的范围内，找到能到达的最远位置
        for (int i = current_pos + 1; i <= current_pos + nums[current_pos] && i < n; i++) {
            // 如果当前位置能到达的最远位置小于当前位置能到达的最远位置，则更新当前位置能到达的最远位置
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
