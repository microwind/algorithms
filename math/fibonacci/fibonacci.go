// Copyright https://github.com/microwind
// Fibonacci Sequence

package main

import "fmt"

func fibonacci(n int) int64 {
	if n <= 1 {
		return int64(n)
	}
	var first int64 = 0
	var second int64 = 1
	var result int64 = 0
	for i := 1; i < n; i++ {
		result = first + second
		first = second
		second = result
	}
	return result
}

func main() {
	fmt.Println("Fibonacci Sequence:")
	for i := 0; i <= 10; i++ {
		fmt.Printf("F(%d) = %d\n", i, fibonacci(i))
	}
}
