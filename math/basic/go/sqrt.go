package main

import (
	"fmt"
	"math"
)

func sqrtNewton(n, epsilon float64) float64 {
	if n < 0 {
		panic("不能计算负数的平方根")
	}
	if n == 0 {
		return 0
	}
	x := n
	for math.Abs(x*x-n) > epsilon {
		x = (x + n/x) / 2.0
	}
	return x
}

func TestSqrtMain() {
	fmt.Println("平方根计算:")
	testValues := []float64{1, 2, 4, 9, 16, 25, 100}
	for _, n := range testValues {
		result := sqrtNewton(n, 1e-10)
		fmt.Printf("sqrt(%.0f) = %.10f\n", n, result)
	}
}
