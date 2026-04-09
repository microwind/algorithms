package main

import (
	"fmt"
	"math/big"
)

func fibonacci(n int) *big.Int {
	if n <= 1 {
		return big.NewInt(int64(n))
	}
	a := big.NewInt(0)
	b := big.NewInt(1)
	for i := 2; i <= n; i++ {
		temp := new(big.Int).Add(a, b)
		a, b = b, temp
	}
	return b
}

func TestFibonacciMain() {
	fmt.Println("斐波那契数列:")
	for i := 0; i < 20; i++ {
		fmt.Printf("F(%d) = %s\n", i, fibonacci(i).String())
	}
}
