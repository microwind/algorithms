package main

import (
	"fmt"
	"math"
	"math/rand"
)

func trapezoidalRule(f func(float64) float64, a, b float64, n int) float64 {
	h := (b - a) / float64(n)
	sum := 0.5 * (f(a) + f(b))
	
	for i := 1; i < n; i++ {
		x := a + float64(i)*h
		sum += f(x)
	}
	
	return sum * h
}

func simpsonsRule(f func(float64) float64, a, b float64, n int) float64 {
	if n%2 != 0 {
		n++ // 确保n为偶数
	}
	
	h := (b - a) / float64(n)
	sum := f(a) + f(b)
	
	for i := 1; i < n; i++ {
		x := a + float64(i)*h
		if i%2 == 0 {
			sum += 2 * f(x)
		} else {
			sum += 4 * f(x)
		}
	}
	
	return sum * h / 3
}

func monteCarloIntegration(f func(float64) float64, a, b float64, samples int) float64 {
	sum := 0.0
	
	for i := 0; i < samples; i++ {
		x := a + (b-a)*rand.Float64()
		sum += f(x)
	}
	
	return (b - a) * sum / float64(samples)
}

func main() {
	// 测试函数：f(x) = x^2
	f := func(x float64) float64 { return x * x }
	
	a, b := 0.0, 1.0
	n := 1000
	
	fmt.Println("数值积分测试 (f(x) = x^2, [0,1]):")
	
	trapezoidal := trapezoidalRule(f, a, b, n)
	fmt.Printf("梯形法则: %.6f\n", trapezoidal)
	
	simpson := simpsonsRule(f, a, b, n)
	fmt.Printf("辛普森法则: %.6f\n", simpson)
	
	monteCarlo := monteCarloIntegration(f, a, b, 10000)
	fmt.Printf("蒙特卡洛积分: %.6f\n", monteCarlo)
	
	fmt.Printf("精确值: %.6f\n", 1.0/3.0)
}
