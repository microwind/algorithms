// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// HeapSortStruct 堆排序算法结构化实现
// 提供基于Tree结构的堆排序实现，展示面向对象的堆排序方式
//
// 算法原理：
// 1. 构建最大堆：将无序数组构建成最大堆结构
// 2. 交换堆顶：将堆顶元素（最大值）与堆尾元素交换
// 3. 调整堆：对剩余元素重新堆化，保持堆结构
// 4. 重复步骤2-3，直到整个数组有序
//
// 时间复杂度：O(n log n) - 构建堆O(n)，每次堆化O(log n)
// 空间复杂度：O(1) - 原地排序，不需要额外空间
// 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置

package main

import (
	"fmt"
	"time"
)

// printArray 打印数组内容的辅助函数
func printArray(arr []int, label string) {
	fmt.Printf("%s: [%v]\n", label, arr)
}

// printHeapTree 打印堆的树形结构
func printHeapTree(arr []int, title string) {
	if len(arr) < 7 {
		fmt.Printf("%s: [%v]\n", title, arr)
		return
	}

	fmt.Println(title)
	fmt.Printf("              %d(0)\n", arr[0])
	fmt.Println("          /         \\")
	fmt.Printf("        %d(1)        %d(2)\n", arr[1], arr[2])
	fmt.Println("       /    \\      /     \\")
	fmt.Printf("   %d(3)  %d(4)  %d(5)  %d(6)\n", arr[3], arr[4], arr[5], arr[6])
	fmt.Println()
}

// performanceTest 性能测试辅助函数
func performanceTest(sortFunc func([]int), arr []int, name string) {
	// 创建数组副本，避免修改原数组
	testArr := make([]int, len(arr))
	copy(testArr, arr)
	printArray(testArr, name+"原始数组")

	// 开始计时
	start := time.Now()
	sortFunc(testArr)
	elapsed := time.Since(start)

	fmt.Printf("%s: %.3fms\n", name, float64(elapsed.Nanoseconds())/1000000.0)
	printArray(testArr, name+"排序结果")
	fmt.Println() // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
var testData = []int{7, 11, 9, 10, 12, 13, 8}

/* 根据完全二叉树结构性质，父子节点与数组下标的关系，通过数组下标i得到节点位置 */

// Tree 定义堆排序过程中使用的堆结构
type Tree struct {
	arr  []int // 用来存储堆的数据
	size int   // 用来标识堆的大小
}

// maxHeapify 保持最大顶堆特性非递归版
//
// 算法思路：
// 使用迭代方式维护堆的性质，避免递归调用
// 从指定节点开始，向下调整直到满足最大堆性质
//
// 步骤说明：
// 1. 保存当前节点的值
// 2. 从左子节点开始遍历
// 3. 找到最大的子节点
// 4. 如果子节点大于当前节点，交换并继续向下
// 5. 最终将原值放到正确位置
//
// 关键点：
// - 使用迭代而非递归，减少函数调用开销
// - 先保存值，最后赋值，减少交换操作
// - 比较左右子节点，选择较大的进行交换
func maxHeapify(tree *Tree, idx int) {
	// 步骤1：初始化变量
	// 关键点：保存当前节点的值，避免频繁交换
	arr := tree.arr
	var current = arr[idx]
	var child = 2*idx + 1

	// 步骤2：从当前位置的左节点开始遍历
	// 关键点：当还有子节点时继续循环
	for child < tree.size {
		fmt.Println("current=", current, " idx=", idx, " child=", child, " size=", tree.size)

		// 步骤3：比较左右子节点，选择较大的
		// 关键点：如果右节点存在且大于左节点，则指向右节点
		if child+1 < tree.size && arr[child] < arr[child+1] {
			child++
		}

		// 步骤4：比较子节点与当前节点
		// 关键点：如果子节点大于当前节点，需要交换
		if arr[child] > current {
			// 步骤4.1：将子节点的值赋给父节点
			// 关键点：直接赋值，不交换，减少操作
			arr[idx] = arr[child]
			// 步骤4.2：当前节点指向该子节点，继续循环
			// 关键点：向下移动，继续调整
			idx = child
		} else {
			// 步骤4.3：子节点小于父节点则跳出循环
			// 关键点：已经满足堆性质，无需继续
			break
		}
		// 步骤5：遍历子树父节点
		// 关键点：计算下一个子节点位置
		child = 2*idx + 1
	}

	// 步骤6：将原值放到正确位置
	// 关键点：最终赋值，完成堆化过程
	arr[idx] = current
}

// heapSort 利用堆结构对数组进行排序
//
// 算法思路：
// 使用Tree结构封装堆排序过程，展示面向对象的实现方式
// 通过构建最大堆和逐步提取最大值来完成排序
//
// 步骤说明：
// 1. 初始化Tree结构
// 2. 构建最大堆
// 3. 逐个提取堆顶元素
// 4. 重新调整堆结构
//
// 关键点：
// - 使用Tree结构封装堆的状态
// - 动态调整堆的大小
// - 原地排序，空间效率高
func heapSort(arr []int) []int {
	// 步骤1：初始化Tree结构
	// 关键点：创建Tree实例，设置数组和大小
	tree := &Tree{}
	tree.arr = arr
	tree.size = len(arr)

	// 步骤2：构建最大堆
	// 关键点：从最后一个非叶子节点开始堆化
	// Go特点：从任意1个父节点开始均可，但通常从最后一个非叶子节点开始
	var current = (tree.size - 1) / 2
	for ; current >= 0; current-- {
		maxHeapify(tree, current)
	}

	// 步骤3：逐个提取堆顶元素并排序
	// 关键点：将最大元素逐步移动到数组末尾
	for tree.size > 0 {
		// 步骤3.1：将最大值调整到堆的末尾
		// 关键点：交换堆顶和堆尾元素
		tree.arr[0], tree.arr[tree.size-1] = tree.arr[tree.size-1], tree.arr[0]
		// 步骤3.2：减少堆的大小
		// 关键点：排除已排序的元素
		tree.size--
		// 步骤3.3：重新调整堆结构
		// 关键点：由于堆顶元素改变，需要重新堆化
		maxHeapify(tree, 0)
	}

	return tree.arr
}

// heapSort1 堆排序结构化版本 - 最大堆
//
// 算法思路：
// 使用Tree结构封装堆排序过程，展示面向对象的实现方式
// 通过构建最大堆和逐步提取最大值来完成排序
//
// 优化效果：
// - 结构化设计，代码更清晰
// - 状态封装，减少参数传递
// - 面向对象风格，易于扩展
//
// 时间复杂度：O(n log n)
// 空间复杂度：O(1) - 原地排序
// 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
func heapSort1(arr []int) {
	fmt.Println("heapSort1 struct-based:")
	printHeapTree(arr, "original array:")

	// 步骤1：执行结构化堆排序
	// 关键点：使用Tree结构封装整个排序过程
	result := heapSort(arr)

	printArray(result, "排序后数组")
}

// main 主函数 - 算法测试和性能对比
func main() {
	// 测试1：结构化版本
	performanceTest(heapSort1, testData, "结构化版本")

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 结构化版本：面向对象设计，代码清晰")
}

/*
 oringal array: [7, 11, 9, 10, 12, 13, 8]
 heap:
               7(0)
           /         \
         11(1)        9(2)
        /    \      /     \
    10(3)  12(4)  13(5)  8(6)

 父节点步骤，构建大顶堆，父节点要大于左右子节点
 这里parent=2，来自(总长度-1)/2，从这个父节点开始构建大顶堆
 1. maxHeapify: parent= 2 left= 5 right= 6 max= 5 size= 7
               7(0)
           /         \
         11(1)        13(2)
        /    \      /     \
    10(3)  12(4)  9(5)  8(6)

 2. maxHeapify: parent= 1 left= 3 right= 4 max= 4 size= 7
               7(0)
           /         \
         12(1)        13(2)
        /    \      /     \
    10(3)  11(4)  9(5)  8(6)

 3. maxHeapify: parent= 0 left= 1 right= 2 max= 2 size= 7
               13(0)
           /         \
         12(1)        7(2)
        /    \      /     \
    10(3)  11(4)  9(5)  8(6)

 3.1 maxHeapify recursion: parent= 2 left= 5 right= 6 max= 5 size= 7
               13(0)
           /         \
         12(1)        9(2)
        /    \      /     \
    10(3)  11(4)  7(5)  8(6)

 子节点堆排序:
 1. swap, child = 6:
               8(0)
           /         \
         12(1)        9(2)
        /    \      /     \
    10(3)  11(4)  7(5)  13(6)

 1.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 6
               12(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  7(5)  13(6)

 1.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 4 size= 6
               12(0)
           /         \
         11(1)        9(2)
        /    \      /     \
    10(3)  8(4)  7(5)  13(6)

 2. swap, child = 5:
               7(0)
           /         \
         11(1)        9(2)
        /    \      /     \
    10(3)  8(4)  12(5)  13(6)

 2.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 5
               11(0)
           /         \
         7(1)        9(2)
        /    \      /     \
    10(3)  8(4)  12(5)  13(6)

 2.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 3 size= 5
               11(0)
           /         \
         10(1)        9(2)
        /    \      /     \
    7(3)  8(4)  12(5)  13(6)

 3. swap, child = 4:
               8(0)
           /         \
         10(1)        9(2)
        /    \      /     \
    7(3)  11(4)  12(5)  13(6)

 3.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 4
               10(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    7(3)  11(4)  12(5)  13(6)

 3.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 1 size= 4

 4. swap, child = 3:
               7(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 4.1 maxHeapify: parent= 0 left= 1 right= 2 max= 2 size= 3
               9(0)
           /         \
         8(1)        7(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 4.2 maxHeapify recursion: parent= 2 left= 5 right= 6 max= 2 size= 3

 5. swap, child = 2:
               7(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 5.1 maxHeapify: parent= 0 left= 1 right= 2 max= 1 size= 2
               8(0)
           /         \
         7(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 5.2 maxHeapify recursion: parent= 1 left= 3 right= 4 max= 1 size= 2

 6. swap, child = 1:
               7(0)
           /         \
         8(1)        9(2)
        /    \      /     \
    10(3)  11(4)  12(5)  13(6)

 6.1 maxHeapify: parent= 0 left= 1 right= 2 max= 0 size= 1

*/

/*
 jarry@jarrys-MacBook-Pro heapsort % go version
 go version go1.19.5 darwin/amd64
 jarry@Mac heapsort %  go run heap_sort_struct.go
结构化版本原始数组: [[7 11 9 10 12 13 8]]
heapSort1 struct-based:
original array:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

current= 9  idx= 2  child= 5  size= 7
current= 11  idx= 1  child= 3  size= 7
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
current= 8  idx= 0  child= 1  size= 6
current= 8  idx= 1  child= 3  size= 6
current= 7  idx= 0  child= 1  size= 5
current= 7  idx= 1  child= 3  size= 5
current= 8  idx= 0  child= 1  size= 4
current= 8  idx= 1  child= 3  size= 4
current= 7  idx= 0  child= 1  size= 3
current= 7  idx= 0  child= 1  size= 2
排序后数组: [[7 8 9 10 11 12 13]]
结构化版本: 0.053ms
结构化版本排序结果: [[7 8 9 10 11 12 13]]
*/
