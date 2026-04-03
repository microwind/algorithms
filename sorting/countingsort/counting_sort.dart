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

import 'dart:io';

/**
 * 打印数组内容的辅助函数
 */
void printArray(List<int> arr, String label) {
  print('$label: [${arr.join(', ')}]');
}

/**
 * 性能测试辅助函数
 */
void performanceTest(Function(List<int>) sortFunc, List<int> arr, String name) {
  // 创建数组副本，避免修改原数组
  List<int> testArr = List.from(arr);
  printArray(testArr, '${name}原始数组');
  
  // 开始计时
  Stopwatch stopwatch = Stopwatch()..start();
  sortFunc(testArr);
  stopwatch.stop();
  
  print('$name: ${stopwatch.elapsedMilliseconds.toDouble() / 1000.0}');
  printArray(testArr, '${name}排序结果');
  print(''); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含负数和重复元素的典型数组
const List<int> testData = [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80];

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
void countingSort1(List<int> arr) {
  print('countingSort1 standard:');
  
  if (arr.isEmpty) {
    return;
  }
  
  // 找到最小值和最大值
  int min = arr.reduce((a, b) => a < b ? a : b);
  int max = arr.reduce((a, b) => a > b ? a : b);
  int range = max - min + 1;
  
  // 创建计数数组
  List<int> count = List.filled(range, 0);
  
  // 统计每个元素出现的次数
  for (int i = 0; i < arr.length; i++) {
    count[arr[i] - min]++;
  }
  
  // 计算累计计数
  for (int i = 1; i < count.length; i++) {
    count[i] += count[i - 1];
  }
  
  // 创建输出数组
  List<int> output = List.filled(arr.length, 0);
  
  // 从后向前遍历，保证稳定性
  for (int i = arr.length - 1; i >= 0; i--) {
    int value = arr[i];
    int index = value - min;
    output[count[index] - 1] = value;
    count[index]--;
  }
  
  // 复制回原数组
  for (int i = 0; i < arr.length; i++) {
    arr[i] = output[i];
  }
  
  printArray(arr, '排序后数组');
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
void countingSort2(List<int> arr) {
  print('countingSort2 memory optimized:');
  
  if (arr.isEmpty) {
    return;
  }
  
  // 找到最小值和最大值
  int min = arr.reduce((a, b) => a < b ? a : b);
  int max = arr.reduce((a, b) => a > b ? a : b);
  int range = max - min + 1;
  
  // 创建计数数组
  List<int> count = List.filled(range, 0);
  
  // 统计每个元素出现的次数
  for (int value in arr) {
    count[value - min]++;
  }
  
  // 直接根据计数重构数组
  int index = 0;
  for (int i = 0; i < count.length; i++) {
    int remaining = count[i];
    while (remaining > 0) {
      arr[index] = i + min;
      index++;
      remaining--;
    }
  }
  
  printArray(arr, '排序后数组');
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
void countingSort3(List<int> arr) {
  print('countingSort3 negative numbers:');
  
  if (arr.isEmpty) {
    return;
  }
  
  // 分离正数和负数
  List<int> negatives = [];
  List<int> positives = [];
  
  for (int value in arr) {
    if (value < 0) {
      negatives.add(value);
    } else {
      positives.add(value);
    }
  }
  
  // 排序负数部分（转换为绝对值排序后反转）
  if (negatives.isNotEmpty) {
    List<int> absNegatives = negatives.map((x) => -x).toList();
    
    // 使用独立的计数排序逻辑
    if (absNegatives.isNotEmpty) {
      // 找到最小值和最大值
      int min = absNegatives.reduce((a, b) => a < b ? a : b);
      int max = absNegatives.reduce((a, b) => a > b ? a : b);
      int range = max - min + 1;
      
      // 创建计数数组
      List<int> count = List.filled(range, 0);
      
      // 统计每个元素出现的次数
      for (int i = 0; i < absNegatives.length; i++) {
        count[absNegatives[i] - min]++;
      }
      
      // 计算累计计数
      for (int i = 1; i < count.length; i++) {
        count[i] += count[i - 1];
      }
      
      // 创建输出数组
      List<int> output = List.filled(absNegatives.length, 0);
      
      // 从后向前遍历，保证稳定性
      for (int i = absNegatives.length - 1; i >= 0; i--) {
        int value = absNegatives[i];
        int index = value - min;
        output[count[index] - 1] = value;
        count[index]--;
      }
      
      // 反转并恢复负号
      for (int i = 0; i < output.length; i++) {
        negatives[i] = -output[output.length - 1 - i];
      }
    }
  }
  
  // 排序正数部分
  if (positives.isNotEmpty) {
    // 使用独立的计数排序逻辑
    if (positives.isNotEmpty) {
      // 找到最小值和最大值
      int min = positives.reduce((a, b) => a < b ? a : b);
      int max = positives.reduce((a, b) => a > b ? a : b);
      int range = max - min + 1;
      
      // 创建计数数组
      List<int> count = List.filled(range, 0);
      
      // 统计每个元素出现的次数
      for (int i = 0; i < positives.length; i++) {
        count[positives[i] - min]++;
      }
      
      // 计算累计计数
      for (int i = 1; i < count.length; i++) {
        count[i] += count[i - 1];
      }
      
      // 创建输出数组
      List<int> output = List.filled(positives.length, 0);
      
      // 从后向前遍历，保证稳定性
      for (int i = positives.length - 1; i >= 0; i--) {
        int value = positives[i];
        int index = value - min;
        output[count[index] - 1] = value;
        count[index]--;
      }
      
      // 复制回正数数组
      for (int i = 0; i < output.length; i++) {
        positives[i] = output[i];
      }
    }
  }
  
  // 合并结果
  List<int> result = [];
  result.addAll(negatives);
  result.addAll(positives);
  
  // 复制回原数组
  for (int i = 0; i < arr.length; i++) {
    arr[i] = result[i];
  }
  
  printArray(arr, '排序后数组');
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
 * 提高处理稀疏数据的效率
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
void countingSort4(List<int> arr) {
  print('countingSort4 bucket optimized:');
  
  if (arr.isEmpty) {
    return;
  }
  
  // 找到最小值和最大值
  int min = arr.reduce((a, b) => a < b ? a : b);
  int max = arr.reduce((a, b) => a > b ? a : b);
  int range = max - min + 1;
  
  // 确定桶的大小（可以调整以优化性能）
  int bucketSize = (range / 10).clamp(1, double.infinity).toInt();
  int bucketCount = ((range + bucketSize - 1) / bucketSize).clamp(5, double.infinity).toInt();
  
  // 创建桶
  List<List<int>> buckets = List.generate(bucketCount, (_) => []);
  
  // 将元素分配到桶中
  for (int value in arr) {
    int bucketIndex;
    if (value == max) {
      bucketIndex = bucketCount - 1;
    } else {
      bucketIndex = (value - min) ~/ bucketSize;
    }
    buckets[bucketIndex].add(value);
  }
  
  // 对每个桶进行排序并合并结果
  List<int> result = [];
  
  for (int i = 0; i < bucketCount; i++) {
    if (buckets[i].isNotEmpty) {
      // 使用独立的计数排序逻辑
      List<int> bucketArray = List.from(buckets[i]);
      
      if (bucketArray.isNotEmpty) {
        // 找到最小值和最大值
        int min = bucketArray.reduce((a, b) => a < b ? a : b);
        int max = bucketArray.reduce((a, b) => a > b ? a : b);
        int range = max - min + 1;
        
        // 创建计数数组
        List<int> count = List.filled(range, 0);
        
        // 统计每个元素出现的次数
        for (int j = 0; j < bucketArray.length; j++) {
          count[bucketArray[j] - min]++;
        }
        
        // 计算累计计数
        for (int j = 1; j < count.length; j++) {
          count[j] += count[j - 1];
        }
        
        // 创建输出数组
        List<int> output = List.filled(bucketArray.length, 0);
        
        // 从后向前遍历，保证稳定性
        for (int j = bucketArray.length - 1; j >= 0; j--) {
          int value = bucketArray[j];
          int index = value - min;
          output[count[index] - 1] = value;
          count[index]--;
        }
        
        // 复制回桶数组
        for (int j = 0; j < output.length; j++) {
          bucketArray[j] = output[j];
        }
      }
      
      // 将排序后的桶内容复制到结果数组
      result.addAll(bucketArray);
    }
  }
  
  // 复制回原数组
  for (int i = 0; i < arr.length; i++) {
    arr[i] = result[i];
  }
  
  printArray(arr, '排序后数组');
}

// ==================== 算法测试和性能对比 ====================

void main() {
  // 测试1：标准版本
  performanceTest(countingSort1, testData, '标准版本');

  // 测试2：内存优化版本
  performanceTest(countingSort2, testData, '内存优化版本');

  // 测试3：负数处理版本
  performanceTest(countingSort3, testData, '负数处理版本');

  // 测试4：桶优化版本
  performanceTest(countingSort4, testData, '桶优化版本');

  print('=== 算法对比总结 ===');
  print('1. 标准版本：经典实现，稳定排序');
  print('2. 内存优化版本：原地修改，节省空间');
  print('3. 负数处理版本：支持负数，功能完整');
  print('4. 桶优化版本：分组处理，适合稀疏数据');
}

/*
打印结果
jarry@Mac heapsort % dart heap_sort.dart    
heapSort1 max-heap原始数组: 7, 11, 9, 10, 12, 13, 8
heapSort1 max-heap:
oringal array:
              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  12(4)  13(5)  8(6)

父节点步骤
1. maxHeapify: idx= 2 left= 5 right= 6 max= 5 size= 7

              7(0)
          /         \
        11(1)        13(2)
       /    \      /     \
   10(3)  12(4)  9(5)  8(6)

3. maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 7

              7(0)
          /         \
        12(1)        13(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

5. maxHeapify: idx= 0 left= 1 right= 2 max= 2 size= 7

              13(0)
          /         \
        12(1)        7(2)
       /    \      /     \
   10(3)  11(4)  9(5)  8(6)

5.1 maxHeapify: idx= 5 left= 11 right= 12 max= 5 size= 7

              13(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  8(6)

子节点堆排序:
7. swap, child = 6:

              8(0)
          /         \
        12(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.1 maxHeapify: idx= 1 left= 3 right= 4 max= 4 size= 6

              12(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  7(5)  13(6)

7.1 maxHeapify: idx= 4 left= 9 right= 10 max= 4 size= 6

              12(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  7(5)  13(6)

8. swap, child = 5:

              7(0)
          /         \
        11(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.1 maxHeapify: idx= 1 left= 3 right= 4 max= 3 size= 5

              11(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  8(4)  12(5)  13(6)

8.1 maxHeapify: idx= 3 left= 7 right= 8 max= 3 size= 5

              11(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  8(4)  12(5)  13(6)

9. swap, child = 4:

              8(0)
          /         \
        10(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

9.1 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 4

              10(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   7(3)  11(4)  12(5)  13(6)

10. swap, child = 3:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

10.1 maxHeapify: idx= 2 left= 5 right= 6 max= 2 size= 3

              9(0)
          /         \
        8(1)        7(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11. swap, child = 2:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

11.1 maxHeapify: idx= 1 left= 3 right= 4 max= 1 size= 2

              8(0)
          /         \
        7(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

12. swap, child = 1:

              7(0)
          /         \
        8(1)        9(2)
       /    \      /     \
   10(3)  11(4)  12(5)  13(6)

排序后数组: 7, 8, 9, 10, 11, 12, 13
heapSort1 max-heap: 0.000ms
heapSort1 max-heap排序结果: 7, 8, 9, 10, 11, 12, 13

heapSort2 min-heap原始数组: 7, 11, 9, 10, 12, 13, 8
heapSort2 min-heap:
排序后数组: 7, 8, 9, 10, 11, 12, 13
heapSort2 min-heap: 0.000ms
heapSort2 min-heap排序结果: 7, 8, 9, 10, 11, 12, 13

heapSort3 iterative原始数组: 7, 11, 9, 10, 12, 13, 8
heapSort3 iterative:
排序后数组: 7, 8, 9, 10, 11, 12, 13
heapSort3 iterative: 0.000ms
heapSort3 iterative排序结果: 7, 8, 9, 10, 11, 12, 13

heapSort4 bottom-up原始数组: 7, 11, 9, 10, 12, 13, 8
heapSort4 bottom-up:
排序后数组: 7, 8, 9, 10, 11, 12, 13
heapSort4 bottom-up: 0.000ms
heapSort4 bottom-up排序结果: 7, 8, 9, 10, 11, 12, 13

heapSort5 non-recursive原始数组: 7, 11, 9, 10, 12, 13, 8
heapSort5 non-recursive:
current= 9  idx= 2  child= 5  size= 7
parent sort: 2 
: 7, 11, 13, 10, 12, 9, 8
current= 11  idx= 1  child= 3  size= 7
parent sort: 1 
: 7, 12, 13, 10, 11, 9, 8
current= 7  idx= 0  child= 1  size= 7
current= 7  idx= 2  child= 5  size= 7
parent sort: 0 
: 13, 12, 9, 10, 11, 7, 8
child start: parent=-1  child=6
current= 8  idx= 0  child= 1  size= 6
current= 8  idx= 1  child= 3  size= 6
child sort: 6 
: 12, 11, 9, 10, 8, 7, 13
current= 7  idx= 0  child= 1  size= 5
current= 7  idx= 1  child= 3  size= 5
child sort: 5 
: 11, 10, 9, 7, 8, 12, 13
current= 8  idx= 0  child= 1  size= 4
current= 8  idx= 1  child= 3  size= 4
child sort: 4 
: 10, 8, 9, 7, 11, 12, 13
current= 7  idx= 0  child= 1  size= 3
child sort: 3 
: 9, 8, 7, 10, 11, 12, 13
current= 7  idx= 0  child= 1  size= 2
child sort: 2 
: 8, 7, 9, 10, 11, 12, 13
child sort: 1 
: 7, 8, 9, 10, 11, 12, 13
排序后数组: 7, 8, 9, 10, 11, 12, 13
heapSort5 non-recursive: 0.000ms
heapSort5 non-recursive排序结果: 7, 8, 9, 10, 11, 12, 13

=== 算法对比总结 ===
1. heapSort1 max-heap：经典实现，升序排序
2. heapSort2 min-heap：反向思维，直观易懂
3. heapSort3 iterative：避免递归，性能优化
4. heapSort4 bottom-up：高效构建，减少比较
5. heapSort5 non-recursive：非递归堆化，父子节点计算函数
*/
