package main

import "fmt"

func isPrime(n int) bool {
	if n < 2 {
		return false
	}
	if n == 2 {
		return true
	}
	if n%2 == 0 {
		return false
	}
	for i := 3; i*i <= n; i += 2 {
		if n%i == 0 {
			return false
		}
	}
	return true
}

func TestPrimeMain() {
	fmt.Println("素数判定:")
	for i := 1; i <= 20; i++ {
		if isPrime(i) {
			fmt.Printf("%d ", i)
		}
	}
	fmt.Println()
}
