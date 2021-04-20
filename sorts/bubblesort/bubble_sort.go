/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import "fmt"

func bubbleSort(list []int) {
	var length = len(list)
	for i := 0; i < length; i++ {
		fmt.Printf("\nno: %d\n", i)
		for j := 0; j < length-i-1; j++ {
			fmt.Printf("j=%d * i=%d | ", j, i)
			if list[j] > list[j+1] {
				var tmp = list[j+1]
				list[j+1] = list[j]
				list[j] = tmp
			}
		}
	}
	fmt.Println(list)
}

func bubbleSort2(list []int) []int {
	// 设立是否交换的标志
	flag := true
	for flag == true {
		flag = false
		// 当前项跟后一项进行比较，如果需要交换
		// 当没有任何一项需要交换时则终止循环
		for i := 0; i < len(list)-1; i++ {
			fmt.Printf("\n %d * %d\n", i, i+1)
			if list[i] < list[i+1] {
				list[i], list[i+1] = list[i+1], list[i]
				flag = true
			}
		}

	}

	return list
}

func bubbleSort3(list []int) []int {
	// 设立是否交换的标志
	flag := true
	length := len(list)
	for i := 0; i < length && flag == true; i++ {
		flag = false
		// 当前项跟后一项进行比较，如果需要交换
		// 当没有任何一项需要交换时则终止循环
		for j := 0; j < length-j-1; j++ {
			fmt.Printf("\nj=%d * i=%d | ", j, i)
			if list[j] < list[j+1] {
				flag = true
				list[j], list[j+1] = list[j+1], list[j]
			}
		}

	}

	return list
}

func main() {
	fmt.Println("bubble sort:")
	data := [...]int{3, 2, 10, -4, -10}
	bubbleSort(data[:])

	fmt.Println("bubble sort2:")
	data2 := [...]int{3, 2, 10, -4, -10}
	fmt.Println(bubbleSort2(data2[:]))

	fmt.Println("bubble sort3:")
	data3 := [...]int{3, 2, 10, -4, -10}
	fmt.Println(bubbleSort3(data3[:]))
}

/*
jarry@jarrys-MacBook-Pro bubblesort % go version
go version go1.15 darwin/amd64
jarry@jarrys-MacBook-Pro bubblesort % go build bubble_sort.go
jarry@jarrys-MacBook-Pro bubblesort % ./bubble_sort
bubble sort:

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
bubble sort3:

j=0 * i=0 |
j=1 * i=0 |
j=0 * i=1 |
j=1 * i=1 |
j=0 * i=2 |
j=1 * i=2 | [10 3 2 -4 -10]
*/
