// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

// 温度单位转换 (Temperature Unit Conversion)
// 摄氏度与华氏度之间的相互转换

package main

import "fmt"

func celsiusToFahrenheit(c float64) float64 {
	return 9.0/5.0*c + 32
}

func fahrenheitToCelsius(f int) int {
	return 5 * (f - 32) / 9
}

func printConversionTable(start, end, step int) {
	fmt.Println("摄氏度到华氏度转换表")
	fmt.Println("摄氏度 | 华氏度")
	fmt.Println("-------|-------")
	
	for c := start; c <= end; c += step {
		f := celsiusToFahrenheit(float64(c))
		fmt.Printf("%6d  | %6.1f\n", c, f)
	}
}

func main() {
	fmt.Println("温度单位转换演示")
	fmt.Println("================\n")
	
	printConversionTable(0, 100, 5)
	
	fmt.Println("\n转换公式:")
	fmt.Println("• 摄氏度→华氏度: °F = °C × 9/5 + 32")
	fmt.Println("• 华氏度→摄氏度: °C = (°F - 32) × 5/9")
}
