// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 温度转换 (Temperature Conversion)
// 摄氏度、华氏度、开尔文之间的相互转换

package main

import "fmt"

// celsiusToFahrenheit 摄氏度转华氏度
// 公式: °F = °C × 9/5 + 32
func celsiusToFahrenheit(celsius float64) float64 {
	return celsius*9.0/5.0 + 32.0
}

// fahrenheitToCelsius 华氏度转摄氏度
// 公式: °C = (°F - 32) × 5/9
func fahrenheitToCelsius(fahrenheit float64) float64 {
	return (fahrenheit - 32.0) * 5.0 / 9.0
}

// celsiusToKelvin 摄氏度转开尔文
// 公式: K = °C + 273.15
func celsiusToKelvin(celsius float64) float64 {
	return celsius + 273.15
}

// kelvinToCelsius 开尔文转摄氏度
// 公式: °C = K - 273.15
func kelvinToCelsius(kelvin float64) float64 {
	return kelvin - 273.15
}

// fahrenheitToKelvin 华氏度转开尔文
func fahrenheitToKelvin(fahrenheit float64) float64 {
	return celsiusToKelvin(fahrenheitToCelsius(fahrenheit))
}

// kelvinToFahrenheit 开尔文转华氏度
func kelvinToFahrenheit(kelvin float64) float64 {
	return celsiusToFahrenheit(kelvinToCelsius(kelvin))
}

// 测试主函数
func main() {
	fmt.Println("温度转换测试")
	fmt.Println("============")

	celsius := 25.0
	fmt.Printf("摄氏度 %.2f°C = 华氏度 %.2f°F\n",
		celsius, celsiusToFahrenheit(celsius))
	fmt.Printf("摄氏度 %.2f°C = 开尔文 %.2fK\n",
		celsius, celsiusToKelvin(celsius))

	fahrenheit := 98.6
	fmt.Printf("华氏度 %.2f°F = 摄氏度 %.2f°C\n",
		fahrenheit, fahrenheitToCelsius(fahrenheit))

	kelvin := 300.0
	fmt.Printf("开尔文 %.2fK = 摄氏度 %.2f°C\n",
		kelvin, kelvinToCelsius(kelvin))
	fmt.Printf("开尔文 %.2fK = 华氏度 %.2f°F\n",
		kelvin, kelvinToFahrenheit(kelvin))
}
