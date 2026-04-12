/**
 * 游程编码(RLE)实现 - Go
 * 核心：连续重复字符转为"字符+计数"
 */

package main

import (
	"fmt"
	"strconv"
	"strings"
)

// 压缩：连续相同字符编码为字符+计数
func compress(text string) string {
	if len(text) == 0 {
		return text
	}
	
	var compressed strings.Builder
	currentChar := text[0]
	count := 1
	
	// 遍历统计连续字符
	for i := 1; i < len(text); i++ {
		if text[i] == currentChar {
			count++  // 连续字符，计数+1
		} else {
			compressed.WriteByte(currentChar)
			if count > 1 {
				compressed.WriteString(strconv.Itoa(count))
			}
			currentChar = text[i]
			count = 1
		}
	}
	
	// 处理最后一个字符
	compressed.WriteByte(currentChar)
	if count > 1 {
		compressed.WriteString(strconv.Itoa(count))
	}
	
	return compressed.String()
}

// 解压：解析"字符+计数"还原字符串
func decompress(compressed string) string {
	if len(compressed) == 0 {
		return compressed
	}
	
	var decompressed strings.Builder
	i := 0
	
	for i < len(compressed) {
		currentChar := compressed[i]
		i++
		
		countStr := ""
		
		// 解析连续数字（计数）
		for i < len(compressed) && compressed[i] >= '0' && compressed[i] <= '9' {
			countStr += string(compressed[i])
			i++
		}
		
		count := 1
		if countStr != "" {
			count, _ = strconv.Atoi(countStr)
		}
		
		// 重复字符count次
		for j := 0; j < count; j++ {
			decompressed.WriteByte(currentChar)
		}
	}
	
	return decompressed.String()
}

func compressionRatio(original, compressed string) float64 {
	return float64(len(compressed)) / float64(len(original))
}

func main() {
	text := "AAAABBBCCDAA"
	fmt.Printf("原始文本: %s\n", text)
	
	compressed := compress(text)
	fmt.Printf("压缩后: %s\n", compressed)
	
	decompressed := decompress(compressed)
	fmt.Printf("解压后: %s\n", decompressed)
	
	fmt.Printf("压缩比: %.2f\n", compressionRatio(text, compressed))
	fmt.Printf("验证: %t\n", text == decompressed)
}
