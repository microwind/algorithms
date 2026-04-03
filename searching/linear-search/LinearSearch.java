/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 线性查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

import java.util.ArrayList;
import java.util.List;

/**
 * 线性查找类
 * 包含多种线性查找实现
 */
public class LinearSearch {
    
    /**
     * 线性查找基础版本 - 查找第一个匹配项
     * 
     * 算法原理：
     * 1. 从数组开头逐个遍历元素
     * 2. 比较当前元素是否等于目标值
     * 3. 找到目标则返回索引，否则继续
     * 4. 遍历结束未找到则返回-1
     * 
     * 适用场景：
     * - 小规模数据集
     * - 无序数据
     * - 需要查找所有匹配项
     * 
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     * 
     * @param arr 待搜索数组
     * @param target 目标值
     * @return 找到返回索引，未找到返回-1
     */
    public static int linearSearch(int[] arr, int target) {
        // 边界检查
        if (arr == null || arr.length == 0) {
            return -1;
        }
        
        // 逐个遍历查找
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                return i; // 找到目标，返回索引
            }
        }
        
        return -1; // 未找到
    }
    
    /**
     * 线性查找 - 查找所有匹配项
     * 
     * 算法思路：
     * 遍历整个数组，收集所有匹配项的索引
     * 适合处理重复元素的情况
     * 
     * @param arr 待搜索数组
     * @param target 目标值
     * @return 包含所有匹配索引的列表
     */
    public static List<Integer> linearSearchAll(int[] arr, int target) {
        List<Integer> result = new ArrayList<>();
        
        // 边界检查
        if (arr == null || arr.length == 0) {
            return result;
        }
        
        // 逐个遍历查找所有匹配项
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                result.add(i);
            }
        }
        
        return result;
    }
    
    /**
     * 线性查找 - 带哨兵优化版本
     * 
     * 算法优化：
     * 在数组末尾设置哨兵（目标值）
     * 减少每次循环中的边界检查
     * 可以略微提高性能
     * 
     * @param arr 待搜索数组
     * @param target 目标值
     * @return 找到返回索引，未找到返回-1
     */
    public static int linearSearchSentinel(int[] arr, int target) {
        // 边界检查
        if (arr == null || arr.length == 0) {
            return -1;
        }
        
        int last = arr[arr.length - 1]; // 保存最后一个元素
        arr[arr.length - 1] = target;    // 设置哨兵
        
        int i = 0;
        // 由于有哨兵，循环一定会终止
        while (arr[i] != target) {
            i++;
        }
        
        arr[arr.length - 1] = last; // 恢复最后一个元素
        
        // 检查是否真的找到目标
        if (i < arr.length - 1 || arr[arr.length - 1] == target) {
            return i;
        }
        
        return -1;
    }
    
    /**
     * 线性查找 - 反向查找版本
     * 
     * 算法思路：
     * 从数组末尾开始向前查找
     * 适合查找最后一个匹配项的场景
     * 
     * @param arr 待搜索数组
     * @param target 目标值
     * @return 找到返回索引，未找到返回-1
     */
    public static int linearSearchReverse(int[] arr, int target) {
        // 边界检查
        if (arr == null || arr.length == 0) {
            return -1;
        }
        
        // 从后向前遍历查找
        for (int i = arr.length - 1; i >= 0; i--) {
            if (arr[i] == target) {
                return i; // 找到目标，返回索引
            }
        }
        
        return -1; // 未找到
    }
    
    /**
     * 线性查找 - 递归版本
     * 
     * 算法思路：
     * 使用递归方式实现线性查找
     * 每次递归处理一个元素
     * 
     * @param arr 待搜索数组
     * @param target 目标值
     * @param index 当前索引
     * @return 找到返回索引，未找到返回-1
     */
    private static int linearSearchRecursive(int[] arr, int target, int index) {
        // 递归出口条件
        if (index >= arr.length) {
            return -1;
        }
        
        // 检查当前元素
        if (arr[index] == target) {
            return index;
        }
        
        // 递归查找下一个元素
        return linearSearchRecursive(arr, target, index + 1);
    }
    
    /**
     * 线性查找 - 递归版本（公共接口）
     * 
     * @param arr 待搜索数组
     * @param target 目标值
     * @return 找到返回索引，未找到返回-1
     */
    public static int linearSearchRecursive(int[] arr, int target) {
        // 边界检查
        if (arr == null || arr.length == 0) {
            return -1;
        }
        
        return linearSearchRecursive(arr, target, 0);
    }
    
    /**
     * 线性查找 - 泛型版本
     * 
     * 算法扩展：
     * 支持任意类型的数组查找
     * 使用泛型提高代码复用性
     * 
     * @param <T> 数组元素类型
     * @param arr 待搜索数组
     * @param target 目标值
     * @return 找到返回索引，未找到返回-1
     */
    public static <T> int linearSearchGeneric(T[] arr, T target) {
        // 边界检查
        if (arr == null || arr.length == 0) {
            return -1;
        }
        
        // 逐个遍历查找
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].equals(target)) {
                return i; // 找到目标，返回索引
            }
        }
        
        return -1; // 未找到
    }
    
    /**
     * 主程序：演示线性查找功能
     */
    public static void main(String[] args) {
        System.out.println("=== 线性查找演示 ===\n");
        
        // 测试数据
        int[] arr = {64, 34, 25, 12, 22, 11, 90, 22};
        int target = 22;
        
        System.out.println("数组:");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println("\n目标元素: " + target + "\n");
        
        // 基本查找测试
        System.out.println("=== 基本查找测试 ===");
        int index = linearSearch(arr, target);
        if (index != -1) {
            System.out.println("基本查找: 找到于索引 " + index);
        } else {
            System.out.println("基本查找: 未找到");
        }
        
        // 查找所有匹配项
        System.out.println("\n=== 查找所有匹配项 ===");
        List<Integer> allIndices = linearSearchAll(arr, target);
        System.out.print("所有匹配位置: ");
        for (int i = 0; i < allIndices.size(); i++) {
            System.out.print(allIndices.get(i) + " ");
        }
        System.out.println("(共" + allIndices.size() + "个)");
        
        // 反向查找测试
        System.out.println("\n=== 反向查找测试 ===");
        int reverseIndex = linearSearchReverse(arr, target);
        if (reverseIndex != -1) {
            System.out.println("反向查找: 找到于索引 " + reverseIndex);
        } else {
            System.out.println("反向查找: 未找到");
        }
        
        // 哨兵查找测试
        System.out.println("\n=== 哨兵查找测试 ===");
        int sentinelIndex = linearSearchSentinel(arr, target);
        if (sentinelIndex != -1) {
            System.out.println("哨兵查找: 找到于索引 " + sentinelIndex);
        } else {
            System.out.println("哨兵查找: 未找到");
        }
        
        // 递归查找测试
        System.out.println("\n=== 递归查找测试 ===");
        int recursiveIndex = linearSearchRecursive(arr, target);
        if (recursiveIndex != -1) {
            System.out.println("递归查找: 找到于索引 " + recursiveIndex);
        } else {
            System.out.println("递归查找: 未找到");
        }
        
        // 查找不存在的元素
        System.out.println("\n=== 查找不存在的元素 ===");
        int notFound = linearSearch(arr, 100);
        System.out.println("查找100: " + (notFound != -1 ? "找到" : "未找到"));
        
        // 泛型查找测试
        System.out.println("\n=== 泛型查找测试 ===");
        String[] strArr = {"apple", "banana", "cherry", "date", "banana"};
        String strTarget = "banana";
        
        System.out.println("字符串数组:");
        for (int i = 0; i < strArr.length; i++) {
            System.out.print(strArr[i] + " ");
        }
        System.out.println("\n目标字符串: " + strTarget);
        
        int strIndex = linearSearchGeneric(strArr, strTarget);
        if (strIndex != -1) {
            System.out.println("泛型查找: 找到于索引 " + strIndex);
        } else {
            System.out.println("泛型查找: 未找到");
        }
        
        List<Integer> strAllIndices = new ArrayList<>();
        for (int i = 0; i < strArr.length; i++) {
            if (strArr[i].equals(strTarget)) {
                strAllIndices.add(i);
            }
        }
        System.out.print("所有匹配位置: ");
        for (int i = 0; i < strAllIndices.size(); i++) {
            System.out.print(strAllIndices.get(i) + " ");
        }
        System.out.println("(共" + strAllIndices.size() + "个)");
        
        // 性能分析
        System.out.println("\n=== 线性查找特点 ===");
        System.out.println("• 算法简单，易于实现");
        System.out.println("• 适用于小规模数据和无序数据");
        System.out.println("• 时间复杂度：O(n)");
        System.out.println("• 空间复杂度：O(1)");
        System.out.println("• 可以查找所有匹配项");
        System.out.println("• 适合处理重复元素");
        
        // 与其他查找算法对比
        System.out.println("\n=== 与其他查找算法对比 ===");
        System.out.println("• 二分查找：O(log n)，但要求数组有序");
        System.out.println("• 哈希查找：O(1)，但需要额外空间");
        System.out.println("• 线性查找：O(n)，但无需预处理");
        System.out.println("• 选择算法取决于数据规模和是否有序");
    }
}

/*
打印结果
jarry@Mac linear-search % javac LinearSearch.java && java LinearSearch
=== 线性查找演示 ===

数组:
64 34 25 12 22 11 90 22 
目标元素: 22

=== 基本查找测试 ===
基本查找: 找到于索引 4

=== 查找所有匹配项 ===
所有匹配位置: 4 7 (共2个)

=== 反向查找测试 ===
反向查找: 找到于索引 7

=== 哨兵查找测试 ===
哨兵查找: 找到于索引 4

=== 递归查找测试 ===
递归查找: 找到于索引 4

=== 查找不存在的元素 ===
查找100: 未找到

=== 泛型查找测试 ===
字符串数组:
apple banana cherry date banana 
目标字符串: banana
泛型查找: 找到于索引 1
所有匹配位置: 1 4 (共2个)

=== 线性查找特点 ===
• 算法简单，易于实现
• 适用于小规模数据和无序数据
• 时间复杂度：O(n)
• 空间复杂度：O(1)
• 可以查找所有匹配项
• 适合处理重复元素

=== 与其他查找算法对比 ===
• 二分查找：O(log n)，但要求数组有序
• 哈希查找：O(1)，但需要额外空间
• 线性查找：O(n)，但无需预处理
• 选择算法取决于数据规模和是否有序
*/
