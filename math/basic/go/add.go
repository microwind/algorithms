package main

import "fmt"

func add(a, b int) int {
	return a + b
}

func safeAdd(a, b int) (int, bool) {
	result := a + b
	if (a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0) {
		return result, false
	}
	return result, true
}

func testAdd() {
	fmt.Println("加法运算:")
	fmt.Printf("5 + 3 = %d\n", add(5, 3))
	fmt.Printf("100 + 200 = %d\n", add(100, 200))
}
