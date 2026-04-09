// Copyright https://github.com/microwind
// Perfect Number Check

package main

import "fmt"

func isPerfect(n int) bool {
	if n <= 1 {
		return false
	}
	sum := 1
	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			sum += i
			if i != n/i {
				sum += n / i
			}
		}
	}
	return sum == n
}

func main() {
	fmt.Print("Perfect numbers up to 1000: ")
	for i := 1; i <= 1000; i++ {
		if isPerfect(i) {
			fmt.Printf("%d ", i)
		}
	}
	fmt.Println()
}
