/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 移动零算法 - Go实现
 *
 * 算法原理：
 * 使用双指针技术。write指针记录非零元素应该写入的位置，read指针遍历数组。
 * 当read遇到非零元素时，将其复制到write位置，然后两个指针都前进。
 * 当read遇到零时，只前进read指针。最后将write之后的位置全部填充为零。
 *
 * 时间复杂度：O(n) - 单次遍历数组
 * 空间复杂度：O(1) - 原地操作
 */

package main

import "fmt"

// moveZeroes 移动零到数组末尾
// 参数：
//   nums - 待处理的数组
func moveZeroes(nums []int) {
	insertPos := 0 // 写指针，指向下一个非零元素应该存放的位置

	// 第一遍：将所有非零元素移到前面
	for _, num := range nums {
		if num != 0 {
			nums[insertPos] = num
			insertPos++
		}
	}

	// 第二遍：将insertPos之后的位置填充为零
	for insertPos < len(nums) {
		nums[insertPos] = 0
		insertPos++
	}
}

// printArray 打印数组
func printArray(nums []int, size int) {
	fmt.Print("[")
	for i := 0; i < size; i++ {
		fmt.Print(nums[i])
		if i < size-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}

func main() {
	nums := []int{0, 1, 0, 3, 12, 0, 5}

	fmt.Print("原始数组: ")
	printArray(nums, len(nums))

	moveZeroes(nums)

	fmt.Print("移动零后: ")
	printArray(nums, len(nums))
}

/*
 * 输出结果：
 * 原始数组: [0, 1, 0, 3, 12, 0, 5]
 * 移动零后: [1, 3, 12, 5, 0, 0, 0]
 */
