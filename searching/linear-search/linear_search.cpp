/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 线性查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

#include <iostream>
#include <vector>
#include <chrono>

/**
 * linearSearch1 - 基本线性查找 - 查找第一个匹配项
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
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linearSearch1(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i; // 找到目标，返回索引
        }
    }
    return -1; // 未找到
}

/**
 * linearSearch2 - 查找所有匹配项
 * 
 * 算法思路：
 * 遍历整个数组，收集所有匹配项的索引
 * 适合处理重复元素的情况
 * 
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @param result - 存储匹配索引的数组
 * @return 匹配项的数量
 */
int linearSearch2(const std::vector<int>& arr, int target, std::vector<int>& result) {
    int count = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            result.push_back(i); // 收集匹配索引
            count++;
        }
    }
    return count; // 返回匹配数量
}

/**
 * linearSearch3 - 带哨兵的线性查找
 * 
 * 算法优化：
 * 在数组末尾设置哨兵（目标值）
 * 减少每次循环中的边界检查
 * 可以略微提高性能
 * 
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linearSearch3(const std::vector<int>& arr, int target) {
    std::vector<int> tempArr = arr; // 复制数组以避免修改原数组
    int last = tempArr.back(); // 保存最后一个元素
    tempArr.back() = target; // 设置哨兵
    
    int i = 0;
    while (tempArr[i] != target) {
        i++;
    }
    
    tempArr.back() = last; // 恢复最后一个元素
    
    if (i < tempArr.size() - 1 || tempArr.back() == target) {
        return i;
    }
    return -1;
}

/**
 * linearSearch4 - 反向线性查找
 * 
 * 算法思路：
 * 从数组末尾开始向前查找
 * 适用于目标值可能在末尾的情况
 * 
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linearSearch4(const std::vector<int>& arr, int target) {
    for (int i = arr.size() - 1; i >= 0; i--) {
        if (arr[i] == target) {
            return i; // 从后往前找到的第一个匹配项
        }
    }
    return -1;
}

/**
 * linearSearch5 - 双向线性查找
 * 
 * 算法思路：
 * 同时从数组两端向中间查找
 * 适用于大型数组，可能减少平均查找时间
 * 
 * @param arr - 待搜索数组
 * @param target - 目标值
 * @return 找到返回索引，未找到返回-1
 */
int linearSearch5(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        if (arr[left] == target) {
            return left; // 左侧找到
        }
        if (arr[right] == target) {
            return right; // 右侧找到
        }
        left++;
        right--;
    }
    
    return -1;
}

/**
 * testLinearSearch - 测试线性查找算法
 * 
 * 测试内容：
 * 1. 基本查找 - 查找第一个匹配项
 * 2. 查找所有匹配项 - 处理重复元素
 * 3. 带哨兵查找 - 优化版本
 * 4. 反向查找 - 从后往前
 * 5. 双向查找 - 两端同时进行
 */
void testLinearSearch() {
    std::cout << "=== 线性查找演示 ===" << std::endl;
    
    // 测试数据
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90, 22};
    int target = 22;
    
    std::cout << "\n数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\n目标元素: " << target << std::endl;
    
    // 1. 基本查找测试
    std::cout << "\n1. 基本查找测试:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    int index = linearSearch1(arr, target);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time1 = end - start;
    
    if (index != -1) {
        std::cout << "基本查找: 找到于索引 " << index 
                 << ", 时间=" << time1.count() << "ms" << std::endl;
    } else {
        std::cout << "基本查找: 未找到" 
                 << ", 时间=" << time1.count() << "ms" << std::endl;
    }
    
    // 2. 查找所有匹配项
    std::cout << "\n2. 查找所有匹配项:" << std::endl;
    std::vector<int> results;
    start = std::chrono::high_resolution_clock::now();
    int count = linearSearch2(arr, target, results);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time2 = end - start;
    
    std::cout << "所有匹配位置: ";
    for (int pos : results) {
        std::cout << pos << " ";
    }
    std::cout << "(共" << count << "个)" 
             << ", 时间=" << time2.count() << "ms" << std::endl;
    
    // 3. 带哨兵查找
    std::cout << "\n3. 带哨兵查找:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    int sentinelResult = linearSearch3(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time3 = end - start;
    
    if (sentinelResult != -1) {
        std::cout << "哨兵查找: 找到于索引 " << sentinelResult 
                 << ", 时间=" << time3.count() << "ms" << std::endl;
    } else {
        std::cout << "哨兵查找: 未找到" 
                 << ", 时间=" << time3.count() << "ms" << std::endl;
    }
    
    // 4. 反向查找
    std::cout << "\n4. 反向查找:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    int reverseResult = linearSearch4(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time4 = end - start;
    
    if (reverseResult != -1) {
        std::cout << "反向查找: 找到于索引 " << reverseResult 
                 << " (从后往前第一个)" 
                 << ", 时间=" << time4.count() << "ms" << std::endl;
    } else {
        std::cout << "反向查找: 未找到" 
                 << ", 时间=" << time4.count() << "ms" << std::endl;
    }
    
    // 5. 双向查找
    std::cout << "\n5. 双向查找:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    int bidirectionalResult = linearSearch5(arr, target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time5 = end - start;
    
    if (bidirectionalResult != -1) {
        std::cout << "双向查找: 找到于索引 " << bidirectionalResult 
                 << ", 时间=" << time5.count() << "ms" << std::endl;
    } else {
        std::cout << "双向查找: 未找到" 
                 << ", 时间=" << time5.count() << "ms" << std::endl;
    }
    
    // 6. 查找不存在的元素
    std::cout << "\n6. 查找不存在的元素:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    int notFound = linearSearch1(arr, 100);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time6 = end - start;
    
    std::cout << "查找100: " << (notFound != -1 ? "找到" : "未找到") 
             << ", 时间=" << time6.count() << "ms" << std::endl;
    
    // 算法特点说明
    std::cout << "\n=== 线性查找特点 ===" << std::endl;
    std::cout << "• 算法简单，易于实现" << std::endl;
    std::cout << "• 适用于小规模数据和无序数据" << std::endl;
    std::cout << "• 时间复杂度：O(n)" << std::endl;
    std::cout << "• 空间复杂度：O(1)" << std::endl;
    std::cout << "• 可以查找所有匹配项" << std::endl;
    std::cout << "• 适合处理重复元素" << std::endl;
    std::cout << "• 优化版本：哨兵查找、双向查找" << std::endl;
}

/**
 * 主程序：演示线性查找功能
 */
int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "线性查找算法演示" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    testLinearSearch();
    
    return 0;
}

/*
打印结果
jarry@Mac linear-search % g++ linear_search.cpp && ./a.out
============================================================
线性查找算法演示
============================================================
=== 线性查找演示 ===

数组: 64 34 25 12 22 11 90 22 
目标元素: 22

1. 基本查找测试:
基本查找: 找到于索引 4, 时间=0.001ms

2. 查找所有匹配项:
所有匹配位置: 4 7 (共2个), 时间=0.001ms

3. 带哨兵查找:
哨兵查找: 找到于索引 4, 时间=0ms

4. 反向查找:
反向查找: 找到于索引 7 (从后往前第一个), 时间=0.001ms

5. 双向查找:
双向查找: 找到于索引 4, 时间=0ms

6. 查找不存在的元素:
查找100: 未找到, 时间=0ms

=== 线性查找特点 ===
• 算法简单，易于实现
• 适用于小规模数据和无序数据
• 时间复杂度：O(n)
• 空间复杂度：O(1)
• 可以查找所有匹配项
• 适合处理重复元素
• 优化版本：哨兵查找、双向查找
*/
