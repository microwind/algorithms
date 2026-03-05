package main

import (
	"fmt"
)

/*
* 反转二进制位
 *
 * 问题：反转一个32位整数的二进制表示
 *
 * 核心思想：
 * - 逐位提取和重建
 * - 位操作实现高效反转
 *
 * 时间复杂度: O(32)
 * 空间复杂度: O(1)
*/

// 逐位反转：从右到左提取，从左到右重建
func ReverseBitsIterative(n uint32) uint32 {
	result := uint32(0)
	for i := 0; i < 32; i++ {
		// 提取n的最右边一位
		bit := n & 1
		// 右移n，处理下一位
		n >>= 1
		// result左移，为新位腾出空间
		result <<= 1
		// 将bit加到result
		result |= bit
	}
	return result
}

// 手动位操作：逐位反转
func ReverseBitsManual(n uint32) uint32 {
	result := uint32(0)
	// 处理32位
	for i := 0; i < 32; i++ {
		// 从n中提取第i位
		if ((n >> uint(i)) & 1) == 1 {
			// 在result中设置第(31-i)位
			result |= (1 << uint(31-i))
		}
	}
	return result
}

// 按字节反转（4个字节的整数）
func ReverseBitsByteByByte(n uint32) uint32 {
	result := uint32(0)

	// 处理4个字节
	for i := 0; i < 4; i++ {
		// 提取第i个字节
		byteVal := (n >> uint(i*8)) & 0xFF

		// 反转字节内的位
		reversedByte := uint32(0)
		for j := 0; j < 8; j++ {
			if ((byteVal >> uint(j)) & 1) == 1 {
				reversedByte |= (1 << uint(7-j))
			}
		}

		// 将反转后的字节放在结果的正确位置
		result |= (reversedByte << uint((3-i)*8))
	}

	return result
}

// 使用查表法反转（针对频繁调用优化）
func ReverseBitsLookup(n uint32) uint32 {
	// 预计算0-255的位反转
	lookup := [256]uint8{}
	for i := 0; i < 256; i++ {
		byteVal := uint32(i)
		reversed := uint8(0)
		for j := 0; j < 8; j++ {
			if ((byteVal >> uint(j)) & 1) == 1 {
				reversed |= (1 << uint(7-j))
			}
		}
		lookup[i] = reversed
	}

	result := uint32(0)
	for i := 0; i < 4; i++ {
		byteVal := uint8((n >> uint(i*8)) & 0xFF)
		reversedByte := lookup[byteVal]
		result |= (uint32(reversedByte) << uint((3-i)*8))
	}

	return result
}

// 打印32位二进制表示
func printBinary32(n uint32) {
	fmt.Printf("0b")
	for i := 31; i >= 0; i-- {
		fmt.Printf("%d", (n>>uint(i))&1)
	}
}

// 测试函数
func main() {
	fmt.Println("=== 反转二进制位 ===\n")

	// 测试用例1：基本用例
	fmt.Println("1. 基本用例:")
	testCases := []uint32{
		1,           // 最右位为1
		2,           // 倒数第二位为1
		3,           // 最右两位为1
		43261596,    // 复杂用例
	}

	for _, num := range testCases {
		result := ReverseBitsIterative(num)

		fmt.Print("  输入:   ")
		printBinary32(num)
		fmt.Printf(" (%d)\n", num)
		fmt.Print("  输出:   ")
		printBinary32(result)
		fmt.Printf(" (%d)\n\n", result)
	}

	// 测试用例2：比较不同算法
	fmt.Println("2. 不同算法的结果比较:")
	testNums := []uint32{0, 1, 2, 7, 15, 255, 43261596, 2147483647}

	for _, num := range testNums {
		iter := ReverseBitsIterative(num)
		manual := ReverseBitsManual(num)
		byteByByte := ReverseBitsByteByByte(num)
		lookup := ReverseBitsLookup(num)

		allMatch := (iter == manual) && (manual == byteByByte) &&
			(byteByByte == lookup)
		if allMatch {
			fmt.Printf("  n=%d: 所有算法一致 = 是\n", num)
		} else {
			fmt.Printf("  n=%d: 所有算法一致 = 否\n", num)
		}
	}
	fmt.Println()

	// 测试用例3：特殊值
	fmt.Println("3. 特殊值:")
	special := []struct {
		value uint32
		desc  string
	}{
		{0x00000000, "全0"},
		{0xFFFFFFFF, "全1"},
		{0x80000000, "仅最左位为1"},
		{0x00000001, "仅最右位为1"},
		{0x12345678, "任意值"},
	}

	for _, s := range special {
		result := ReverseBitsIterative(s.value)
		fmt.Printf("  %-15s: 0x%08X -> 0x%08X\n",
			s.desc, s.value, result)
	}
	fmt.Println()

	// 测试用例4：验证对称性（反转两次应该恢复）
	fmt.Println("4. 验证反转的对称性（反转两次应该恢复）:")
	symmetryNums := []uint32{1, 7, 255, 43261596}

	for _, num := range symmetryNums {
		once := ReverseBitsIterative(num)
		twice := ReverseBitsIterative(once)
		if num == twice {
			fmt.Printf("  %d: 反转两次后恢复 = 是\n", num)
		} else {
			fmt.Printf("  %d: 反转两次后恢复 = 否\n", num)
		}
	}
}
