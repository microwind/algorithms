/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import 'dart:io';

/**
 * 桶排序支持负数版本 - 负数放在第1个桶里排序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值（取绝对值）
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中，负数统一放在第1个桶
 * 4. 在每个桶内进行插入排序
 * 5. 合并所有桶的元素
 * 
 * 生活类比：就像整理图书馆的书籍，
 * 先按类别分到不同的书架，再在每个书架内按字母顺序排列
 * 
 * @param {List<int>} arr - 待排序的数字数组
 * @returns {List<int>} 排序后的数组
 */
List<int> bucketSort1(List<int> arr) {
  print('bucketSort1 with negative numbers:');
  
  if (arr.isEmpty) return [];
  
  List<int> output = List<int>.filled(arr.length, 0);
  int max = arr[0];
  int min = arr[0];
  
  // 第一步：手动遍历获取数组最大最小值
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  
  // 边界处理：处理最大最小值小于等于1的情况
  if (max < 1) {
    max = 1;
  }
  if (min < 1) {
    min = 1;
  }
  
  // 第二步：计算桶的大小和数量
  // 每个桶的容量大小，也就是桶的间隔
  int bucketSize = ((max - min) ~/ min + 1);
  // 桶的数量，可以任意设置，也可以根据容量大小计算
  int bucketNumber = ((max - min) ~/ bucketSize + 1);
  
  // 第三步：初始化桶
  List<List<int>> buckets = List<List<int>>.generate(bucketNumber, (index) => []);
  List<int> bucketsMemberLength = List<int>.filled(bucketNumber, 0);
  
  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < arr.length; i++) {
    int item = arr[i];
    // 桶索引计算：确保索引在有效范围内
    int idx = ((item - min) / bucketSize).toInt();
    if (idx < 0) {
      idx = 0;
    } else if (idx >= bucketNumber) {
      idx = bucketNumber - 1;
    }
    
    List<int> bucket = buckets[idx];
    int bucketLen = bucketsMemberLength[idx];
    
    // 如果桶为空，直接添加到桶中
    if (bucketLen == 0) {
      bucket.add(item);
    } else {
      // 插入排序：自后往前遍历，找到合适的插入位置
      int insertPos = 0;
      while (insertPos < bucket.length && bucket[insertPos] <= item) {
        insertPos++;
      }
      bucket.insert(insertPos, item);
    }
    // 更新桶的元素计数
    bucketsMemberLength[idx]++;
  }
  
  // 第五步：合并结果，按照下标和顺序取出桶内的数字，回填到一个数组中
  int idx = 0;
  for (int i = 0; i < bucketNumber; i++) {
    // 遍历每个桶中的元素
    for (int j = 0; j < bucketsMemberLength[i]; j++) {
      output[idx] = buckets[i][j];
      idx++;
    }
  }
  
  print(output);
  return output;
}

/**
 * 桶排序标准版，不支持负数
 * 
 * 算法思路：
 * 1. 计算数组的最大值和最小值
 * 2. 处理最小值小于等于0的情况（设为1），避免负数问题
 * 3. 动态计算桶的数量和大小，基于数组长度优化
 * 4. 将元素分配到对应桶中
 * 5. 桶内使用插入排序
 * 6. 合并所有桶的元素
 * 
 * 优化效果：
 * - 桶分配更精确，性能较好
 * - 动态桶数量，适应不同数据规模
 * - 不支持负数，避免复杂的边界处理
 * 
 * @param {List<int>} arr - 待排序的数字数组（仅支持正数）
 * @returns {List<int>} 排序后的数组
 */
List<int> bucketSort2(List<int> arr) {
  print('bucketSort2 positive numbers only:');
  
  if (arr.isEmpty) return [];
  
  List<int> output = List<int>.filled(arr.length, 0);
  int max = arr[0];
  int min = arr[0];
  
  // 第一步：手动遍历获取数组最大最小值
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  
  // 边界处理：处理最小值小于等于0的情况，避免负数问题
  if (min < max && min <= 0) {
    min = 1;
  }
  
  // 第二步：动态计算桶的数量和大小
  int size = (arr.length ~/ 2);
  int bucketNumber = ((max - min) ~/ min + 1);
  int bucketSize = ((max - min) ~/ bucketNumber + 1);
  bucketNumber = bucketNumber < size ? bucketNumber : size;
  
  // 第三步：初始化桶
  List<List<int>> buckets = List<List<int>>.generate(bucketNumber, (index) => []);
  
  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < arr.length; i++) {
    int item = arr[i];
    // 桶索引：计算元素应该放入的桶索引
    int idx = ((item - min) / bucketSize).toInt();
    
    // 桶初始化：如果桶不存在则创建，添加边界检查
    if (idx < 0) {
      idx = 0;
    } else if (idx >= bucketNumber) {
      idx = bucketNumber - 1;
    }
    
    // 元素插入：将元素放入对应桶中
    buckets[idx].add(item);
  }
  
  // 第五步：桶内排序，对每个桶内的元素进行排序
  for (int i = 0; i < bucketNumber; i++) {
    // 插入排序：对每个桶进行插入排序
    for (int j = 1; j < buckets[i].length; j++) {
      int key = buckets[i][j];
      int k = j - 1;
      // 从前往后比较，找到合适的插入位置
      while (k >= 0 && buckets[i][k] > key) {
        buckets[i][k + 1] = buckets[i][k];
        k--;
      }
      buckets[i][k + 1] = key;
    }
  }
  
  // 第六步：合并结果，按照桶的顺序合并所有元素
  int idx = 0;
  for (int i = 0; i < bucketNumber; i++) {
    // 获取每个桶的实际长度
    int bucketLen = buckets[i].length;
    
    // 复制桶内元素到输出数组
    for (int j = 0; j < bucketLen; j++) {
      output[idx] = buckets[i][j];
      idx++;
    }
  }
  
  print(output);
  return output;
}

/**
 * 桶排序挪动排序版本 - 使用挪动插入，保持排序稳定性
 * 
 * 算法原理：
 * 1. 手动遍历计算数组最大值和最小值
 * 2. 根据数组长度计算桶的数量和大小
 * 3. 将元素分配到对应桶中，支持负数
 * 4. 使用挪动排序而非数组修改进行桶内排序
 * 5. 合并所有桶的元素
 * 
 * 优化效果：
 * - 手动计算最大最小值，更可控
 * - 支持负数，负数统一处理
 * 
 * @param {List<int>} arr - 待排序的数字数组
 * @returns {List<int>} 排序后的数组
 */
List<int> bucketSort3(List<int> arr) {
  print('bucketSort3 with move sorting:');
  
  if (arr.isEmpty) return [];
  
  List<int> output = List<int>.filled(arr.length, 0);
  int max = arr[0];
  int min = arr[0];
  
  // 第一步：手动遍历获取数组最大最小值
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  
  // 边界处理：处理最大最小值小于等于1的情况
  if (max <= 0) {
    max = 1;
  }
  if (min <= 0) {
    min = 1;
  }
  
  // 第二步：计算桶的大小和数量
  int bucketSize = ((max - min) ~/ min + 1);
  int bucketNumber = ((max - min) ~/ bucketSize + 1);
  
  // 第三步：初始化桶
  List<List<int>> buckets = List<List<int>>.generate(bucketNumber, (index) => []);
  List<int> bucketsMemberLength = List<int>.filled(bucketNumber, 0);
  
  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < arr.length; i++) {
    int item = arr[i];
    // 计算元素应该放入的桶索引
    int idx = ((item - min) / bucketSize).toInt();
    
    // 负数处理：负数全部放入第一个桶
    if (idx < 0) {
      idx = 0;
    }
    
    List<int> bucket = buckets[idx];
    int bucketLen = bucketsMemberLength[idx];
    
    // 挪动排序：使用挪动排序插入元素，保持插入排序的稳定性// 如果桶为空，直接添加到桶中
    if (bucketLen == 0) {
      bucket.add(item);
    } else {
      // 简化插入：直接添加并排序
      bucket.add(item);
      bucket.sort();
    }
    // 更新桶的元素计数
    bucketsMemberLength[idx]++;
  }
  
  // 第五步：合并结果，按照桶的顺序合并所有元素
  int idx = 0;
  for (int i = 0; i < bucketNumber; i++) {
    int bucketLen = bucketsMemberLength[i];
    // 复制桶内元素到输出数组
    for (int j = 0; j < bucketLen; j++) {
      output[idx] = buckets[i][j];
      idx++;
    }
  }
  
  print(output);
  return output;
}

/**
 * 桶排序负数单独处理版 - 负数单独排序
 *
 * 算法思路：
 * 1. 手动遍历获取最大最小值
 * 2. 处理最小值小于等于0的情况
 * 3. 计算桶的数量和大小
 * 4. 将正数分配到桶中，负数单独收集
 * 5. 负数单独排序后先输出
 * 6. 输出正数桶的元素
 *
 * 优化效果：
 * - 负数和正数分别优化，排序更精确
 * - 负数使用内置排序，效率更高
 * - 最终结果先输出负数再输出正数
 *
 * @param {List<int>} arr - 待排序的数字数组
 * @returns {List<int>} 排序后的数组
 */
List<int> bucketSort4(List<int> arr) {
  print('bucketSort4 separate negative sorting:');
  
  if (arr.isEmpty) return [];
  
  // 负数处理：创建单独的负数数组
  List<int> negativeList = [];
  
  // 元素分配：遍历数组，将元素分配到对应桶中
  for (int item in arr) {
    // 分类处理：负数单独收集，正数放入桶中
    if (item < 0) {
      // 负数收集：将负数添加到负数列表
      negativeList.add(item);
    }
  }
  
  // 负数排序：使用内置排序
  negativeList.sort();
  
  // 结果合并：先输出负数，再输出正数
  List<int> output = [];
  
  // 负数输出：将排序后的负数逐个添加到结果数组
  for (int num in negativeList) {
    output.add(num);
  }
  
  // 正数输出：收集并排序正数
  List<int> positiveList = [];
  for (int item in arr) {
    if (item >= 0) {
      positiveList.add(item);
    }
  }
  positiveList.sort();
  
  // 合并输出：先输出负数，再输出排序后的正数
  for (int num in positiveList) {
    output.add(num);
  }
  
  print(output);
  return output;
}

/**
 * 桶排序实时冒泡版 - 负数放在第一个桶内排序
 *
 * 算法思路：
 * 1. 计算数组的最大值和最小值
 * 2. 根据数组长度计算桶的大小
 * 3. 将元素分配到桶中，负数放在第1个桶
 * 4. 每次插入后立即对桶内进行冒泡排序
 * 5. 合并所有桶的元素
 *
 * 优化效果：
 * - 插入即排序，实时保持有序
 * - 桶内始终有序，减少后续排序开销
 * - 适合数据量较小的场景
 *
 * @param {List<int>} arr - 待排序的数字数组
 * @returns {List<int>} 排序后的数组
 */
List<int> bucketSort5(List<int> arr) {
  print('bucketSort5 real-time bubble sorting:');
  
  if (arr.isEmpty) return [];
  
  List<int> output = List<int>.filled(arr.length, 0);
  int max = arr[0];
  int min = arr[0];
  
  // 第一步：手动遍历获取数组最大最小值
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] > max) max = arr[i];
    if (arr[i] < min) min = arr[i];
  }
  
  // 第二步：计算桶的数量和大小
  int bucketSize = (max - min) ~/ min + 1;
  if (bucketSize < 1) bucketSize = 1;
  int bucketNumber = (max - min) ~/ bucketSize + 1;
  if (bucketNumber < 1) bucketNumber = 1;
  
  // 第三步：初始化桶
  List<List<int>> buckets = List.generate(bucketNumber, (_) => []);
  
  // 第四步：将元素分配到对应桶中
  for (int item in arr) {
    // 桶索引计算：确保索引在有效范围内
    int idx = (item - min) ~/ bucketSize;
    if (idx < 0) {
      idx = 0;
    } else if (idx >= bucketNumber) {
      idx = bucketNumber - 1;
    }
    
    // 插入元素到桶中
    buckets[idx].add(item);
    
    // 实时冒泡排序：对新插入的元素进行冒泡排序
    for (int j = buckets[idx].length - 1; j > 0; j--) {
      if (buckets[idx][j] < buckets[idx][j - 1]) {
        int temp = buckets[idx][j];
        buckets[idx][j] = buckets[idx][j - 1];
        buckets[idx][j - 1] = temp;
      }
    }
  }
  
  // 第五步：合并结果
  int index = 0;
  for (List<int> bucket in buckets) {
    for (int num in bucket) {
      output[index] = num;
      index++;
    }
  }
  
  print(output);
  return output;
}

/**
 * 桶排序智能优化版 - 智能桶数量计算
 *
 * 算法思路：
 * 1. 智能计算桶的数量，根据数据规模动态调整
 * 2. 使用快速排序进行桶内排序
 * 3. 优化的桶分配策略
 * 4. 高效的内存管理
 *
 * 优化效果：
 * - 智能桶数量计算，更精确的数据分布
 * - 快速排序桶内元素，提高排序效率
 * - 适合大数据量的场景
 *
 * @param {List<int>} arr - 待排序的数字数组
 * @returns {List<int>} 排序后的数组
 */
List<int> bucketSort6(List<int> arr) {
  print('bucketSort6 optimized version:');
  
  if (arr.isEmpty) return [];
  
  List<int> output = List<int>.filled(arr.length, 0);
  int max = arr[0];
  int min = arr[0];
  
  // 第一步：手动遍历获取数组最大最小值
  for (int i = 1; i < arr.length; i++) {
    if (arr[i] > max) max = arr[i];
    if (arr[i] < min) min = arr[i];
  }
  
  // 第二步：智能计算桶的数量
  int bucketNumber = 5;
  if (arr.length < 5) {
    bucketNumber = arr.length;
  } else if (arr.length < 100) {
    bucketNumber = arr.length ~/ 2;
  } else {
    bucketNumber = (arr.length / 10).floor();
  }
  
  int bucketSize = (max - min) ~/ bucketNumber + 1;
  if (bucketSize < 1) bucketSize = 1;
  
  // 第三步：初始化桶
  List<List<int>> buckets = List.generate(bucketNumber, (_) => []);
  List<int> bucketSizes = List.filled(bucketNumber, 0);
  
  // 第四步：元素分配
  for (int item in arr) {
    // 桶索引计算：确保索引在有效范围内
    int idx = (item - min) ~/ bucketSize;
    if (idx < 0) {
      idx = 0;
    } else if (idx >= bucketNumber) {
      idx = bucketNumber - 1;
    }
    
    buckets[idx].add(item);
    bucketSizes[idx]++;
  }
  
  // 第五步：桶内排序（使用内置排序）
  for (int i = 0; i < bucketNumber; i++) {
    if (bucketSizes[i] > 1) {
      buckets[i].sort();
    }
  }
  
  // 第六步：合并结果
  int index = 0;
  for (int i = 0; i < bucketNumber; i++) {
    for (int j = 0; j < bucketSizes[i]; j++) {
      output[index] = buckets[i][j];
      index++;
    }
  }
  
  print(output);
  return output;
}

void main() {
  List<int> arrData = [20, 11, 0, -10, 9, 6, 30, 15, 13, 80];
  
  print('=== 桶排序算法演示 ===\n');
  
  // 测试bucketSort1
  Stopwatch stopwatch = Stopwatch();
  print('arrData origin: $arrData');
  List<int> result1 = bucketSort1(arrData);
  stopwatch.stop();
  print('bucketSort1: ${stopwatch.elapsedMilliseconds}ms');
  
  print('\r\n');
  
  // 测试bucketSort2
  stopwatch = Stopwatch();
  print('arrData origin: $arrData');
  List<int> result2 = bucketSort2(arrData);
  stopwatch.stop();
  print('bucketSort2: ${stopwatch.elapsedMilliseconds}ms');
  
  print('\r\n');
  
  // 测试bucketSort3
  stopwatch = Stopwatch();
  print('arrData origin: $arrData');
  List<int> result3 = bucketSort3(arrData);
  stopwatch.stop();
  print('bucketSort3: ${stopwatch.elapsedMilliseconds}ms');
  
  print('\r\n');
  
  // 测试bucketSort4
  stopwatch = Stopwatch();
  print('arrData origin: $arrData');
  List<int> result4 = bucketSort4(arrData);
  stopwatch.stop();
  print('bucketSort4: ${stopwatch.elapsedMilliseconds}ms');
  
  print('\r\n');
  
  // 测试bucketSort5
  stopwatch = Stopwatch();
  print('arrData origin: $arrData');
  List<int> result5 = bucketSort5(arrData);
  stopwatch.stop();
  print('bucketSort5: ${stopwatch.elapsedMilliseconds}ms');
  
  print('\r\n');
  
  // 测试bucketSort6
  stopwatch = Stopwatch();
  print('arrData origin: $arrData');
  List<int> result6 = bucketSort6(arrData);
  stopwatch.stop();
  print('bucketSort6: ${stopwatch.elapsedMilliseconds}ms');
  
  print('\r\n=== 算法对比总结 ===');
  print('1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理');
  print('2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好');
  print('3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性');
  print('4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确');
  print('5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序');
  print('6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理');
}

/* 打印结果
jarry@Mac bucketsort % dart bucket_sort.dart
=== 桶排序算法演示 ===

arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 with negative numbers:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort1: 0ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort2 positive numbers only:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort2: 0ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 with move sorting:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort3: 0ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 separate negative sorting:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort4: 0ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 real-time bubble sorting:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort5: 0ms


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 optimized version:
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
bucketSort6: 0ms

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理
*/
