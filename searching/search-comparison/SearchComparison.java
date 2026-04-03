/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */

import java.util.*;

/**
 * 搜索算法类
 * 包含多种搜索算法实现
 */
public class SearchComparison {
    
    /**
     * linearSearch - 线性查找 - O(n)
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
     * @param {int[]} arr - 待搜索数组
     * @param {int} target - 目标值
     * @returns {int} 找到返回索引，未找到返回-1
     */
    public static int linearSearch(int[] arr, int target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }

    /**
     * binarySearch - 二分查找 - O(log n)，要求数组有序
     * 
     * 算法原理：
     * 1. 初始化左右边界：left=0, right=arr.length-1
     * 2. 计算中间位置：mid = (left + right) / 2
     * 3. 比较中间值与目标值
     * 4. 根据比较结果调整查找范围
     * 5. 重复直到找到目标或范围为空
     * 
     * @param {int[]} arr - 有序数组
     * @param {int} target - 目标值
     * @returns {int} 找到返回索引，未找到返回-1
     */
    public static int binarySearch(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }

    /**
     * jumpSearch - 跳跃查找 - O(√n)，要求数组有序
     * 
     * 算法原理：
     * 1. 计算跳跃步长：step = Math.sqrt(n)
     * 2. 按步长跳跃查找目标所在的块
     * 3. 在目标块内进行线性查找
     * 4. 结合跳跃和线性查找的优势
     * 
     * @param {int[]} arr - 有序数组
     * @param {int} target - 目标值
     * @returns {int} 找到返回索引，未找到返回-1
     */
    public static int jumpSearch(int[] arr, int target) {
        int n = arr.length;
        int step = (int) Math.sqrt(n);
        
        // 找到目标所在的块
        int prev = 0;
        while (arr[Math.min(step, n) - 1] < target) {
            prev = step;
            step += (int) Math.sqrt(n);
            if (prev >= n) {
                return -1;
            }
        }
        
        // 在线性搜索目标
        while (arr[prev] < target) {
            prev += 1;
            if (prev == Math.min(step, n)) {
                return -1;
            }
        }
        
        return (arr[prev] == target) ? prev : -1;
    }

    /**
     * exponentialSearch - 指数查找 - O(log n)，要求数组有序
     * 
     * 算法原理：
     * 1. 指数增长确定查找范围
     * 2. 在确定范围内进行二分查找
     * 3. 结合指数增长和二分查找的优势
     * 
     * @param {int[]} arr - 有序数组
     * @param {int} target - 目标值
     * @returns {int} 找到返回索引，未找到返回-1
     */
    public static int exponentialSearch(int[] arr, int target) {
        int n = arr.length;
        
        // 如果目标在第一个位置
        if (arr[0] == target) {
            return 0;
        }
        
        // 找到范围
        int bound = 1;
        while (bound < n && arr[bound] <= target) {
            bound *= 2;
        }
        
        // 在该范围内进行二分查找
        int left = bound / 2;
        int right = Math.min(bound, n - 1);
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }

    /**
     * interpolationSearch - 插值查找 - O(log log n)，要求数组均匀分布
     * 
     * 算法原理：
     * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
     * 2. 根据估算位置调整查找范围
     * 3. 重复直到找到目标或确定不存在
     * 
     * @param {int[]} arr - 有序数组
     * @param {int} target - 目标值
     * @returns {int} 找到返回索引，未找到返回-1
     */
    public static int interpolationSearch(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;
        
        while (low <= high && target >= arr[low] && target <= arr[high]) {
            if (low == high) {
                return (arr[low] == target) ? low : -1;
            }
            
            // 防止除零错误
            if (arr[high] == arr[low]) {
                break;
            }
            
            // 计算插值位置
            int pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);
            
            // 检查计算的位置是否有效
            if (pos < low || pos > high) {
                break;
            }
            
            if (arr[pos] == target) {
                return pos;
            }
            
            if (arr[pos] < target) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        
        return -1;
    }

    /**
     * hashSearch - 哈希查找 - O(1)，需要额外空间
     * 
     * 算法原理：
     * 1. 构建哈希表存储所有元素
     * 2. 通过哈希函数计算目标位置
     * 3. 直接访问对应位置
     * 
     * @param {int[]} arr - 待搜索数组
     * @param {int} target - 目标值
     * @returns {int} 找到返回索引，未找到返回-1
     */
    public static int hashSearch(int[] arr, int target) {
        // 构建哈希表
        Map<Integer, Integer> hashTable = new HashMap<>();
        for (int i = 0; i < arr.length; i++) {
            hashTable.put(arr[i], i);
        }
        
        Integer result = hashTable.get(target);
        return (result != null) ? result : -1;
    }

    /**
     * testAlgorithms - 测试所有搜索算法的性能
     * 
     * @param {int[]} arr - 有序数组
     * @param {int[]} unsortedArr - 无序数组
     * @param {int} target - 目标值
     */
    public static void testAlgorithms(int[] arr, int[] unsortedArr, int target) {
        System.out.println("\n数组大小: " + arr.length);
        System.out.println("查找目标: " + target);
        
        System.out.println("\n有序数组搜索算法对比:");
        System.out.println("------------------------------------------------------------");
        
        // 二分查找
        long startTime = System.currentTimeMillis();
        int result = binarySearch(arr, target);
        long endTime = System.currentTimeMillis();
        System.out.println("二分查找:     索引=" + result + ", 时间=" + (endTime - startTime) + "ms");
        
        // 跳跃查找
        startTime = System.currentTimeMillis();
        result = jumpSearch(arr, target);
        endTime = System.currentTimeMillis();
        System.out.println("跳跃查找:     索引=" + result + ", 时间=" + (endTime - startTime) + "ms");
        
        // 指数查找
        startTime = System.currentTimeMillis();
        result = exponentialSearch(arr, target);
        endTime = System.currentTimeMillis();
        System.out.println("指数查找:     索引=" + result + ", 时间=" + (endTime - startTime) + "ms");
        
        // 插值查找
        startTime = System.currentTimeMillis();
        result = interpolationSearch(arr, target);
        endTime = System.currentTimeMillis();
        System.out.println("插值查找:     索引=" + result + ", 时间=" + (endTime - startTime) + "ms");
        
        // 哈希查找
        startTime = System.currentTimeMillis();
        result = hashSearch(arr, target);
        endTime = System.currentTimeMillis();
        System.out.println("哈希查找:     索引=" + result + ", 时间=" + (endTime - startTime) + "ms");
        
        System.out.println("\n无序数组搜索:");
        System.out.println("------------------------------------------------------------");
        
        // 线性查找（无序数组）
        startTime = System.currentTimeMillis();
        result = linearSearch(unsortedArr, target);
        endTime = System.currentTimeMillis();
        System.out.println("线性查找:     索引=" + result + ", 时间=" + (endTime - startTime) + "ms");
    }

    /**
     * printAlgorithmSummary - 打印算法复杂度总结
     */
    public static void printAlgorithmSummary() {
        System.out.println("\n\n算法复杂度总结:");
        System.out.println("  线性查找:     O(n) - 无需预处理");
        System.out.println("  二分查找:     O(log n) - 需要有序");
        System.out.println("  跳跃查找:     O(√n) - 需要有序");
        System.out.println("  指数查找:     O(log n) - 需要有序");
        System.out.println("  插值查找:     O(log log n) - 需要均匀分布");
        System.out.println("  哈希查找:     O(1) - 需要额外空间");
        
        System.out.println("\n适用场景建议:");
        System.out.println("  • 小规模无序数据: 线性查找");
        System.out.println("  • 大规模有序数据: 二分查找");
        System.out.println("  • 均匀分布数据: 插值查找");
        System.out.println("  • 频繁查找操作: 哈希查找");
        System.out.println("  • 静态数据集合: 跳跃查找/指数查找");
    }

    /**
     * 主程序：演示搜索算法综合对比
     * 
     * @param {String[]} args - 命令行参数
     */
    public static void main(String[] args) {
        System.out.println("============================================================");
        System.out.println("搜索算法综合对比");
        System.out.println("============================================================");
        
        // 创建测试数据
        int n = 10000;
        int[] sortedArr = new int[n];
        int[] unsortedArr = new int[n];
        
        for (int i = 0; i < n; i++) {
            sortedArr[i] = i;
            unsortedArr[i] = n - 1 - i; // 逆序
        }
        
        int target = 9999;
        
        // 测试所有算法
        testAlgorithms(sortedArr, unsortedArr, target);
        
        // 打印总结
        printAlgorithmSummary();
    }
}

/*
打印结果
jarry@Mac search-comparison % javac SearchComparison.java && java SearchComparison
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0ms
跳跃查找:     索引=9999, 时间=0ms
指数查找:     索引=9999, 时间=0ms
插值查找:     索引=9999, 时间=0ms
哈希查找:     索引=9999, 时间=1ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=1ms

算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
*/
