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
const HeapType = {
    MIN_HEAP: 'MIN_HEAP', // 最小堆：父节点 <= 子节点
    MAX_HEAP: 'MAX_HEAP' // 最大堆：父节点 >= 子节点
};

// 堆结构
class Heap {
    constructor(type) {
        this.data = []; // 存储堆元素的数组
        this.type = type; // 堆类型（最小堆或最大堆）
    }

    /**
     * 获取父节点索引
     * 根据完全二叉树的性质，父节点索引 = Math.floor((i - 1) / 2)
     */
    parent(i) {
        return Math.floor((i - 1) / 2);
    }

    /**
     * 获取左子节点索引
     * 根据完全二叉树的性质，左子节点索引 = 2 * i + 1
     */
    leftChild(i) {
        return 2 * i + 1;
    }

    /**
     * 获取右子节点索引
     * 根据完全二叉树的性质，右子节点索引 = 2 * i + 2
     */
    rightChild(i) {
        return 2 * i + 2;
    }

    /**
     * 交换两个元素
     * 交换堆中指定位置的两个元素
     */
    swap(i, j) {
        const temp = this.data[i];
        this.data[i] = this.data[j];
        this.data[j] = temp;
    }

    /**
     * 向上堆化
     * 将插入的元素向上调整，保持堆性质
     * 时间复杂度：O(log n)
     */
    heapifyUp(i) {
        while (i > 0 && this.shouldSwap(this.parent(i), i)) {
            this.swap(this.parent(i), i);
            i = this.parent(i);
        }
    }

    /**
     * 判断是否需要交换
     * 根据堆类型判断父节点和子节点是否需要交换
     */
    shouldSwap(parent, child) {
        if (this.type === HeapType.MIN_HEAP) {
            return this.data[parent] > this.data[child];
        } else {
            return this.data[parent] < this.data[child];
        }
    }

    /**
     * 向下堆化
     * 将堆顶元素向下调整，保持堆性质
     * 时间复杂度：O(log n)
     */
    heapifyDown(i) {
        const left = this.leftChild(i);
        const right = this.rightChild(i);
        let extreme = i;

        // 查找更极端的子节点
        // 最大堆找更大的，最小堆找更小的
        if (left < this.size() && this.shouldSwap(extreme, left)) {
            extreme = left;
        }
        if (right < this.size() && this.shouldSwap(extreme, right)) {
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
     * 1. 将元素添加到数组末尾
     * 2. 向上堆化调整位置
     * 时间复杂度：O(log n)
     */
    insert(value) {
        this.data.push(value);
        this.heapifyUp(this.size() - 1);
    }

    /**
     * 获取堆顶元素
     * 返回堆顶元素（最大堆返回最大值，最小堆返回最小值）
     * 时间复杂度：O(1)
     */
    peek() {
        if (this.isEmpty()) {
            console.log("堆为空!");
            return null;
        }
        return this.data[0];
    }

    /**
     * 移除堆顶元素
     * 1. 保存堆顶元素
     * 2. 将最后一个元素移到堆顶
     * 3. 向下堆化调整
     * 时间复杂度：O(log n)
     */
    extract() {
        if (this.isEmpty()) {
            console.log("堆为空!");
            return null;
        }

        const root = this.data[0];
        const last = this.data.pop();
        
        if (this.size() > 0) {
            this.data[0] = last;
            this.heapifyDown(0);
        }

        return root;
    }

    /**
     * 获取堆大小
     * 返回堆中元素的数量
     * 时间复杂度：O(1)
     */
    size() {
        return this.data.length;
    }

    /**
     * 检查堆是否为空
     * 返回堆是否为空
     * 时间复杂度：O(1)
     */
    isEmpty() {
        return this.size() === 0;
    }

    /**
     * 打印堆
     * 按照堆类型打印堆中所有元素
     */
    print() {
        console.log(`heap[${this.type}]: [${this.data.join(', ')}]`);
    }

    /**
     *  main function - test heap
     */
    static test() {
        // 测试最小堆
        console.log("=== minimum heap test ===");
        const minHeap = new Heap(HeapType.MIN_HEAP);

        const testData = [10, 20, 15, 30, 5];
        console.log("insert data:");
        for (const value of testData) {
            process.stdout.write(value + " ");
            minHeap.insert(value);
        }
        console.log();
        minHeap.print();
        console.log();

        console.log("=== extract elements ===");
        while (!minHeap.isEmpty()) {
            console.log(`extract: ${minHeap.extract()}`);
            minHeap.print();
        }
        console.log();

        // 测试最大堆
        console.log("=== maximum heap test ===");
        const maxHeap = new Heap(HeapType.MAX_HEAP);

        console.log("insert data:");
        for (const value of testData) {
            process.stdout.write(value + " ");
            maxHeap.insert(value);
        }
        console.log();
        maxHeap.print();
        console.log();

        console.log("=== extract elements ===");
        while (!maxHeap.isEmpty()) {
            console.log(`extract: ${maxHeap.extract()}`);
            maxHeap.print();
        }
        console.log();

        console.log("=== 堆特性 ===");
        console.log("1. 完全二叉树，存储在数组中");
        console.log("2. 最小堆：父节点 <= 子节点");
        console.log("3. 最大堆：父节点 >= 子节点");
        console.log("4. 插入和提取时间复杂度：O(log n)");
        console.log("5. 查看堆顶时间复杂度：O(1)");
    }
}

// run test if this file is executed directly
if (require.main === module) {
    Heap.test();
}

module.exports = { Heap, HeapType };
