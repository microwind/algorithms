package main

import "fmt"

const MAX_SIZE = 100

/*
大顶堆：根节点始终为堆中的最大值。
         6
       /   \
      5     4
     / \   /
    3   2 1
*/
// 调整堆的结构，确保父节点大于或等于其子节点，符合大顶堆的性质
func heapifyMax(arr []int, n, i int) {
  largest := i     // 假设当前节点 i 为最大节点
  left := 2*i + 1  // 左子节点的索引
  right := 2*i + 2 // 右子节点的索引

  // 如果左子节点存在且大于当前最大值
  if left < n && arr[left] > arr[largest] {
    largest = left // 更新最大值索引
  }

  // 如果右子节点存在且大于当前最大值
  if right < n && arr[right] > arr[largest] {
    largest = right // 更新最大值索引
  }

  // 如果最大值不再是原节点 i，交换节点 i 和最大值节点
  if largest != i {
    arr[i], arr[largest] = arr[largest], arr[i]

    // 递归调整交换后的子树，确保其也符合大顶堆性质
    heapifyMax(arr, n, largest)
  }
}

/*
小顶堆：根节点始终为堆中的最小值。
         1
       /   \
      2     4
     / \   /
    5   3 6
*/
// 调整堆的结构，确保父节点小于或等于其子节点，符合小顶堆的性质
func heapifyMin(arr []int, n, i int) {
  smallest := i    // 假设当前节点 i 为最小节点
  left := 2*i + 1  // 左子节点的索引
  right := 2*i + 2 // 右子节点的索引

  // 如果左子节点存在且小于当前最小值
  if left < n && arr[left] < arr[smallest] {
    smallest = left // 更新最小值索引
  }

  // 如果右子节点存在且小于当前最小值
  if right < n && arr[right] < arr[smallest] {
    smallest = right // 更新最小值索引
  }

  // 如果最小值不再是原节点 i，交换节点 i 和最小值节点
  if smallest != i {
    arr[i], arr[smallest] = arr[smallest], arr[i]

    // 递归调整交换后的子树，确保其也符合小顶堆性质
    heapifyMin(arr, n, smallest)
  }
}

// 构建大顶堆
// 从最后一个非叶子节点开始，逐步调用 heapifyMax() 进行堆化
func buildMaxHeap(arr []int, n int) {
  // 从最后一个非叶子节点开始调整
  for i := n/2 - 1; i >= 0; i-- {
    heapifyMax(arr, n, i)
  }
}

// 构建小顶堆
// 从最后一个非叶子节点开始，逐步调用 heapifyMin() 进行堆化
func buildMinHeap(arr []int, n int) {
  // 从最后一个非叶子节点开始调整
  for i := n/2 - 1; i >= 0; i-- {
    heapifyMin(arr, n, i)
  }
}

// 打印堆
// 输出堆的内容
func printHeap(arr []int, n int) {
  for i := 0; i < n; i++ {
    fmt.Printf("%d ", arr[i])
  }
  fmt.Println()
}

func main() {
  // 初始化一个数组，用于构建大顶堆和小顶堆
  maxHeap := []int{3, 1, 6, 5, 2, 4}
  minHeap := []int{3, 1, 6, 5, 2, 4}

  // 计算数组的元素个数
  maxN := len(maxHeap)
  minN := len(minHeap)

  // 构建大顶堆
  buildMaxHeap(maxHeap, maxN)
  fmt.Print("Max heap: ")
  printHeap(maxHeap, maxN) // 输出大顶堆的结果

  // 构建小顶堆
  buildMinHeap(minHeap, minN)
  fmt.Print("Min heap: ")
  printHeap(minHeap, minN) // 输出小顶堆的结果
}

/*
jarry@MacBook-Pro heap % go run heap.go
Max heap: 6 5 4 1 2 3
Min heap: 1 2 4 5 3 6
*/
