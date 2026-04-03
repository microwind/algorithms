/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 堆排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 打印数组内容的辅助函数
 */
void printArray(int arr[], int size, const char* label) {
    printf("%s: [", label);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * 打印堆的树形结构
 */
void printHeapTree(int arr[], int size, const char* title) {
    if (size < 7) {
        printf("%s: [", title);
        for (int i = 0; i < size; i++) {
            printf("%d", arr[i]);
            if (i < size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        return;
    }
    
    printf("%s\n", title);
    printf("              %d(0)\n", arr[0]);
    printf("          /         \\\n");
    printf("        %d(1)        %d(2)\n", arr[1], arr[2]);
    printf("       /    \\      /     \\\n");
    printf("   %d(3)  %d(4)  %d(5)  %d(6)\n", arr[3], arr[4], arr[5], arr[6]);
    printf("\n");
}

/**
 * 性能测试辅助函数
 */
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char* name) {
    // 创建数组副本，避免修改原数组
    int* testArr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        testArr[i] = arr[i];
    }
    printArray(testArr, size, name);
    
    // 开始计时
    clock_t start = clock();
    sortFunc(testArr, size);
    clock_t end = clock();
    
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.3fms\n", name, duration);
    printArray(testArr, size, "排序后数组");
    printf("\n"); // 空行分隔
    
    free(testArr);
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
int testData[] = {7, 11, 9, 10, 12, 13, 8};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 堆化辅助函数 - 最大堆
 */
void heapify(int arr[], int n, int i) {
    int largest = i; // 初始化最大元素为根节点
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点
    
    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // 如果右子节点大于当前最大节点
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // 如果最大节点不是根节点，交换并继续堆化
    if (largest != i) {
        // 关键点：交换父子节点
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

/**
 * 带步骤打印的堆化函数
 */
void heapifyWithSteps(int arr[], int n, int i, int parentStep) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // 第一步：比较左子节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // 第二步：比较右子节点
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // 第三步：如果需要交换，执行交换并递归堆化
    if (largest != i) {
        // 关键点：交换父子节点
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        int newLeft = 2 * largest + 1;
        int newRight = 2 * largest + 2;
        int maxIdx = largest;
        
        if (newLeft < n && arr[newLeft] > arr[maxIdx]) maxIdx = newLeft;
        if (newRight < n && arr[newRight] > arr[maxIdx]) maxIdx = newRight;
        
        char subStep[3];
        if (largest == 0) sprintf(subStep, "1");
        else if (largest == 1) sprintf(subStep, "1");
        else if (largest == 2) sprintf(subStep, "1");
        else if (largest == 3) sprintf(subStep, "1");
        else if (largest == 4) sprintf(subStep, "1");
        else if (largest == 5) sprintf(subStep, "1");
        else sprintf(subStep, "1");
        
        printf("%d.%s maxHeapify: idx= %d left= %d right= %d max= %d size= %d\n", 
               parentStep, subStep, largest, newLeft, newRight, maxIdx, n);
        printHeapTree(arr, n, "");
        
        heapifyWithSteps(arr, n, largest, parentStep);
    }
}

/**
 * 堆排序基础版本 - 最大堆
 * 
 * 算法原理：
 * 1. 构建最大堆：将无序数组构建成最大堆结构
 * 2. 交换堆顶：将堆顶元素（最大值）与堆尾元素交换
 * 3. 调整堆：对剩余元素重新堆化，保持堆结构
 * 4. 重复步骤2-3，直到整个数组有序
 * 
 * 生活类比：就像在队伍中挑选最高的人站到最后，
 * 然后在剩下的人中再挑选最高的站到倒数第二个位置，依此类推
 * 
 * 时间复杂度：O(n log n) - 构建堆O(n)，每次堆化O(log n)
 * 空间复杂度：O(1) - 原地排序，不需要额外空间
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
void heapSort1(int arr[], int n) {
    printf("heapSort1 max-heap:\n");
    
    printHeapTree(arr, n, "oringal array:");
    
    // 第一步：构建最大堆
    printf("父节点步骤\n");
    int stepCount = 1;
    // 关键点：从最后一个非叶子节点开始堆化
    for (int i = n / 2 - 1; i >= 0; i--) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int maxIdx = i;
        
        if (left < n && arr[left] > arr[maxIdx]) maxIdx = left;
        if (right < n && arr[right] > arr[maxIdx]) maxIdx = right;
        
        printf("%d. maxHeapify: idx= %d left= %d right= %d max= %d size= %d\n", 
               stepCount, i, left, right, maxIdx, n);
        stepCount++;
        
        if (maxIdx != i) {
            int temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
            printHeapTree(arr, n, "");
            
            // 递归堆化
            heapifyWithSteps(arr, n, maxIdx, stepCount);
            stepCount++;
        } else {
            stepCount++;
        }
    }
    
    // 第二步：逐个取出堆顶元素并排序
    printf("子节点堆排序:\n");
    for (int i = n - 1; i > 0; i--) {
        printf("%d. swap, child = %d:\n", stepCount, i);
        // 将堆顶元素（最大）与末尾元素交换
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        printHeapTree(arr, n, "");
        
        // 第三步：重新调整堆
        heapifyWithSteps(arr, i, 0, stepCount);
        stepCount++;
    }
    
    printArray(arr, n, "排序后数组");
}

/**
 * 堆化辅助函数 - 最小堆
 */
void heapifyMin(int arr[], int n, int i) {
    int smallest = i; // 初始化最小元素为根节点
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点
    
    // 如果左子节点小于根节点
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }
    
    // 如果右子节点小于当前最小节点
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }
    
    // 如果最小节点不是根节点，交换并继续堆化
    if (smallest != i) {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapifyMin(arr, n, smallest);
    }
}

/**
 * 堆排序优化版本 - 最小堆
 * 
 * 算法思路：
 * 使用最小堆进行排序，最终结果为升序
 * 构建最小堆后，依次取出最小元素放到已排序区域
 * 
 * 优化效果：
 * - 直接得到升序结果，无需反转
 * - 某些场景下更直观
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
void heapSort2(int arr[], int n) {
    printf("heapSort2 min-heap:\n");
    
    int* sorted = (int*)malloc(n * sizeof(int));
    int sortedIndex = 0;
    
    // 第一步：构建最小堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMin(arr, n, i);
    }
    
    // 第二步：逐个取出最小元素
    for (int i = n - 1; i >= 0; i--) {
        // 将堆顶元素（最小）与末尾元素交换
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // 保存最小元素到排序数组
        sorted[sortedIndex++] = arr[i];
        
        // 第三步：重新调整堆
        heapifyMin(arr, i, 0);
    }
    
    // 第四步：将排序结果复制回原数组（升序）
    for (int i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }
    
    free(sorted);
    printArray(arr, n, "排序后数组");
}

/**
 * 堆排序 - 迭代版本
 * 
 * 算法思路：
 * 使用迭代方式实现堆化，避免递归调用
 * 通过循环调整父子节点关系
 * 
 * 优化效果：
 * - 避免了递归调用的开销
 * - 更好的性能表现
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
void heapSort3(int arr[], int n) {
    printf("heapSort3 iterative:\n");
    
    // 构建最大堆（迭代方式）
    for (int i = n / 2 - 1; i >= 0; i--) {
        int current = i;
        while (1) {
            int largest = current;
            int left = 2 * current + 1;
            int right = 2 * current + 2;
            
            if (left < n && arr[left] > arr[largest]) {
                largest = left;
            }
            if (right < n && arr[right] > arr[largest]) {
                largest = right;
            }
            
            if (largest == current) {
                break;
            }
            
            int temp = arr[current];
            arr[current] = arr[largest];
            arr[largest] = temp;
            current = largest;
        }
    }
    
    // 逐个取出堆顶元素
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // 迭代堆化
        int current = 0;
        while (1) {
            int largest = current;
            int left = 2 * current + 1;
            int right = 2 * current + 2;
            
            if (left < i && arr[left] > arr[largest]) {
                largest = left;
            }
            if (right < i && arr[right] > arr[largest]) {
                largest = right;
            }
            
            if (largest == current) {
                break;
            }
            
            int temp2 = arr[current];
            arr[current] = arr[largest];
            arr[largest] = temp2;
            current = largest;
        }
    }
    
    printArray(arr, n, "排序后数组");
}

/**
 * 堆排序 - 自底向上版本
 * 
 * 算法思路：
 * 从底部开始构建堆，逐步向上调整
 * 使用不同的堆化策略，提高构建效率
 * 
 * 优化效果：
 * - 更高效的堆构建过程
 * - 减少不必要的比较
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
void heapSort4(int arr[], int n) {
    printf("heapSort4 bottom-up:\n");
    
    // 自底向上构建最大堆
    for (int i = 1; i < n; i++) {
        int child = i;
        int parent = (child - 1) / 2;
        
        // 向上调整
        while (parent >= 0 && arr[parent] < arr[child]) {
            int temp = arr[parent];
            arr[parent] = arr[child];
            arr[child] = temp;
            child = parent;
            parent = (child - 1) / 2;
            if (child == 0) {
                break;
            }
        }
    }
    
    // 逐个取出堆顶元素
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // 向下调整
        int parent = 0;
        int child = 1;
        
        while (child < i) {
            // 选择较大的子节点
            if (child + 1 < i && arr[child] < arr[child + 1]) {
                child++;
            }
            
            if (arr[parent] >= arr[child]) {
                break;
            }
            
            int temp2 = arr[parent];
            arr[parent] = arr[child];
            arr[child] = temp2;
            parent = child;
            child = 2 * parent + 1;
        }
    }
    
    printArray(arr, n, "排序后数组");
}

// 根据完全二叉树结构性质，父子节点与数组下标的关系
int getParent(int i) { return (i - 1) / 2; }
int getLeft(int i) { return 2 * i + 1; }
int getRight(int i) { return 2 * i + 2; }

/**
 * 始终保持大顶堆特性, 构建大顶堆的非递归写法
 */
void maxHeapifyNonRecursive(int array[], int idx, int size) {
    int current = array[idx];
    int idxMut = idx;
    int child = getLeft(idxMut);
    // 从当前位置的左节点开始遍历
    while (child < size) {
        printf("current= %d  idx= %d  child= %d  size= %d\n", current, idxMut, child, size);
        // 如果左节点小于右节点且小于总长度，则指向右节点
        if (child + 1 < size && array[child] < array[child + 1]) {
            child++;
        }
        if (array[child] > current) {
            // 如果子节点大于父节点，将子节点的值赋给父节点
            array[idxMut] = array[child];
            // 当前节点指向该子节点，继续循环
            idxMut = child;
        } else {
            // 子节点小于父节点则跳出循环
            break;
        }
        // 遍历子树父节点
        child = getLeft(idxMut);
    }
    // 赋值为父节点的值
    array[idxMut] = current;
}

/**
 * 堆排序 - 非递归版本
 * 
 * 算法思路：
 * 使用非递归方式实现堆化，提供父子节点计算函数
 * 通过循环调整堆结构，避免递归调用
 * 
 * 优化效果：
 * - 避免递归调用栈开销
 * - 更直观的父子节点关系计算
 * - 详细的调试日志输出
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 堆化过程可能改变相等元素的相对位置
 */
void heapSort5(int arr[], int n) {
    printf("heapSort5 non-recursive:\n");
    
    // 最底层的父节点
    int parent = getParent(n) - 1;
    // 最底层的子节点
    int child = n - 1;
    
    // 从最后的父节点开始遍历，构建大顶堆，并把最大数冒出到堆顶
    while (parent >= 0) {
        maxHeapifyNonRecursive(arr, parent, n);
        printf("parent sort: %d ", parent);
        printArray(arr, n, "");
        parent--;
    }
    
    printf("child start: parent=%d  child=%d\n", parent, child);
    // 自下向上逐个将子节点数与最顶端的数进行交换，并保持最大堆特性
    while (child > 0) {
        // 将顶端的父节点与当前子节点互换
        int temp = arr[0];
        arr[0] = arr[child];
        arr[child] = temp;
        // 自最底层往上遍历构建大顶堆，已经排好序的不再交换
        maxHeapifyNonRecursive(arr, 0, child);
        printf("child sort: %d ", child);
        printArray(arr, n, "");
        child--;
    }
    
    printArray(arr, n, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：最大堆版本
    performanceTest(heapSort1, testData, testDataSize, "最大堆版本");

    // 测试2：最小堆版本
    performanceTest(heapSort2, testData, testDataSize, "最小堆版本");

    // 测试3：迭代版本
    performanceTest(heapSort3, testData, testDataSize, "迭代版本");

    // 测试4：自底向上版本
    performanceTest(heapSort4, testData, testDataSize, "自底向上版本");

    // 测试5：非递归版本
    performanceTest(heapSort5, testData, testDataSize, "非递归版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 最大堆版本：经典实现，升序排序\n");
    printf("2. 最小堆版本：反向思维，直观易懂\n");
    printf("3. 迭代版本：避免递归，性能优化\n");
    printf("4. 自底向上版本：高效构建，减少比较\n");
    printf("5. 非递归版本：非递归堆化，父子节点计算函数\n");

    return 0;
}

/*
打印结果
jarry@Mac heapsort % gcc heap_sort.c -o heap_sort && ./heap_sort
最大堆版本: [7, 11, 9, 10, 12, 13, 8]
heapSort1 max-heap:
oringal array:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

父节点步骤
1. maxHeapify: idx= 2 left= 5 right= 6 max= 5 size= 7

              7(0)
          /         \
        11(1)        13(2)
       /    \      /     \
   10(3)  12(4)  9(5)  8(6)

3. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7

              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

5. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7

              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

6.1 maxHeapify: idx= 5 left= 11 right= 12 max= 5 size= 7

              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
7. swap, child = 6:

              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.1 maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 6
: [12, 8, 9, 10, 11, 7]
7.1 maxHeapify: idx= 4 left= 9 right= 10 max= 4 size= 6
: [12, 11, 9, 10, 8, 7]
8. swap, child = 5:

              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.1 maxHeapify: idx= 1 left= 3 right= 4 max= 3 size= 5
: [11, 7, 9, 10, 8]
8.1 maxHeapify: idx= 3 left= 7 right= 8 max= 3 size= 5
: [11, 10, 9, 7, 8]
9. swap, child = 4:

              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

9.1 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 4
: [10, 8, 9, 7]
10. swap, child = 3:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

10.1 maxHeapify: idx= 2 left= 5 right= 6 max= 2 size= 3
: [9, 8, 7]
11. swap, child = 2:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11.1 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 2
: [8, 7]
12. swap, child = 1:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

排序后数组: [7, 8, 9, 10, 11, 12, 13]
最大堆版本: 0.159ms
排序后数组: [7, 8, 9, 10, 11, 12, 13]

最小堆版本: [7, 11, 9, 10, 12, 13, 8]
heapSort2 min-heap:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
最小堆版本: 0.007ms
排序后数组: [7, 8, 9, 10, 11, 12, 13]

迭代版本: [7, 11, 9, 10, 12, 13, 8]
heapSort3 iterative:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.005ms
排序后数组: [7, 8, 9, 10, 11, 12, 13]

自底向上版本: [7, 11, 9, 10, 12, 13, 8]
heapSort4 bottom-up:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.003ms
排序后数组: [7, 8, 9, 10, 11, 12, 13]

非递归版本: [7, 11, 9, 10, 12, 13, 8]
heapSort5 non-recursive:
current= 9  idx= 2  child= 5  size= 7
parent sort: 2 : [7, 11, 13, 10, 12, 9, 8]
current= 11  idx= 1  child= 3  size= 7
parent sort: 1 : [7, 12, 13, 10, 11, 9, 8]
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
parent sort: 0 : [13, 12, 9, 10, 11, 7, 8]
child start: parent=-1  child=6
current= 8  idx= 0  child= 1  size= 6
current= 8  idx= 1  child= 3  size= 6
child sort: 6 : [12, 11, 9, 10, 8, 7, 13]
current= 7  idx= 0  child= 1  size= 5
current= 7  idx= 1  child= 3  size= 5
child sort: 5 : [11, 10, 9, 7, 8, 12, 13]
current= 8  idx= 0  child= 1  size= 4
current= 8  idx= 1  child= 3  size= 4
child sort: 4 : [10, 8, 9, 7, 11, 12, 13]
current= 7  idx= 0  child= 1  size= 3
child sort: 3 : [9, 8, 7, 10, 11, 12, 13]
current= 7  idx= 0  child= 1  size= 2
child sort: 2 : [8, 7, 9, 10, 11, 12, 13]
child sort: 1 : [7, 8, 9, 10, 11, 12, 13]
排序后数组: [7, 8, 9, 10, 11, 12, 13]
非递归版本: 0.050ms
排序后数组: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 最大堆版本：经典实现，升序排序
2. 最小堆版本：反向思维，直观易懂
3. 迭代版本：避免递归，性能优化
4. 自底向上版本：高效构建，减少比较
5. 非递归版本：非递归堆化，父子节点计算函数
*/
