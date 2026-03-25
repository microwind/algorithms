/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
	"fmt"
	"time"
)

/**
 * 冒泡排序升序，将最大的元素冒泡到最后
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 * 稳定性：稳定
 */
func bubbleSort1(list []int) []int {
	var length = len(list)
	// 外层循环控制排序轮数，每轮确定一个最大值的位置
	for i := 0; i < length; i++ {
		fmt.Printf("\nno: %d\n", i)
		// 内层循环控制比较次数，length-i-1 避免重复比较已排序部分
		for j := 0; j < length-i-1; j++ {
			fmt.Printf("j=%d * i=%d | ", j, i)
			// 比较相邻元素，如果前者大于后者则交换
			if list[j] > list[j+1] {
				// 使用临时变量交换相邻元素
				var tmp = list[j+1]
				list[j+1] = list[j]
				list[j] = tmp
			}
		}
	}
	return list
}

/**
 * 冒泡排序降序，将最小的元素冒泡到最后
 * 使用无限循环配合交换标志，针对已排序情况做优化
 * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
 */
func bubbleSort2(list []int) []int {
	// 设立是否交换的标志
	flag := true
	// 使用无限循环，直到某一轮没有发生任何交换为止
	for flag == true {
		flag = false  // 每轮开始时重置标志
		// 内层循环比较所有相邻元素
		for i := 0; i < len(list)-1; i++ {
			fmt.Printf("\n %d * %d\n", i, i+1)
			// 降序排序：如果前者小于后者则交换
			if list[i] < list[i+1] {
				// Go 的多重赋值交换，更简洁
				list[i], list[i+1] = list[i+1], list[i]
				flag = true  // 发生交换，设置标志
			}
	}
	}
	return list
}

/**
 * 冒泡排序降序，将最小的元素冒泡到最后
 * 使用交换标志优化，当某一轮无交换时提前终止
 * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
 */
func bubbleSort3(list []int) []int {
	// 设立是否交换的标志
	flag := true
	length := len(list)
	// 外层循环增加 flag 条件，当数组已有序时提前终止
	for i := 0; i < length && flag == true; i++ {
		flag = false  // 每轮开始时重置标志
		// 内层循环控制比较次数，length-i-1 避免重复比较已排序部分
		for j := 0; j < length-i-1; j++ {
			fmt.Printf("\nj=%d * i=%d | ", j, i)
			// 降序排序：如果前者小于后者则交换
			if list[j] < list[j+1] {
				flag = true  // 发生交换，设置标志
				// Go 的多重赋值交换，更简洁
				list[j], list[j+1] = list[j+1], list[j]
			}
		}
	}
	return list
}

/**
 * 冒泡排序升序，记录最后交换位置的优化版本
 * 通过记录最后一次交换的位置，减少不必要的比较
 * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
 */
func bubbleSort4(list []int) []int {
	length := len(list)
	lastSwap := length - 1  // 记录最后一次交换的位置
	
	// 外层循环控制排序轮数，最多进行 length-1 轮
	for i := 0; i < length-1; i++ {
		isSorted := true  // 标记本轮是否发生交换
		currentLastSwap := 0  // 记录当前轮次的最后交换位置
		
		// 内层循环只比较到 lastSwap 位置，减少不必要的比较
		for j := 0; j < lastSwap; j++ {
			if list[j] > list[j+1] {
				// 交换相邻元素
				list[j], list[j+1] = list[j+1], list[j]
				isSorted = false  // 发生交换，标记为未排序
				currentLastSwap = j  // 更新最后交换位置
			}
		}
		
		lastSwap = currentLastSwap  // 更新下一轮的比较边界
		if isSorted {
			break  // 如果本轮没有交换，说明已有序，提前终止
		}
	}
	
	return list
}

func main() {
	fmt.Println("bubble sort1:")
	time1 := time.Now()
	data1 := [...]int{3, 2, 10, -4, -10}
	fmt.Println(bubbleSort1(data1[:]))
	fmt.Println("sort1 end. cost:", time.Since(time1))

	fmt.Println("bubble sort2:")
	time2 := time.Now()
	data2 := [...]int{3, 2, 10, -4, -10}
	fmt.Println(bubbleSort2(data2[:]))
	fmt.Println("sort2 end:", time.Since(time2))

	fmt.Println("bubble sort3:")
	time3 := time.Now()
	data3 := [...]int{3, 2, 10, -4, -10}
	fmt.Println(bubbleSort3(data3[:]))
	fmt.Println("sort3 end:", time.Since(time3))

	fmt.Println("bubble sort4 (optimized):")
	time4 := time.Now()
	data4 := [...]int{3, 2, 10, -4, -10}
	fmt.Println(bubbleSort4(data4[:]))
	fmt.Println("sort4 end:", time.Since(time4))
}

/*
jarry@jarrys-MacBook-Pro bubblesort % go version
go version go1.15 darwin/amd64
jarry@jarrys-MacBook-Pro bubblesort % go build bubble_sort.go
jarry@jarrys-MacBook-Pro bubblesort % ./bubble_sort
bubble sort1:

no: 0
j=0 * i=0 | j=1 * i=0 | j=2 * i=0 | j=3 * i=0 |
no: 1
j=0 * i=1 | j=1 * i=1 | j=2 * i=1 |
no: 2
j=0 * i=2 | j=1 * i=2 |
no: 3
j=0 * i=3 |
no: 4
[-10 -4 2 3 10]
sort1 end. cost: 45.563µs
bubble sort2:

 0 * 1

 1 * 2

 2 * 3

 3 * 4

 0 * 1

 1 * 2

 2 * 3

 3 * 4

 0 * 1

 1 * 2

 2 * 3

 3 * 4
[10 3 2 -4 -10]
sort2 end: 22.048µs
bubble sort3:

j=0 * i=0 |
j=1 * i=0 |
j=0 * i=1 |
j=1 * i=1 |
j=0 * i=2 |
j=1 * i=2 | [10 3 2 -4 -10]
sort3 end: 12.25µs
*/
