#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

/*
大顶堆：根节点始终为堆中的最大值。
         6
       /   \
      5     4
     / \   /
    3   2 1
*/
// 调整堆的结构，确保父节点大于或等于其子节点，符合大顶堆的性质
void heapify_max(int arr[], int n, int i)
{
  int largest = i;       // 假设当前节点 i 为最大节点
  int left = 2 * i + 1;  // 左子节点的索引
  int right = 2 * i + 2; // 右子节点的索引

  // 如果左子节点存在且大于当前最大值
  if (left < n && arr[left] > arr[largest])
    largest = left; // 更新最大值索引

  // 如果右子节点存在且大于当前最大值
  if (right < n && arr[right] > arr[largest])
    largest = right; // 更新最大值索引

  // 如果最大值不再是原节点 i，交换节点 i 和最大值节点
  if (largest != i)
  {
    int temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;

    // 递归调整交换后的子树，确保其也符合大顶堆性质
    heapify_max(arr, n, largest);
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
void heapify_min(int arr[], int n, int i)
{
  int smallest = i;      // 假设当前节点 i 为最小节点
  int left = 2 * i + 1;  // 左子节点的索引
  int right = 2 * i + 2; // 右子节点的索引

  // 如果左子节点存在且小于当前最小值
  if (left < n && arr[left] < arr[smallest])
    smallest = left; // 更新最小值索引

  // 如果右子节点存在且小于当前最小值
  if (right < n && arr[right] < arr[smallest])
    smallest = right; // 更新最小值索引

  // 如果最小值不再是原节点 i，交换节点 i 和最小值节点
  if (smallest != i)
  {
    int temp = arr[i];
    arr[i] = arr[smallest];
    arr[smallest] = temp;

    // 递归调整交换后的子树，确保其也符合小顶堆性质
    heapify_min(arr, n, smallest);
  }
}

// 构建大顶堆
// 从最后一个非叶子节点开始，逐步调用 heapify_max() 进行堆化
void build_max_heap(int arr[], int n)
{
  // 从最后一个非叶子节点开始调整
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    heapify_max(arr, n, i);
  }
}

// 构建小顶堆
// 从最后一个非叶子节点开始，逐步调用 heapify_min() 进行堆化
void build_min_heap(int arr[], int n)
{
  // 从最后一个非叶子节点开始调整
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    heapify_min(arr, n, i);
  }
}

// 打印堆
// 输出堆的内容
void print_heap(int arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
  // 初始化一个数组，用于构建大顶堆和小顶堆
  int max_heap[] = {3, 1, 6, 5, 2, 4};
  int min_heap[] = {3, 1, 6, 5, 2, 4};

  // 计算数组的元素个数
  int max_n = sizeof(max_heap) / sizeof(max_heap[0]);
  int min_n = sizeof(min_heap) / sizeof(min_heap[0]);

  // 构建大顶堆
  build_max_heap(max_heap, max_n);
  printf("Max heap: ");
  print_heap(max_heap, max_n); // 输出大顶堆的结果

  // 构建小顶堆
  build_min_heap(min_heap, min_n);
  printf("Min heap: ");
  print_heap(min_heap, min_n); // 输出小顶堆的结果

  return 0;
}

/*
jarry@MacBook-Pro heap % gcc heap.c
jarry@MacBook-Pro heap % ./a.out
Max heap: 6 5 4 1 2 3
Min heap: 1 2 4 5 3 6
*/