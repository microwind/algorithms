/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 数学基础 - 阶乘计算 (Factorial)
 * 计算非负整数的阶乘 n!
 * 支持递归、迭代和大数计算
 * 时间复杂度: O(n)
 */

package main

import (
	"fmt"
	"math/big"
)

/**
 * 迭代计算阶乘
 *
 * 算法原理：
 * - n! = 1 × 2 × 3 × ... × n
 * - 0! = 1（空积的定义）
 *
 * 参数:
 *     n: 非负整数（n ≤ 20，避免uint64溢出）
 * 返回:
 *     n! 的结果
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
func FactorialIterative(n int) uint64 {
	if n < 0 {
		panic("n必须非负")
	}
	if n > 20 {
		panic("n太大，会导致uint64溢出")
	}

	var result uint64 = 1
	for i := 2; i <= n; i++ {
		result *= uint64(i)
	}
	return result
}

/**
 * 递归计算阶乘
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n) - 递归栈
 */
func FactorialRecursive(n int) uint64 {
	if n < 0 {
		panic("n必须非负")
	}
	if n <= 1 {
		return 1
	}
	return uint64(n) * FactorialRecursive(n-1)
}

/**
 * 尾递归优化版本
 */
func FactorialTailRecursive(n int, accumulator uint64) uint64 {
	if n <= 1 {
		return accumulator
	}
	return FactorialTailRecursive(n-1, accumulator*uint64(n))
}

/**
 * 大数阶乘计算（使用math/big）
 *
 * 可以计算任意大的阶乘
 */
func FactorialBig(n int) *big.Int {
	if n < 0 {
		panic("n必须非负")
	}

	result := big.NewInt(1)
	for i := 2; i <= n; i++ {
		result.Mul(result, big.NewInt(int64(i)))
	}
	return result
}

/**
 * 排列数 P(n, k) = n! / (n-k)!
 */
func Permutation(n, k int) uint64 {
	if k > n || k < 0 {
		panic("k必须在0到n之间")
	}
	if n > 20 {
		panic("n太大")
	}

	var result uint64 = 1
	for i := n; i > n-k; i-- {
		result *= uint64(i)
	}
	return result
}

/**
 * 组合数 C(n, k) = n! / (k! × (n-k)!)
 */
func Combination(n, k int) uint64 {
	if k > n || k < 0 {
		panic("k必须在0到n之间")
	}
	if k > n/2 {
		k = n - k // 利用对称性
	}
	if n > 20 {
		panic("n太大")
	}

	var result uint64 = 1
	for i := 1; i <= k; i++ {
		result = result * uint64(n-k+i) / uint64(i)
	}
	return result
}

/**
 * 大数组合数计算
 */
func CombinationBig(n, k int) *big.Int {
	if k > n || k < 0 {
		panic("k必须在0到n之间")
	}
	if k > n/2 {
		k = n - k
	}

	result := big.NewInt(1)
	for i := 1; i <= k; i++ {
		// result = result * (n-k+i) / i
		result.Mul(result, big.NewInt(int64(n-k+i)))
		result.Div(result, big.NewInt(int64(i)))
	}
	return result
}

/**
 * 测试函数
 */
func testFactorial() {
	fmt.Println("==================================================")
	fmt.Println("    阶乘计算演示 (Factorial n!)")
	fmt.Println("==================================================")
	fmt.Println()

	// 阶乘表
	fmt.Println("阶乘表 (0! 到 20!):")
	fmt.Println("--------------------------------------------------")
	for i := 0; i <= 20; i++ {
		result := FactorialIterative(i)
		fmt.Printf("%2d! = %20d\n", i, result)
	}

	// 大数阶乘
	fmt.Println("\n==================================================")
	fmt.Println("大数阶乘 (使用math/big):")
	fmt.Println("==================================================")
	for _, n := range []int{50, 100, 200, 500} {
		factN := FactorialBig(n)
		digits := len(factN.String())
		fmt.Printf("%d! 的位数: %d\n", n, digits)
	}

	// 显示100!的前50位和后20位
	fact100 := FactorialBig(100)
	fact100Str := fact100.String()
	fmt.Printf("\n100! = %s...%s\n", fact100Str[:50], fact100Str[len(fact100Str)-20:])

	// 排列组合
	fmt.Println("\n==================================================")
	fmt.Println("排列组合计算:")
	fmt.Println("==================================================")
	fmt.Printf("P(10, 3) = %d (从10个中取3个排列)\n", Permutation(10, 3))
	fmt.Printf("C(10, 3) = %d (从10个中取3个组合)\n", Combination(10, 3))
	fmt.Printf("C(52, 5) = %d (扑克牌5张组合数)\n", Combination(52, 5))

	// 大数组合数
	fmt.Println("\n大数组合数:")
	fmt.Println("--------------------------------------------------")
	cb := CombinationBig(1000, 500)
	cbStr := cb.String()
	fmt.Printf("C(1000, 500) 的位数: %d\n", len(cbStr))
	fmt.Printf("C(1000, 500) = %s...%s\n", cbStr[:30], cbStr[len(cbStr)-20:])

	// 杨辉三角
	fmt.Println("\n==================================================")
	fmt.Println("杨辉三角（前8行）:")
	fmt.Println("==================================================")
	for n := 0; n < 8; n++ {
		// 打印前导空格
		for i := 0; i < 7-n; i++ {
			fmt.Print("  ")
		}
		for k := 0; k <= n; k++ {
			fmt.Printf("%4d ", Combination(n, k))
		}
		fmt.Println()
	}

	// 数学性质
	fmt.Println("\n==================================================")
	fmt.Println("阶乘的数学性质:")
	fmt.Println("==================================================")
	fmt.Println("• 定义: n! = n × (n-1) × ... × 2 × 1")
	fmt.Println("• 递推: n! = n × (n-1)!")
	fmt.Println("• 0! = 1（空积的定义）")
	fmt.Println("• 增长: 阶乘比指数增长更快")
	fmt.Println("• 斯特林近似: n! ≈ √(2πn) × (n/e)^n")

	// 应用场景
	fmt.Println("\n==================================================")
	fmt.Println("应用场景:")
	fmt.Println("==================================================")
	fmt.Println("• 排列组合: 计算可能性的总数")
	fmt.Println("• 概率论: 生日问题、洗牌算法")
	fmt.Println("• 泰勒级数: e^x = Σ x^n/n!")
	fmt.Println("• 图论: 计算不同图的数量")
	fmt.Println("• 密码学: 密钥空间计算")

	// Go特性
	fmt.Println("\n==================================================")
	fmt.Println("Go特性:")
	fmt.Println("==================================================")
	fmt.Println("• 多返回值: 支持错误处理模式")
	fmt.Println("• 大数支持: math/big包提供任意精度整数")
	fmt.Println("• 类型安全: 编译时类型检查")
	fmt.Println("• 性能: 接近C语言的执行效率")
	fmt.Println("• 并发: goroutine支持并行计算")
}

// TestFactorialMain 阶乘测试主函数
func TestFactorialMain() {
	testFactorial()
}
