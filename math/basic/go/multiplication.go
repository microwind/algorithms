package main

import "fmt"

func multiply(a, b int) int {
	return a * b
}

func multiplySafe(a, b int) (int, bool) {
	result := a * b
	if a != 0 && result/a != b {
		return result, false
	}
	return result, true
}

func TestMultiplicationMain() {
	fmt.Println("乘法运算:")
	fmt.Printf("12 × 8 = %d\n", multiply(12, 8))
	fmt.Printf("7 × 8 = %d\n", multiply(7, 8))
}
