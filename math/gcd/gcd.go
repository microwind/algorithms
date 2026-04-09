// Copyright https://github.com/microwind
// GCD - Greatest Common Divisor

package main

import "fmt"

func gcd(x, y int) int {
	for y != 0 {
		x, y = y, x%y
	}
	return x
}

func main() {
	fmt.Printf("GCD(48, 18) = %d\n", gcd(48, 18))
	fmt.Printf("GCD(56, 98) = %d\n", gcd(56, 98))
}
