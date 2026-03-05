package main

import (
	"fmt"
	"math/rand"
	"time"
)

// 洗牌算法（Shuffle）- Go 版本
//
// 实现 Fisher–Yates 洗牌：
// - ShuffleInPlace: 原地洗牌，直接修改切片
// - ShuffledCopy: 返回打乱后的新切片，原切片不变

// ShuffleInPlace 对切片 nums 进行原地洗牌
func ShuffleInPlace(nums []int) {
	// 从最后一个元素开始，依次与前面随机位置的元素交换
	for i := len(nums) - 1; i > 0; i-- {
		// 生成 [0, i] 之间的随机下标
		j := rand.Intn(i + 1)
		nums[i], nums[j] = nums[j], nums[i]
	}
}

// ShuffledCopy 返回一个打乱后的新切片，原切片不变
func ShuffledCopy(nums []int) []int {
	copySlice := make([]int, len(nums))
	copy(copySlice, nums)
	ShuffleInPlace(copySlice)
	return copySlice
}

func main() {
	// 为 rand 设置随机种子
	rand.Seed(time.Now().UnixNano())

	fmt.Println("========== Shuffle (Go) ==========")
	original := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	fmt.Println("原切片:", original)

	arr1 := make([]int, len(original))
	copy(arr1, original)
	ShuffleInPlace(arr1)
	fmt.Println("原地洗牌结果:", arr1)

	arr2 := ShuffledCopy(original)
	fmt.Println("新切片洗牌结果:", arr2)
	fmt.Println("原切片保持不变:", original)
}

