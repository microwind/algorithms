/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供5种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * 打印数组内容的辅助函数
 */
void printArray(int arr[], int size, const char *label)
{
    printf("%s: [", label);
    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
            printf(", ");
        printf("%d", arr[i]);
    }
    printf("]\n");
}

/**
 * 性能测试辅助函数
 */
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char *name)
{
    // 创建数组副本，避免修改原数组
    int *testArr = (int *)malloc(size * sizeof(int));
    memcpy(testArr, arr, size * sizeof(int));

    printArray(testArr, size, name);

    // 开始计时
    clock_t startTime = clock();
    sortFunc(testArr, size);
    clock_t endTime = clock();

    double duration = ((double)(endTime - startTime)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.3fms\n", name, duration);
    printArray(testArr, size, name);
    printf("\n"); // 空行分隔

    free(testArr);
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
int testData[] = {33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

// 测试负数数据
int negativeTestData[] = {170, 45, 75, -90, -802, 24, 2, 66, -5, 0};
int negativeTestDataSize = sizeof(negativeTestData) / sizeof(negativeTestData[0]);

/**
 * 获取数字的指定位数
 */
int getDigit(int num, int exp)
{
    return abs(num) / exp % 10;
}

/**
 * 计数排序，根据基数按位进行计数
 *
 * ## 算法特点
 * - 按位进行计数排序，支持负数处理
 * - 使用最小值偏移处理负数
 * - 基于计数排序的稳定特性
 * - 适用于基数排序的按位处理
 *
 * ## 复杂度分析
 * - 时间复杂度：O(n + k)，k为基数范围（通常为10）
 * - 空间复杂度：O(n + k) - 需要计数数组和输出数组
 * - 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param len - 数组长度
 * @param exponent - 当前处理的位数基数（1, 10, 100, ...）
 * @return void 无返回值，直接修改原数组
 */
void countingSort(int arr[], int len, int exponent)
{
    // 第一步：初始化变量和数组，按10个桶大小，0-9的个位数
    int sorted_list[len];
    int range = 10;
    int count_list[range];

    // 第二步：找出最小值
    // 关键点：处理负数情况，需要找到最小值进行偏移
    int min_value = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] < min_value)
            min_value = arr[i];
    }

    // 第三步：初始化计数数组
    // 关键点：memset将计数数组清零
    memset(count_list, 0, range * sizeof(int));

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - min_value来处理负数，确保索引为正数
    for (int i = 0; i < len; i++)
    {
        int item = arr[i] - min_value;
        int idx = (item / exponent) % range;
        count_list[idx]++;
    }

    // 第五步：构建计数排序，当前位置加上左侧位置
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for (int i = 1; i < range; i++)
    {
        count_list[i] += count_list[i - 1];
    }

    // 第六步：构建输出数组，根据计数数组按顺序取得排序内容
    // 关键点：从后向前遍历，保持排序的稳定性
    for (int i = len - 1; i >= 0; i--)
    {
        int item = arr[i] - min_value;
        int idx = (item / exponent) % range;
        // 关键点：根据位置重排结果，减去min值还原数据
        sorted_list[count_list[idx] - 1] = arr[i];
        count_list[idx]--;
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for (int i = 0; i < len; i++)
    {
        arr[i] = sorted_list[i];
    }
}

/**
 * 基数排序，从低位到高位LSD版，基于计数排序
 *
 * ## 算法特点
 * - 从低位到高位进行排序（LSD - Least Significant Digit）
 * - 基于计数排序实现，支持负数处理
 * - 稳定排序：保持相等元素的相对位置
 * - 适用于整数排序，特别是大范围数字
 *
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k) - 需要额外的计数和输出数组
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param len - 数组长度
 * @return void 无返回值，直接修改原数组
 */
void radix_sort1(int arr[], int len)
{
    // 第一步：找出最大值
    // 关键点：确定排序的位数范围
    int max_value = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max_value)
            max_value = arr[i];
    }

    // 第二步：找出最小值
    // 关键点：处理负数情况，需要找到最小值进行偏移
    int min_value = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] < min_value)
            min_value = arr[i];
    }

    // 第三步：根据最大值，逐个按进位(基数)来应用排序
    // 关键点：exponent即数位基数，按个十百千递增
    for (int exponent = 1; (max_value - min_value) / exponent > 0; exponent *= 10)
    {
        countingSort(arr, len, exponent);
    }
}

/**
 * MSD递归排序函数
 */
void msdSort(int arr[], int left, int right, int exp)
{
    // 第一步：递归终止条件检查
    // 关键点：范围无效或位数不足时返回
    if (left >= right || exp < 1)
    {
        return;
    }

    // 第二步：创建桶
    // 关键点：创建10个桶，对应0-9的数字
    int *buckets[10];
    int bucketSizes[10] = {0};

    // 第三步：分配到桶中
    // 关键点：根据当前位数将元素分配到对应桶中
    for (int i = left; i <= right; i++)
    {
        int digit = getDigit(arr[i], exp);
        if (bucketSizes[digit] == 0)
        {
            buckets[digit] = (int *)malloc((right - left + 1) * sizeof(int));
        }
        buckets[digit][bucketSizes[digit]++] = arr[i];
    }

    // 第四步：重新排序并递归处理每个桶
    // 关键点：将桶中元素复制回原数组，并递归处理子数组
    int index = left;
    for (int i = 0; i < 10; i++)
    {
        if (bucketSizes[i] > 0)
        {
            // 步骤4.1：复制桶中元素回原数组
            // 关键点：按桶的顺序复制元素，保持稳定性
            for (int j = 0; j < bucketSizes[i]; j++)
            {
                arr[index++] = buckets[i][j];
            }

            // 步骤4.2：递归处理下一个位数
            // 关键点：递归处理当前桶的子数组
            msdSort(arr, left, index - 1, exp / 10);
            left = index;
        }
    }

    // 第五步：释放桶内存
    // 关键点：释放动态分配的桶内存，避免内存泄漏
    for (int i = 0; i < 10; i++)
    {
        if (bucketSizes[i] > 0)
        {
            free(buckets[i]);
        }
    }
}

/**
 * MSD基数排序版本
 *
 * ## 算法特点
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 使用递归处理子数组
 * - 桶排序实现，动态分配内存
 * - 适合处理字符串或变长数据
 *
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k) - 需要桶和计数数组
 * - 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param size - 数组大小
 * @return void 无返回值，直接修改原数组
 */
void radixSort2(int arr[], int size)
{
    printf("radixSort2 MSD:\n");

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (size == 0)
        return;

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    int exp = 1;
    while (max / exp > 0)
    {
        exp *= 10;
    }

    // 第四步：调用MSD递归排序
    // 关键点：从最高位开始递归排序
    msdSort(arr, 0, size - 1, exp / 10);

    // 第五步：输出排序结果
    printArray(arr, size, "排序后数组");
}

/**
 * 迭代MSD基数排序版本
 *
 * ## 算法特点
 * - 使用栈模拟递归，避免递归深度过大
 * - 从最高位开始排序（MSD - Most Significant Digit）
 * - 桶排序实现，动态分配内存
 * - 适合处理大数据集
 *
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数
 * - 空间复杂度：O(n + k + s) - s为栈空间
 * - 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param size - 数组大小
 * @return void 无返回值，直接修改原数组
 */
void radixSort3(int arr[], int size)
{
    printf("radixSort3 iterative MSD:\n");

    // 第一步：递归终止条件检查
    // 关键点：空数组直接返回
    if (size == 0)
        return;

    // 第二步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定最高位数
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    // 第三步：计算最高位对应的基数
    // 关键点：exp从1开始，不断乘以10直到超过最大值
    int exp = 1;
    while (max / exp > 0)
    {
        exp *= 10;
    }

    // 第四步：使用栈模拟递归
    // 关键点：定义栈结构体，存储左右边界和当前位数
    typedef struct
    {
        int left, right, exp;
    } StackItem;

    // 第五步：初始化栈
    // 关键点：创建栈数组，初始化栈顶指针
    StackItem stack[100];
    int top = -1;

    // 第六步：初始入栈
    // 关键点：将整个数组范围和最高位基数入栈
    stack[++top] = (StackItem){0, size - 1, exp / 10};

    // 第七步：循环处理栈中的范围
    // 关键点：栈不为空时继续处理，模拟递归调用过程
    while (top >= 0)
    {
        // 步骤7.1：从栈中取出待处理的范围
        // 关键点：后进先出，取出栈顶元素
        StackItem item = stack[top--];
        int left = item.left;
        int right = item.right;
        int currentExp = item.exp;

        // 步骤7.2：递归终止条件检查
        // 关键点：范围无效或位数不足时跳过
        if (left >= right || currentExp < 1)
        {
            continue;
        }

        // 步骤7.3：创建桶
        // 关键点：创建10个桶，对应0-9的数字
        int *buckets[10];
        int bucketSizes[10] = {0};

        // 步骤7.4：分配到桶中
        // 关键点：根据当前位数将元素分配到对应桶中
        for (int i = left; i <= right; i++)
        {
            int digit = getDigit(arr[i], currentExp);
            if (bucketSizes[digit] == 0)
            {
                buckets[digit] = (int *)malloc((right - left + 1) * sizeof(int));
            }
            buckets[digit][bucketSizes[digit]++] = arr[i];
        }

        // 步骤7.5：重新排序并将子问题入栈
        // 关键点：将桶中元素复制回原数组，并将子问题入栈
        int index = left;
        for (int i = 0; i < 10; i++)
        {
            if (bucketSizes[i] > 0)
            {
                // 步骤7.5.1：复制桶中元素回原数组
                // 关键点：按桶的顺序复制元素，保持稳定性
                for (int j = 0; j < bucketSizes[i]; j++)
                {
                    arr[index++] = buckets[i][j];
                }

                // 步骤7.5.2：将子问题入栈
                // 关键点：将子数组范围和下一位数入栈，逆序处理保持正确顺序
                stack[++top] = (StackItem){left, index - 1, currentExp / 10};
                left = index;
            }
        }

        // 步骤7.6：释放桶内存
        // 关键点：释放动态分配的桶内存，避免内存泄漏
        for (int i = 0; i < 10; i++)
        {
            if (bucketSizes[i] > 0)
            {
                free(buckets[i]);
            }
        }
    }

    // 第八步：输出排序结果
    printArray(arr, size, "排序后数组");
}

/**
 * 桶优化基数排序版本
 *
 * ## 算法特点
 * - 使用动态桶大小，优化内存使用
 * - 适合处理稀疏数据
 * - 减少不必要的内存分配
 * - 提高处理效率
 *
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为实际使用的基数范围
 * - 空间复杂度：O(n + k') - k'为实际使用的基数范围（≤k）
 * - 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param size - 数组大小
 * @return void 无返回值，直接修改原数组
 */
void radixSort4(int arr[], int size)
{
    printf("radixSort4 bucket optimized:\n");

    // 第一步：找到最大值以确定位数
    // 关键点：遍历数组找出最大值，用于确定处理位数
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    // 第二步：对每个位数进行计数排序
    // 关键点：从个位开始，逐位处理，直到最高位
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        // 步骤2.1：分配输出数组
        // 关键点：为当前位数的排序结果分配内存
        int *output = (int *)malloc(size * sizeof(int));

        // 步骤2.2：动态确定桶范围
        // 关键点：统计当前位数的最小和最大值，减少桶数量
        int minDigit = 9, maxDigit = 0;
        for (int i = 0; i < size; i++)
        {
            int digit = getDigit(arr[i], exp);
            if (digit < minDigit)
                minDigit = digit;
            if (digit > maxDigit)
                maxDigit = digit;
        }

        // 步骤2.3：创建动态大小的计数数组
        // 关键点：只创建实际需要的桶大小，优化内存使用
        int bucketSize = maxDigit - minDigit + 1;
        int *count = (int *)calloc(bucketSize, sizeof(int));

        // 步骤2.4：统计每个数字的出现次数
        // 关键点：使用偏移量处理，支持任意范围的数字
        for (int i = 0; i < size; i++)
        {
            int digit = getDigit(arr[i], exp);
            count[digit - minDigit]++;
        }

        // 步骤2.5：计算累计计数
        // 关键点：当前位置加上左侧位置，形成累积计数
        for (int i = 1; i < bucketSize; i++)
        {
            count[i] += count[i - 1];
        }

        // 步骤2.6：构建输出数组
        // 关键点：从后向前遍历，保持排序的稳定性
        for (int i = size - 1; i >= 0; i--)
        {
            int digit = getDigit(arr[i], exp);
            output[count[digit - minDigit] - 1] = arr[i];
            count[digit - minDigit]--;
        }

        // 步骤2.7：复制回原数组
        // 关键点：将排序结果复制回原数组，准备下一位处理
        for (int i = 0; i < size; i++)
        {
            arr[i] = output[i];
        }

        // 步骤2.8：释放内存
        // 关键点：释放动态分配的内存，避免内存泄漏
        free(count);
        free(output);
    }

    // 第三步：输出排序结果
    printArray(arr, size, "排序后数组");
}

/**
 * 递归基数排序辅助函数
 *
 * ## 算法特点
 * - 递归处理每一位的计数排序
 * - 从最低位开始递归到最高位
 * - 支持负数处理
 * - 使用计数排序作为基础
 *
 * @param arr - 待排序的数字数组
 * @param size - 数组大小
 * @param exponent - 当前处理的位数基数
 * @param min_value - 数组最小值，用于负数处理
 * @param max_value - 数组最大值，用于确定递归终止条件
 * @return void 无返回值，直接修改原数组
 */
void recursiveRadixSort(int arr[], int size, int exponent, int min_value, int max_value)
{
    // 第一步：递归终止条件检查
    // 关键点：当基数超过最大值时停止递归
    if ((max_value - min_value) / exponent == 0)
    {
        return;
    }

    // 第二步：初始化计数排序变量
    // 关键点：为当前位数的计数排序准备变量
    int range = 10;
    int count_list[range];
    int sorted_list[size];

    // 第三步：初始化计数数组
    // 关键点：memset将计数数组清零
    memset(count_list, 0, range * sizeof(int));

    // 第四步：根据数字所在位置进行计数
    // 关键点：使用arr[i] - min_value来处理负数，确保索引为正数
    for (int i = 0; i < size; i++)
    {
        int item = arr[i] - min_value;
        int idx = (item / exponent) % range;
        count_list[idx]++;
    }

    // 第五步：构建计数排序
    // 关键点：后面的位数为前面的累加之和，形成累积计数
    for (int i = 1; i < range; i++)
    {
        count_list[i] += count_list[i - 1];
    }

    // 第六步：构建输出数组
    // 关键点：从后向前遍历，保持排序的稳定性
    for (int i = size - 1; i >= 0; i--)
    {
        int item = arr[i] - min_value;
        int idx = (item / exponent) % range;
        sorted_list[count_list[idx] - 1] = arr[i];
        count_list[idx]--;
    }

    // 第七步：复制到数组重排原始数组
    // 关键点：将排序结果复制回原数组
    for (int i = 0; i < size; i++)
    {
        arr[i] = sorted_list[i];
    }

    // 第八步：递归处理下一位
    // 关键点：递归调用处理更高位数
    recursiveRadixSort(arr, size, exponent * 10, min_value, max_value);
}

/**
 * 递归基数排序版本
 *
 * ## 算法特点
 * - 使用递归处理每一位的排序
 * - 基于计数排序的LSD实现
 * - 支持负数处理
 * - 递归深度由数字位数决定
 *
 * ## 复杂度分析
 * - 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * - 空间复杂度：O(n + k + d) - 需要额外空间和递归栈
 * - 稳定性：稳定 - 计数排序保持相等元素的相对位置
 *
 * @param arr - 待排序的数字数组
 * @param size - 数组大小
 * @return void 无返回值，直接修改原数组
 */
void radixSort5(int arr[], int size)
{
    // 第一步：输出测试信息
    // 关键点：标识当前测试的算法类型
    printf("radixSort5 递归基数排序:\n");

    // 第二步：找出最大值和最小值
    // 关键点：确定排序的位数范围和处理负数
    int max_value = arr[0];
    int min_value = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max_value)
            max_value = arr[i];
        if (arr[i] < min_value)
            min_value = arr[i];
    }

    // 第三步：调用递归基数排序
    // 关键点：从最低位（个位）开始递归排序
    recursiveRadixSort(arr, size, 1, min_value, max_value);

    // 第四步：输出排序结果
    // 关键点：显示排序后的数组，验证算法正确性
    printArray(arr, size, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main()
{
    // 测试1：radix_sort1 - 计数排序基数排序版本（支持负数）
    performanceTest(radix_sort1, testData, testDataSize, "radix_sort1 - 计数排序基数排序版本");

    // 测试2：radixSort2 - MSD基数排序版本
    performanceTest(radixSort2, testData, testDataSize, "radixSort2 - MSD基数排序版本");

    // 测试3：radixSort3 - 迭代MSD基数排序版本
    performanceTest(radixSort3, testData, testDataSize, "radixSort3 - 迭代MSD基数排序版本");

    // 测试4：radixSort4 - 桶优化基数排序版本
    performanceTest(radixSort4, testData, testDataSize, "radixSort4 - 桶优化基数排序版本");

    // 测试5：radixSort5 - 递归基数排序版本
    performanceTest(radixSort5, testData, testDataSize, "radixSort5 - 递归基数排序版本");

    // 测试6：负数数据处理
    printf("\n=== 负数测试 ===\n");
    performanceTest(radixSort5, negativeTestData, negativeTestDataSize, "radixSort5 - 递归基数排序版本（负数测试）");

    printf("=== 算法对比总结 ===\n");
    printf("1. radix_sort1：计数排序基数排序版本，支持负数\n");
    printf("2. radixSort2：MSD基数排序版本，高位优先递归处理\n");
    printf("3. radixSort3：迭代MSD基数排序版本，避免递归性能稳定\n");
    printf("4. radixSort4：桶优化基数排序版本，动态桶大小内存优化\n");
    printf("5. radixSort5：递归基数排序版本，递归处理每一位\n");

    return 0;
}
/*打印结果
jarry@Mac radixsort % gcc radix_sort.c -o radix_sort && ./radix_sort
radix_sort1 - 计数排序基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radix_sort1 - 计数排序基数排序版本: 0.004ms
radix_sort1 - 计数排序基数排序版本: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort2 - MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort2 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort2 - MSD基数排序版本: 0.005ms
radixSort2 - MSD基数排序版本: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort3 - 迭代MSD基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort3 - 迭代MSD基数排序版本: 0.005ms
radixSort3 - 迭代MSD基数排序版本: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort4 - 桶优化基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort4 - 桶优化基数排序版本: 0.006ms
radixSort4 - 桶优化基数排序版本: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

radixSort5 - 递归基数排序版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort5 递归基数排序:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
radixSort5 - 递归基数排序版本: 0.003ms
radixSort5 - 递归基数排序版本: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]


=== 负数测试 ===
radixSort5 - 递归基数排序版本（负数测试）: [170, 45, 75, -90, -802, 24, 2, 66, -5, 0]
radixSort5 递归基数排序:
排序后数组: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]
radixSort5 - 递归基数排序版本（负数测试）: 0.003ms
radixSort5 - 递归基数排序版本（负数测试）: [-802, -90, -5, 0, 2, 24, 45, 66, 75, 170]

=== 算法对比总结 ===
1. radix_sort1：计数排序基数排序版本，支持负数
2. radixSort2：MSD基数排序版本，高位优先递归处理
3. radixSort3：迭代MSD基数排序版本，避免递归性能稳定
4. radixSort4：桶优化基数排序版本，动态桶大小内存优化
5. radixSort5：递归基数排序版本，递归处理每一位
 */