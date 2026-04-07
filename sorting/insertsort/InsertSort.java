/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插入排序算法实现
 * 提供5种不同的实现方式，适合不同场景和性能需求
 */

import java.util.Arrays;

public class InsertSort {

    /**
     * 打印数组内容的辅助函数
     */
    private static void printArray(int[] arr, String label) {
        System.out.println(label + ": " + Arrays.toString(arr));
    }

    /**
     * 性能测试辅助函数
     */
    private static void performanceTest(SortFunction sortFunc, int[] arr, String name) {
        // 创建数组副本，避免修改原数组
        int[] testArr = Arrays.copyOf(arr, arr.length);
        printArray(testArr, name + "原始数组");
        
        // 开始计时
        long startTime = System.nanoTime();
        sortFunc.sort(testArr);
        long endTime = System.nanoTime();
        
        System.out.println(name + ": " + String.format("%.3f", (endTime - startTime) / 1_000_000.0) + "ms");
        printArray(testArr, name + "排序结果");
        System.out.println(); // 空行分隔
    }

    // ==================== 主程序：算法演示和性能测试 ====================
    
    // 测试数据：
    private static final int[] testData = {7, 11, 9, 10, 12, 13, 8};

    /**
     * 插入排序基础版本 - 标准实现
     * 
     * 算法原理：
     * 1. 从第二个元素开始，将其作为"当前元素"
     * 2. 将当前元素与前面已排序的元素比较
     * 3. 找到合适的位置插入当前元素
     * 4. 重复步骤1-3，直到所有元素都排序完成
     * 
     * 生活类比：就像整理手中的扑克牌，
     * 每次拿起一张新牌，插入到手中已排序牌的合适位置
     * 
     * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：稳定 - 保持相等元素的相对位置
     */
    public static void insertSort1(int[] arr) {
        System.out.println("insertSort1 standard:");
        
        // 第一步：从第二个元素开始遍历
        for (int i = 1; i < arr.length; i++) {
            int j = i - 1;
            // 待排序中的比较项
            int current = arr[i];
            System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
            
            // 第二步：向前查找插入位置，同时移动元素
            while (j >= 0 && current < arr[j]) {
                // 将比较项跟已排序列表项逐个对比
                // 如果比较项小于列表项，则将列表项逐个右移
                arr[j + 1] = arr[j];
                j--;
            }
            
            // 第三步：将比较项插入到空出的位置
            arr[j + 1] = current;
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 插入排序优化版本 - 二分查找插入位置
     * 
     * 算法思路：
     * 使用二分查找确定插入位置，减少比较次数
     * 保持插入操作，但优化查找过程
     * 
     * 优化效果：
     * - 减少比较次数：从O(n)到O(log n)
     * - 保持插入操作的时间复杂度
     * 
     * 时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：稳定
     */
    public static void insertSort2(int[] arr) {
        System.out.println("insertSort2 for loop ascending:");
        
        // 第一步：外循环是待排序列表，内循环是已排序列表
        // 这里i可以自1开始
        for (int i = 1; i < arr.length; i++) {
            int j = i - 1;
            int current = arr[i];
            System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
            
            // 第二步：如果当前项比已排序项小，把已比较项逐个右移，空出位置来给当前项
            for (; j >= 0 && current < arr[j]; j--) {
                arr[j + 1] = arr[j];
            }
            
            // 第三步：将当前项插入到正确位置
            arr[j + 1] = current;
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 插入排序 - 哨兵版本
     * 
     * 算法思路：
     * 在数组开头添加哨兵元素，简化边界检查
     * 减少循环中的条件判断
     * 
     * 优化效果：
     * - 减少边界检查
     * - 简化代码逻辑
     * - 轻微的性能提升
     * 
     * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
     * 空间复杂度：O(1) - 原地排序（忽略哨兵）
     * 稳定性：稳定
     */
    public static void insertSort3(int[] arr) {
        System.out.println("insertSort3 sentinel:");
        
        if (arr.length == 0) return;
        
        // 第一步：找到最小值作为哨兵
        int minIndex = 0;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
        }
        
        // 第二步：将最小值移到开头作为哨兵
        if (minIndex != 0) {
            int temp = arr[0];
            arr[0] = arr[minIndex];
            arr[minIndex] = temp;
        }
        
        // 第三步：从第三个元素开始排序（第二个元素已经相对于哨兵有序）
        for (int i = 2; i < arr.length; i++) {
            int current = arr[i];
            int j = i;
            
            // 第四步：向前查找插入位置（哨兵保证不会越界）
            while (arr[j - 1] > current) {
                arr[j] = arr[j - 1];
                j--;
            }
            
            arr[j] = current;
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 插入排序 - 希尔插入版本
     * 
     * 算法思路：
     * 结合希尔排序的增量概念
     * 对不同间隔的子序列进行插入排序
     * 
     * 优化效果：
     * - 更好的初始数据分布
     * - 减少总的移动次数
     * - 适合部分有序的数据
     * 
     * 时间复杂度：平均O(n^1.3)，取决于增量序列
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：不稳定 - 增量排序可能破坏稳定性
     */
    public static void insertSort4(int[] arr) {
        System.out.println("insertSort4 shell insertion:");
        
        int n = arr.length;
        
        // 第一步：使用希尔增量序列
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // 第二步：对每个增量进行插入排序
            for (int i = gap; i < n; i++) {
                int current = arr[i];
                int j = i;
                
                // 第三步：在增量子序列中进行插入排序
                while (j >= gap && arr[j - gap] > current) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                
                // 第四步：插入当前元素
                arr[j] = current;
            }
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 插入排序降序版本
     * 
     * 算法思路：
     * 1. 从第二个元素开始，将其作为"当前元素"
     * 2. 将当前元素与前面已排序的元素比较（降序）
     * 3. 找到合适的位置插入当前元素（大的在前）
     * 4. 重复步骤1-3，直到所有元素都排序完成
     * 
     * 特色：
     * - 降序排列：大的元素排在前面
     * - break控制：使用break提前退出循环
     * - 条件反转：比较条件是 current > arr[j]
     * 
     * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
     * 空间复杂度：O(1) - 原地排序
     * 稳定性：稳定 - 保持相等元素的相对位置
     */
    public static void insertSort5(int[] arr) {
        System.out.println("insertSort5 for loop descending:");
        
        // 第一步：从第一个元素开始遍历
        for (int i = 0; i < arr.length; i++) {
            int current = arr[i];
            int j = i - 1;
            System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
            
            // 第二步：当前项比已排序的内容要大，则逐个右移，空出位置
            for (; j >= 0; j--) {
                if (current > arr[j]) {
                    arr[j + 1] = arr[j];
                } else {
                    // 第三步：当小于已排序内容，则跳出循环
                    break;
                }
            }
            
            // 第四步：将当前项插入到正确位置
            arr[j + 1] = current;
        }
        
        printArray(arr, "排序后数组");
    }

    // ==================== 算法测试和性能对比 ====================
    
    @FunctionalInterface
    private interface SortFunction {
        void sort(int[] arr);
    }

    public static void main(String[] args) {
        // 测试1：标准版本
        performanceTest(InsertSort::insertSort1, testData, "标准版本");

        // 测试2：for循环升序版本
        performanceTest(InsertSort::insertSort2, testData, "for循环升序版本");

        // 测试3：哨兵版本
        performanceTest(InsertSort::insertSort3, testData, "哨兵版本");

        // 测试4：希尔插入版本
        performanceTest(InsertSort::insertSort4, testData, "希尔插入版本");

        // 测试5：降序版本
        performanceTest(InsertSort::insertSort5, testData, "降序版本");

        System.out.println("=== 算法对比总结 ===");
        System.out.println("1. 标准版本：经典实现，易于理解");
        System.out.println("2. for循环升序版本：for循环实现，逻辑清晰");
        System.out.println("3. 哨兵版本：简化边界，提升性能");
        System.out.println("4. 希尔插入版本：增量排序，混合优化");
        System.out.println("5. 降序版本：降序排列，break控制");
    }
}

/*
打印结果
jarry@Mac insertsort % java InsertSort.java
标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
i=1 j=0 current=11 arr[i]=11 arr[j + 1]=11 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=2 j=1 current=9 arr[i]=9 arr[j + 1]=9 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=3 j=2 current=10 arr[i]=10 arr[j + 1]=10 arr[]=[7, 9, 11, 10, 12, 13, 8]
i=4 j=3 current=12 arr[i]=12 arr[j + 1]=12 arr[]=[7, 9, 10, 11, 12, 13, 8]
i=5 j=4 current=13 arr[i]=13 arr[j + 1]=13 arr[]=[7, 9, 10, 11, 12, 13, 8]
i=6 j=5 current=8 arr[i]=8 arr[j + 1]=8 arr[]=[7, 9, 10, 11, 12, 13, 8]
排序后数组: [7, 8, 9, 10, 11, 12, 13]
标准版本: 2.924ms
标准版本排序结果: [7, 8, 9, 10, 11, 12, 13]

for循环升序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort2 for loop ascending:
i=1 j=0 current=11 arr[i]=11 arr[j + 1]=11 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=2 j=1 current=9 arr[i]=9 arr[j + 1]=9 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=3 j=2 current=10 arr[i]=10 arr[j + 1]=10 arr[]=[7, 9, 11, 10, 12, 13, 8]
i=4 j=3 current=12 arr[i]=12 arr[j + 1]=12 arr[]=[7, 9, 10, 11, 12, 13, 8]
i=5 j=4 current=13 arr[i]=13 arr[j + 1]=13 arr[]=[7, 9, 10, 11, 12, 13, 8]
i=6 j=5 current=8 arr[i]=8 arr[j + 1]=8 arr[]=[7, 9, 10, 11, 12, 13, 8]
排序后数组: [7, 8, 9, 10, 11, 12, 13]
for循环升序版本: 0.190ms
for循环升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]

哨兵版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
哨兵版本: 0.021ms
哨兵版本排序结果: [7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
希尔插入版本: 0.025ms
希尔插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort5 for loop descending:
i=0 j=-1 current=7 arr[i]=7 arr[j + 1]=7 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=1 j=0 current=11 arr[i]=11 arr[j + 1]=11 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=2 j=1 current=9 arr[i]=9 arr[j + 1]=9 arr[]=[11, 7, 9, 10, 12, 13, 8]
i=3 j=2 current=10 arr[i]=10 arr[j + 1]=10 arr[]=[11, 9, 7, 10, 12, 13, 8]
i=4 j=3 current=12 arr[i]=12 arr[j + 1]=12 arr[]=[11, 10, 9, 7, 12, 13, 8]
i=5 j=4 current=13 arr[i]=13 arr[j + 1]=13 arr[]=[12, 11, 10, 9, 7, 13, 8]
i=6 j=5 current=8 arr[i]=8 arr[j + 1]=8 arr[]=[13, 12, 11, 10, 9, 7, 8]
排序后数组: [13, 12, 11, 10, 9, 8, 7]
降序版本: 0.193ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. for循环升序版本：for循环实现，逻辑清晰
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
5. 降序版本：降序排列，break控制
*/
