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

// 堆类型枚举
enum HeapType {
    MIN_HEAP,
    MAX_HEAP
}

// 堆结构
class Heap {
    private data: number[];
    private size: number;
    private type: HeapType;
    private static readonly MAX_SIZE: number = 100;
    
    constructor(type: HeapType) {
        this.data = new Array(Heap.MAX_SIZE);
        this.size = 0;
        this.type = type;
    }
    
    /**
     *  获取父节点索引
     */
    private parent(i: number): number {
        return Math.floor((i - 1) / 2);
    }
    
    /**
     *  获取左子节点索引
     */
    private leftChild(i: number): number {
        return 2 * i + 1;
    }
    
    /**
     *  获取右子节点索引
     */
    private rightChild(i: number): number {
        return 2 * i + 2;
    }
    
    /**
     * 交换两个元素
     */
    private swap(i: number, j: number): void {
        const temp = this.data[i];
        this.data[i] = this.data[j];
        this.data[j] = temp;
    }
    
    /**
     * 向上堆化
     */
    private heapifyUp(i: number): void {
        while (i > 0 && this.shouldSwap(this.parent(i), i)) {
            this.swap(this.parent(i), i);
            i = this.parent(i);
        }
    }
    
    /**
     * 判断是否需要交换
     */
    private shouldSwap(parent: number, child: number): boolean {
        if (this.type === HeapType.MIN_HEAP) {
            return this.data[parent] > this.data[child];
        } else {
            return this.data[parent] < this.data[child];
        }
    }
    
    /**
     * 向下堆化
     */
    private heapifyDown(i: number): void {
        const left = this.leftChild(i);
        const right = this.rightChild(i);
        let extreme = i;
        
        // 查找更极端的子节点
        if (left < this.size && this.shouldSwap(extreme, left)) {
            extreme = left;
        }
        if (right < this.size && this.shouldSwap(extreme, right)) {
            extreme = right;
        }
        
        // 如果子节点更极端，交换并继续
        if (extreme !== i) {
            this.swap(i, extreme);
            this.heapifyDown(extreme);
        }
    }
    
    /**
     * 插入元素
     */
    public insert(value: number): boolean {
        if (this.size >= Heap.MAX_SIZE) {
            console.log("heap is full!");
            return false;
        }
        
        this.data[this.size] = value;
        this.heapifyUp(this.size);
        this.size++;
        
        return true;
    }
    
    /**
     * get the top element
     */
    public peek(): number {
        if (this.size === 0) {
            console.log("堆为空!");
            return Number.MIN_SAFE_INTEGER;
        }
        return this.data[0];
    }
    
    /**
     * remove the top element
     */
    public extract(): number {
        if (this.size === 0) {
            console.log("堆为空!");
            return Number.MIN_SAFE_INTEGER;
        }
        
        const root = this.data[0];
        this.data[0] = this.data[this.size - 1];
        this.size--;
        this.heapifyDown(0);
        
        return root;
    }
    
    /**
     * 获取堆大小
     */
    public getSize(): number {
        return this.size;
    }
    
    /**
     * 检查堆是否为空
     */
    public isEmpty(): boolean {
        return this.size === 0;
    }
    
    /**
     * 打印堆
     */
    public print(): void {
        const heapType = this.type === HeapType.MIN_HEAP ? "MIN_HEAP" : "MAX_HEAP";
        console.log(`heap[${heapType}]: [${this.data.slice(0, this.size).join(', ')}]`);
    }
    
    /**
     * verify heap property
     */
    public verifyHeapProperty(): boolean {
        return this.verifyHeapPropertyRecursive(0);
    }
    
    private verifyHeapPropertyRecursive(index: number): boolean {
        if (index >= this.size) {
            return true;  // out of range, property satisfied
        }
        
        const left = this.leftChild(index);
        const right = this.rightChild(index);
        
        // check left child
        if (left < this.size) {
            if (this.type === HeapType.MIN_HEAP && this.data[index] > this.data[left]) {
                return false;
            }
            if (this.type === HeapType.MAX_HEAP && this.data[index] < this.data[left]) {
                return false;
            }
            if (!this.verifyHeapPropertyRecursive(left)) {
                return false;
            }
        }
        
        // check right child
        if (right < this.size) {
            if (this.type === HeapType.MIN_HEAP && this.data[index] > this.data[right]) {
                return false;
            }
            if (this.type === HeapType.MAX_HEAP && this.data[index] < this.data[right]) {
                return false;
            }
            if (!this.verifyHeapPropertyRecursive(right)) {
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * 堆排序演示
     */
    public heapSort(data: number[], ascending: boolean): number[] {
        console.log(`\n堆排序 (${ascending ? "升序" : "降序"}): `);
        
        // 创建临时堆
        const tempHeap = new Heap(ascending ? HeapType.MIN_HEAP : HeapType.MAX_HEAP);
        
        // 插入所有元素
        for (const item of data) {
            tempHeap.insert(item);
        }
        
        // 按顺序提取元素
        const result: number[] = [];
        while (!tempHeap.isEmpty()) {
            result.push(tempHeap.extract());
        }
        
        console.log(`[${result.join(', ')}]`);
        return result;
    }
    
    /**
     * 优先队列应用示例
     */
    public priorityQueueDemo(): void {
        console.log("\n优先队列应用示例:");
        
        // 任务优先队列（最大堆）
        const taskQueue = new Heap(HeapType.MAX_HEAP);
        
        interface Task {
            priority: number;
            description: string;
        }
        
        const tasks: Task[] = [
            { priority: 3, description: "low priority task" },
            { priority: 5, description: "high priority task" },
            { priority: 2, description: "very low priority task" },
            { priority: 4, description: "medium priority task" },
            { priority: 1, description: "lowest priority task" }
        ];
        
        // add tasks
        console.log("  adding tasks:");
        for (const task of tasks) {
            taskQueue.insert(task.priority);
            console.log(`    added: ${task.description} (priority: ${task.priority})`);
        }
        
        // process tasks (by priority)
        console.log("  processing tasks in order:");
        let order = 1;
        while (!taskQueue.isEmpty()) {
            const priority = taskQueue.extract();
            console.log(`    task ${order}: priority ${priority}`);
            order++;
        }
    }
    
    /**
     * 查找第k大元素
     */
    public findKthLargest(data: number[], k: number): number | null {
        if (k <= 0 || k > data.length) {
            return null;
        }
        
        const minHeap = new Heap(HeapType.MIN_HEAP);
        
        // 用前k个元素构建堆
        for (let i = 0; i < k; i++) {
            minHeap.insert(data[i]);
        }
        
        // process remaining elements
        for (let i = k; i < data.length; i++) {
            if (data[i] > minHeap.peek()) {
                minHeap.extract();
                minHeap.insert(data[i]);
            }
        }
        
        return minHeap.peek();
    }
    
    /**
     * 数据流的中位数查找器
     */
    public static medianFinder(): void {
        console.log("\n数据流中位数测试:");
        
        class MedianFinder {
            private maxHeap: Heap;
            private minHeap: Heap;
            
            constructor() {
                this.maxHeap = new Heap(HeapType.MAX_HEAP);
                this.minHeap = new Heap(HeapType.MIN_HEAP);
            }
            
            public addNum(num: number): void {
                // 先添加到最大堆
                this.maxHeap.insert(num);
                
                // 将最大堆中最大的元素移动到最小堆
                const maxVal = this.maxHeap.extract();
                if (maxVal !== Number.MIN_SAFE_INTEGER) {
                    this.minHeap.insert(maxVal);
                }
                
                // 如果需要，平衡两个堆
                if (this.maxHeap.getSize() < this.minHeap.getSize()) {
                    const minVal = this.minHeap.extract();
                    if (minVal !== Number.MIN_SAFE_INTEGER) {
                        this.maxHeap.insert(minVal);
                    }
                }
            }
            
            public findMedian(): number {
                if (this.maxHeap.getSize() > this.minHeap.getSize()) {
                    return this.maxHeap.peek();
                } else {
                    return (this.maxHeap.peek() + this.minHeap.peek()) / 2;
                }
            }
        }
        
        const finder = new MedianFinder();
        const stream = [5, 15, 1, 3, 8, 7, 9, 10, 6];
        
        for (const num of stream) {
            finder.addNum(num);
            const median = finder.findMedian();
            console.log(`  added ${num}, current median: ${median}`);
        }
    }
    
    /**
     * main function - test heap
     */
    public static test(): void {
        console.log("=".repeat(50));
        console.log("堆算法实现");
        console.log("=".repeat(50));
        
        // 测试最小堆
        console.log("\n=== 最小堆测试 ===");
        const minHeap = new Heap(HeapType.MIN_HEAP);
        
        const testData = [10, 20, 15, 30, 5];
        console.log("inserting data:");
        for (const value of testData) {
            process.stdout.write(`${value} `);
            minHeap.insert(value);
        }
        console.log();
        minHeap.print();
        console.log();
        
        console.log("=== 提取元素 ===");
        while (!minHeap.isEmpty()) {
            const extracted = minHeap.extract();
            console.log(`extracted: ${extracted}`);
            minHeap.print();
        }
        console.log();
        
        // 测试最大堆
        console.log("=== 最大堆测试 ===");
        const maxHeap = new Heap(HeapType.MAX_HEAP);
        
        console.log("inserting data:");
        for (const value of testData) {
            process.stdout.write(`${value} `);
            maxHeap.insert(value);
        }
        console.log();
        maxHeap.print();
        console.log();
        
        console.log("=== 提取元素 ===");
        while (!maxHeap.isEmpty()) {
            const extracted = maxHeap.extract();
            console.log(`extracted: ${extracted}`);
            maxHeap.print();
        }
        console.log();
        
        // 测试堆排序
        const sortData = [64, 34, 25, 12, 22, 11, 90, 88, 45, 50];
        maxHeap.heapSort(sortData, true);   // ascending
        maxHeap.heapSort(sortData, false);  // descending
        
        // 测试优先队列
        maxHeap.priorityQueueDemo();
        
        // 测试第k大
        console.log("\n=== kth largest element test ===");
        const arr = [3, 2, 1, 5, 6, 4];
        for (let k = 1; k <= Math.min(3, arr.length); k++) {
            const kthLargest = maxHeap.findKthLargest(arr, k);
            console.log(`${k}th largest: ${kthLargest}`);
        }
        
        // 测试中位数查找器
        Heap.medianFinder();
        
        console.log("\n=== 堆特性 ===");
        console.log("1. 完全二叉树，存储在数组中");
        console.log("2. 最小堆：父节点 <= 子节点");
        console.log("3. 最大堆：父节点 >= 子节点");
        console.log("4. 插入和提取时间复杂度：O(log n)");
        console.log("5. 查看堆顶时间复杂度: O(1)");
        console.log("6. 堆排序时间复杂度: O(n log n)");
        console.log("7. 空间复杂度: O(n)");
        
        console.log("\n=== 应用 ===");
        console.log("优先队列、堆排序、查找第k大元素,");
        console.log("数据流中位数、图算法（Dijkstra、Prim）,");
        console.log("操作系统任务调度、事件模拟。");
    }
}

// run test if this file is executed directly
if (require.main === module) {
    Heap.test();
}

export { Heap, HeapType };
