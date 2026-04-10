// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 完整版日历打印程序 (Calendar - Full Version)
// 根据年月输出当月日历，支持显示前后月份日期
//
// 核心算法：
// 1. 以1900年1月1日（星期一）为基准日期
// 2. 使用累加天数法计算任意日期是星期几
// 3. 日历显示包含上个月末尾几天和下个月开头几天

package main

import "fmt"

// 基准日期设定：1900年1月1日，星期一
const startYear = 1900
const startMonth = 1
const startDay = 1
const startWeekday = 1 // 1=星期一

// 星期标题
var weekdays = []string{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}

// 月份名称
var monthNames = []string{
	"Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
	"Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec.",
}

// isLeapYear 判断是否为闰年
func isLeapYear(year int) bool {
	return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)
}

// getMonthDays 获取某月的天数
func getMonthDays(month, year int) int {
	switch month {
	case 2:
		if isLeapYear(year) {
			return 29
		}
		return 28
	case 4, 6, 9, 11:
		return 30
	default:
		return 31
	}
}

// getLastMonthDays 获取上个月的天数
func getLastMonthDays(month, year int) int {
	lastMonth := month - 1
	lastYear := year
	if month == 1 {
		lastMonth = 12
		lastYear = year - 1
	}
	return getMonthDays(lastMonth, lastYear)
}

// getWeekdayOfDate 计算指定日期是星期几（核心算法）
func getWeekdayOfDate(month, day, year int) int {
	weekday := startWeekday

	// 累加从1900年到目标年份-1的所有天数
	for i := startYear; i < year; i++ {
		weekday = (weekday + 365) % 7
		if isLeapYear(i) {
			weekday = (weekday + 1) % 7
		}
	}

	// 累加从1月到目标月份-1的所有天数
	for i := startMonth; i < month; i++ {
		weekday = (weekday + getMonthDays(i, year)) % 7
	}

	// 加上目标日期与1日的差值
	if day > startDay {
		weekday = (weekday + (day - startDay)) % 7
	}

	return weekday
}

// getFirstWeekdayOfMonth 获取某月第一天是星期几
func getFirstWeekdayOfMonth(month, year int) int {
	return getWeekdayOfDate(month, 1, year)
}

// getLastWeekdayOfMonth 获取某月最后一天是星期几
func getLastWeekdayOfMonth(month, year int) int {
	lastDay := getMonthDays(month, year)
	return getWeekdayOfDate(month, lastDay, year)
}

// printCalendarTitle 打印日历标题
func printCalendarTitle(month, year int) {
	fmt.Printf("%12s%4s %d\n", "", monthNames[month-1], year)
}

// printWeeklyTitle 打印星期标题
func printWeeklyTitle() {
	for _, day := range weekdays {
		fmt.Printf("%5s", day)
	}
}

// printLastMonthLastDays 打印上个月最后几天（用"]"标记）
func printLastMonthLastDays(weekday, month, year int) {
	lastDays := getLastMonthDays(month, year)
	startDay := lastDays - weekday + 1
	for i := startDay; i <= lastDays; i++ {
		fmt.Printf("%2s%2d]", "", i)
	}
}

// printNextMonthStartDays 打印下个月开始几天（用"]"标记）
func printNextMonthStartDays(weekday int) {
	nextDays := 7 - weekday
	for i := 1; i < nextDays; i++ {
		fmt.Printf("%2s%2d]", "", i)
	}
}

// printCalendar 打印日历（包含前后月份日期）
func printCalendar(month, year int) {
	// 打印标题和星期标题
	printCalendarTitle(month, year)
	printWeeklyTitle()
	fmt.Println()

	// 计算当月第一天是周几
	firstWeekday := getFirstWeekdayOfMonth(month, year)
	weekday := firstWeekday

	// 打印上个月最后几天
	printLastMonthLastDays(weekday, month, year)

	// 获取当月总天数
	daysInMonth := getMonthDays(month, year)

	// 循环输出当月所有日期
	for day := 1; day <= daysInMonth; day++ {
		fmt.Printf("%2s", "")
		fmt.Printf("%3d", day)
		if weekday == 6 {
			fmt.Println()
		}
		weekday = (weekday + 1) % 7
	}

	// 打印下个月开头几天
	lastWeekday := getLastWeekdayOfMonth(month, year)
	printNextMonthStartDays(lastWeekday)
}

// main 测试主函数
func main() {
	fmt.Println("完整版日历打印程序")
	fmt.Println("==================")

	month := 12
	day := 30
	year := 2003

	// 测试：计算2003年12月30日是星期几
	weekday := getWeekdayOfDate(month, day, year)
	fmt.Printf("[%d] = %s\n", weekday, weekdays[weekday])
	fmt.Printf("TEST: %s %d days = %d\n", monthNames[month-1], year, getMonthDays(month, year))
	fmt.Printf("%d-%d-%d is %s = weekdays[%d]\n", year, month, day, weekdays[weekday], weekday)
	fmt.Println()

	// 循环打印48个月的日历（4年）
	tmpMonth := 0
	tmpYear := year
	maxMonth := 48

	for m := 0; m < maxMonth; m++ {
		tmpMonth++
		if tmpMonth == 13 {
			tmpMonth = 1
			tmpYear++
		}
		fmt.Printf("%d-%d\n", tmpMonth, tmpYear)
		printCalendar(tmpMonth, tmpYear)
		fmt.Println("\n")
	}
}
