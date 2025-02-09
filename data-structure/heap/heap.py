MAX_SIZE = 100

"""
大顶堆：根节点始终为堆中的最大值。
         6
       /   \
      5     4
     / \   /
    3   2 1
"""
# 调整堆的结构，确保父节点大于或等于其子节点，符合大顶堆的性质


def heapify_max(arr, n, i):
    largest = i        # 假设当前节点 i 为最大节点
    left = 2 * i + 1   # 左子节点的索引
    right = 2 * i + 2  # 右子节点的索引

    # 如果左子节点存在且大于当前最大值
    if left < n and arr[left] > arr[largest]:
        largest = left  # 更新最大值索引

    # 如果右子节点存在且大于当前最大值
    if right < n and arr[right] > arr[largest]:
        largest = right  # 更新最大值索引

    # 如果最大值不再是原节点 i，交换节点 i 和最大值节点
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]

        # 递归调整交换后的子树，确保其也符合大顶堆性质
        heapify_max(arr, n, largest)


"""
小顶堆：根节点始终为堆中的最小值。
         1
       /   \
      2     4
     / \   /
    5   3 6
"""
# 调整堆的结构，确保父节点小于或等于其子节点，符合小顶堆的性质


def heapify_min(arr, n, i):
    smallest = i        # 假设当前节点 i 为最小节点
    left = 2 * i + 1    # 左子节点的索引
    right = 2 * i + 2   # 右子节点的索引

    # 如果左子节点存在且小于当前最小值
    if left < n and arr[left] < arr[smallest]:
        smallest = left  # 更新最小值索引

    # 如果右子节点存在且小于当前最小值
    if right < n and arr[right] < arr[smallest]:
        smallest = right  # 更新最小值索引

    # 如果最小值不再是原节点 i，交换节点 i 和最小值节点
    if smallest != i:
        arr[i], arr[smallest] = arr[smallest], arr[i]

        # 递归调整交换后的子树，确保其也符合小顶堆性质
        heapify_min(arr, n, smallest)

# 构建大顶堆


def build_max_heap(arr, n):
    for i in range(n // 2 - 1, -1, -1):
        heapify_max(arr, n, i)

# 构建小顶堆


def build_min_heap(arr, n):
    for i in range(n // 2 - 1, -1, -1):
        heapify_min(arr, n, i)

# 打印堆


def print_heap(arr, n):
    print(" ".join(map(str, arr[:n])))


max_heap = [3, 1, 6, 5, 2, 4]
min_heap = [3, 1, 6, 5, 2, 4]

max_n = len(max_heap)
min_n = len(min_heap)

# 构建大顶堆
build_max_heap(max_heap, max_n)
print("Max heap:")
print_heap(max_heap, max_n)

# 构建小顶堆
build_min_heap(min_heap, min_n)
print("Min heap:")
print_heap(min_heap, min_n)

"""
jarry@MacBook-Pro heap % python heap.py
Max heap:
6 5 4 1 2 3
Min heap:
1 2 4 5 3 6
"""
