// Copyright https://github.com/microwind
// Fast Power (Binary Exponentiation)

package main

import "fmt"

func fastPower(base, exponent, mod int64) int64 {
	result := int64(1)
	base = base % mod
	for exponent > 0 {
		if exponent&1 == 1 {
			result = (result * base) % mod
		}
		base = (base * base) % mod
		exponent >>= 1
	}
	return result
}

func main() {
	fmt.Printf("2^10 = %d\n", fastPower(2, 10, 1000000007))
	fmt.Printf("3^5 = %d\n", fastPower(3, 5, 1000000007))
}
