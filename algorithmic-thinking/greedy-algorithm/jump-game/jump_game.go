package main

import (
	"fmt"
)

/*
* 跳跃游戏（贪心算法）
 *
 * 算法思路：
 * - 给定一个数组，每个元素表示当前位置最大可跳跃步数
 * - 判断能否到达最后一个位置
 * - 贪心策略：每一步记录当前能到达的最远位置
*/

// CanJump 判断能否到达最后一个位置
func CanJump(nums []int) bool {
	if len(nums) == 0 || len(nums) == 1 {
		return true
	}

	maxReach := 0

	for i := 0; i < len(nums); i++ {
		// 如果当前位置超过了最远可达位置，则无法到达
		if i > maxReach {
			return false
		}

		// 更新最远可达位置
		if i+nums[i] > maxReach {
			maxReach = i + nums[i]
		}

		// 如果已经能到达最后一位，提前返回true
		if maxReach >= len(nums)-1 {
			return true
		}
	}

	return maxReach >= len(nums)-1
}

// MinJumps 返回到达最后一位所需的最少跳跃次数
func MinJumps(nums []int) int {
	if len(nums) == 0 || len(nums) == 1 {
		return 0
	}

	// 检查是否可达
	maxReach := 0
	for i := 0; i < len(nums)-1; i++ {
		if i > maxReach {
			return -1
		}
		if i+nums[i] > maxReach {
			maxReach = i + nums[i]
		}
	}

	if maxReach < len(nums)-1 {
		return -1
	}

	// 贪心法计算最少跳跃次数
	jumps := 0
	currentEnd := 0
	farthest := 0

	for i := 0; i < len(nums)-1; i++ {
		if i+nums[i] > farthest {
			farthest = i + nums[i]
		}

		if i == currentEnd {
			jumps++
			currentEnd = farthest
		}
	}

	return jumps
}

// JumpPath 返回到达终点的跳跃路径（索引序列）
func JumpPath(nums []int) []int {
	path := []int{}

	if len(nums) == 0 {
		return path
	}

	if len(nums) == 1 {
		return []int{0}
	}

	// 检查是否可达
	maxReach := 0
	for i := 0; i < len(nums); i++ {
		if i > maxReach {
			return []int{}
		}
		if i+nums[i] > maxReach {
			maxReach = i + nums[i]
		}
		if maxReach >= len(nums)-1 {
			break
		}
	}

	if maxReach < len(nums)-1 {
		return []int{}
	}

	// 贪心构造跳跃路径
	path = append(path, 0)
	currentPos := 0

	for currentPos < len(nums)-1 {
		nextPos := currentPos
		maxNextReach := currentPos + nums[currentPos]

		// 遍历当前位置能到达的范围内，找到能到达的最远位置
		for i := currentPos + 1; i <= currentPos+nums[currentPos] && i < len(nums); i++ {
			// 如果当前位置能到达的最远位置小于当前位置能到达的最远位置，则更新当前位置能到达的最远位置
			if i+nums[i] > maxNextReach {
				maxNextReach = i + nums[i]
				nextPos = i
			}
		}

		if nextPos == currentPos {
			return []int{}
		}

		path = append(path, nextPos)
		currentPos = nextPos
	}

	return path
}

// JumpGameAnalysis 保存跳跃游戏分析结果
type JumpGameAnalysis struct {
	CanReach bool
	MinJumps int
	Path     []int
}

// AnalyzeJumpGame 综合分析跳跃游戏问题
func AnalyzeJumpGame(nums []int) JumpGameAnalysis {
	canReach := CanJump(nums)
	minJumps := MinJumps(nums)
	path := JumpPath(nums)

	return JumpGameAnalysis{
		CanReach: canReach,
		MinJumps: minJumps,
		Path:     path,
	}
}

func testBasicReachable() {
	fmt.Println("\n[测试1] 可到达")

	nums := []int{2, 3, 1, 1, 4}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testNotReachable() {
	fmt.Println("\n[测试2] 不可到达")

	nums := []int{3, 2, 1, 0, 4}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testSingleElement() {
	fmt.Println("\n[测试3] 单元素")

	nums := []int{0}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testZeroJump() {
	fmt.Println("\n[测试4] 除最后一位外全为零")

	nums := []int{0, 1}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testLargeJumps() {
	fmt.Println("\n[测试5] 跳跃步数很大")

	nums := []int{10, 0, 0, 0, 0}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testMultipleJumps() {
	fmt.Println("\n[测试6] 需要多次跳跃")

	nums := []int{2, 3, 1, 1, 1}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testBlocked() {
	fmt.Println("\n[测试7] 倒数第二步被阻断")

	nums := []int{1, 0, 1, 0}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testTwoElement() {
	fmt.Println("\n[测试8] 两元素数组")

	nums := []int{2, 3}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testDecreasing() {
	fmt.Println("\n[测试9] 大数组递减")

	nums := []int{5, 4, 3, 2, 1, 0}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testComplex() {
	fmt.Println("\n[测试10] 复杂可达场景")

	nums := []int{2, 5, 0, 0}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func main() {
	fmt.Println("==================================================")
	fmt.Println("跳跃游戏 - 贪心算法 (Go)")
	fmt.Println("==================================================")

	testBasicReachable()
	testNotReachable()
	testSingleElement()
	testZeroJump()
	testLargeJumps()
	testMultipleJumps()
	testBlocked()
	testTwoElement()
	testDecreasing()
	testComplex()
}
