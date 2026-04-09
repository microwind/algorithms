package main

import "fmt"

func average(numbers []float64) float64 {
	if len(numbers) == 0 {
		return 0
	}
	var sum float64
	for _, n := range numbers {
		sum += n
	}
	return sum / float64(len(numbers))
}

func averageSafe(a, b int64) float64 {
	return float64(a)/2.0 + float64(b)/2.0
}

func testAverage() {
	fmt.Println("平均值计算:")
	numbers := []float64{10, 20, 30, 40, 50}
	fmt.Printf("平均值 = %.2f\n", average(numbers))
}
