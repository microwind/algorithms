package main

import (
	"fmt"
	"math"
	"sort"
)

func mean(data []float64) float64 {
	sum := 0.0
	for _, value := range data {
		sum += value
	}
	return sum / float64(len(data))
}

func median(data []float64) float64 {
	sorted := make([]float64, len(data))
	copy(sorted, data)
	sort.Float64s(sorted)
	
	n := len(sorted)
	if n%2 == 0 {
		return (sorted[n/2-1] + sorted[n/2]) / 2
	}
	return sorted[n/2]
}

func variance(data []float64) float64 {
	meanValue := mean(data)
	sum := 0.0
	for _, value := range data {
		sum += math.Pow(value-meanValue, 2)
	}
	return sum / float64(len(data))
}

func standardDeviation(data []float64) float64 {
	return math.Sqrt(variance(data))
}

func percentile(data []float64, percentile float64) float64 {
	sorted := make([]float64, len(data))
	copy(sorted, data)
	sort.Float64s(sorted)
	
	index := (percentile / 100.0) * float64(len(sorted)-1)
	lower := int(math.Floor(index))
	upper := int(math.Ceil(index))
	
	if lower == upper {
		return sorted[lower]
	}
	
	weight := index - float64(lower)
	return sorted[lower]*(1-weight) + sorted[upper]*weight
}

func skewness(data []float64) float64 {
	meanValue := mean(data)
	std := standardDeviation(data)
	sum := 0.0
	
	for _, value := range data {
		sum += math.Pow((value-meanValue)/std, 3)
	}
	
	return sum / float64(len(data))
}

func kurtosis(data []float64) float64 {
	meanValue := mean(data)
	std := standardDeviation(data)
	sum := 0.0
	
	for _, value := range data {
		sum += math.Pow((value-meanValue)/std, 4)
	}
	
	return sum/float64(len(data)) - 3 // 减去3得到超额峰度
}

func main() {
	data := []float64{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	
	fmt.Println("描述统计测试:")
	fmt.Printf("均值: %.2f\n", mean(data))
	fmt.Printf("中位数: %.2f\n", median(data))
	fmt.Printf("方差: %.2f\n", variance(data))
	fmt.Printf("标准差: %.2f\n", standardDeviation(data))
	fmt.Printf("25%分位数: %.2f\n", percentile(data, 25))
	fmt.Printf("75%分位数: %.2f\n", percentile(data, 75))
	fmt.Printf("偏度: %.2f\n", skewness(data))
	fmt.Printf("峰度: %.2f\n", kurtosis(data))
}
