/*
*
 * 凯撒密码 - 简单的替换加密
 *
 * 问题：将字母表中的每个字母移动固定位数
 *
 * 核心思想：
 * - 字母替换
 * - 循环移位
 * - 保持大小写
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

package main

import (
	"fmt"
	"unicode"
)

/*
*
 * 凯撒加密
*/
func caesarEncrypt(text string, shift int) string {
	result := []rune(text)

	for i, c := range result {
		if unicode.IsUpper(c) {
			result[i] = rune((int(c-'A')+shift)%26 + 'A')
		} else if unicode.IsLower(c) {
			result[i] = rune((int(c-'a')+shift)%26 + 'a')
		}
	}

	return string(result)
}

/*
*
 * 凯撒解密
*/
func caesarDecrypt(text string, shift int) string {
	return caesarEncrypt(text, 26-(shift%26))
}

/*
*
 * 主函数
*/
func main() {
	fmt.Println("=== 凯撒密码 ===")

	text := "Hello, World!"
	shift := 3

	fmt.Printf("明文: %s\n", text)
	fmt.Printf("移位数: %d\n", shift)

	// 加密
	encrypted := caesarEncrypt(text, shift)
	fmt.Printf("加密后: %s\n", encrypted)

	// 解密
	decrypted := caesarDecrypt(encrypted, shift)
	fmt.Printf("解密后: %s\n", decrypted)

	valid := text == decrypted
	fmt.Printf("验证: %t\n", valid)
}
