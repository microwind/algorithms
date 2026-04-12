/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description:
 *  LZ77压缩算法实现 - Go
 *  核心：滑动窗口查找重复模式，输出(offset, length, char)三元组
 */

package main

import (
	"fmt"
	"strings"
)

// Token: LZ77压缩令牌 (偏移量, 匹配长度, 下一个字符)
type Token struct {
	Offset    int
	Length    int
	Character rune
}

func (t Token) String() string {
	if t.Length > 0 {
		return fmt.Sprintf("(%d,%d)", t.Offset, t.Length)
	}
	return fmt.Sprintf("(%c)", t.Character)
}

// LZ77压缩：滑动窗口查找最长匹配
func lz77Compress(input string) []Token {
	fmt.Println("LZ77压缩开始...")
	var tokens []Token
	windowSize := 256  // 滑动窗口大小
	position := 0
	
	for position < len(input) {
		// 计算当前窗口范围
		maxLength := windowSize
		if position < windowSize {
			maxLength = position
		}
		
		window := input[position-maxLength : position]
		
		bestLength := 0
		bestOffset := 0
		
		// 在窗口中搜索最长匹配串
		for i := 0; i < len(window); i++ {
			matchLength := 0
			for position+matchLength < len(input) &&
				i+matchLength < len(window) &&
				input[position+matchLength] == window[i+matchLength] {
				matchLength++
			}
			
			if matchLength > bestLength {
				bestLength = matchLength
				bestOffset = len(window) - i
			}
		}
		
		if bestLength >= 3 { // 最小匹配长度
			var nextChar rune
			if position+bestLength < len(input) {
				nextChar = rune(input[position+bestLength])
			}
			tokens = append(tokens, Token{bestOffset, bestLength, nextChar})
			fmt.Printf("找到匹配: 偏移=%d, 长度=%d\n", bestOffset, bestLength)
			position += bestLength + 1
		} else {
			tokens = append(tokens, Token{0, 0, rune(input[position])})
			fmt.Printf("字面量: %c\n", input[position])
			position++
		}
	}
	
	fmt.Printf("LZ77压缩完成，令牌数: %d\n", len(tokens))
	return tokens
}

func lz77Decompress(tokens []Token) string {
	fmt.Println("LZ77解压开始...")
	var output strings.Builder
	
	for i, token := range tokens {
		fmt.Printf("处理令牌 %d: %v\n", i, token)
		
		if token.Length > 0 {
			start := output.Len() - token.Offset
			for j := 0; j < token.Length; j++ {
				output.WriteByte(output.String()[start+j])
			}
			if token.Character != 0 {
				output.WriteRune(token.Character)
			}
		} else {
			output.WriteRune(token.Character)
		}
	}
	
	fmt.Printf("LZ77解压完成，长度: %d\n", output.Len())
	return output.String()
}

func compressionRatio(original string, compressed []Token) float64 {
	originalSize := len(original) * 8 // 假设每个字符8位
	compressedSize := 0
	for _, token := range compressed {
		compressedSize += 16 // 偏移和长度各8位
		if token.Length > 0 {
			compressedSize += 8 // 字符8位
		}
	}
	return float64(compressedSize) / float64(originalSize)
}

func main() {
	// 主函数，演示LZ77压缩和解压
	input := "ABABABABABAABABABABA"
	fmt.Println("=== LZ77算法演示 ===")
	fmt.Printf("原始文本: %s\n", input)
	fmt.Printf("原始长度: %d\n", len(input))
	
	// 压缩
	compressed := lz77Compress(input)
	fmt.Printf("压缩结果: %v\n", compressed)
	
	// 计算压缩比
	ratio := compressionRatio(input, compressed)
	fmt.Printf("压缩比: %.2f\n", ratio)
	
	// 解压
	decompressed := lz77Decompress(compressed)
	fmt.Printf("解压结果: %s\n", decompressed)
	fmt.Printf("解压长度: %d\n", len(decompressed))
	
	// 验证
	isValid := input == decompressed
	if isValid {
		fmt.Println("验证结果: ✓ 成功")
	} else {
		fmt.Println("验证结果: ✗ 失败")
	}
	fmt.Println("=== 演示结束 ===")
}
