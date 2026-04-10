// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 日期格式化与解析 (Date Format)
// 支持多种日期格式转换

package main

import (
	"fmt"
	"strings"
)

// 英文月份名称
var monthNamesEN = []string{
	"January", "February", "March", "April",
	"May", "June", "July", "August",
	"September", "October", "November", "December",
}

// 中文月份名称
var monthNamesCN = []string{
	"一月", "二月", "三月", "四月",
	"五月", "六月", "七月", "八月",
	"九月", "十月", "十一月", "十二月",
}

// formatDate 将日期格式化为不同格式的字符串
// 参数: year, month, day - 年月日, format - 格式类型: "ISO", "US", "CN", "FULL"
// 返回: 格式化后的日期字符串
func formatDate(year, month, day int, format string) string {
	return formatDateTime(year, month, day, 0, 0, 0, format)
}

// formatDateTime 将日期时间格式化为不同格式的字符串
func formatDateTime(year, month, day, hour, minute, second int, format string) string {
	fmtUpper := strings.ToUpper(format)
	
	switch fmtUpper {
	case "ISO":
		// ISO 8601: 2024-01-01
		return fmt.Sprintf("%04d-%02d-%02d", year, month, day)
	case "US":
		// US格式: 01/01/2024
		return fmt.Sprintf("%02d/%02d/%04d", month, day, year)
	case "CN":
		// 中文格式: 2024年01月01日
		return fmt.Sprintf("%04d年%02d月%02d日", year, month, day)
	case "FULL":
		// 完整格式: 2024-01-01 12:30:45
		return fmt.Sprintf("%04d-%02d-%02d %02d:%02d:%02d",
			year, month, day, hour, minute, second)
	default:
		return "Unknown format"
	}
}

// getMonthName 获取月份名称
// 参数: month - 月份 (1-12), chinese - 是否返回中文名称
// 返回: 月份名称
func getMonthName(month int, chinese bool) string {
	if month < 1 || month > 12 {
		if chinese {
			return "未知"
		}
		return "Unknown"
	}
	if chinese {
		return monthNamesCN[month-1]
	}
	return monthNamesEN[month-1]
}

// 测试主函数
func main() {
	fmt.Println("日期格式化示例")
	fmt.Println("==============")
	
	year, month, day := 2024, 3, 15
	hour, minute, second := 14, 30, 0
	
	fmt.Printf("原始日期: %d年%d月%d日\n", year, month, day)
	fmt.Println()
	
	// 测试各种格式
	fmt.Printf("ISO格式:   %s\n", formatDate(year, month, day, "ISO"))
	fmt.Printf("US格式:    %s\n", formatDate(year, month, day, "US"))
	fmt.Printf("中文格式:  %s\n", formatDate(year, month, day, "CN"))
	fmt.Printf("完整格式:  %s\n", formatDateTime(year, month, day, hour, minute, second, "FULL"))
	fmt.Println()
	
	// 测试月份名称
	fmt.Println("月份名称:")
	fmt.Printf("  英文: %s\n", getMonthName(month, false))
	fmt.Printf("  中文: %s\n", getMonthName(month, true))
}
