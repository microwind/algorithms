/*
*
 * LZW压缩算法 - 字典压缩
 *
 * 问题：使用动态字典进行无损数据压缩
 *
 * 核心思想：
 * - 动态构建编码字典
 * - 查找最长匹配字符串
 * - 输出字典索引
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

package main

import (
	"fmt"
	"strconv"
)

const maxDictSize = 4096

/*
*
 * LZW压缩
*/
func lzwCompress(input string) []int {
	dictionary := make(map[string]int)

	// 初始化字典（单字符）
	for i := 0; i < 256; i++ {
		dictionary[string(rune(i))] = i
	}

	compressed := []int{}
	current := ""
	dictSize := 256

	for _, char := range input {
		combined := current + string(char)

		if _, exists := dictionary[combined]; exists {
			current = combined
		} else {
			// 输出current的编码
			compressed = append(compressed, dictionary[current])

			// 将combined加入字典
			if dictSize < maxDictSize {
				dictionary[combined] = dictSize
				dictSize++
			}

			// 重置current为char
			current = string(char)
		}
	}

	// 输出最后一个编码
	if current != "" {
		compressed = append(compressed, dictionary[current])
	}

	return compressed
}

/*
*
 * LZW解压
*/
func lzwDecompress(compressed []int) string {
	dictionary := make(map[int]string)

	// 初始化字典（单字符）
	for i := 0; i < 256; i++ {
		dictionary[i] = string(rune(i))
	}

	output := ""
	oldCode := compressed[0]
	oldString := dictionary[oldCode]
	output += oldString

	dictSize := 256

	for i := 1; i < len(compressed); i++ {
		newCode := compressed[i]
		var stringVal string

		if _, exists := dictionary[newCode]; !exists {
			// 特殊情况：new_code不在字典中
			stringVal = oldString + string(oldString[0])
		} else {
			stringVal = dictionary[newCode]
		}

		output += stringVal

		// 将old_string + string[0]加入字典
		if dictSize < maxDictSize {
			dictionary[dictSize] = oldString + string(stringVal[0])
			dictSize++
		}

		oldString = stringVal
	}

	return output
}

/*
*
 * 主函数
*/
func main() {
	input := "TOBEORNOTTOBEORTOBEORNOT"
	fmt.Println("=== LZW压缩算法 ===")
	fmt.Println("原始文本:", input)

	compressed := lzwCompress(input)
	fmt.Print("压缩后编码: ")
	for _, code := range compressed {
		fmt.Print(strconv.Itoa(code) + " ")
	}
	fmt.Println()

	decompressed := lzwDecompress(compressed)
	fmt.Println("解压后文本:", decompressed)

	valid := input == decompressed
	fmt.Println("验证:", valid)
}
