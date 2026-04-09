// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

// 组合计算 (Combination)
// 计算从n个元素中选取k个元素的组合数

package main

import "fmt"

// 计算阶乘
func factorial(n int) int64 {
	var product int64 = 1
	for i := 1; i <= n; i++ {
		product *= int64(i)
	}
	return product
}

// 计算组合数 C(n,k)
func combine(n, k int) int64 {
	return factorial(n) / (factorial(k) * factorial(n-k))
}

func main() {
	n := 5
	fmt.Println("组合计算 C(n,k)")
	fmt.Println("===============")
	
	for k := 1; k <= n; k++ {
		result := combine(n, k)
		fmt.Printf("C(%d,%d) = %d\n", n, k, result)
	}
}
