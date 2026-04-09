/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/*
 * 树算法 - 最大堆/最小堆实现 (MaxHeap/MinHeap)
 * 完全二叉树，满足堆序性质
 * 用于优先队列、堆排序等
 */

package main

import (
	"fmt"
	"math"
)

// 堆类型枚举
type HeapType int
const (
	MIN_HEAP HeapType = iota // 最小堆
	MAX_HEAP // 最大堆
)

// 堆结构
type Heap struct {
	data []int // 存储堆元素的数组
	size int // 堆中元素的数量
	typ  HeapType // 堆类型（最小堆或最大堆）
}

// create new heap
func NewHeap(typ HeapType) *Heap {
	return &Heap{
		data: make([]int, 0), // 初始化空数组
		size: 0, // 初始大小为0
		typ:  typ, // 设置堆类型
	}
}

/**
 * 获取父节点索引
 * 根据完全二叉树的性质，父节点索引 = (i - 1) / 2
 */
func (h *Heap) parent(i int) int {
	return (i - 1) / 2
}

/**
 * 获取左子节点索引
 * 根据完全二叉树的性质，左子节点索引 = 2 * i + 1
 */
func (h *Heap) leftChild(i int) int {
	return 2*i + 1
}

/**
 * 获取右子节点索引
 * 根据完全二叉树的性质，右子节点索引 = 2 * i + 2
 */
func (h *Heap) rightChild(i int) int {
	return 2*i + 2
}

/**
 * 交换两个元素
 * 交换堆中指定位置的两个元素
 */
func (h *Heap) swap(i, j int) {
	h.data[i], h.data[j] = h.data[j], h.data[i]
}

/**
 * 判断是否需要交换
 * 根据堆类型判断父节点和子节点是否需要交换
 */
func (h *Heap) shouldSwap(parent, child int) bool {
	if h.typ == MIN_HEAP {
		return h.data[parent] > h.data[child]
	}
	return h.data[parent] < h.data[child]
}

/**
 * 向上堆化
 * 将插入的元素向上调整，保持堆性质
 * 时间复杂度：O(log n)
 */
func (h *Heap) heapifyUp(i int) {
	for i > 0 && h.shouldSwap(h.parent(i), i) {
		h.swap(h.parent(i), i)
		i = h.parent(i)
	}
}

/**
 * 向下堆化
 * 将堆顶元素向下调整，保持堆性质
 * 时间复杂度：O(log n)
 */
func (h *Heap) heapifyDown(i int) {
	left := h.leftChild(i)
	right := h.rightChild(i)
	extreme := i

	// 查找更极端的子节点
	if left < h.size && h.shouldSwap(extreme, left) {
		extreme = left
	}
	if right < h.size && h.shouldSwap(extreme, right) {
		extreme = right
	}

	// 如果子节点更极端，交换并继续
	if extreme != i {
		h.swap(i, extreme)
		h.heapifyDown(extreme)
	}
}

/**
 * 插入元素
 * 1. 将元素添加到数组末尾
 * 2. 向上堆化调整位置
 * 时间复杂度：O(log n)
 */
func (h *Heap) insert(value int) {
	h.data = append(h.data, value)
	h.size++
	h.heapifyUp(h.size - 1)
}

/**
 * 获取堆顶元素
 * 返回堆顶元素（最大堆返回最大值，最小堆返回最小值）
 * 时间复杂度：O(1)
 */
func (h *Heap) peek() int {
	if h.isEmpty() {
		fmt.Println("堆为空!")
		return math.MinInt32
	}
	return h.data[0]
}

/**
 * 移除堆顶元素
 * 1. 保存堆顶元素
 * 2. 将最后一个元素移到堆顶
 * 3. 向下堆化调整
 * 时间复杂度：O(log n)
 */
func (h *Heap) extract() int {
	if h.isEmpty() {
		fmt.Println("堆为空!")
		return math.MinInt32
	}

	root := h.data[0]
	h.data[0] = h.data[h.size-1]
	h.data = h.data[:h.size-1]
	h.size--
	h.heapifyDown(0)

	return root
}

/**
 * 获取堆大小
 * 返回堆中元素的数量
 * 时间复杂度：O(1)
 */
func (h *Heap) getSize() int {
	return h.size
}

/**
 * 检查堆是否为空
 * 返回堆是否为空
 * 时间复杂度：O(1)
 */
func (h *Heap) isEmpty() bool {
	return h.size == 0
}

/**
 * 打印堆
 * 按照堆类型打印堆中所有元素
 */
func (h *Heap) print() {
	fmt.Printf("heap[%v]: [", h.getHeapType())
	for i := 0; i < h.size; i++ {
		fmt.Printf("%d", h.data[i])
		if i < h.size-1 {
			fmt.Printf(", ")
		}
	}
	fmt.Println("]")
}

/**
 * get heap type string
 */
func (h *Heap) getHeapType() string {
	if h.typ == MIN_HEAP {
		return "MIN_HEAP"
	}
	return "MAX_HEAP"
}

/**
 * 主函数 - 测试堆
 */
func main() {
	// 测试最小堆
	fmt.Println("=== minimum heap test ===")
	minHeap := NewHeap(MIN_HEAP)

	testData := []int{10, 20, 15, 30, 5}
	fmt.Println("insert data:")
	for _, value := range testData {
		fmt.Printf("%d ", value)
		minHeap.insert(value)
	}
	fmt.Println()
	minHeap.print()
	fmt.Println()

	fmt.Println("=== extract elements ===")
	for !minHeap.isEmpty() {
		fmt.Printf("extract: %d\n", minHeap.extract())
		minHeap.print()
	}
	fmt.Println()

	// test maximum heap
	fmt.Println("=== 最大堆测试 ===")
	maxHeap := NewHeap(MAX_HEAP)

	fmt.Println("insert data:")
	for _, value := range testData {
		fmt.Printf("%d ", value)
		maxHeap.insert(value)
	}
	fmt.Println()
	maxHeap.print()
	fmt.Println()

	fmt.Println("=== extract elements ===")
	for !maxHeap.isEmpty() {
		fmt.Printf("extract: %d\n", maxHeap.extract())
		maxHeap.print()
	}
	fmt.Println()

	fmt.Println("=== 堆特性 ===")
	fmt.Println("1. 完全二叉树，存储在数组中")
	fmt.Println("2. 最小堆：父节点 <= 子节点")
	fmt.Println("3. 最大堆：父节点 >= 子节点")
	fmt.Println("4. 插入和提取时间复杂度：O(log n)")
	fmt.Println("5. 查看堆顶时间复杂度：O(1)")
}
