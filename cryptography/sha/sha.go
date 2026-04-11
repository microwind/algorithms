/*
*
 * SHA-256哈希算法 - 密码学哈希函数
 *
 * 问题：生成消息的固定长度哈希值
 *
 * 核心思想：
 * - 填充消息到512位的倍数
 * - 分块处理
 * - 位操作和逻辑运算
 *
 * 注意：此实现使用Go内置库
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/

package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

/*
*
 * SHA-256哈希函数（使用Go内置库）
*/
func sha256Hash(message string) string {
	hash := sha256.Sum256([]byte(message))
	return hex.EncodeToString(hash[:])
}

/*
*
 * 主函数
*/
func main() {
	fmt.Println("=== SHA-256哈希算法 ===")

	message := "Hello, World!"
	fmt.Printf("消息: %s\n", message)

	hash := sha256Hash(message)
	fmt.Printf("SHA-256: %s\n", hash)

	fmt.Println("\n注意：此实现使用Go内置库，")
	fmt.Println("实际应用应使用成熟的加密库。")
}
