"""
堆 (Heap) - 优先队列实现
使用二叉堆实现最大堆和最小堆
"""


class MaxHeap:
    """最大堆实现"""
    
    def __init__(self):
        self.heap = []
    
    def parent(self, i):
        return (i - 1) // 2
    
    def left_child(self, i):
        return 2 * i + 1
    
    def right_child(self, i):
        return 2 * i + 2
    
    def insert(self, val):
        """插入元素"""
        self.heap.append(val)
        self._heapify_up(len(self.heap) - 1)
    
    def _heapify_up(self, i):
        """向上调整堆"""
        while i > 0 and self.heap[i] > self.heap[self.parent(i)]:
            self.heap[i], self.heap[self.parent(i)] = self.heap[self.parent(i)], self.heap[i]
            i = self.parent(i)
    
    def extract_max(self):
        """提取最大值"""
        if not self.heap:
            return None
        
        max_val = self.heap[0]
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        self._heapify_down(0)
        return max_val
    
    def _heapify_down(self, i):
        """向下调整堆"""
        largest = i
        left = self.left_child(i)
        right = self.right_child(i)
        
        if left < len(self.heap) and self.heap[left] > self.heap[largest]:
            largest = left
        
        if right < len(self.heap) and self.heap[right] > self.heap[largest]:
            largest = right
        
        if largest != i:
            self.heap[i], self.heap[largest] = self.heap[largest], self.heap[i]
            self._heapify_down(largest)
    
    def peek(self):
        """查看最大值"""
        return self.heap[0] if self.heap else None
    
    def size(self):
        return len(self.heap)


class MinHeap:
    """最小堆实现"""
    
    def __init__(self):
        self.heap = []
    
    def parent(self, i):
        return (i - 1) // 2
    
    def left_child(self, i):
        return 2 * i + 1
    
    def right_child(self, i):
        return 2 * i + 2
    
    def insert(self, val):
        """插入元素"""
        self.heap.append(val)
        self._heapify_up(len(self.heap) - 1)
    
    def _heapify_up(self, i):
        """向上调整堆"""
        while i > 0 and self.heap[i] < self.heap[self.parent(i)]:
            self.heap[i], self.heap[self.parent(i)] = self.heap[self.parent(i)], self.heap[i]
            i = self.parent(i)
    
    def extract_min(self):
        """提取最小值"""
        if not self.heap:
            return None
        
        min_val = self.heap[0]
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        self._heapify_down(0)
        return min_val
    
    def _heapify_down(self, i):
        """向下调整堆"""
        smallest = i
        left = self.left_child(i)
        right = self.right_child(i)
        
        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left
        
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right
        
        if smallest != i:
            self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
            self._heapify_down(smallest)
    
    def peek(self):
        """查看最小值"""
        return self.heap[0] if self.heap else None
    
    def size(self):
        return len(self.heap)


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("堆 (Heap) 实现")
    print("=" * 50)
    
    # 最大堆测试
    print("\n最大堆测试:")
    max_heap = MaxHeap()
    values = [3, 1, 4, 1, 5, 9, 2, 6]
    print(f"插入数据: {values}")
    for val in values:
        max_heap.insert(val)
    
    print(f"当前最大值: {max_heap.peek()}")
    print(f"堆大小: {max_heap.size()}")
    
    print("提取最大值顺序:")
    while max_heap.size() > 0:
        print(f"  {max_heap.extract_max()}")
    
    # 最小堆测试
    print("\n最小堆测试:")
    min_heap = MinHeap()
    for val in values:
        min_heap.insert(val)
    
    print(f"当前最小值: {min_heap.peek()}")
    print("提取最小值顺序:")
    while min_heap.size() > 0:
        print(f"  {min_heap.extract_min()}")
    
    print("\n堆的特点:")
    print("  • 完全二叉树结构")
    print("  • 最大堆: 父节点 >= 子节点")
    print("  • 最小堆: 父节点 <= 子节点")
    print("  • 插入、删除: O(log n)")
    print("  • 查看最大/最小值: O(1)")
    print("  • 应用: 优先队列、堆排序、Top K问题")
