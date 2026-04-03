/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 快速排序算法实现集合
 * 
 * 本文件包含7种不同的快速排序实现，涵盖了快速排序的主要算法变体：
 * - 不同的基准选择策略（中间、左侧、最后、第一个元素）
 * - 不同的扫描方式（相向扫描、单向扫描、双向扫描、三路分区）
 * - 不同的实现方式（递归、迭代、栈模拟）
 * - 不同的分区策略（Hoare分区、Lomuto分区、三路分区）
 * 
 * @author jarryli@gmail.com
 * @version 2.0
 * @date 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/**
 * 交换两个整数的值
 * @param a 第一个整数的指针
 * @param b 第二个整数的指针
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * 打印数组指定范围内的元素
 * @param arr 目标数组
 * @param start 起始索引（包含）
 * @param end 结束索引（包含）
 */
void printArrayRange(int arr[], int start, int end)
{
    printf("[");
    for (int i = start; i <= end; i++) {
        printf("%d", arr[i]);
        if (i < end) {
            printf(", ");
        }
    }
    printf("]");
}

/**
 * 打印整个数组的内容
 * @param arr 目标数组
 * @param size 数组大小
 * @param label 打印标签
 */
void printArray(int arr[], int size, const char *label)
{
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
 * 快速排序1 - 标准递归版本
 * 
 * 算法特点：
 * - 使用中间元素作为基准，避免最坏情况
 * - 双向扫描：左右指针相向移动，减少交换次数
 * - 原地排序：不需要额外空间
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
/*
quick_sort1 递归步骤:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([])
  [7]
 */
void *quickSort1(int arr[], int low, int high)
{
    // 步骤1：初始化指针和基准
    int i = low > 0 ? low : 0;  // 处理边界情况
    int j = high;
    int midIndex = (i + j) / 2;
    int pivot = arr[midIndex];

    // 步骤2：分区过程 - 双向扫描
    while (i <= j) {
        // 步骤2.1：左指针向右扫描，找到大于基准的元素
        while (arr[i] < pivot) {
            i++;
        }
        
        // 步骤2.2：右指针向左扫描，找到小于基准的元素
        while (arr[j] > pivot) {
            j--;
        }

        printf("\r\n  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);

        // 步骤2.3：交换元素并缩小范围
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            // 关键点：缩小搜索范围
            i++;
            j--;
        }
    }
    
    // 步骤3：递归处理左右子数组
    if (low < j) {
        printf("\r\n  low < j:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
        quickSort1(arr, low, j);
    }
    if (i < high) {
        printf("\r\n  i < high:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
        quickSort1(arr, i, high);
    }

    return arr;
}

/**
 * 快速排序2 - 递归分区交换版本
 * 
 * 算法特点：
 * - 使用左侧第一个元素作为基准
 * - 单向扫描：从左向右一次性扫描
 * - Lomuto分区方案的变体
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
int partition(int *arr, int left, int right)
{
    // 步骤1：初始化基准和分区指针
    int pivotIndex = left;           // 基准位置
    int partitionIndex = pivotIndex + 1;  // 分区指针
    
    // 步骤2：遍历数组进行分区
    for (int i = partitionIndex; i <= right; i++) {
        // 步骤2.1：将小于基准的元素交换到左侧
        if (arr[i] < arr[pivotIndex]) {
            swap(&arr[i], &arr[partitionIndex]);
            partitionIndex++;  // 扩展小于基准的区域
        }
    }
    
    // 步骤3：将基准元素放到正确位置
    swap(&arr[pivotIndex], &arr[partitionIndex - 1]);
    
    // 调试输出
    printf("\r\n");
    printArrayRange(arr, left, partitionIndex);
    printf(" partitionIndex=%d, arr[partitionIndex]=%d ", partitionIndex, arr[partitionIndex]);
    printArrayRange(arr, partitionIndex, right);
    
    return partitionIndex - 1;
}

int *quickSort2(int *arr, int left, int right)
{
    // 步骤1：递归终止条件检查
    if (left < right) {
        // 步骤2：分区并获取基准位置
        int pivot = partition(arr, left, right);
        
        // 步骤3：递归处理左右子数组
        quickSort2(arr, left, pivot - 1);
        quickSort2(arr, pivot + 1, right);
    }
    return arr;
}

// ==================== 栈数据结构实现 ====================

/** 栈结构 - 用于非递归快速排序 */
typedef struct stack {
    int top;
    int *data;
    int size;
} stack;

/** 栈指针类型 */
typedef struct stack *Stack;

/** 创建栈 */
Stack stack_create(int max_size)
{
    Stack s = (Stack)malloc(sizeof(struct stack));
    s->data = (int *)malloc(max_size * sizeof(int));
    s->top = -1;
    s->size = max_size;
    return s;
}

/** 判断栈是否为空 */
bool stack_is_empty(Stack s)
{
    return s->top == -1;
}

/** 入栈 */
void stack_push(Stack s, int value)
{
    s->top++;
    s->data[s->top] = value;
}

/** 出栈 */
int stack_pop(Stack s)
{
    return s->data[s->top--];
}

/** 判断栈是否已满 */
bool stack_is_full(Stack s)
{
    return s->top == s->size - 1;
}


int stack_len(Stack s)
{
    return s->top;
}

/**
 * 快排方式3，非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
 *
 * 算法思路：
 * 使用栈来模拟递归调用，避免递归深度过大
 * 与标准递归版本相同的分区逻辑，但使用迭代而非递归
 *
 * 步骤说明：
 * 1. 创建栈：创建一个栈来存储待处理的子数组范围
 * 2. 初始化栈：将初始范围（low, high）压入栈中
 * 3. 循环处理：当栈不为空时，弹出范围进行分区处理
 * 4. 分区操作：对当前范围进行标准的快速排序分区
 * 5. 子范围入栈：将分区后的子范围压入栈中继续处理
 *
 * 关键点：
 * - 栈模拟：使用栈代替递归调用栈，避免递归深度过大
 * - 迭代处理：通过循环不断处理栈中的范围，直到栈为空
 * - 内存管理：需要手动创建和释放栈内存
 * - 分区逻辑：与标准递归版本完全相同的分区算法
 *
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 显式栈空间
 * 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 */
void *quickSort3(int arr[], int low, int high)
{
    // 步骤1：创建栈
    // 关键点：栈大小为high - low，足够存储所有可能的子范围
    Stack stack = stack_create(high - low);
    printf("\nhigh - low = %d\n", high - low);
    int i, j, midIndex, pivot, tmp;

    // 步骤2：初始化栈
    // 关键点：与标准递归版相同，只是将递归改为遍历栈的方式
    // 关键点：先将左右各取一个入栈，注意顺序：先low后high
    stack_push(stack, low);
    stack_push(stack, high);

    // 步骤3：循环处理栈中的范围
    // 关键点：当栈内还有数据时继续处理
    while (!stack_is_empty(stack))
    {
        // 步骤3.1：出栈获取当前范围
        // 关键点：如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
        // 关键点：注意出栈顺序，先high后low，与入栈顺序相反
        j = high = stack_pop(stack);
        i = low = stack_pop(stack);

        // 步骤3.2：初始化分区参数
        // 关键点：与标准递归版相同的基准选择和分区逻辑
        midIndex = (i + j) / 2;
        pivot = arr[midIndex];

        // 步骤3.3：分区过程
        // 关键点：与标准递归版相同的分区逻辑
        while (i <= j)
        {
            // 步骤3.3.1：左指针扫描
            // 关键点：找到大于基准的元素
            while (arr[i] < pivot)
            {
                printf("\r\narr[i] < pivot: i=%d, j=%d, arr[i]=%d, arr[j]=%d, pivot=%d", i, j, arr[i], arr[j], pivot);
                i++;
            }
            // 步骤3.3.2：右指针扫描
            // 关键点：找到小于基准的元素
            while (arr[j] > pivot)
            {
                printf("\r\narr[i] > pivot: i=%d, j=%d, arr[i]=%d, arr[j]=%d, pivot=%d", i, j, arr[i], arr[j], pivot);
                j--;
            }

            // 步骤3.3.3：交换元素
            // 关键点：当左指针小于等于右指针时交换
            if (i <= j)
            {
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
                i++;
                j--;
            }
        }

        // 步骤3.4：将子范围入栈
        // 关键点：与递归版不同，这里添加到栈中，以便继续循环
        if (low < j)
        {
            printf("\r\n  low < j:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
            // 关键点：将左子范围压入栈，注意顺序：先low后high
            stack_push(stack, low);
            stack_push(stack, j);
        }
        if (i < high)
        {
            printf("\r\n  i < high:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
            // 关键点：将右子范围压入栈，注意顺序：先low后high
            stack_push(stack, i);
            stack_push(stack, high);
        }
    }

    // 步骤4：释放栈内存
    // 关键点：手动释放栈内存，避免内存泄漏
    free(stack);
    return arr;
}

/**
 * 快排方式4，迭代版本。使用栈来模拟递归调用，使用Lomuto分区。
 * 
 * 算法思路：
 * 使用栈来模拟递归调用，避免递归深度过大
 * 使用最后一个元素作为基准（Lomuto分区）
 * 
 * 步骤说明：
 * 1. 创建栈：创建一个栈来存储待处理的子数组范围
 * 2. 初始化栈：将初始范围（0, size-1）压入栈中
 * 3. 循环处理：当栈不为空时，弹出范围进行分区处理
 * 4. 分区操作：对当前范围进行Lomuto分区
 * 5. 子范围入栈：将分区后的子范围压入栈中继续处理
 * 
 * 关键点：
 * - 栈模拟：使用栈代替递归调用栈，避免递归深度过大
 * - Lomuto分区：使用最后一个元素作为基准
 * - 迭代处理：通过循环不断处理栈中的范围，直到栈为空
 * - 内存管理：需要手动创建和释放栈内存
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 显式栈空间
 * 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 */
int partitionLomuto(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low - 1;     // 小于基准的元素的边界
    
    // 遍历数组，将小于基准的元素移到左边
    for (int j = low; j < high; j++) {
        // 关键点：找到小于基准的元素
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // 将基准元素放到正确位置
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void *quickSort4(int arr[], int size)
{
    printf("quickSort4 迭代版本:\n");
    printArrayRange(arr, 0, size);
    
    // 步骤1：创建栈
    // 关键点：栈大小为size，足够存储所有可能的子范围
    Stack stack = stack_create(size);
    
    // 步骤2：初始化栈
    // 关键点：将初始范围压入栈中，注意顺序：先low后high
    stack_push(stack, 0);
    stack_push(stack, size - 1);
    
    // 步骤3：循环处理栈中的范围
    // 关键点：当栈不为空时继续处理
    while (!stack_is_empty(stack))
    {
        // 步骤3.1：出栈获取当前范围
        // 关键点：注意出栈顺序，先high后low，与入栈顺序相反
        int high = stack_pop(stack);
        int low = stack_pop(stack);
        
        // 步骤3.2：分区操作
        // 关键点：使用Lomuto分区方案
        int pi = partitionLomuto(arr, low, high);
        
        // 步骤3.3：将左半部分入栈
        // 关键点：当左半部分有多个元素时入栈
        if (pi - 1 > low)
        {
            stack_push(stack, low);
            stack_push(stack, pi - 1);
        }
        
        // 步骤3.4：将右半部分入栈
        // 关键点：当右半部分有多个元素时入栈
        if (pi + 1 < high)
        {
            stack_push(stack, pi + 1);
            stack_push(stack, high);
        }
    }
    
    // 步骤4：释放栈内存
    // 关键点：手动释放栈内存，避免内存泄漏
    free(stack);
    return arr;
}

/**
 * 快速排序5 - Lomuto分区递归版本
 * 
 * 算法特点：
 * - 使用最后一个元素作为基准
 * - 单向扫描：从左向右一次性扫描
 * - Lomuto分区：经典的分区方案
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void *quickSort5(int arr[], int size)
{
    printf("\nquickSort5 Lomuto分区递归版本:\n");
    printArrayRange(arr, 0, size);
    
    // 步骤1：递归终止条件检查
    if (size <= 1) {
        return arr;
    }
    
    // 步骤2：分区并获取基准位置
    int pi = partitionLomuto(arr, 0, size - 1);
    
    // 步骤3：递归排序左右子数组
    if (pi > 0) quickSort5(arr, pi);
    if (pi < size - 1) quickSort5(arr + pi + 1, size - pi - 1);
    
    return arr;
}

/**
 * 快速排序6 - Hoare分区递归版本
 * 
 * 算法特点：
 * - 使用第一个元素作为基准
 * - 双向扫描：左右指针同时向中间移动
 * - Hoare分区：经典的分区方案
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void *quickSort6(int arr[], int size)
{
    printf("\nquickSort6 Hoare分区递归版本:\n");
    printArrayRange(arr, 0, size);
    
    // 步骤1：递归终止条件检查
    if (size <= 1) {
        return arr;
    }
    
    // 步骤2：初始化基准和双向指针
    int pivot = arr[0];     // 第一个元素作为基准
    int i = 1;             // 左指针
    int j = size - 1;       // 右指针
    
    // 步骤3：双向分区
    while (i <= j) {
        // 步骤3.1：左指针扫描，找到大于基准的元素
        while (i <= j && arr[i] <= pivot) {
            i++;
        }
        
        // 步骤3.2：右指针扫描，找到小于基准的元素
        while (i <= j && arr[j] > pivot) {
            j--;
        }
        
        // 步骤3.3：交换元素
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    
    // 步骤4：调整基准位置
    swap(&arr[0], &arr[j]);
    
    // 步骤5：递归处理左右子数组
    quickSort6(arr, j);
    quickSort6(arr + j + 1, size - j - 1);
    
    return arr;
}

/**
 * 快速排序7 - 三路分区递归版本
 * 
 * 算法特点：
 * - 使用第一个元素作为基准
 * - 三路分区：处理重复元素，提高效率
 * - 递归优化：减少递归调用次数
 * 
 * 时间复杂度：平均O(n log n)，最坏O(n²)
 * 空间复杂度：O(log n) - 递归调用栈
 * 稳定性：不稳定
 */
void *quickSort7(int arr[], int size)
{
    printf("\nquickSort7 三路分区递归版本:\n");
    printArrayRange(arr, 0, size);
    
    // 步骤1：递归终止条件检查
    if (size <= 1) {
        return arr;
    }
    
    // 步骤2：初始化基准和三路指针
    int pivot = arr[0];      // 第一个元素作为基准
    int lt = 0;              // 小于基准的右边界
    int gt = size - 1;       // 大于基准的左边界
    int i = 1;               // 当前遍历指针
    
    // 步骤3：三路分区
    while (i <= gt) {
        if (arr[i] < pivot) {
            // 步骤3.1：小于基准，交换到左边
            swap(&arr[lt], &arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            // 步骤3.2：大于基准，交换到右边
            swap(&arr[i], &arr[gt]);
            gt--;
        } else {
            // 步骤3.3：等于基准，直接跳过
            i++;
        }
    }
    
    // 步骤4：递归处理
    quickSort7(arr, lt);
    quickSort7(arr + gt + 1, size - gt - 1);
    
    return arr;
}

/**
 * 性能测试辅助函数
 */
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char *name)
{
    // 创建数组副本，避免修改原数组
    int *testArr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        testArr[i] = arr[i];
    }

    printf("%s原始数组: ", name);
    printArray(testArr, size, "");

    // 开始计时
    clock_t start = clock();
    sortFunc(testArr, size);
    clock_t end = clock();

    double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.3fms\n", name, duration);
    printf("%s排序结果: ", name);
    printArray(testArr, size, "");
    printf("\n"); // 空行分隔

    free(testArr);
}

/**
 * 快速排序包装函数
 */
void quickSort1Wrapper(int arr[], int size)
{
    quickSort1(arr, 0, size - 1);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

void quickSort2Wrapper(int arr[], int size)
{
    quickSort2(arr, 0, size - 1);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

void quickSort3Wrapper(int arr[], int size)
{
    quickSort3(arr, 0, size - 1);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

void quickSort4Wrapper(int arr[], int size)
{
    quickSort4(arr, size);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

void quickSort5Wrapper(int arr[], int size)
{
    quickSort5(arr, size);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

void quickSort6Wrapper(int arr[], int size)
{
    quickSort6(arr, size);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

void quickSort7Wrapper(int arr[], int size)
{
    quickSort7(arr, size);
    printf("排序后数组: ");
    printArray(arr, size, "");
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
int testData[] = {7, 11, 9, 10, 12, 13, 8};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

// ==================== 算法测试和性能对比 ====================

int main()
{
    // 测试1：标准递归版本
    performanceTest(quickSort1Wrapper, testData, testDataSize, "标准递归版本");

    // 测试2：递归分区交换版本
    performanceTest(quickSort2Wrapper, testData, testDataSize, "递归分区交换版本");

    // 测试3：非递归版本
    performanceTest(quickSort3Wrapper, testData, testDataSize, "非递归版本");

    // 测试4：迭代版本
    performanceTest(quickSort4Wrapper, testData, testDataSize, "迭代版本");

    // 测试5：Lomuto分区递归版本
    performanceTest(quickSort5Wrapper, testData, testDataSize, "Lomuto分区递归版本");

    // 测试6：Hoare分区递归版本
    performanceTest(quickSort6Wrapper, testData, testDataSize, "Hoare分区递归版本");

    // 测试7：三路分区递归版本
    performanceTest(quickSort7Wrapper, testData, testDataSize, "三路分区递归版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 标准递归版本：中间基准，相向扫描\n");
    printf("2. 递归分区交换版本：左侧基准，单向扫描\n");
    printf("3. 非递归版本：栈模拟，避免递归\n");
    printf("4. 迭代版本：Lomuto分区，栈模拟\n");
    printf("5. Lomuto分区递归版本：最后基准，单向扫描\n");
    printf("6. Hoare分区递归版本：第一个基准，双向扫描\n");
    printf("7. 三路分区递归版本：第一个基准，三路分区\n");

    return 0;
}

/*
jarry@Mac quicksort % gcc quick_sort.c -o quick_sort && ./quick_sort
标准递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

  low=0, high=6, i=1, j=6, midIndex=3, pivot=10
  low=0, high=6, i=3, j=3, midIndex=3, pivot=10
  low < j:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  low=0, high=2, i=1, j=1, midIndex=1, pivot=8
  i < high:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  low=4, high=6, i=5, j=6, midIndex=5, pivot=13
  low < j:recursion:  low=4, high=6, i=6, j=5, midIndex=5, pivot=13
  low=4, high=5, i=4, j=5, midIndex=4, pivot=12排序后数组: : [7, 8, 9, 10, 11, 12, 13]
标准递归版本: 0.016ms
标准递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

递归分区交换版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

[7, 11] partitionIndex=1, arr[partitionIndex]=11 [11, 9, 10, 12, 13, 8]
[8, 9, 10, 11, 13] partitionIndex=5, arr[partitionIndex]=13 [13, 12]
[8, 9] partitionIndex=2, arr[partitionIndex]=9 [9, 10]
[9, 10] partitionIndex=3, arr[partitionIndex]=10 [10]
[12, 13, 0] partitionIndex=7, arr[partitionIndex]=0 []排序后数组: : [7, 8, 9, 10, 11, 12, 13]
递归分区交换版本: 0.014ms
递归分区交换版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

非递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

high - low = 6

arr[i] < pivot: i=0, j=6, arr[i]=7, arr[j]=8, pivot=10
arr[i] < pivot: i=2, j=5, arr[i]=9, arr[j]=13, pivot=10
arr[i] > pivot: i=3, j=5, arr[i]=10, arr[j]=13, pivot=10
arr[i] > pivot: i=3, j=4, arr[i]=10, arr[j]=12, pivot=10
  low < j:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  i < high:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=4, j=6, arr[i]=12, arr[j]=11, pivot=13
  low < j:recursion:  low=4, high=6, i=6, j=5, midIndex=5, pivot=13
arr[i] < pivot: i=0, j=2, arr[i]=7, arr[j]=9, pivot=8
arr[i] > pivot: i=1, j=2, arr[i]=8, arr[j]=9, pivot=8排序后数组: : [7, 8, 9, 10, 11, 12, 13]
非递归版本: 0.026ms
非递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
quickSort4 迭代版本:
[7, 11, 9, 10, 12, 13, 8, 0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.006ms
迭代版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

Lomuto分区递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort5 Lomuto分区递归版本:
[7, 11, 9, 10, 12, 13, 8, 0]
quickSort5 Lomuto分区递归版本:
[7, 8]
quickSort5 Lomuto分区递归版本:
[9, 10, 12, 13, 11, 0]
quickSort5 Lomuto分区递归版本:
[9, 10, 11]
quickSort5 Lomuto分区递归版本:
[9, 10]
quickSort5 Lomuto分区递归版本:
[13, 12, 0]
quickSort5 Lomuto分区递归版本:
[13, 0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
Lomuto分区递归版本: 0.017ms
Lomuto分区递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

Hoare分区递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort6 Hoare分区递归版本:
[7, 11, 9, 10, 12, 13, 8, 0]
quickSort6 Hoare分区递归版本:
[7]
quickSort6 Hoare分区递归版本:
[11, 9, 10, 12, 13, 8, 0]
quickSort6 Hoare分区递归版本:
[8, 9, 10, 11]
quickSort6 Hoare分区递归版本:
[8]
quickSort6 Hoare分区递归版本:
[9, 10, 11]
quickSort6 Hoare分区递归版本:
[9]
quickSort6 Hoare分区递归版本:
[10, 11]
quickSort6 Hoare分区递归版本:
[13, 12, 0]
quickSort6 Hoare分区递归版本:
[12, 13]
quickSort6 Hoare分区递归版本:
[0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
Hoare分区递归版本: 0.025ms
Hoare分区递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

三路分区递归版本原始数组: : [7, 11, 9, 10, 12, 13, 8]

quickSort7 三路分区递归版本:
[7, 11, 9, 10, 12, 13, 8, 0]
quickSort7 三路分区递归版本:
[7]
quickSort7 三路分区递归版本:
[9, 10, 12, 13, 8, 11, 0]
quickSort7 三路分区递归版本:
[8, 9]
quickSort7 三路分区递归版本:
[13, 12, 11, 10, 0]
quickSort7 三路分区递归版本:
[12, 11, 10, 13]
quickSort7 三路分区递归版本:
[11, 10, 12]
quickSort7 三路分区递归版本:
[10, 11]
quickSort7 三路分区递归版本:
[12]
quickSort7 三路分区递归版本:
[13]
quickSort7 三路分区递归版本:
[0]排序后数组: : [7, 8, 9, 10, 11, 12, 13]
三路分区递归版本: 0.025ms
三路分区递归版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 标准递归版本：中间基准，相向扫描
2. 递归分区交换版本：左侧基准，单向扫描
3. 非递归版本：栈模拟，避免递归
4. 迭代版本：Lomuto分区，栈模拟
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/
