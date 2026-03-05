package main

import (
	"fmt"
	"strings"
)

/*
* Maximize Number - Remove k digits to get maximum value
 *
 * Algorithm:
 * - Given a digit string and k, remove k digits to maximize the resulting number
 * - Use a greedy stack-based approach
*/
/*
* 移除k位数字使数值最大（贪心算法）
 *
 * 算法思路：
 * - 给定一个数字字符串和整数k
 * - 移除k位数字，使剩下的数字最大
 * - 策略：贪心地用单调栈，每次遇到比栈顶大的数字就移除栈顶
*/

// RemoveKDigits 移除k位数字，使剩下的数字最大
func RemoveKDigits(numStr string, k int) string {
	n := len(numStr)

	if k >= n {
		return "0"
	}

	if k == 0 {
		return numStr
	}

	// Stack-based greedy approach
	stack := []rune{}
	toDelete := k

	for _, digit := range numStr {
		// Remove smaller digits from stack when we encounter a larger digit
		for toDelete > 0 && len(stack) > 0 && stack[len(stack)-1] < digit {
			stack = stack[:len(stack)-1]
			toDelete--
		}
		stack = append(stack, digit)
	}

	// If we still have digits to delete, remove from the end
	if toDelete > 0 {
		stack = stack[:len(stack)-toDelete]
	}

	// Build result
	result := string(stack)

	// Handle leading zeros
	result = strings.TrimLeft(result, "0")
	if result == "" {
		return "0"
	}

	return result
}

func testStandardExample() {
	fmt.Println("\n[Test 1] Standard example from problem")
	fmt.Println("\n[测试1] 标准示例")

	numStr := "1432219"
	k := 3
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '4321'\n")
}

func testLeadingZeros() {
	fmt.Println("\n[Test 2] Remove leading zeros")
	fmt.Println("\n[测试2] 去除前导零")

	numStr := "10200"
	k := 1
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '200'\n")
}

func testSameDigits() {
	fmt.Println("\n[Test 3] All same digits")
	fmt.Println("\n[测试3] 全部相同数字")

	numStr := "1111"
	k := 2
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '11'\n")
}

func testDescendingOrder() {
	fmt.Println("\n[Test 4] Descending digits - remove from end")
	fmt.Println("\n[测试4] 递减数字 - 从末尾移除")

	numStr := "54321"
	k := 2
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '321'\n")
}

func testAscendingOrder() {
	fmt.Println("\n[Test 5] Ascending digits - remove from front")
	fmt.Println("\n[测试5] 递增数字 - 从前面移除")

	numStr := "12345"
	k := 2
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '345'\n")
}

func testRemoveAll() {
	fmt.Println("\n[Test 6] Remove all digits")
	fmt.Println("\n[测试6] 移除所有数字")

	numStr := "123"
	k := 3
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '0'\n")
}

func testRemoveZero() {
	fmt.Println("\n[Test 7] Remove zero digits")
	fmt.Println("\n[测试7] 不移除数字")

	numStr := "1234"
	k := 0
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '1234'\n")
}

func testMultipleZeros() {
	fmt.Println("\n[Test 8] Multiple zeros in middle")
	fmt.Println("\n[测试8] 中间有多个零")

	numStr := "100200"
	k := 2
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
}

func testMixed() {
	fmt.Println("\n[Test 9] Mixed digits")
	fmt.Println("\n[测试9] 混合数字")

	numStr := "112"
	k := 1
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
	fmt.Printf("Expected: '12'\n")
}

func testLargeNumber() {
	fmt.Println("\n[Test 10] Large number")
	fmt.Println("\n[测试10] 大数字")

	numStr := "987654321"
	k := 4
	result := RemoveKDigits(numStr, k)

	fmt.Printf("Input: '%s', k=%d\n", numStr, k)
	fmt.Printf("Output: '%s'\n", result)
}

func main() {
	fmt.Println("==================================================")
    fmt.Println("移除k位数字使数值最大 - 贪心算法 (Go)")
	fmt.Println("==================================================")

	testStandardExample()
	testLeadingZeros()
	testSameDigits()
	testDescendingOrder()
	testAscendingOrder()
	testRemoveAll()
	testRemoveZero()
	testMultipleZeros()
	testMixed()
	testLargeNumber()
}
