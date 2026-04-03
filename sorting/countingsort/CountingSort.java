/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 计数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

import java.util.Arrays;

public class CountingSort {

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
    
    // 测试数据：包含负数和重复元素的典型数组
    private static final int[] testData = {20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80};

    /**
     * 计数排序基础版本 - 标准实现
     * 
     * 算法原理：
     * 1. 统计每个元素出现的次数
     * 2. 计算累计计数以确定元素位置
     * 3. 根据累计计数将元素放到正确位置
     * 4. 从后向前遍历保证稳定性
     * 
     * 生活类比：就像统计班级学生成绩分布，
     * 先统计每个分数段有多少人，然后按分数段排序
     * 
     * 时间复杂度：O(n + k)，n为元素个数，k为数据范围
     * 空间复杂度：O(k) - 需要计数数组
     * 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
     */
    public static void countingSort1(int[] arr) {
        System.out.println("countingSort1 standard:");
        
        if (arr.length == 0) return;
        
        // 找到最小值和最大值
        int min = Arrays.stream(arr).min().orElse(0);
        int max = Arrays.stream(arr).max().orElse(0);
        int range = max - min + 1;
        
        // 创建计数数组
        int[] count = new int[range];
        
        // 统计每个元素出现的次数
        for (int i = 0; i < arr.length; i++) {
            count[arr[i] - min]++;
        }
        
        // 计算累计计数
        for (int i = 1; i < count.length; i++) {
            count[i] += count[i - 1];
        }
        
        // 创建输出数组
        int[] output = new int[arr.length];
        
        // 从后向前遍历，保证稳定性
        for (int i = arr.length - 1; i >= 0; i--) {
            int index = arr[i] - min;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }
        
        // 复制回原数组
        System.arraycopy(output, 0, arr, 0, arr.length);
        
        printArray(arr, "排序后数组");
    }

    /**
     * 计数排序优化版本 - 内存优化
     * 
     * 算法思路：
     * 直接在原数组上进行修改，减少内存使用
     * 使用原地排序技术
     * 
     * 优化效果：
     * - 减少额外空间使用
     * - 更好的缓存性能
     * 
     * 时间复杂度：O(n + k)
     * 空间复杂度：O(k)
     * 稳定性：不稳定 - 原地修改可能影响稳定性
     */
    public static void countingSort2(int[] arr) {
        System.out.println("countingSort2 memory optimized:");
        
        if (arr.length == 0) return;
        
        // 找到最小值和最大值
        int min = Arrays.stream(arr).min().orElse(0);
        int max = Arrays.stream(arr).max().orElse(0);
        int range = max - min + 1;
        
        // 创建计数数组
        int[] count = new int[range];
        
        // 统计每个元素出现的次数
        for (int i = 0; i < arr.length; i++) {
            count[arr[i] - min]++;
        }
        
        // 直接根据计数重构数组
        int index = 0;
        for (int i = 0; i < count.length; i++) {
            while (count[i] > 0) {
                arr[index] = i + min;
                index++;
                count[i]--;
            }
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 计数排序 - 负数单独处理版本
     * 
     * 算法思路：
     * 专门处理包含负数的情况
     * 分别处理负数和正数部分
     * 
     * 优化效果：
     * - 支持负数排序
     * - 保持算法稳定性
     * 
     * 时间复杂度：O(n + k)
     * 空间复杂度：O(k)
     * 稳定性：稳定
     */
    public static void countingSort3(int[] arr) {
        System.out.println("countingSort3 negative numbers:");
        
        if (arr.length == 0) return;
        
        // 分离正数和负数
        java.util.List<Integer> negatives = new java.util.ArrayList<>();
        java.util.List<Integer> positives = new java.util.ArrayList<>();
        
        for (int value : arr) {
            if (value < 0) {
                negatives.add(value);
            } else {
                positives.add(value);
            }
        }
        
        // 排序负数部分（转换为绝对值排序后反转）
        if (!negatives.isEmpty()) {
            int[] negArray = negatives.stream().mapToInt(Math::abs).toArray();
            countingSort1(negArray);
            
            // 反转并恢复负号
            for (int i = 0; i < negArray.length; i++) {
                negatives.set(i, -negArray[negArray.length - 1 - i]);
            }
        }
        
        // 排序正数部分
        if (!positives.isEmpty()) {
            int[] posArray = positives.stream().mapToInt(Integer::intValue).toArray();
            countingSort1(posArray);
            
            for (int i = 0; i < posArray.length; i++) {
                positives.set(i, posArray[i]);
            }
        }
        
        // 合并结果
        int index = 0;
        for (int neg : negatives) {
            arr[index++] = neg;
        }
        for (int pos : positives) {
            arr[index++] = pos;
        }
        
        printArray(arr, "排序后数组");
    }

    /**
     * 计数排序 - 桶优化版本
     * 
     * 算法思路：
     * 使用桶的概念，将相近的数值分组
     * 减少计数数组的大小
     * 适合大数据范围但分布稀疏的情况
     * 
     * 优化效果：
     * - 减少内存使用
     * - 提高处理稀疏数据的效率
     * 
     * 时间复杂度：O(n + k)
     * 空间复杂度：O(k)
     * 稳定性：稳定
     */
    public static void countingSort4(int[] arr) {
        System.out.println("countingSort4 bucket optimized:");
        
        if (arr.length == 0) return;
        
        // 找到最小值和最大值
        int min = Arrays.stream(arr).min().orElse(0);
        int max = Arrays.stream(arr).max().orElse(0);
        int range = max - min + 1;
        
        // 确定桶的大小（可以调整以优化性能）
        int bucketSize = Math.max(1, range / 10);
        int bucketCount = (range + bucketSize - 1) / bucketSize;
        
        // 创建桶
        java.util.ArrayList<Integer>[] buckets = new java.util.ArrayList[bucketCount];
        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = new java.util.ArrayList<>();
        }
        
        // 将元素分配到桶中
        for (int i = 0; i < arr.length; i++) {
            int bucketIndex = (arr[i] - min) / bucketSize;
            buckets[bucketIndex].add(arr[i]);
        }
        
        // 对每个桶进行排序并合并结果
        int index = 0;
        for (int i = 0; i < bucketCount; i++) {
            if (!buckets[i].isEmpty()) {
                // 对桶内元素使用标准计数排序
                int[] bucketArray = buckets[i].stream().mapToInt(Integer::intValue).toArray();
                countingSort1(bucketArray);
                
                // 将排序后的桶内容复制回原数组
                for (int j = 0; j < bucketArray.length; j++) {
                    arr[index] = bucketArray[j];
                    index++;
                }
            }
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
        performanceTest(CountingSort::countingSort1, testData, "标准版本");

        // 测试2：内存优化版本
        performanceTest(CountingSort::countingSort2, testData, "内存优化版本");

        // 测试3：负数处理版本
        performanceTest(CountingSort::countingSort3, testData, "负数处理版本");

        // 测试4：桶优化版本
        performanceTest(CountingSort::countingSort4, testData, "桶优化版本");

        System.out.println("=== 算法对比总结 ===");
        System.out.println("1. 标准版本：经典实现，稳定排序");
        System.out.println("2. 内存优化版本：原地修改，节省空间");
        System.out.println("3. 负数处理版本：支持负数，功能完整");
        System.out.println("4. 桶优化版本：分组处理，适合稀疏数据");
    }
}

/*
打印结果
jarry@Mac countingsort % java CountingSort.java
CountingSort.java:244: warning: [unchecked] unchecked conversion
        java.util.ArrayList<Integer>[] buckets = new java.util.ArrayList[bucketCount];
                                                 ^
  required: ArrayList<Integer>[]
  found:    ArrayList[]
1 warning
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 1.391ms
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.076ms
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
countingSort1 standard:
排序后数组: [10]
countingSort1 standard:
排序后数组: [0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.885ms
负数处理版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
countingSort1 standard:
排序后数组: [-10]
countingSort1 standard:
排序后数组: [0, 6]
countingSort1 standard:
排序后数组: [9, 9, 11, 11, 13, 15]
countingSort1 standard:
排序后数组: [20]
countingSort1 standard:
排序后数组: [30]
countingSort1 standard:
排序后数组: [80]
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
桶优化版本: 0.209ms
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
