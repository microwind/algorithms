// Copyright https://github.com/microwind
// Digit Sum

package main

import "fmt"

func digitSum(n int) int {
	sum := 0
	for n > 0 {
		sum += n % 10
		n /= 10
	}
	return sum
}

func main() {
	n := 12345
	fmt.Printf("Digit sum of %d = %d\n", n, digitSum(n))
}
