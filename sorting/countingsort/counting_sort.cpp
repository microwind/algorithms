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

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

/**
 * 打印数组内容的辅助函数
 */
void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": [";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "]" << std::endl;
}

/**
 * 性能测试辅助函数
 */
void performanceTest(void (*sortFunc)(std::vector<int>&), const std::vector<int>& arr, const std::string& name) {
    // 创建数组副本，避免修改原数组
    std::vector<int> testArr = arr;
    printArray(testArr, name + "原始数组");
    
    // 开始计时
    auto startTime = std::chrono::high_resolution_clock::now();
    sortFunc(testArr);
    auto endTime = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << name << ": " << duration.count() / 1000.0 << "ms" << std::endl;
    printArray(testArr, name + "排序结果");
    std::cout << std::endl; // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含负数和重复元素的典型数组
const std::vector<int> testData = {20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80};

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
void countingSort1(std::vector<int>& arr) {
    std::cout << "countingSort1 standard:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    // 创建计数数组
    std::vector<int> count(range, 0);
    
    // 统计每个元素出现的次数
    for (int i = 0; i < arr.size(); ++i) {
        count[arr[i] - minVal]++;
    }
    
    // 计算累计计数
    for (int i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }
    
    // 创建输出数组
    std::vector<int> output(arr.size());
    
    // 从后向前遍历，保证稳定性
    for (int i = arr.size() - 1; i >= 0; --i) {
        int index = arr[i] - minVal;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }
    
    // 复制回原数组
    arr = output;
    
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
void countingSort2(std::vector<int>& arr) {
    std::cout << "countingSort2 memory optimized:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    // 创建计数数组
    std::vector<int> count(range, 0);
    
    // 统计每个元素出现的次数
    for (int i = 0; i < arr.size(); ++i) {
        count[arr[i] - minVal]++;
    }
    
    // 直接根据计数重构数组
    int index = 0;
    for (int i = 0; i < count.size(); ++i) {
        while (count[i] > 0) {
            arr[index] = i + minVal;
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
void countingSort3(std::vector<int>& arr) {
    std::cout << "countingSort3 negative numbers:" << std::endl;
    
    if (arr.empty()) return;
    
    // 分离正数和负数
    std::vector<int> negatives;
    std::vector<int> positives;
    
    for (int value : arr) {
        if (value < 0) {
            negatives.push_back(value);
        } else {
            positives.push_back(value);
        }
    }
    
    // 排序负数部分（转换为绝对值排序后反转）
    if (!negatives.empty()) {
        std::vector<int> absNegatives;
        for (int neg : negatives) {
            absNegatives.push_back(-neg);
        }
        
        // 使用独立的计数排序逻辑
        if (!absNegatives.empty()) {
            // 找到最小值和最大值
            int minAbs = *std::min_element(absNegatives.begin(), absNegatives.end());
            int maxAbs = *std::max_element(absNegatives.begin(), absNegatives.end());
            int rangeAbs = maxAbs - minAbs + 1;
            
            // 创建计数数组
            std::vector<int> count(rangeAbs, 0);
            
            // 统计每个元素出现的次数
            for (int i = 0; i < absNegatives.size(); ++i) {
                count[absNegatives[i] - minAbs]++;
            }
            
            // 计算累计计数
            for (int i = 1; i < count.size(); ++i) {
                count[i] += count[i - 1];
            }
            
            // 创建输出数组
            std::vector<int> output(absNegatives.size());
            
            // 从后向前遍历，保证稳定性
            for (int i = absNegatives.size() - 1; i >= 0; --i) {
                int index = absNegatives[i] - minAbs;
                output[count[index] - 1] = absNegatives[i];
                count[index]--;
            }
            
            // 反转并恢复负号
            for (int i = 0; i < output.size(); ++i) {
                negatives[i] = -output[output.size() - 1 - i];
            }
        }
    }
    
    // 排序正数部分
    if (!positives.empty()) {
        // 使用独立的计数排序逻辑
        if (!positives.empty()) {
            // 找到最小值和最大值
            int minPos = *std::min_element(positives.begin(), positives.end());
            int maxPos = *std::max_element(positives.begin(), positives.end());
            int rangePos = maxPos - minPos + 1;
            
            // 创建计数数组
            std::vector<int> count(rangePos, 0);
            
            // 统计每个元素出现的次数
            for (int i = 0; i < positives.size(); ++i) {
                count[positives[i] - minPos]++;
            }
            
            // 计算累计计数
            for (int i = 1; i < count.size(); ++i) {
                count[i] += count[i - 1];
            }
            
            // 创建输出数组
            std::vector<int> output(positives.size());
            
            // 从后向前遍历，保证稳定性
            for (int i = positives.size() - 1; i >= 0; --i) {
                int index = positives[i] - minPos;
                output[count[index] - 1] = positives[i];
                count[index]--;
            }
            
            // 复制回正数数组
            for (int i = 0; i < output.size(); ++i) {
                positives[i] = output[i];
            }
        }
    }
    
    // 合并结果
    std::vector<int> result;
    result.insert(result.end(), negatives.begin(), negatives.end());
    result.insert(result.end(), positives.begin(), positives.end());
    
    // 复制回原数组
    arr = result;
    
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
void countingSort4(std::vector<int>& arr) {
    std::cout << "countingSort4 bucket optimized:" << std::endl;
    
    if (arr.empty()) return;
    
    // 找到最小值和最大值
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    // 确定桶的大小（可以调整以优化性能）
    int bucketSize = std::max(1, range / 10);
    int bucketCount = (range + bucketSize - 1) / bucketSize;
    
    // 创建桶
    std::vector<std::vector<int>> buckets(bucketCount);
    
    // 将元素分配到桶中
    for (int i = 0; i < arr.size(); ++i) {
        int bucketIndex = (arr[i] - minVal) / bucketSize;
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // 对每个桶进行排序并合并结果
    std::vector<int> result;
    for (int i = 0; i < bucketCount; ++i) {
        if (!buckets[i].empty()) {
            // 使用独立的计数排序逻辑
            std::vector<int>& bucket = buckets[i];
            
            if (!bucket.empty()) {
                // 找到桶内最小值和最大值
                int minBucket = *std::min_element(bucket.begin(), bucket.end());
                int maxBucket = *std::max_element(bucket.begin(), bucket.end());
                int rangeBucket = maxBucket - minBucket + 1;
                
                // 创建计数数组
                std::vector<int> count(rangeBucket, 0);
                
                // 统计每个元素出现的次数
                for (int j = 0; j < bucket.size(); ++j) {
                    count[bucket[j] - minBucket]++;
                }
                
                // 计算累计计数
                for (int j = 1; j < count.size(); ++j) {
                    count[j] += count[j - 1];
                }
                
                // 创建输出数组
                std::vector<int> output(bucket.size());
                
                // 从后向前遍历，保证稳定性
                for (int j = bucket.size() - 1; j >= 0; --j) {
                    int index = bucket[j] - minBucket;
                    output[count[index] - 1] = bucket[j];
                    count[index]--;
                }
                
                // 复制回桶
                for (int j = 0; j < output.size(); ++j) {
                    bucket[j] = output[j];
                }
            }
            
            // 将排序后的桶内容复制回原数组
            for (int j = 0; j < buckets[i].size(); ++j) {
                result.push_back(buckets[i][j]);
            }
        }
    }
    
    // 复制回原数组
    arr = result;
    
    printArray(arr, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：标准版本
    performanceTest(countingSort1, testData, "标准版本");

    // 测试2：内存优化版本
    performanceTest(countingSort2, testData, "内存优化版本");

    // 测试3：负数处理版本
    performanceTest(countingSort3, testData, "负数处理版本");

    // 测试4：桶优化版本
    performanceTest(countingSort4, testData, "桶优化版本");

    std::cout << "=== 算法对比总结 ===" << std::endl;
    std::cout << "1. 标准版本：经典实现，稳定排序" << std::endl;
    std::cout << "2. 内存优化版本：原地修改，节省空间" << std::endl;
    std::cout << "3. 负数处理版本：支持负数，功能完整" << std::endl;
    std::cout << "4. 桶优化版本：分组处理，适合稀疏数据" << std::endl;

    return 0;
}

/*
打印结果
jarry@Mac countingsort % g++ counting_sort.cpp -o counting_sort && ./counting_sort
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 0.009ms
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.007ms
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
countingSort1 standard:
排序后数组: [10]
countingSort1 standard:
排序后数组: [0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.019ms
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
桶优化版本: 0.031ms
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
