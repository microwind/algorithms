package main

import (
	"fmt"
	"time"
)

/*
 * 最大XOR对 - 找数组中最大的XOR值
 *
 * 问题：给定一个数组，找到任意两个元素的最大XOR值
 *
 * 核心思想：
 * - 暴力法：比较所有对
 * - 字典树(Trie)：高效地查找最大XOR
 *
 * 时间复杂度:
 * - 暴力法: O(n^2)
 * - Trie方法: O(n * k) 其中k是整数的位数
 *
 * 空间复杂度: O(n * k) for Trie
 */

// 暴力法：比较所有对
func MaxXorPairBruteForce(nums []int) int {
	maxXor := 0
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			xorVal := nums[i] ^ nums[j]
			if xorVal > maxXor {
				maxXor = xorVal
			}
		}
	}
	return maxXor
}

// Trie树节点
type TrieNode struct {
	children [2]*TrieNode  // 0和1两个分支
}

// 将数字的二进制表示插入Trie树
func insertTrie(root *TrieNode, num int) {
	node := root
	// 从最高位到最低位遍历
	for i := 31; i >= 0; i-- {
		bit := (num >> uint(i)) & 1
		if node.children[bit] == nil {
			node.children[bit] = &TrieNode{}
		}
		node = node.children[bit]
	}
}

// 找与给定数字最大XOR的数
//
// 贪心策略：对于每一位，尽可能走不同的路径以最大化XOR
func findMaxXor(root *TrieNode, num int) int {
	node := root
	maxXor := 0
	// 从最高位到最低位遍历
	for i := 31; i >= 0; i-- {
		bit := (num >> uint(i)) & 1
		// 优先走相反的路径（这样XOR结果该位为1）
		toggleBit := 1 - bit

		if node.children[toggleBit] != nil {
			maxXor |= (1 << uint(i))
			node = node.children[toggleBit]
		} else if node.children[bit] != nil {
			node = node.children[bit]
		} else {
			// 不应该出现这种情况
			break
		}
	}
	return maxXor
}

// 使用Trie树找最大XOR对
func MaxXorPairTrie(nums []int) int {
	if len(nums) < 2 {
		return 0
	}

	root := &TrieNode{}

	// 构建Trie树
	for _, num := range nums {
		insertTrie(root, num)
	}

	maxXor := 0
	// 对每个数字，找与它最大XOR的数
	for _, num := range nums {
		xorVal := findMaxXor(root, num)
		if xorVal > maxXor {
			maxXor = xorVal
		}
	}

	return maxXor
}

// 贪心法（不用Trie）：逐位构建答案
func MaxXorPairGreedy(nums []int) int {
	if len(nums) < 2 {
		return 0
	}

	maxXor := 0
	prefixMask := 0

	// 从最高位到最低位
	for i := 31; i >= 0; i-- {
		prefixMask |= (1 << uint(i))

		// 收集所有数的前缀
		prefixes := make(map[int]bool)
		for _, num := range nums {
			prefixes[num&prefixMask] = true
		}

		// 尝试在当前位设为1
		temp := maxXor | (1 << uint(i))

		// 检查是否存在两个数的前缀异或为temp
		for prefix := range prefixes {
			if prefixes[temp^prefix] {
				maxXor = temp
				break
			}
		}
	}

	return maxXor
}

// 测试函数
func main() {
	fmt.Println("=== 最大XOR对 ===\n")

	// 测试用例1：基本用例
	fmt.Println("1. 基本用例:")
	testArrays := [][]int{
		{1, 2, 3, 4, 5},
		{8, 10, 2},
		{14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70},
	}

	for _, nums := range testArrays {
		fmt.Printf("  数组: %v\n", nums)

		brute := MaxXorPairBruteForce(nums)
		trie := MaxXorPairTrie(nums)
		greedy := MaxXorPairGreedy(nums)

		fmt.Printf("  最大XOR (暴力): %d\n", brute)
		fmt.Printf("  最大XOR (Trie): %d\n", trie)
		fmt.Printf("  最大XOR (贪心): %d\n", greedy)
		if brute == trie && trie == greedy {
			fmt.Println("  所有方法一致: 是")
		} else {
			fmt.Println("  所有方法一致: 否")
		}
		fmt.Println()
	}

	// 测试用例2：XOR对的详细信息
	fmt.Println("2. XOR对的详细信息:")
	nums2 := []int{1, 2, 3, 4, 5}
	fmt.Printf("  数组: %v\n", nums2)

	maxXor := 0
	bestI, bestJ := -1, -1
	for i := 0; i < len(nums2); i++ {
		for j := i + 1; j < len(nums2); j++ {
			xorVal := nums2[i] ^ nums2[j]
			if xorVal > maxXor {
				maxXor = xorVal
				bestI = i
				bestJ = j
			}
			if xorVal >= 4 {  // 只显示较大的XOR值
				fmt.Printf("    %d ^ %d = %d\n", nums2[i], nums2[j], xorVal)
			}
		}
	}
	fmt.Printf("  最大XOR对: %d ^ %d = %d\n\n",
		nums2[bestI], nums2[bestJ], maxXor)

	// 测试用例3：边界情况
	fmt.Println("3. 边界情况:")
	boundaryTests := [][]int{
		{5},
		{5, 3},
		{1},
		{7, 7},
	}

	for _, nums := range boundaryTests {
		fmt.Printf("  数组: %v -> 最大XOR: %d\n",
			nums, MaxXorPairTrie(nums))
	}
	fmt.Println()

	// 测试用例4：较大数组
	fmt.Println("4. 较大数组测试:")
	largeSize := 100
	largeNums := make([]int, largeSize)
	for i := 0; i < largeSize; i++ {
		largeNums[i] = i + 1
	}

	start := time.Now()
	resultGreedy := MaxXorPairGreedy(largeNums)
	greedyTime := time.Since(start)

	start = time.Now()
	resultTrie := MaxXorPairTrie(largeNums)
	trieTime := time.Since(start)

	fmt.Printf("  数组大小: %d\n", largeSize)
	fmt.Printf("  贪心法结果: %d, 耗时: %v\n", resultGreedy, greedyTime)
	fmt.Printf("  Trie法结果: %d, 耗时: %v\n", resultTrie, trieTime)
}
