// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// Unix时间戳转换 (Timestamp Conversion)
// 演示时间戳与日期时间字符串之间的相互转换

package main

import (
	"fmt"
	"time"
)

// timestampToDatetime 将Unix时间戳转换为日期时间字符串
// 参数: timestamp - 时间戳（秒）
// 返回: 格式化的日期时间字符串
func timestampToDatetime(timestamp int64) string {
	// 转换为time.Time对象
	t := time.Unix(timestamp, 0)
	// 格式化为字符串
	return t.Format("2006-01-02 15:04:05")
}

// datetimeToTimestamp 将日期时间字符串转换为Unix时间戳
// 参数: datetimeStr - 日期时间字符串 (格式: 2006-01-02 15:04:05)
// 返回: 时间戳（秒）
func datetimeToTimestamp(datetimeStr string) (int64, error) {
	layout := "2006-01-02 15:04:05"
	t, err := time.Parse(layout, datetimeStr)
	if err != nil {
		return -1, err
	}
	return t.Unix(), nil
}

// getCurrentTimestamp 获取当前时间戳（秒）
func getCurrentTimestamp() int64 {
	return time.Now().Unix()
}

// 测试主函数
func main() {
	fmt.Println("Unix时间戳转换测试")
	fmt.Println("==================")

	// 测试时间戳转日期
	timestamp := int64(1704067200) // 2024-01-01 00:00:00 UTC
	datetime := timestampToDatetime(timestamp)
	fmt.Printf("时间戳 %d -> 日期时间: %s\n", timestamp, datetime)

	// 测试日期转时间戳
	testDate := "2024-06-15 12:30:00"
	convertedTimestamp, err := datetimeToTimestamp(testDate)
	if err != nil {
		fmt.Printf("解析错误: %v\n", err)
	} else {
		fmt.Printf("日期时间 %s -> 时间戳: %d\n", testDate, convertedTimestamp)
	}

	// 测试当前时间戳
	current := getCurrentTimestamp()
	fmt.Printf("当前时间戳: %d\n", current)
	fmt.Printf("当前日期时间: %s\n", timestampToDatetime(current))
}
