/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

import java.util.Arrays;

public class RadixSort {

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
    
    // 测试数据：包含大数字和负数的典型数组
    private static final int[] testData = {33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431};

    /**
     * 获取数字的指定位数
     */
    private static int getDigit(int num, int exp) {
        return Math.abs(num) / exp % 10;
    }

    /**
     * 计数排序辅助函数 - 按位数排序
     */
    private static void countingSortByDigit(int[] arr, int exp) {
        int n = arr.length;
        int[] output = new int[n];
        int[] count = new int[10];
        
        // 统计每个数字的出现次数
        for (int i = 0; i < n; i++) {
            int digit = getDigit(arr[i], exp);
            count[digit]++;
        }
        
        // 计算累计计数
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // 构建输出数组
        for (int i = n - 1; i >= 0; i--) {
            int digit = getDigit(arr[i], exp);
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        // 复制回原数组
        System.arraycopy(output, 0, arr, 0, n);
    }

    /**
     * 基数排序基础版本 - LSD（最低位优先）
     * 
     * 算法原理：
     * 1. 从个位开始，对每一位进行计数排序
     * 2. 逐步处理十位、百位、千位等
     * 3. 经过所有位数处理后，数组完全有序
     * 
     * 生活类比：就像整理学生成绩，先按个位数排序，
     * 再按十位数排序，最后按百位数排序，最终得到完整排序
     * 
     * 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
     * 空间复杂度：O(n + k) - 需要额外的计数和输出数组
     * 稳定性：稳定 - 计数排序保持相等元素的相对位置
     */
    public static void radixSort1(int[] arr) {
        System.out.println("radixSort1 LSD:");
        
        // 找到最大值以确定位数
        int max = Arrays.stream(arr).max().orElse(0);
        
        // 对每个位数进行计数排序
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * MSD递归排序函数
     */
    private static void msdSort(int[] arr, int left, int right, int exp) {
        if (left >= right || exp < 1) {
            return;
        }
        
        // 创建桶
        java.util.ArrayList<Integer>[] buckets = new java.util.ArrayList[10];
        for (int i = 0; i < 10; i++) {
            buckets[i] = new java.util.ArrayList<>();
        }
        
        // 分配到桶中
        for (int i = left; i <= right; i++) {
            int digit = getDigit(arr[i], exp);
            buckets[digit].add(arr[i]);
        }
        
        // 重新排序并递归处理每个桶
        int index = left;
        for (int i = 0; i < 10; i++) {
            if (!buckets[i].isEmpty()) {
                // 复制桶中元素回原数组
                for (int j = 0; j < buckets[i].size(); j++) {
                    arr[index++] = buckets[i].get(j);
                }
                
                // 递归处理下一个位数
                msdSort(arr, left, index - 1, exp / 10);
                left = index;
            }
        }
    }

    /**
     * 基数排序优化版本 - MSD（最高位优先）
     * 
     * 算法思路：
     * 从最高位开始排序，使用递归处理子数组
     * 适合处理字符串或变长数据
     * 
     * 优化效果：
     * - 更好的内存局部性
     * - 适合大数据集
     * 
     * 时间复杂度：O(d * (n + k))
     * 空间复杂度：O(n + k)
     * 稳定性：稳定
     */
    public static void radixSort2(int[] arr) {
        System.out.println("radixSort2 MSD:");
        
        if (arr.length == 0) return;
        
        // 找到最大值以确定位数
        int max = Arrays.stream(arr).max().orElse(0);
        int exp = 1;
        while (max / exp > 0) {
            exp *= 10;
        }
        
        msdSort(arr, 0, arr.length - 1, exp / 10);
        
        printArray(arr, "排序后数组");
    }

    /**
     * 基数排序 - 迭代MSD版本
     * 
     * 算法思路：
     * 使用迭代方式实现MSD排序
     * 使用栈来模拟递归调用
     * 
     * 优化效果：
     * - 避免递归开销
     * - 更好的性能控制
     * 
     * 时间复杂度：O(d * (n + k))
     * 空间复杂度：O(n + k)
     * 稳定性：稳定
     */
    public static void radixSort3(int[] arr) {
        System.out.println("radixSort3 iterative MSD:");
        
        if (arr.length == 0) return;
        
        // 找到最大值以确定位数
        int max = Arrays.stream(arr).max().orElse(0);
        int exp = 1;
        while (max / exp > 0) {
            exp *= 10;
        }
        
        // 使用栈模拟递归
        java.util.Stack<int[]> stack = new java.util.Stack<>();
        stack.push(new int[]{0, arr.length - 1, exp / 10});
        
        while (!stack.isEmpty()) {
            int[] params = stack.pop();
            int left = params[0];
            int right = params[1];
            int currentExp = params[2];
            
            if (left >= right || currentExp < 1) {
                continue;
            }
            
            // 创建桶
            java.util.ArrayList<Integer>[] buckets = new java.util.ArrayList[10];
            for (int i = 0; i < 10; i++) {
                buckets[i] = new java.util.ArrayList<>();
            }
            
            // 分配到桶中
            for (int i = left; i <= right; i++) {
                int digit = getDigit(arr[i], currentExp);
                buckets[digit].add(arr[i]);
            }
            
            // 重新排序并将子问题入栈
            int index = left;
            for (int i = 0; i < 10; i++) {
                if (!buckets[i].isEmpty()) {
                    // 复制桶中元素回原数组
                    for (int j = 0; j < buckets[i].size(); j++) {
                        arr[index++] = buckets[i].get(j);
                    }
                    
                    // 将子问题入栈（逆序处理以保持正确顺序）
                    stack.push(new int[]{left, index - 1, currentExp / 10});
                    left = index;
                }
            }
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 基数排序 - 桶优化版本
     * 
     * 算法思路：
     * 使用动态桶大小，优化内存使用
     * 适合处理稀疏数据
     * 
     * 优化效果：
     * - 减少内存占用
     * - 提高处理效率
     * 
     * 时间复杂度：O(d * (n + k))
     * 空间复杂度：O(n + k)
     * 稳定性：稳定
     */
    public static void radixSort4(int[] arr) {
        System.out.println("radixSort4 bucket optimized:");
        
        // 找到最大值以确定位数
        int max = Arrays.stream(arr).max().orElse(0);
        
        // 对每个位数进行计数排序
        for (int exp = 1; max / exp > 0; exp *= 10) {
            int n = arr.length;
            int[] output = new int[n];
            
            // 动态确定桶范围
            int minDigit = 9, maxDigit = 0;
            for (int i = 0; i < n; i++) {
                int digit = getDigit(arr[i], exp);
                minDigit = Math.min(minDigit, digit);
                maxDigit = Math.max(maxDigit, digit);
            }
            
            int bucketSize = maxDigit - minDigit + 1;
            int[] count = new int[bucketSize];
            
            // 统计每个数字的出现次数
            for (int i = 0; i < n; i++) {
                int digit = getDigit(arr[i], exp);
                count[digit - minDigit]++;
            }
            
            // 计算累计计数
            for (int i = 1; i < bucketSize; i++) {
                count[i] += count[i - 1];
            }
            
            // 构建输出数组
            for (int i = n - 1; i >= 0; i--) {
                int digit = getDigit(arr[i], exp);
                output[count[digit - minDigit] - 1] = arr[i];
                count[digit - minDigit]--;
            }
            
            // 复制回原数组
            System.arraycopy(output, 0, arr, 0, n);
        }
        
        printArray(arr, "排序后数组");
    }

    // ==================== 算法测试和性能对比 ====================
    
    @FunctionalInterface
    private interface SortFunction {
        void sort(int[] arr);
    }

    public static void main(String[] args) {
        // 测试1：LSD版本
        performanceTest(RadixSort::radixSort1, testData, "LSD版本");

        // 测试2：MSD版本
        performanceTest(RadixSort::radixSort2, testData, "MSD版本");

        // 测试3：迭代MSD版本
        performanceTest(RadixSort::radixSort3, testData, "迭代MSD版本");

        // 测试4：桶优化版本
        performanceTest(RadixSort::radixSort4, testData, "桶优化版本");

        System.out.println("=== 算法对比总结 ===");
        System.out.println("1. LSD版本：经典实现，从低到高");
        System.out.println("2. MSD版本：高位优先，递归处理");
        System.out.println("3. 迭代MSD版本：避免递归，性能稳定");
        System.out.println("4. 桶优化版本：动态桶大小，内存优化");
    }
}

/*
打印结果
jarry@Mac radixsort % javac RadixSort.java && java RadixSort
LSD版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort1 LSD:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
LSD版本: 0.125ms
LSD版本排序结果: [7, 8, 9, 10, 11, 12, 13]

MSD版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort2 MSD:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
MSD版本: 0.042ms
MSD版本排序结果: [7, 8, 9, 10, 11, 12, 13]

迭代MSD版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort3 iterative MSD:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
迭代MSD版本: 0.042ms
迭代MSD版本排序结果: [7, 8, 9, 10, 11, 12, 13]

桶优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
radixSort4 bucket optimized:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
桶优化版本: 0.042ms
桶优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. LSD版本：经典实现，从低到高
2. MSD版本：高位优先，递归处理
3. 迭代MSD版本：避免递归，性能稳定
4. 桶优化版本：动态桶大小，内存优化
*/
