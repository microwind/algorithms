// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 日历打印 (Calendar Printer)
// 根据年月输出当月日历
//
// 本文件提供两种算法实现：
// 1. Zeller公式法：通过数学公式直接计算星期几，计算速度快
// 2. 基准日期法：从1900年1月1日累加天数计算，直观易懂（与C版本一致）

package main

import "fmt"

// 基准日期设定：1900年1月1日，星期一（与C版本一致）
const startYear = 1900
const startMonth = 1
const startDay = 1
const startWeekday = 1 // 1=星期一

// 星期标题
var weekdays = []string{"日", "一", "二", "三", "四", "五", "六"}

// 月份名称
var monthNames = []string{
	"一月", "二月", "三月", "四月", "五月", "六月",
	"七月", "八月", "九月", "十月", "十一月", "十二月",
}

// isLeapYear 判断是否为闰年
// 闰年规则：能被4整除且不能被100整除，或能被400整除
func isLeapYear(year int) bool {
	return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)
}

// getMonthDays 获取某月的天数
func getMonthDays(year, month int) int {
	days := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if month == 2 && isLeapYear(year) {
		return 29
	}
	return days[month-1]
}

// getFirstWeekday_Zeller 使用Zeller公式计算某月第一天是星期几
// 算法特点：数学公式直接计算，O(1)时间复杂度
// 返回: 0=星期日, 1=星期一, ..., 6=星期六
func getFirstWeekday_Zeller(year, month int) int {
	if month < 3 {
		month += 12
		year -= 1
	}
	k := year % 100
	j := year / 100
	h := (1 + (13*(month+1))/5 + k + k/4 + j/4 - 2*j) % 7
	if h < 0 {
		h += 7
	}
	dayMap := []int{6, 0, 1, 2, 3, 4, 5}
	return dayMap[h]
}

// getWeekdayOfDate_Base 使用基准日期法计算指定日期是星期几
// 算法特点：从1900年1月1日累加天数，直观易懂
// 公式：(startWeekday + 天数差) % 7 = 目标星期
// 返回: 0=星期日, 1=星期一, ..., 6=星期六
func getWeekdayOfDate_Base(year, month, day int) int {
	weekday := startWeekday
	totalDays := weekday

	// 累加从1900年到目标年份-1的所有天数
	for i := startYear; i < year; i++ {
		totalDays += 365
		if isLeapYear(i) {
			totalDays += 1 // 闰年加1天
		}
	}

	// 累加从1月到目标月份-1的所有天数
	for i := startMonth; i < month; i++ {
		totalDays += getMonthDays(year, i)
	}

	// 加上目标日期与1日的差值
	if day > startDay {
		totalDays += (day - startDay)
	}

	// 对7取模得到星期
	return totalDays % 7
}

// getFirstWeekday 获取某月第一天是星期几（默认使用基准日期法，与C版本一致）
func getFirstWeekday(year, month int) int {
	// 使用基准日期法，与C版本calendar_simple.c算法一致
	return getWeekdayOfDate_Base(year, month, 1)
}

// printCalendar 打印日历
func printCalendar(year, month int) {
	fmt.Printf("\n      %s %d\n", monthNames[month-1], year)
	fmt.Println("===========================")

	// 打印星期标题
	for _, day := range weekdays {
		fmt.Printf("%3s ", day)
	}
	fmt.Println()

	// 计算第一天是星期几和该月天数
	firstWeekday := getFirstWeekday(year, month)
	daysInMonth := getMonthDays(year, month)

	// 打印第一行前面的空格
	for i := 0; i < firstWeekday; i++ {
		fmt.Print("    ")
	}

	// 打印日期
	weekday := firstWeekday
	for day := 1; day <= daysInMonth; day++ {
		fmt.Printf("%3d ", day)
		weekday++
		if weekday == 7 {
			fmt.Println()
			weekday = 0
		}
	}
	fmt.Println()
}

// 测试主函数
func main() {
	fmt.Println("日历打印程序")
	fmt.Println("============")

	// 打印2024年1月日历
	printCalendar(2024, 1)

	// 打印2024年6月日历
	printCalendar(2024, 6)
}

/*
jarry@Mac calendar % go run calendar_simple.go
日历打印程序
============

      一月 2024
===========================
  日   一   二   三   四   五   六
      1   2   3   4   5   6
  7   8   9  10  11  12  13
 14  15  16  17  18  19  20
 21  22  23  24  25  26  27
 28  29  30  31

      六月 2024
===========================
  日   一   二   三   四   五   六
                          1
  2   3   4   5   6   7   8
  9  10  11  12  13  14  15
 16  17  18  19  20  21  22
 23  24  25  26  27  28  29
 30
*/
