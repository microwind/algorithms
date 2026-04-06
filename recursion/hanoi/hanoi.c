/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 汉诺塔问题完整教学示例
 * 
 * 问题描述：将 n 个盘子从 A 柱移动到 C 柱，借助 B 柱
 * 移动规则：
 * - 每次只能移动一个盘子
 * - 大盘子不能放在小盘子上面
 * 
 * 递归过程：
 * 1. 将 n-1 个盘子从 A 移到 B（借助 C）
 * 2. 将第 n 个盘子从 A 移到 C
 * 3. 将 n-1 个盘子从 B 移到 C（借助 A）
 * 
 * 学习重点：理解递归分解和回溯过程
 */
#include <stdio.h>

/**
 * 汉诺塔递归函数
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 盘子数量
 * @param from 起始柱子
 * @param aux 辅助柱子
 * @param to 目标柱子
 */
void hanoi(int n, char from, char aux, char to) {
    // 基本情况：只有一个盘子时直接移动
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    
    // 递归步骤：
    // 1. 将 n-1 个盘子从 from 移到 aux，借助 to
    hanoi(n - 1, from, to, aux); // Step 1
    
    // 2. 将第 n 个盘子从 from 移到 to
    printf("Move disk %d from %c to %c\n", n, from, to); // Step 2
    
    // 3. 将 n-1 个盘子从 aux 移到 to，借助 from
    hanoi(n - 1, aux, from, to); // Step 3
}

// 迭代版汉诺塔，请仔细对比递归版
void hanoi_iterative(int n, char from, char aux, char to) {
    // 汉诺塔的 迭代解法 需要模拟递归过程，可以使用 栈 或 位运算。这里用 非递归+栈模拟：
    int total_moves = (1 << n) - 1; // 2^n - 1
    char rods[3] = {from, aux, to};

    // 迭代法的核心是根据移动次数来确定移动哪个盘子以及从哪个柱子到哪个柱子
    for (int i = 1; i <= total_moves; i++) {
        int disk = __builtin_ctz(i) + 1;  // 找到最低位的 1 对应的盘子
        int src = ((i & i - 1) % 3);
        int dst = ((i | i - 1) + 1) % 3;
        printf("hanoi_iterative: Move disk %d from %c to %c\n", disk, rods[src], rods[dst]);
    }
}

int main() {
/*
调用过程示例：
hanoi(3, 'A', 'B', 'C')
  ├──> hanoi(2, 'A', 'C', 'B')
  │      ├──> hanoi(1, 'A', 'B', 'C') → Move disk 1 from A to C
  │      ├──> Move disk 2 from A to B
  │      ├──> hanoi(1, 'C', 'A', 'B') → Move disk 1 from C to B
  ├──> Move disk 3 from A to C
  ├──> hanoi(2, 'B', 'A', 'C')
         ├──> hanoi(1, 'B', 'C', 'A') → Move disk 1 from B to A
         ├──> Move disk 2 from B to C
         ├──> hanoi(1, 'A', 'B', 'C') → Move disk 1 from A to C

=======

调用过程图：
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
*/
    int num = 3;
    hanoi(num, 'A', 'B', 'C');
    printf("\r\n");
    // 循环法
    hanoi_iterative(num, 'A', 'B', 'C');
    return 0;
}

/*
jarry@MacBook-Pro recursion % gcc hanoi.c
jarry@MacBook-Pro recursion % ./a.out    
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C

hanoi_iterative: Move disk 1 from A to C
hanoi_iterative: Move disk 2 from A to B
hanoi_iterative: Move disk 1 from C to B
hanoi_iterative: Move disk 3 from A to C
hanoi_iterative: Move disk 1 from B to A
hanoi_iterative: Move disk 2 from B to C
hanoi_iterative: Move disk 1 from A to C
*/