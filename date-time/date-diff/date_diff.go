// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 日期差计算 (Date Difference)
// 计算两个日期之间的天数差

package main

import (
	"fmt"
	"math"
)

// Date 日期结构体
type Date struct {
	Year  int
	Month int
	Day   int
}

// isLeapYear 判断是否为闰年
func isLeapYear(year int) bool {
	return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)
}

// daysInMonth 获取某月的天数
func daysInMonth(year, month int) int {
	days := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if month == 2 && isLeapYear(year) {
		return 29 // 闰年2月有29天
	}
	return days[month-1]
}

// daysSinceEpoch 计算从公元1年1月1日到给定日期的天数
func daysSinceEpoch(date Date) int {
	days := 0

	// 计算之前年份的天数
	for y := 1; y < date.Year; y++ {
		if isLeapYear(y) {
			days += 366
		} else {
			days += 365
		}
	}

	// 计算之前月份的天数
	for m := 1; m < date.Month; m++ {
		days += daysInMonth(date.Year, m)
	}

	// 计算当月的天数
	days += date.Day

	return days
}

// daysBetween 计算两个日期之间的天数差
func daysBetween(date1, date2 Date) int {
	days1 := daysSinceEpoch(date1)
	days2 := daysSinceEpoch(date2)
	return int(math.Abs(float64(days2 - days1)))
}

// 测试主函数
func main() {
	date1 := Date{2024, 1, 1}   // 元旦
	date2 := Date{2024, 10, 1}  // 国庆节

	diff := daysBetween(date1, date2)
	fmt.Println("日期差计算测试")
	fmt.Println("============")
	fmt.Printf("从 %d-%02d-%02d 到 %d-%02d-%02d\n",
		date1.Year, date1.Month, date1.Day,
		date2.Year, date2.Month, date2.Day)
	fmt.Printf("相差天数: %d 天\n", diff)
}
