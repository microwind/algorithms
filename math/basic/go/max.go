package main

import "fmt"

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func testMax() {
	fmt.Println("最大值/最小值:")
	fmt.Printf("max(5, 3) = %d\n", max(5, 3))
	fmt.Printf("min(5, 3) = %d\n", min(5, 3))
}
