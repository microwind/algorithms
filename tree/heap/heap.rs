/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/*
 * 树算法 - 最大堆/最小堆实现 (MaxHeap/MinHeap)
 * 完全二叉树满足堆序性质
 * 用于优先队列、堆排序等
 */

use std::cmp::{Ord, Ordering, PartialOrd};
use std::collections::BinaryHeap;

/// heap type enumeration
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum HeapType {
    MinHeap, // 最小堆：父节点 <= 子节点
    MaxHeap, // 最大堆：父节点 >= 子节点
}

/// heap structure with generic type T
/// T must implement Ord for comparison
#[derive(Debug, Clone)]
pub struct Heap<T: Ord> {
    data: Vec<T>, // 存储堆元素的向量
    heap_type: HeapType, // 堆类型
}

impl<T: Ord + Clone + std::fmt::Debug> Heap<T> {
    /// create new heap with specified type
    pub fn new(heap_type: HeapType) -> Self {
        Self {
            data: Vec::new(),
            heap_type,
        }
    }

    /// get parent index
/// 根据完全二叉树的性质，父节点索引 = (i - 1) / 2
    fn parent(i: usize) -> usize {
        (i - 1) / 2
    }

    /// get left child index
/// 根据完全二叉树的性质，左子节点索引 = 2 * i + 1
    fn left_child(i: usize) -> usize {
        2 * i + 1
    }

    /// get right child index
/// 根据完全二叉树的性质，右子节点索引 = 2 * i + 2
    fn right_child(i: usize) -> usize {
        2 * i + 2
    }

    /// swap two elements
/// 交换堆中指定位置的两个元素
    fn swap(&mut self, i: usize, j: usize) {
        self.data.swap(i, j);
    }

    /// determine whether to swap based on heap type
/// 根据堆类型判断父节点和子节点是否需要交换
    fn should_swap(&self, parent_idx: usize, child_idx: usize) -> bool {
        match self.heap_type {
            HeapType::MinHeap => self.data[parent_idx] > self.data[child_idx],
            HeapType::MaxHeap => self.data[parent_idx] < self.data[child_idx],
        }
    }

    /// heapify up (sift up) operation
/// 将插入的元素向上调整，保持堆性质
/// 时间复杂度：O(log n)
    fn heapify_up(&mut self, mut index: usize) {
        while index > 0 {
            let parent = Self::parent(index);
            if self.should_swap(parent, index) {
                self.swap(parent, index);
                index = parent;
            } else {
                break;
            }
        }
    }

    /// heapify down (sift down) operation
/// 将堆顶元素向下调整，保持堆性质
/// 时间复杂度：O(log n)
    fn heapify_down(&mut self, mut index: usize) {
        let size = self.data.len();
        
        while index < size {
            let left = Self::left_child(index);
            let right = Self::right_child(index);
            let mut extreme = index;

            // find the more extreme child
            // 查找更极端的子节点（最大堆找更大的，最小堆找更小的）
            if left < size && self.should_swap(extreme, left) {
                extreme = left;
            }
            if right < size && self.should_swap(extreme, right) {
                extreme = right;
            }

            if extreme != index {
                self.swap(index, extreme);
                index = extreme;
            } else {
                break;
            }
        }
    }

    /// insert element into heap
/// 1. 将元素添加到向量末尾
/// 2. 向上堆化调整位置
/// 时间复杂度：O(log n)
    pub fn insert(&mut self, value: T) {
        self.data.push(value);
        self.heapify_up(self.data.len() - 1);
    }

    /// get the top element without removing it
/// 返回堆顶元素（最大堆返回最大值，最小堆返回最小值）
/// 时间复杂度：O(1)
    pub fn peek(&self) -> Option<&T> {
        self.data.first()
    }

    /// extract the top element
/// 1. 保存堆顶元素
/// 2. 将最后一个元素移到堆顶
/// 3. 向下堆化调整
/// 时间复杂度：O(log n)
    pub fn extract(&mut self) -> Option<T> {
        if self.data.is_empty() {
            return None;
        }

        let last = self.data.pop();
        if self.data.is_empty() {
            return last;
        }

        let root = std::mem::replace(&mut self.data[0], last.unwrap());
        self.heapify_down(0);
        Some(root)
    }

    /// get heap size
/// 返回堆中元素的数量
/// 时间复杂度：O(1)
    pub fn size(&self) -> usize {
        self.data.len()
    }

    /// 检查堆是否为空
    pub fn is_empty(&self) -> bool {
        self.data.is_empty()
    }

    /// verify heap property
/// 验证堆性质是否满足
    pub fn verify_heap_property(&self) -> bool {
        self.verify_heap_property_recursive(0)
    }

    fn verify_heap_property_recursive(&self, index: usize) -> bool {
        let left = Self::left_child(index);
        let right = Self::right_child(index);

        if left < self.data.len() {
            if !self.should_swap(index, left) {
                return false;
            }
            if !self.verify_heap_property_recursive(left) {
                return false;
            }
        }

        if right < self.data.len() {
            if !self.should_swap(index, right) {
                return false;
            }
            if !self.verify_heap_property_recursive(right) {
                return false;
            }
        }

        true
    }

    /// print heap contents
/// 按照堆类型打印堆中所有元素
    pub fn print(&self) {
        let heap_type_str = match self.heap_type {
            HeapType::MinHeap => "MinHeap",
            HeapType::MaxHeap => "MaxHeap",
        };
        println!("{}: {:?}", heap_type_str, self.data);
    }

    /// 堆排序演示
    pub fn heap_sort(arr: &[T], ascending: bool) -> Vec<T> {
        if arr.is_empty() {
            return Vec::new();
        }

        let heap_type = if ascending {
            HeapType::MinHeap
        } else {
            HeapType::MaxHeap
        };

        let mut heap = Heap::new(heap_type);
        for item in arr {
            heap.insert(item.clone());
        }

        let mut result = Vec::new();
        while let Some(item) = heap.extract() {
            result.push(item);
        }

        result
    }
}

/// 使用堆的优先队列实现
/// 优先队列始终优先处理最高优先级的元素
pub struct PriorityQueue<T: Ord> {
    heap: Heap<T>,
}

impl<T: Ord + Clone + std::fmt::Debug> PriorityQueue<T> {
    /// 创建新优先队列
    pub fn new(min_heap: bool) -> Self {
        let heap_type = if min_heap {
            HeapType::MinHeap
        } else {
            HeapType::MaxHeap
        };
        Self {
            heap: Heap::new(heap_type),
        }
    }

    /// enqueue element
/// 向优先队列中添加元素
    pub fn enqueue(&mut self, item: T) {
        self.heap.insert(item);
    }

    /// dequeue element
/// 从优先队列中移除并返回最高优先级元素
    pub fn dequeue(&mut self) -> Option<T> {
        self.heap.extract()
    }

    /// peek at front element
/// 查看优先队列中的最高优先级元素
    pub fn peek(&self) -> Option<&T> {
        self.heap.peek()
    }

    /// check if empty
/// 检查优先队列是否为空
    pub fn is_empty(&self) -> bool {
        self.heap.is_empty()
    }

    /// get queue size
/// 获取优先队列大小
    pub fn size(&self) -> usize {
        self.heap.size()
    }
}

/// find kth largest element using min heap
/// 使用最小堆查找第k大元素
/// 算法思路：维护一个大小为k的最小堆
pub fn find_kth_largest(arr: &[i32], k: usize) -> Option<i32> {
    if k == 0 || k > arr.len() {
        return None;
    }

    let mut heap = Heap::new(HeapType::MinHeap);

    // build heap with first k elements
    for &item in arr.iter().take(k) {
        heap.insert(item);
    }

    // process remaining elements
    for &item in arr.iter().skip(k) {
        if let Some(&min_val) = heap.peek() {
            if item > min_val {
                heap.extract();
                heap.insert(item);
            }
        }
    }

    heap.extract()
}

/// find kth smallest element using max heap
/// 使用最大堆查找第k小元素
/// 算法思路：维护一个大小为k的最大堆
pub fn find_kth_smallest(arr: &[i32], k: usize) -> Option<i32> {
    if k == 0 || k > arr.len() {
        return None;
    }

    let mut heap = Heap::new(HeapType::MaxHeap);

    // build heap with first k elements
    for &item in arr.iter().take(k) {
        heap.insert(item);
    }

    // process remaining elements
    for &item in arr.iter().skip(k) {
        if let Some(&max_val) = heap.peek() {
            if item < max_val {
                heap.extract();
                heap.insert(item);
            }
        }
    }

    heap.extract()
}

/// 数据流中位数查找器
/// 使用两个堆来动态维护数据流的中位数
pub struct MedianFinder {
    max_heap: Heap<i32>, // 较小一半：最大堆存储较小的数
    min_heap: Heap<i32>, // 较大一半：最小堆存储较大的数
}

impl MedianFinder {
    /// 创建新中位数查找器
    pub fn new() -> Self {
        Self {
            max_heap: Heap::new(HeapType::MaxHeap),
            min_heap: Heap::new(HeapType::MinHeap),
        }
    }

    /// 向数据流添加数字
    pub fn add_num(&mut self, num: i32) {
        // 首先添加到最大堆
        self.max_heap.insert(num);
        
        // 从最大堆移动最大值到最小堆
        if let Some(max_val) = self.max_heap.extract() {
            self.min_heap.insert(max_val);
        }
        
        // 平衡堆
        if self.max_heap.size() < self.min_heap.size() {
            if let Some(min_val) = self.min_heap.extract() {
                self.max_heap.insert(min_val);
            }
        }
    }

    /// find current median
/// 查找当前中位数
/// 如果最大堆元素多，中位数就是最大堆顶
/// 否则取两个堆顶的平均值
    pub fn find_median(&self) -> f64 {
        if self.max_heap.size() > self.min_heap.size() {
            *self.max_heap.peek().unwrap() as f64
        } else {
            let max_val = *self.max_heap.peek().unwrap() as f64;
            let min_val = *self.min_heap.peek().unwrap() as f64;
            (max_val + min_val) / 2.0
        }
    }
}

fn main() {
    println!("{}", "=".repeat(70));
    println!("Heap Algorithms - Rust Implementation");
    println!("{}", "=".repeat(70));

    // test min heap
    println!("\n=== Min Heap Test ===");
    let mut min_heap = Heap::new(HeapType::MinHeap);
    let test_data = vec![10, 20, 15, 30, 5];
    
    println!("Inserting data: {:?}", test_data);
    for &item in &test_data {
        min_heap.insert(item);
    }
    
    println!("Min heap test:");
    min_heap.print();
    println!("Heap property valid: {}", min_heap.verify_heap_property());

    println!("Extracting elements:");
    while let Some(extracted) = min_heap.extract() {
        println!("Extracted: {}", extracted);
        min_heap.print();
    }

    // test max heap
    println!("\n=== Max Heap Test ===");
    let mut max_heap = Heap::new(HeapType::MaxHeap);
    
    println!("Inserting data: {:?}", test_data);
    for &item in &test_data {
        max_heap.insert(item);
    }
    
    println!("Max heap test:");
    max_heap.print();
    println!("Heap property valid: {}", max_heap.verify_heap_property());

    println!("Extracting elements:");
    while let Some(extracted) = max_heap.extract() {
        println!("Extracted: {}", extracted);
        max_heap.print();
    }

    // 测试堆排序
    println!("\n=== Heap Sort Test ===");
    let sort_data = vec![64, 34, 25, 12, 22, 11, 90, 88, 45, 50];
    println!("Original: {:?}", sort_data);
    
    let ascending = Heap::heap_sort(&sort_data, true);
    println!("Ascending sort: {:?}", ascending);
    
    let descending = Heap::heap_sort(&sort_data, false);
    println!("Descending sort: {:?}", descending);

    // 测试优先队列
    println!("\n=== Priority Queue Test ===");
    let mut pq = PriorityQueue::new(true);
    let tasks = vec![(3, "low"), (1, "high"), (5, "critical"), (2, "medium"), (4, "urgent")];
    
    println!("Adding tasks with priorities:");
    for (priority, description) in &tasks {
        println!("  {}: priority {}", description, priority);
        pq.enqueue(*priority);
    }
    
    println!("Priority queue test:");
    while let Some(item) = pq.dequeue() {
        println!("Dequeued: {}", item);
    }

    // 测试第k元素
    println!("\n=== Kth Elements Test ===");
    let arr = [3, 2, 1, 5, 6, 4];
    println!("Array: {:?}", arr);
    for k in 1..=arr.len() {
        let kth_largest = find_kth_largest(&arr, k);
        let kth_smallest = find_kth_smallest(&arr, k);
        println!("{}th largest: {}", k, kth_largest.unwrap());
        println!("{}th smallest: {}", k, kth_smallest.unwrap());
    }

    // test median finder
    println!("\n=== Median Stream Test ===");
    let mut finder = MedianFinder::new();
    let stream = vec![5, 15, 1, 3, 8, 7, 9, 10, 6];
    
    for &num in &stream {
        finder.add_num(num);
        let median = finder.find_median();
        println!("Added {}, current median: {:.1}", num, median);
    }

    println!("\n=== 算法特性 ===");
    println!("1. 完全二叉树结构存储在数组中");
    println!("2. 最小堆：父节点 <= 子节点");
    println!("3. 最大堆：父节点 >= 子节点");
    println!("4. 插入和提取：O(log n)");
    println!("5. 查看：O(1)");
    println!("6. 堆排序：O(n log n)");
    println!("7. 空间复杂度：O(n)");

    println!("\n=== 应用 ===");
    println!("优先队列、堆排序、查找第k大元素,");
    println!("数据流中位数、图算法（Dijkstra、Prim）,");
    println!("操作系统任务调度、事件模拟。");
}
