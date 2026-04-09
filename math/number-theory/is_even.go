// Copyright https://github.com/microwind
// Check if number is even/odd

package main

import "fmt"

func isEven(n int) bool {
	return n%2 == 0
}

func main() {
	testNumbers := []int{2, 3, 4, 5, 10, 15}
	for _, n := range testNumbers {
		if isEven(n) {
			fmt.Printf("%d is even\n", n)
		} else {
			fmt.Printf("%d is odd\n", n)
		}
	}
}
