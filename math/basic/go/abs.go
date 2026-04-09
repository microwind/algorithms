/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 绝对值计算 (Absolute Value)
 * 计算数值的绝对值
 * 时间复杂度: O(1)
 */

package main

import (
	"fmt"
	"math"
)

/**
 * 计算整数的绝对值
 *
 * 算法原理：
 * - 正数：绝对值就是其本身
 * - 负数：绝对值是其相反数
 * - 零：绝对值是零
 *
 * 参数:
 *     n: 要求绝对值的整数
 * 返回:
 *     n的绝对值
 *
 * 时间复杂度: O(1) - 常数时间
 * 空间复杂度: O(1) - 常数空间
 */
func AbsoluteValueInt(n int) int {
	if n < 0 {
		return -n
	}
	return n
}

/**
 * 计算int64的绝对值
 */
func AbsoluteValueInt64(n int64) int64 {
	if n < 0 {
		return -n
	}
	return n
}

/**
 * 计算float64的绝对值
 */
func AbsoluteValueFloat(n float64) float64 {
	return math.Abs(n)
}

/**
 * 泛型版本的绝对值（Go 1.18+）
 */
func AbsoluteValueGeneric[T ~int | ~int8 | ~int16 | ~int32 | ~int64](n T) T {
	if n < 0 {
		return -n
	}
	return n
}

/**
 * 测试函数
 */
func testAbsoluteValue() {
	fmt.Println("========================================")
	fmt.Println("    绝对值计算演示 (Absolute Value)")
	fmt.Println("========================================")
	fmt.Println()

	// 测试用例
	testCasesInt := []int{-42, 0, 100, -999999}
	testCasesFloat := []float64{-3.14, 2.718, -0.0}

	fmt.Println("整数测试:")
	fmt.Println("----------------------------------------")
	for _, num := range testCasesInt {
		result := AbsoluteValueInt(num)
		fmt.Printf("输入: %10d | 绝对值: %10d\n", num, result)
	}

	fmt.Println("\n浮点数测试:")
	fmt.Println("----------------------------------------")
	for _, num := range testCasesFloat {
		result := AbsoluteValueFloat(num)
		fmt.Printf("输入: %10.3f | 绝对值: %10.3f\n", num, result)
	}

	// 数学性质
	fmt.Println("\n========================================")
	fmt.Println("数学性质:")
	fmt.Println("========================================")
	fmt.Println("• 非负性: |x| ≥ 0")
	fmt.Println("• 正定性: |x| = 0 当且仅当 x = 0")
	fmt.Println("• 对称性: |-x| = |x|")
	fmt.Println("• 三角不等式: |x + y| ≤ |x| + |y|")
	fmt.Println("• 乘法性质: |x × y| = |x| × |y|")

	// 应用场景
	fmt.Println("\n========================================")
	fmt.Println("应用场景:")
	fmt.Println("========================================")
	fmt.Println("• 距离计算: 曼哈顿距离、欧几里得距离")
	fmt.Println("• 误差分析: 绝对误差、相对误差")
	fmt.Println("• 数值比较: 比较浮点数精度")
	fmt.Println("• 向量运算: 向量的模（长度）")

	// 代码示例
	fmt.Println("\n========================================")
	fmt.Println("Go代码示例:")
	fmt.Println("========================================")
	fmt.Println(`
// 计算两点间距离
func distance(x1, y1, x2, y2 float64) float64 {
	dx := math.Abs(x2 - x1)
	dy := math.Abs(y2 - y1)
	return math.Sqrt(dx*dx + dy*dy)
}

// 误差比较
func roughlyEqual(a, b, epsilon float64) bool {
	return math.Abs(a-b) < epsilon
}
`)
}

// TestAbsMain 绝对值测试主函数
func TestAbsMain() {
	testAbsoluteValue()
}
