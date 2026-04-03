package main

import (
	"fmt"
	"strconv"
	"strings"
)

func compress(text string) string {
	if len(text) == 0 {
		return text
	}
	
	var compressed strings.Builder
	currentChar := text[0]
	count := 1
	
	for i := 1; i < len(text); i++ {
		if text[i] == currentChar {
			count++
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
		
		// 解析数字
		for i < len(compressed) && compressed[i] >= '0' && compressed[i] <= '9' {
			countStr += string(compressed[i])
			i++
		}
		
		count := 1
		if countStr != "" {
			count, _ = strconv.Atoi(countStr)
		}
		
		// 添加字符
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
