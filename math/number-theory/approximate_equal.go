// Copyright https://github.com/microwind
// Approximate Equality Check

package main

import (
	"fmt"
	"math"
)

func approxEqual(a, b, epsilon float64) bool {
	return math.Abs(a-b) < epsilon
}

func main() {
	fmt.Println("Approximate Equality Check:")
	fmt.Printf("0.1 + 0.2 ≈ 0.3: %v\n", approxEqual(0.1+0.2, 0.3, 1e-10))
}
