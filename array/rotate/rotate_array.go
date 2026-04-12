/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组旋转算法 - Go实现
 *
 * 算法原理：
 * - 将数组的前d个元素移动到数组末尾
 * - 剩余元素左移填充前面位置
 * - 使用临时数组存储前d个元素
 *
 * 旋转类型：
 * - 左旋转：元素向左移动，前面的移到后面
 * - 右旋转：元素向右移动，后面的移到前面
 *
 * 本实现为左旋转（将前d个元素移到末尾）
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(d) - 需要临时存储d个元素
 *
 * 优化：使用三次反转法可将空间复杂度降至O(1)
 *
 * 应用场景：
 * - 循环移位
 * - 数据重排
 * - 图像处理中的像素移动
 */

package main

import "fmt"

// rotateArray 数组左旋转函数
// 将数组前d个元素移到数组末尾
// 参数：
//   arr - 待旋转的数组
//   d - 旋转位置数（前d个元素移到末尾）
func rotateArray(arr []int, d int) {
    n := len(arr)
    // 步骤1：保存前d个元素到临时数组
    temp := make([]int, d)
    copy(temp, arr[:d])
    
    // 步骤2：将剩余元素左移（向前移动d位）
    for i := 0; i < n-d; i++ {
        arr[i] = arr[i+d]
    }
    
    // 步骤3：将临时数组元素放到数组末尾
    for i := 0; i < d; i++ {
        arr[n-d+i] = temp[i]
    }
}

// printArray 打印数组
func printArray(arr []int) {
    fmt.Print("[")
    for i, v := range arr {
        fmt.Print(v)
        if i < len(arr)-1 {
            fmt.Print(", ")
        }
    }
    fmt.Println("]")
}

func main() {
    arr := []int{1, 2, 3, 4, 5, 6, 7}
    d := 3  // 旋转3位

    fmt.Print("Original array: ")
    printArray(arr)

    rotateArray(arr, d)

    fmt.Printf("Rotated array (d=%d): ", d)
    printArray(arr)
}

/*
 * 输出结果：
 * Original array: [1, 2, 3, 4, 5, 6, 7]
 * Rotated array (d=3): [4, 5, 6, 7, 1, 2, 3]
 */
