/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 两数之和算法 - Go实现
 *
 * 算法原理：
 * 使用哈希表辅助查找。遍历数组时，对于每个元素，计算目标值与当前元素的差值（补数），
 * 检查补数是否已在哈希表中。如果在，则找到答案；否则将当前元素存入哈希表。
 *
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(n) - 哈希表存储
 */

package main

import "fmt"

// twoSum 两数之和
// 使用哈希表查找补数
// 参数：
//   nums - 输入数组
//   target - 目标和
// 返回：两个数的索引数组
func twoSum(nums []int, target int) []int {
    seen := make(map[int]int) // 哈希表，存储元素值到索引的映射
    
    for i, num := range nums {
        need := target - num // 计算补数
        // 检查补数是否已在哈希表中
        if idx, ok := seen[need]; ok {
            return []int{idx, i} // 找到答案，返回两个索引
        }
        seen[num] = i // 将当前元素存入哈希表
    }
    
    return []int{} // 未找到答案
}

func main() {
    nums := []int{2, 7, 11, 15}
    target := 9
    
    result := twoSum(nums, target)
    
    if len(result) > 0 {
        fmt.Printf("目标值: %d\n", target)
        fmt.Printf("结果索引: [%d, %d]\n", result[0], result[1])
        fmt.Printf("对应数值: %d + %d = %d\n", nums[result[0]], nums[result[1]], target)
    } else {
        fmt.Println("未找到答案")
    }
}

/*
 * 输出结果：
 * 目标值: 9
 * 结果索引: [0, 1]
 * 对应数值: 2 + 7 = 9
 */
