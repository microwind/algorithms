/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
 
using System;
using System.Diagnostics;

/**
 * 冒泡排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */
public class BubbleSort
{
    /**
     * 冒泡排序基础版本 - 升序排列
     * 
     * 算法原理：
     * 1. 从数组左端开始，依次比较相邻元素
     * 2. 若左元素大于右元素，则交换位置
     * 3. 继续向后比较，直到数组末尾
     * 4. 重复以上过程，每轮都会将当前未排序部分的最大值"冒泡"到最后
     * 
     * 生活类比：就像水中的气泡，轻的气泡会自然上浮到水面
     * 在排序中，大的数字会逐渐"上浮"到数组的右侧
     * 
     * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
     * 空间复杂度：O(1) - 只使用常数个额外变量
     * 稳定性：稳定 - 相等元素的相对位置不会改变
     * 
     * @param arr 待排序的整数数组
     */
    public void BubbleSort1(int[] arr)
    {
        Console.WriteLine("bubbleSort1 from left to right:");
        int len = arr.Length;
        // 外循环：控制排序轮数，每轮确定一个最大值的位置
        for (int i = 0; i < len; i++)
        {
            // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
            for (int j = 0; j < len - i - 1; j++)
            {
                // 关键点：自左往右每两个进行比较，把大的交换到右侧
                if (arr[j] > arr[j + 1])
                {
                    // C#特点：使用临时变量交换
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        PrintArray(arr, "基础升序版本排序结果");
    }

    /**
     * 冒泡排序基础版本 - 降序排列
     * 
     * 算法思路：
     * 与升序版本相反，从数组末尾开始比较
     * 每轮将当前未排序部分的最小值"下沉"到左侧
     * 
     * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
     * 空间复杂度：O(1) - 只使用常数个额外变量
     * 稳定性：稳定 - 相等元素的相对位置不会改变
     * 
     * @param arr 待排序的整数数组
     */
    public void BubbleSort2(int[] arr)
    {
        Console.WriteLine("bubbleSort2 from right to left:");
        int len = arr.Length;
        // 外循环：控制排序轮数，每轮确定一个最小值的位置
        for (int i = 0; i < len; i++)
        {
            // 内循环：从右向左比较，j > i 避免重复比较已排序部分
            for (int j = len - 1; j > i; j--)
            {
                // 关键点：自右往左每两个进行比较，把小的交换到右侧
                if (arr[j - 1] < arr[j])
                {
                    // C#特点：使用临时变量交换
                    int temp = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        PrintArray(arr, "基础降序版本排序结果");
    }

    /**
     * 冒泡排序优化版本
     * 
     * 优化思路：
     * 增加一个标志位，记录某一轮是否发生了元素交换
     * 如果某一轮没有发生任何交换，说明数组已经完全有序
     * 此时可以提前终止排序过程，避免不必要的比较
     * 
     * 优化效果：
     * - 对于完全有序的数组：时间复杂度从 O(n²) 优化到 O(n)
     * - 对于部分有序的数组：也会有明显的性能提升
     * - 对于完全逆序的数组：性能与基础版本相同
     * 
     * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
     * 稳定性：稳定 - 相等元素的相对位置不会改变
     * 
     * @param arr 待排序的整数数组
     */
    public void BubbleSort3(int[] arr)
    {
        Console.WriteLine("bubbleSort3 add flag:");
        // 优化点：增加一个标志，如果某一轮没有进行过任何的交换
        // 则说明当前数组已排好序，则不必继续后面的遍历
        int len = arr.Length;
        bool flag = true;

        // 外循环：增加 flag 条件，当数组已有序时提前终止
        for (int i = 0; i < len && flag == true; i++)
        {
            flag = false; // 每轮开始时重置标志
            // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
            for (int j = 0; j < len - i - 1; j++)
            {
                // 关键点：自左往右每两个进行比较，把大的交换到右侧
                if (arr[j] > arr[j + 1])
                {
                    flag = true; // 发生交换，设置标志
                    // C#特点：使用临时变量交换
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        PrintArray(arr, "优化版本排序结果");
    }

    /**
     * 插入冒泡排序法
     * 
     * 算法思路：
     * 将数组分为两部分：左侧已排序区域，右侧待排序区域
     * 每次从待排序区域取出第一个元素，插入到已排序区域的正确位置
     * 
     * 这种方法结合了插入排序的思想，在某些情况下性能更好
     * 
     * 时间复杂度：O(n²)，空间复杂度：O(1)
     * 稳定性：稳定 - 相等元素的相对位置不会改变
     * 
     * @param arr 待排序的整数数组
     */
    public void BubbleSort4(int[] arr)
    {
        Console.WriteLine("bubbleSort4:");
        int len = arr.Length;
        // 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
        for (int i = 1; i < len; i++)
        {
            bool swapped = false;
            // 内循环：在已排序区域中查找插入位置
            for (int j = 0; j < i; j++)
            {
                // 关键点：如果待插入元素小于已排序区域的某个元素，则交换
                if (arr[j] > arr[j + 1])
                {
                    // C#特点：使用临时变量交换
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        PrintArray(arr, "插入式版本排序结果");
    }

    /**
     * 打印数组内容的辅助函数
     * @param arr 要打印的数组
     * @param label 数组的标签说明
     */
    public void PrintArray(int[] arr, string label)
    {
        Console.Write($"{label}: [");
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write(arr[i]);
            if (i < arr.Length - 1)
            {
                Console.Write(", ");
            }
        }
        Console.WriteLine("]");
    }

    /**
     * 性能测试辅助函数
     * @param sortFunc 排序函数
     * @param arr 测试数组
     * @param name 版本名称
     */
    public void PerformanceTest(Action<int[]> sortFunc, int[] arr, string name)
    {
        int[] testArr = (int[])arr.Clone();
        PrintArray(testArr, $"{name}原始数组");
        
        Stopwatch stopwatch = Stopwatch.StartNew();
        sortFunc(testArr);
        stopwatch.Stop();
        
        Console.WriteLine($"{name}: {stopwatch.Elapsed.TotalMilliseconds:F3}ms");
        Console.WriteLine();
    }

    /**
     * 主测试函数
     */
    public void Run()
    {
        Console.WriteLine("=== 冒泡排序算法演示 ===");
        Console.WriteLine();

        int[] testData = { 7, 11, 9, 10, 12, 13, 8 };

        // 测试1：基础升序版本
        PerformanceTest(BubbleSort1, testData, "基础升序版本");

        // 测试2：基础降序版本
        PerformanceTest(BubbleSort2, testData, "基础降序版本");

        // 测试3：优化版本
        PerformanceTest(BubbleSort3, testData, "优化版本");

        // 测试4：插入式版本
        PerformanceTest(BubbleSort4, testData, "插入式版本");

        Console.WriteLine("=== 算法对比总结 ===");
        Console.WriteLine("1. 基础版本：简单易懂，适合学习算法原理");
        Console.WriteLine("2. 降序版本：展示算法的灵活性，可按需排序");
        Console.WriteLine("3. 优化版本：通过标志位优化，适合实际应用");
        Console.WriteLine("4. 插入式版本：结合其他排序思想，性能更稳定");
    }
}

// 执行测试
class Program
{
    static void Main(string[] args)
    {
        BubbleSort sorter = new BubbleSort();
        sorter.Run();
    }
}

/* 打印结果
jarry@Mac bubblesort % dotnet run
=== 冒泡排序算法演示 ===

基础升序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort1 from left to right:
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本: 0.xxxms

基础降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort2 from right to left:
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本: 0.xxxms

优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort3 add flag:
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本: 0.xxxms

插入式版本原始数组: [7, 11, 9, 10, 12, 13, 8]
bubbleSort4:
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本: 0.xxxms

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
*/
