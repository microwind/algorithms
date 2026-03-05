package main

import (
	"fmt"
	"math/rand"
	"time"
)

// 随机采样（Reservoir Sampling）- Go 版本
//
// 从数据流中等概率抽取 k 个元素：
// - 不需要预先知道数据总量 n
// - 保证每个元素被选中的概率相同（k/n）

// ReservoirSampling 对整数切片 data 做水库采样，返回 k 个样本
func ReservoirSampling(data []int, k int) []int {
	reservoir := make([]int, 0, k)

	for i, v := range data {
		if i < k {
			// 前 k 个元素直接放入水池
			reservoir = append(reservoir, v)
		} else {
			// 对于第 i 个元素，以 k/(i+1) 的概率替换
			j := rand.Intn(i + 1) // 0..i
			if j < k {
				reservoir[j] = v
			}
		}
	}

	return reservoir
}

func main() {
	rand.Seed(time.Now().UnixNano())

	fmt.Println("========== Random Sampling (Go) ==========")
	data := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	fmt.Println("数据:", data)

	k := 3
	for t := 1; t <= 3; t++ {
		sample := ReservoirSampling(data, k)
		fmt.Printf("第 %d 次采样: %v\n", t, sample)
	}
}

