// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
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
package main

import "fmt"

// 全局移动计数器
var moveCount int

/**
 * 汉诺塔递归函数
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 盘子数量
 * @param source 起始柱子
 * @param auxiliary 辅助柱子
 * @param target 目标柱子
 */
func hanoi(n int, source byte, auxiliary byte, target byte) {
	// 基本情况：只有一个盘子时直接移动
	if n == 1 {
		fmt.Printf("Move disk 1 from %c to %c\n", source, target)
		moveCount++
		return
	}

	// 递归步骤：
	// 1. 将 n-1 个盘子从 source 移到 auxiliary，借助 target
	hanoi(n-1, source, auxiliary, target) // Step 1

	// 2. 将第 n 个盘子从 source 移到 target
	fmt.Printf("Move disk %d from %c to %c\n", n, source, target) // Step 2
	moveCount++

	// 3. 将 n-1 个盘子从 auxiliary 移到 target，借助 source
	hanoi(n-1, auxiliary, target, source) // Step 3
}

/**
 * 主函数 - 测试汉诺塔问题
 */
func main() {
	fmt.Println("=== 汉诺塔问题 ===")

	// 测试不同数量的盘子
	for n := 2; n <= 4; n++ {
		fmt.Printf("n = %d:\n", n)
		moveCount = 0

		// 调用递归函数
		hanoi(n, 'A', 'B', 'C')

		// 输出移动次数验证
		expectedMoves := 1<<uint(n) - 1 // 2^n - 1
		fmt.Printf("总移动次数: %d (应为 %d)\n", moveCount, expectedMoves)
		fmt.Println()
	}
}
