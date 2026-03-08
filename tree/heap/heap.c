/*
 * 树算法 - 最大堆/最小堆实现 (MaxHeap/MinHeap)
 * 完全二叉树，满足堆序性质
 * 用于优先队列、堆排序等
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

// 堆类型枚举
typedef enum {
    MIN_HEAP,
    MAX_HEAP
} HeapType;

// 堆结构
typedef struct {
    int data[MAX_SIZE];
    int size;
    HeapType type;
} Heap;

/**
 * 创建堆
 */
Heap* create_heap(HeapType type) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->type = type;
    return heap;
}

/**
 * 交换两个元素
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * 获取父节点索引
 */
int parent(int i) {
    return (i - 1) / 2;
}

/**
 * 获取左子节点索引
 */
int left_child(int i) {
    return 2 * i + 1;
}

/**
 * 获取右子节点索引
 */
int right_child(int i) {
    return 2 * i + 2;
}

/**
 * 比较函数，根据堆类型返回比较结果
 */
int compare(Heap* heap, int a, int b) {
    if (heap->type == MIN_HEAP) {
        return a < b;  // 最小堆：小的优先
    } else {
        return a > b;  // 最大堆：大的优先
    }
}

/**
 * 向上调整堆（插入时使用）
 */
void heapify_up(Heap* heap, int index) {
    while (index > 0 && compare(heap, heap->data[index], heap->data[parent(index)])) {
        swap(&heap->data[index], &heap->data[parent(index)]);
        index = parent(index);
    }
}

/**
 * 向下调整堆（删除时使用）
 */
void heapify_down(Heap* heap, int index) {
    int smallest_or_largest = index;
    int left = left_child(index);
    int right = right_child(index);
    
    if (left < heap->size && compare(heap, heap->data[left], heap->data[smallest_or_largest])) {
        smallest_or_largest = left;
    }
    
    if (right < heap->size && compare(heap, heap->data[right], heap->data[smallest_or_largest])) {
        smallest_or_largest = right;
    }
    
    if (smallest_or_largest != index) {
        swap(&heap->data[index], &heap->data[smallest_or_largest]);
        heapify_down(heap, smallest_or_largest);
    }
}

/**
 * 插入元素
 */
int heap_insert(Heap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("堆已满，无法插入\n");
        return 0;
    }
    
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    
    return 1;
}

/**
 * 获取堆顶元素（最小值或最大值）
 */
int heap_peek(Heap* heap) {
    if (heap->size == 0) {
        printf("堆为空\n");
        return (heap->type == MIN_HEAP) ? INT_MAX : INT_MIN;
    }
    
    return heap->data[0];
}

/**
 * 删除堆顶元素
 */
int heap_extract(Heap* heap) {
    if (heap->size == 0) {
        printf("堆为空，无法删除\n");
        return (heap->type == MIN_HEAP) ? INT_MAX : INT_MIN;
    }
    
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    
    return root;
}

/**
 * 检查堆是否为空
 */
int heap_is_empty(Heap* heap) {
    return heap->size == 0;
}

/**
 * 获取堆的大小
 */
int heap_size(Heap* heap) {
    return heap->size;
}

/**
 * 打印堆的内容
 */
void print_heap(Heap* heap) {
    printf("堆内容 (");
    printf(heap->type == MIN_HEAP ? "最小堆" : "最大堆");
    printf("): [");
    
    for (int i = 0; i < heap->size; i++) {
        printf("%d", heap->data[i]);
        if (i < heap->size - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * 验证堆性质
 */
int verify_heap_property(Heap* heap, int index) {
    if (index >= heap->size) {
        return 1;  // 超出范围，满足性质
    }
    
    int left = left_child(index);
    int right = right_child(index);
    
    // 检查与左子节点的堆序性质
    if (left < heap->size) {
        if (heap->type == MIN_HEAP && heap->data[index] > heap->data[left]) {
            return 0;
        }
        if (heap->type == MAX_HEAP && heap->data[index] < heap->data[left]) {
            return 0;
        }
    }
    
    // 检查与右子节点的堆序性质
    if (right < heap->size) {
        if (heap->type == MIN_HEAP && heap->data[index] > heap->data[right]) {
            return 0;
        }
        if (heap->type == MAX_HEAP && heap->data[index] < heap->data[right]) {
            return 0;
        }
    }
    
    // 递归检查子树
    return verify_heap_property(heap, left) && verify_heap_property(heap, right);
}

/**
 * 堆排序演示
 */
void heap_sort_demo(int arr[], int n, int ascending) {
    printf("\n堆排序 (%s): ", ascending ? "升序" : "降序");
    
    // 创建临时堆
    Heap* temp_heap = create_heap(ascending ? MIN_HEAP : MAX_HEAP);
    
    // 插入所有元素
    for (int i = 0; i < n; i++) {
        heap_insert(temp_heap, arr[i]);
    }
    
    // 依次取出元素
    printf("[");
    for (int i = 0; i < n; i++) {
        int val = heap_extract(temp_heap);
        printf("%d", val);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
    
    free(temp_heap);
}

/**
 * 优先队列应用示例
 */
void priority_queue_demo() {
    printf("\n优先队列应用示例:\n");
    
    // 任务优先级队列（最大堆）
    Heap* task_queue = create_heap(MAX_HEAP);
    
    struct {
        int priority;
        char* description;
    } tasks[] = {
        {3, "低优先级任务"},
        {5, "高优先级任务"},
        {2, "很低优先级任务"},
        {4, "中优先级任务"},
        {1, "最低优先级任务"}
    };
    
    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);
    
    // 添加任务
    printf("  添加任务:\n");
    for (int i = 0; i < num_tasks; i++) {
        heap_insert(task_queue, tasks[i].priority);
        printf("    添加: %s (优先级: %d)\n", 
               tasks[i].description, tasks[i].priority);
    }
    
    // 处理任务（按优先级）
    printf("  处理任务顺序:\n");
    int order = 1;
    while (!heap_is_empty(task_queue)) {
        int priority = heap_extract(task_queue);
        printf("    第%d个: 优先级 %d\n", order++, priority);
    }
    
    free(task_queue);
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("最大堆/最小堆实现 (MaxHeap/MinHeap)\n");
    printf("==================================================\n");
    
    // 最小堆测试
    printf("\n最小堆测试:\n");
    Heap* min_heap = create_heap(MIN_HEAP);
    
    int min_data[] = {5, 3, 8, 1, 6, 9, 2, 7, 4};
    int min_size = sizeof(min_data) / sizeof(min_data[0]);
    
    for (int i = 0; i < min_size; i++) {
        heap_insert(min_heap, min_data[i]);
        printf("  插入 %d: ", min_data[i]);
        print_heap(min_heap);
    }
    
    printf("\n  堆顶元素: %d\n", heap_peek(min_heap));
    printf("  堆性质验证: %s\n", 
           verify_heap_property(min_heap, 0) ? "✓" : "✗");
    
    printf("\n  依次删除元素:\n");
    while (!heap_is_empty(min_heap)) {
        int val = heap_extract(min_heap);
        printf("    删除 %d: ", val);
        print_heap(min_heap);
    }
    
    // 最大堆测试
    printf("\n最大堆测试:\n");
    Heap* max_heap = create_heap(MAX_HEAP);
    
    int max_data[] = {5, 3, 8, 1, 6, 9, 2, 7, 4};
    int max_size = sizeof(max_data) / sizeof(max_data[0]);
    
    for (int i = 0; i < max_size; i++) {
        heap_insert(max_heap, max_data[i]);
    }
    
    printf("  最终堆: ");
    print_heap(max_heap);
    printf("  堆性质验证: %s\n", 
           verify_heap_property(max_heap, 0) ? "✓" : "✗");
    
    // 堆排序演示
    int sort_data[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    int sort_size = sizeof(sort_data) / sizeof(sort_data[0]);
    
    heap_sort_demo(sort_data, sort_size, 1);  // 升序
    heap_sort_demo(sort_data, sort_size, 0);  // 降序
    
    // 优先队列应用
    priority_queue_demo();
    
    printf("\n应用场景:\n");
    printf("  • 优先队列\n");
    printf("  • 堆排序\n");
    printf("  • 图算法 (Dijkstra, Prim)\n");
    printf("  • 操作系统任务调度\n");
    printf("  • 事件驱动模拟\n");
    printf("  • 查找第k大/小元素\n");
    
    printf("\n复杂度分析:\n");
    printf("  • 插入: O(log n)\n");
    printf("  • 删除堆顶: O(log n)\n");
    printf("  • 查看堆顶: O(1)\n");
    printf("  • 建堆: O(n)\n");
    printf("  • 空间复杂度: O(n)\n");
    
    // 释放内存
    free(min_heap);
    free(max_heap);
    
    return 0;
}
