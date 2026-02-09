package main

import (
	"fmt"
)

/*
 * Jump Game - Can reach the last index with greedy jumps
 *
 * Algorithm:
 * - Given an array where each element is the maximum jump length from that position
 * - Determine if you can reach the last index
 * - Greedy approach: track the maximum index we can reach so far
 */

// CanJump determines if we can reach the last index of the array
func CanJump(nums []int) bool {
	if len(nums) == 0 || len(nums) == 1 {
		return true
	}

	maxReach := 0

	for i := 0; i < len(nums); i++ {
		// If current position is beyond what we can reach, return false
		if i > maxReach {
			return false
		}

		// Update the maximum position we can reach
		if i+nums[i] > maxReach {
			maxReach = i + nums[i]
		}

		// Early termination: if we can reach the end, return true
		if maxReach >= len(nums)-1 {
			return true
		}
	}

	return maxReach >= len(nums)-1
}

// MinJumps finds the minimum number of jumps needed to reach the last index
func MinJumps(nums []int) int {
	if len(nums) == 0 || len(nums) == 1 {
		return 0
	}

	// Check if reachable
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

	// Find minimum jumps using greedy
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

// JumpPath finds a path from start to end
func JumpPath(nums []int) []int {
	path := []int{}

	if len(nums) == 0 {
		return path
	}

	if len(nums) == 1 {
		return []int{0}
	}

	// Check if reachable
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

	// Greedy path construction
	path = append(path, 0)
	currentPos := 0

	for currentPos < len(nums)-1 {
		nextPos := currentPos
		maxNextReach := currentPos + nums[currentPos]

		for i := currentPos + 1; i <= currentPos+nums[currentPos] && i < len(nums); i++ {
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

// JumpGameAnalysis holds the analysis results
type JumpGameAnalysis struct {
	CanReach bool
	MinJumps int
	Path     []int
}

// AnalyzeJumpGame analyzes a jump game problem comprehensively
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
	fmt.Println("\n[Test 1] Reachable - should return true")

	nums := []int{2, 3, 1, 1, 4}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testNotReachable() {
	fmt.Println("\n[Test 2] Not reachable - should return false")

	nums := []int{3, 2, 1, 0, 4}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testSingleElement() {
	fmt.Println("\n[Test 3] Single element")

	nums := []int{0}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testZeroJump() {
	fmt.Println("\n[Test 4] All zeros except last")

	nums := []int{0, 1}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testLargeJumps() {
	fmt.Println("\n[Test 5] Large jumps available")

	nums := []int{10, 0, 0, 0, 0}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testMultipleJumps() {
	fmt.Println("\n[Test 6] Requires multiple jumps")

	nums := []int{2, 3, 1, 1, 1}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testBlocked() {
	fmt.Println("\n[Test 7] Blocked at second-to-last")

	nums := []int{1, 0, 1, 0}
	result := CanJump(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", result)
}

func testTwoElement() {
	fmt.Println("\n[Test 8] Two element array")

	nums := []int{2, 3}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testDecreasing() {
	fmt.Println("\n[Test 9] Large array with decreasing values")

	nums := []int{5, 4, 3, 2, 1, 0}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func testComplex() {
	fmt.Println("\n[Test 10] Complex reachable scenario")

	nums := []int{2, 5, 0, 0}
	analysis := AnalyzeJumpGame(nums)

	fmt.Printf("Input: %v\n", nums)
	fmt.Printf("Can reach end: %v\n", analysis.CanReach)
	fmt.Printf("Min jumps: %d\n", analysis.MinJumps)
	fmt.Printf("Path: %v\n", analysis.Path)
}

func main() {
	fmt.Println("==================================================")
	fmt.Println("JUMP GAME - Greedy Approach (Go)")
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
