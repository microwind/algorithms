// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 闰年判断 (Leap Year Check)
// 判断给定年份是否为闰年

package main

import "fmt"

// isLeapYear 判断是否为闰年
// 参数: year - 待判断的年份
// 返回: true表示闰年，false表示平年
func isLeapYear(year int) bool {
	// 闰年条件：能被4整除且不能被100整除，或者能被400整除
	return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)
}

// 测试主函数
func main() {
	testYears := []int{2000, 2004, 1900, 2023, 2024}
	
	fmt.Println("闰年判断测试")
	fmt.Println("============")
	
	for _, year := range testYears {
		isLeap := isLeapYear(year)
		if isLeap {
			fmt.Printf("%d年: 闰年\n", year)
		} else {
			fmt.Printf("%d年: 平年\n", year)
		}
	}
}
