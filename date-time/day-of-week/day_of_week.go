// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 星期计算 (Day of Week)
// 使用 Zeller 公式计算给定日期是星期几

package main

import "fmt"

// 星期名称（中文）
var weekdayNamesCN = []string{
	"星期日", "星期一", "星期二", "星期三",
	"星期四", "星期五", "星期六",
}

// dayOfWeek 使用 Zeller 公式计算星期几
// 参数:
//     year: 年份
//     month: 月份 (1-12)
//     day: 日期 (1-31)
// 返回: 0=星期日, 1=星期一, ..., 6=星期六
func dayOfWeek(year, month, day int) int {
	// 调整月份：1月和2月视为上一年的13月和14月
	if month < 3 {
		month += 12
		year -= 1
	}

	q := day           // 日期
	m := month         // 调整后的月份
	k := year % 100    // 世纪内的年份
	j := year / 100    // 零基世纪

	// Zeller 公式计算
	h := (q + (13*(m+1))/5 + k + k/4 + j/4 - 2*j) % 7

	// 处理负数情况
	if h < 0 {
		h += 7
	}

	// 转换映射：Zeller结果 -> 标准结果 (0=星期日)
	dayMap := []int{6, 0, 1, 2, 3, 4, 5}
	return dayMap[h]
}

// 测试主函数
func main() {
	testDates := [][3]int{
		{2024, 1, 1},    // 元旦
		{2024, 2, 10},   // 春节
		{2024, 10, 1},   // 国庆节
		{2000, 1, 1},    // 千禧年
		{1949, 10, 1},   // 建国日
	}

	fmt.Println("星期计算测试")
	fmt.Println("============")

	for _, date := range testDates {
		year, month, day := date[0], date[1], date[2]
		weekday := dayOfWeek(year, month, day)
		name := weekdayNamesCN[weekday]
		fmt.Printf("%d-%02d-%02d: %s\n", year, month, day, name)
	}
}
