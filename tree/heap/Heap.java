/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树算法 - 最大堆/最小堆实现 (MaxHeap/MinHeap)
 * 完全二叉树满足堆序性质
 * 用于优先队列、堆排序等
 */

// 堆类型枚举
enum HeapType {
    MIN_HEAP, // 最小堆：父节点 <= 子节点
    MAX_HEAP // 最大堆：父节点 >= 子节点
}

// 堆结构
class Heap {
    private int[] data; // 存储堆元素的数组
    private int size; // 堆中元素的数量
    private HeapType type; // 堆类型（最小堆或最大堆）
    private static final int MAX_SIZE = 100; // 堆的最大容量
    
    public Heap(HeapType type) {
        this.data = new int[MAX_SIZE]; // 初始化数组
        this.size = 0; // 初始大小为0
        this.type = type; // 设置堆类型
    }
    
    /**
     * 获取父节点索引
     * 根据完全二叉树的性质，父节点索引 = (i - 1) / 2
     */
    private int parent(int i) {
        return (i - 1) / 2;
    }
    
    /**
     * 获取左子节点索引
     * 根据完全二叉树的性质，左子节点索引 = 2 * i + 1
     */
    private int leftChild(int i) {
        return 2 * i + 1;
    }
    
    /**
     * 获取右子节点索引
     * 根据完全二叉树的性质，右子节点索引 = 2 * i + 2
     */
    private int rightChild(int i) {
        return 2 * i + 2;
    }
    
    /**
     * 交换两个元素
     */
    private void swap(int i, int j) {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    
    /**
     * 向上堆化操作
     */
    private void heapifyUp(int index) {
        while (index > 0) {
            int parent = parent(index);
            
            boolean needSwap = false;
            if (type == HeapType.MIN_HEAP) {
                needSwap = data[parent] > data[index];
            } else {
                needSwap = data[parent] < data[index];
            }
            
            if (needSwap) {
                swap(parent, index);
                index = parent;
            } else {
                break;
            }
        }
    }
    
    /**
     * 向下堆化操作
     */
    private void heapifyDown(int index) {
        while (true) {
            int left = leftChild(index);
            int right = rightChild(index);
            int target = index;
            
            if (left < size) {
                boolean needSwap = false;
                if (type == HeapType.MIN_HEAP) {
                    needSwap = data[left] < data[target];
                } else {
                    needSwap = data[left] > data[target];
                }
                if (needSwap) {
                    target = left;
                }
            }
            
            if (right < size) {
                boolean needSwap = false;
                if (type == HeapType.MIN_HEAP) {
                    needSwap = data[right] < data[target];
                } else {
                    needSwap = data[right] > data[target];
                }
                if (needSwap) {
                    target = right;
                }
            }
            
            if (target != index) {
                swap(index, target);
                index = target;
            } else {
                break;
            }
        }
    }
    
    /**
     * 插入元素
     */
    public void insert(int value) {
        if (size >= MAX_SIZE) {
            throw new RuntimeException("Heap is full");
        }
        
        data[size] = value;
        heapifyUp(size);
        size++;
    }
    
    /**
     * 提取根元素
     */
    public int extract() {
        if (size == 0) {
            throw new RuntimeException("Heap is empty");
        }
        
        int root = data[0];
        data[0] = data[size - 1];
        size--;
        heapifyDown(0);
        
        return root;
    }
    
    /**
     * 查看根元素
     */
    public int peek() {
        if (size == 0) {
            throw new RuntimeException("Heap is empty");
        }
        return data[0];
    }
    
    /**
     * 获取堆大小
     */
    public int getSize() {
        return size;
    }
    
    /**
     * 检查堆是否为空
     */
    public boolean isEmpty() {
        return size == 0;
    }
    
    /**
     * 堆排序
     */
    public void heapSort(int[] arr, boolean ascending) {
        // build heap
        Heap heap = new Heap(ascending ? HeapType.MAX_HEAP : HeapType.MIN_HEAP);
        for (int value : arr) {
            heap.insert(value);
        }
        
        // 提取元素
        for (int i = 0; i < arr.length; i++) {
            arr[i] = heap.extract();
        }
    }
    
    /**
     * 查找第k大元素
     */
    public static int findKthLargest(int[] arr, int k) {
        Heap minHeap = new Heap(HeapType.MIN_HEAP);
        
        for (int i = 0; i < k; i++) {
            minHeap.insert(arr[i]);
        }
        
        for (int i = k; i < arr.length; i++) {
            if (arr[i] > minHeap.peek()) {
                minHeap.extract();
                minHeap.insert(arr[i]);
            }
        }
        
        return minHeap.peek();
    }
    
    /**
     * 中位数查找器
     */
    public static void medianFinder() {
        System.out.println("Median Finder Demo:");
        int[] data = {5, 15, 1, 3, 8, 7, 9, 10, 6, 11, 4};
        Heap maxHeap = new Heap(HeapType.MAX_HEAP);
        Heap minHeap = new Heap(HeapType.MIN_HEAP);
        
        for (int num : data) {
            System.out.printf("Insert %d: ", num);
            
            if (maxHeap.isEmpty() || num <= maxHeap.peek()) {
                maxHeap.insert(num);
            } else {
                minHeap.insert(num);
            }
            
            // balance heaps
            if (maxHeap.getSize() > minHeap.getSize() + 1) {
                minHeap.insert(maxHeap.extract());
            } else if (minHeap.getSize() > maxHeap.getSize()) {
                maxHeap.insert(minHeap.extract());
            }
            
            // calculate median
            double median;
            if (maxHeap.getSize() == minHeap.getSize()) {
                median = (maxHeap.peek() + minHeap.peek()) / 2.0;
            } else {
                median = maxHeap.peek();
            }
            
            System.out.printf("Median = %.1f\n", median);
        }
    }
    
    /**
     * 主函数 - 测试堆
     */
    public static void main(String[] args) {
        System.out.println("=".repeat(50));
        System.out.println("Heap Algorithm - Java Implementation");
        System.out.println("=".repeat(50));
        
        // test max heap
        System.out.println("\n=== Max Heap Test ===");
        Heap maxHeap = new Heap(HeapType.MAX_HEAP);
        int[] testData = {4, 10, 3, 5, 1};
        
        System.out.println("Insert elements:");
        for (int value : testData) {
            maxHeap.insert(value);
            System.out.printf("Insert %d: ", value);
            printHeap(maxHeap);
        }
        
        System.out.println("\nExtract elements:");
        while (!maxHeap.isEmpty()) {
            int extracted = maxHeap.extract();
            System.out.printf("Extract %d: ", extracted);
            printHeap(maxHeap);
        }
        
        // test min heap
        System.out.println("\n=== Min Heap Test ===");
        Heap minHeap = new Heap(HeapType.MIN_HEAP);
        
        System.out.println("Insert elements:");
        for (int value : testData) {
            minHeap.insert(value);
            System.out.printf("Insert %d: ", value);
            printHeap(minHeap);
        }
        
        // 测试堆排序
        System.out.println("\n=== Heap Sort Test ===");
        int[] sortData = {3, 1, 4, 1, 5, 9, 2, 6};
        System.out.println("Original: " + java.util.Arrays.toString(sortData));
        
        int[] ascending = sortData.clone();
        maxHeap.heapSort(ascending, true);
        System.out.println("Ascending: " + java.util.Arrays.toString(ascending));
        
        int[] descending = sortData.clone();
        maxHeap.heapSort(descending, false);
        System.out.println("Descending: " + java.util.Arrays.toString(descending));
        
        // test kth largest
        System.out.println("\n=== Kth Largest Test ===");
        int[] kthData = {3, 2, 1, 5, 6, 4};
        System.out.println("Array: " + java.util.Arrays.toString(kthData));
        for (int k = 1; k <= kthData.length; k++) {
            int kth = findKthLargest(kthData, k);
            System.out.printf("%dth largest: %d\n", k, kth);
        }
        
        // 测试中位数查找器
        medianFinder();
        
        System.out.println("\n=== Heap Characteristics ===");
        System.out.println("1. 完全二叉树，存储在数组中");
        System.out.println("2. 最小堆：父节点 <= 子节点");
        System.out.println("3. 最大堆：父节点 >= 子节点");
        System.out.println("4. 插入和提取时间复杂度：O(log n)");
        System.out.println("5. 查看堆顶时间复杂度：O(1)");
        System.out.println("6. 堆排序时间复杂度：O(n log n)");
        System.out.println("7. 空间复杂度：O(n)");
        
        System.out.println("\n=== 应用 ===");
        System.out.println("优先队列、堆排序、查找第k大元素,");
        System.out.println("数据流中位数、图算法（Dijkstra、Prim）,");
        System.out.println("操作系统任务调度、事件模拟。");
    }
    
    /**
     * 打印堆元素
     */
    private static void printHeap(Heap heap) {
        System.out.print("[");
        for (int i = 0; i < heap.getSize(); i++) {
            System.out.print(heap.data[i]);
            if (i < heap.getSize() - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }
}
