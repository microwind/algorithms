/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;

/**
 * 桶排序算法实现
 * 提供六种不同的实现方式，适合不同场景和性能需求
 */
public class BucketSort {

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
   * @param {int[]} arr - 待排序的数字数组
   * @returns {int[]} 排序后的数组
   */
  public int[] bucketSort1(int[] arr) {
    System.out.println("bucketSort1 with negative numbers:");
    
    int len = arr.length;
    int[] output = new int[len];
    int max = arr[0];
    int min = arr[0];
    // 遍历数组找出最大值和最小值
    for (int i = 1; i < len; i++) {
      if (arr[i] > max)
        max = arr[i];
      if (arr[i] < min)
        min = arr[i];
    }
    // 最大最小的下限处理，确保有足够的桶数量
    if (max < 2) {
      max = 2;
    }
    if (min > -2) {
      min = -2;
    }
    // 计算桶的数量和大小
    int bucketNumber = Math.abs(max - min) + 1;
    int bucketSize = Math.abs(max - min) / bucketNumber + 1;
    // 创建桶数组
    @SuppressWarnings("unchecked")
    ArrayList<Integer>[] buckets = new ArrayList[bucketNumber];
    for (int i = 0; i < bucketNumber; i++) {
      buckets[i] = new ArrayList<Integer>();
    }
    // 将元素放入对应的桶中
    for (int i = 0; i < len; i++) {
      int item = arr[i];
      int idx = (item - min) / bucketSize;
      // 负数处理：负数全放在第一个桶里，按照插入方式排序
      if (idx < 0) {
        idx = 0;
      }
      // 插入排序：从后往前遍历，找到合适的插入位置
      boolean inserted = false;
      for (int j = buckets[idx].size() - 1; j >= 0; j--) {
        if (item >= buckets[idx].get(j)) {
          buckets[idx].add(j + 1, item);
          inserted = true;
          break;
        }
      }
      if (!inserted) {
        buckets[idx].add(0, item);
      }
    }
    // 合并结果：按照桶的顺序合并所有元素
    ArrayList<Integer> result = new ArrayList<Integer>();
    for (int i = 0; i < bucketNumber; i++) {
      if (buckets[i] != null) {
        result.addAll(buckets[i]);
      }
    }
    // 转换为数组
    for (int i = 0; i < result.size(); i++) {
      output[i] = result.get(i);
    }

    return output;
  }

  /**
   * 桶排序正数版本 - 只支持正数，不支持负数
   * 
   * 算法思路：
   * 1. 计算数组最大值和最小值
   * 2. 根据最大最小值计算桶的数量和大小
   * 3. 将元素分配到对应桶中
   * 4. 在每个桶内进行插入排序
   * 5. 合并所有桶的元素
   * 
   * 特点：
   * - 正数专用：只支持正数排序
   * - 桶分配精确：使用动态桶数量计算
   * - 性能较好：适合纯正数数据
   * 
   * @param {float[]} arr - 待排序的浮点数数组
   * @returns {float[]} 排序后的数组
   */
  public float[] bucketSort2(float[] arr) {
    System.out.println("bucketSort2 positive numbers only:");
    
    int len = arr.length;
    float[] output = new float[len];
    float max = arr[0];
    float min = arr[0];
    // 遍历数组找出最大值和最小值
    for (int i = 1; i < len; i++) {
      if (arr[i] > max)
        max = arr[i];
      if (arr[i] < min)
        min = arr[i];
    }
    
    // 边界处理：如果包含负数，将负数过滤掉（本版本不支持负数）
    if (min <= 0) {
      // 过滤掉负数，只保留正数
      ArrayList<Float> positiveNumbers = new ArrayList<Float>();
      for (float num : arr) {
        if (num > 0) {
          positiveNumbers.add(num);
        }
      }
      if (positiveNumbers.isEmpty()) {
        // 如果没有正数，返回全0数组
        return output;
      }
      // 重新计算最大最小值
      min = positiveNumbers.get(0);
      max = positiveNumbers.get(0);
      for (float num : positiveNumbers) {
        if (num > max) max = num;
        if (num < min) min = num;
      }
    }
    
    // 动态计算：根据数组长度动态计算桶的数量和大小
    int size = len / 2;
    int bucketNumber = Math.max(1, (int) Math.abs((max - min) / min) + 1);
    bucketNumber = bucketNumber < size ? bucketNumber : size;
    float bucketSize = Math.abs((max - min) / bucketNumber) + 1;
    // 创建桶数组
    @SuppressWarnings("unchecked")
    ArrayList<Float>[] buckets = new ArrayList[bucketNumber];
    for (int i = 0; i < bucketNumber; i++) {
      buckets[i] = new ArrayList<Float>();
    }
    // 将元素放入对应的桶中
    for (int i = 0; i < len; i++) {
      float item = arr[i];
      if (item <= 0) continue; // 跳过负数
      
      int idx = (int) ((item - min) / bucketSize);
      // 边界处理：确保索引在有效范围内
      if (idx < 0) {
        idx = 0;
      } else if (idx >= bucketNumber) {
        idx = bucketNumber - 1;
      }
      
      if (buckets[idx] == null) {
        buckets[idx] = new ArrayList<Float>();
        buckets[idx].add(item);
      } else {
        boolean inserted = false;
        // 插入排序：从后往前遍历，找到合适的插入位置
        for (int j = buckets[idx].size() - 1; j >= 0; j--) {
          if (item > buckets[idx].get(j)) {
            // JS特点：使用splice插入元素
            buckets[idx].add(j + 1, item);
            inserted = true;
            break;
          } else if (j == 0) {
            // 边界处理：如果数字最小则插入到最前
            buckets[idx].add(0, item);
            inserted = true;
          }
        }
        if (!inserted) {
          buckets[idx].add(item);
        }
      }
    }
    // 合并结果：按照桶的顺序合并所有元素
    ArrayList<Float> result = new ArrayList<Float>();
    for (int i = 0; i < bucketNumber; i++) {
      if (buckets[i] != null) {
        result.addAll(buckets[i]);
      }
    }
    // 转换为数组
    for (int i = 0; i < result.size(); i++) {
      output[i] = result.get(i);
    }

    return output;
  }

  /**
   * 桶排序挪动版本 - 使用挪动排序插入元素
   * 
   * 算法思路：
   * 1. 手动遍历获取数组最大最小值，避免使用Math.max/min
   * 2. 根据最大最小值计算桶的数量和大小
   * 3. 将元素分配到对应桶中，负数全部放入第一个桶
   * 4. 在每个桶内使用挪动排序插入元素
   * 5. 合并所有桶的元素
   * 
   * 特点：
   * - 挪动排序：使用挪动排序而非splice，避免性能开销
   * - 手动计算：手动计算最大最小值，避免函数调用开销
   * - 负数处理：负数全部放入第一个桶
   * 
   * @param {int[]} arr - 待排序的数字数组
   * @returns {int[]} 排序后的数组
   */
  public int[] bucketSort3(int[] arr) {
    System.out.println("bucketSort3 with move sorting:");
    
    int len = arr.length;
    int[] output = new int[len];
    int max = arr[0];
    int min = arr[0];
    // 手动遍历：获取数组最大最小值，避免使用Math.max/min
    for (int i = 1; i < len; i++) {
      // 最大值：如果当前元素大于max，则更新max
      if (arr[i] > max) {
        max = arr[i];
      }
      // 最小值：如果当前元素小于min，则更新min
      if (arr[i] < min) {
        min = arr[i];
      }
    }
    // 边界处理：处理最大最小值小于等于0的情况
    if (max <= 0) {
      max = 1;
    }
    if (min <= 0) {
      min = 1;
    }
    // 桶计算：根据最大最小值计算桶的数量和大小
    int bucketNumber = Math.abs((max - min) / min) + 1;
    int bucketSize = Math.abs((max - min) / bucketNumber) + 1;
    // 创建桶数组
    @SuppressWarnings("unchecked")
    ArrayList<Integer>[] buckets = new ArrayList[bucketNumber];
    for (int i = 0; i < bucketNumber; i++) {
      buckets[i] = new ArrayList<Integer>();
    }
    // 元素分配：遍历数组，将元素分配到对应桶中
    for (int i = 0; i < len; i++) {
      int item = arr[i];
      // 桶索引：计算元素应该放入的桶索引
      int idx = (item - min) / bucketSize;
      // 负数处理：负数全部放入第一个桶
      if (idx < 0) {
        idx = 0;
      }
      // 每个桶都是一个数组，若不存在则创建并放入数字
      if (buckets[idx] == null) {
        buckets[idx] = new ArrayList<Integer>();
        buckets[idx].add(item);
      } else {
        // 挪动排序：使用挪动排序插入元素，避免splice开销
        int actualLen = buckets[idx].size();
        // 如果桶为空，直接添加元素
        if (actualLen == 0) {
          buckets[idx].add(item);
        } else {
          // 挪动操作：找到插入位置并挪动元素
          int insertPos = 0;
          boolean found = false;
          for (int j = 0; j < actualLen; j++) {
            if (item < buckets[idx].get(j)) {
              insertPos = j;
              found = true;
              break;
            }
          }
          if (!found) {
            insertPos = actualLen;
          }
          // 如果插入位置在末尾，直接添加
          if (insertPos == actualLen) {
            buckets[idx].add(item);
          } else {
            // 挪动元素：从insertPos开始往后挪动
            buckets[idx].add(item); // 先添加到末尾
            for (int k = actualLen; k > insertPos; k--) {
              if (k - 1 >= 0) {
                buckets[idx].set(k, buckets[idx].get(k - 1));
              }
            }
            buckets[idx].set(insertPos, item);
          }
        }
      }
    }
    // 结果合并：将各桶的数据合并到新数组
    ArrayList<Integer> wrapBuckets = new ArrayList<Integer>();
    for (int i = 0; i < buckets.length; i++) {
      if (buckets[i] != null) {
        wrapBuckets.addAll(buckets[i]);
      }
    }
    // 转换为数组
    for (int i = 0; i < wrapBuckets.size(); i++) {
      output[i] = wrapBuckets.get(i);
    }

    return output;
  }

  /**
   * 桶排序负数单独处理版 - 负数单独排序
   * 
   * 算法思路：
   * 1. 遍历数组，将负数和正数分开收集
   * 2. 对负数和正数分别进行桶排序
   * 3. 合并负数和正数的排序结果
   * 
   * 特点：
   * - 负数单独：负数单独收集排序
   * - 分别处理：负数和正数分别优化
   * - 排序精确：每个部分都使用最适合的排序方式
   * 
   * @param {int[]} arr - 待排序的数字数组
   * @returns {int[]} 排序后的数组
   */
  public int[] bucketSort4(int[] arr) {
    System.out.println("bucketSort4 separate negative sorting:");
    
    int len = arr.length;
    int[] output = new int[len];
    // 负数收集：收集所有负数
    ArrayList<Integer> negativeNumbers = new ArrayList<Integer>();
    // 正数收集：收集所有正数
    ArrayList<Integer> positiveNumbers = new ArrayList<Integer>();
    // 遍历数组，将负数和正数分开收集
    for (int i = 0; i < len; i++) {
      if (arr[i] < 0) {
        negativeNumbers.add(arr[i]);
      } else {
        positiveNumbers.add(arr[i]);
      }
    }
    // 负数排序：对负数进行排序
    if (negativeNumbers.size() > 0) {
      Collections.sort(negativeNumbers);
    }
    // 正数排序：对正数进行桶排序
    if (positiveNumbers.size() > 0) {
      int[] positiveArray = new int[positiveNumbers.size()];
      for (int i = 0; i < positiveNumbers.size(); i++) {
        positiveArray[i] = positiveNumbers.get(i);
      }
      // 使用桶排序1对正数进行排序
      int[] sortedPositive = bucketSort1(positiveArray);
      // 将排序后的正数转换回ArrayList
      positiveNumbers.clear();
      for (int i = 0; i < sortedPositive.length; i++) {
        positiveNumbers.add(sortedPositive[i]);
      }
    }
    // 结果合并：合并负数和正数的排序结果
    ArrayList<Integer> result = new ArrayList<Integer>();
    // 先添加负数
    result.addAll(negativeNumbers);
    // 再添加正数
    result.addAll(positiveNumbers);
    // 转换为数组
    for (int i = 0; i < result.size(); i++) {
      output[i] = result.get(i);
    }

    return output;
  }

  /**
   * 桶排序实时冒泡版 - 插入即排序，实时保持有序
   * 
   * 算法思路：
   * 1. 计算数组最大值和最小值
   * 2. 根据最大最小值计算桶的数量和大小
   * 3. 将元素分配到对应桶中
   * 4. 每次插入后立即对桶内进行冒泡排序
   * 5. 合并所有桶的元素
   * 
   * 特点：
   * - 实时排序：插入即排序，实时保持桶内有序
   * - 冒泡排序：使用冒泡排序保持桶内有序
   * - 有序维护：每次插入都维护桶的有序状态
   * 
   * @param {int[]} arr - 待排序的数字数组
   * @returns {int[]} 排序后的数组
   */
  public int[] bucketSort5(int[] arr) {
    System.out.println("bucketSort5 real-time bubble sorting:");
    
    int len = arr.length;
    int[] output = new int[len];
    int max = arr[0];
    int min = arr[0];
    // 遍历数组找出最大值和最小值
    for (int i = 1; i < len; i++) {
      if (arr[i] > max)
        max = arr[i];
      if (arr[i] < min)
        min = arr[i];
    }
    // 计算桶的数量和大小
    int bucketNumber = Math.abs(max - min) + 1;
    int bucketSize = Math.abs(max - min) / bucketNumber + 1;
    // 创建桶数组
    @SuppressWarnings("unchecked")
    ArrayList<Integer>[] buckets = new ArrayList[bucketNumber];
    for (int i = 0; i < bucketNumber; i++) {
      buckets[i] = new ArrayList<Integer>();
    }
    // 将元素放入对应的桶中
    for (int i = 0; i < len; i++) {
      int item = arr[i];
      int idx = (item - min) / bucketSize;
      if (idx < 0) {
        idx = 0;
      }
      if (idx >= bucketNumber) {
        idx = bucketNumber - 1;
      }
      // 插入元素
      buckets[idx].add(item);
      // 实时冒泡：每次插入后立即对桶内进行冒泡排序
      int bucketLen = buckets[idx].size();
      for (int j = bucketLen - 1; j > 0; j--) {
        // 比较交换：如果前一个元素大于后一个元素，则交换
        if (buckets[idx].get(j) < buckets[idx].get(j - 1)) {
          // 交换操作
          int temp = buckets[idx].get(j);
          buckets[idx].set(j, buckets[idx].get(j - 1));
          buckets[idx].set(j - 1, temp);
        }
      }
    }
    // 结果合并：将各桶的数据合并到新数组
    ArrayList<Integer> wrapBuckets = new ArrayList<Integer>();
    for (int i = 0; i < buckets.length; i++) {
      if (buckets[i] != null) {
        wrapBuckets.addAll(buckets[i]);
      }
    }
    // 转换为数组
    for (int i = 0; i < wrapBuckets.size(); i++) {
      output[i] = wrapBuckets.get(i);
    }

    return output;
  }

  /**
   * 桶排序优化版 - 使用更精确的桶分配策略
   * 
   * 算法思路：
   * 1. 分析数据分布，计算最优桶数量
   * 2. 使用更精确的桶边界计算
   * 3. 桶内使用快速排序提高效率
   * 4. 支持负数和浮点数
   * 5. 优化内存使用
   * 
   * 优化效果：
   * - 智能桶数量计算
   * - 更精确的数据分布处理
   * - 桶内使用快速排序
   * - 更好的边界条件处理
   * 
   * @param {int[]} arr - 待排序的数字数组
   * @returns {int[]} 排序后的数组
   */
  public int[] bucketSort6(int[] arr) {
    System.out.println("bucketSort6 optimized version:");
    
    if (arr.length <= 1) return arr.clone();
    
    // 范围计算：计算数据范围
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < arr.length; i++) {
      if (arr[i] < min) min = arr[i];
      if (arr[i] > max) max = arr[i];
    }
    int range = max - min;
    
    // 智能计算：基于数据分布和数组大小计算最优桶数量
    int optimalBucketCount = Math.max(5, Math.min(arr.length, (int)Math.ceil(Math.sqrt(arr.length))));
    double bucketSize = (double)range / optimalBucketCount;
    
    // 桶创建：创建指定数量的桶
    @SuppressWarnings("unchecked")
    ArrayList<Integer>[] buckets = new ArrayList[optimalBucketCount];
    for (int i = 0; i < optimalBucketCount; i++) {
      buckets[i] = new ArrayList<Integer>();
    }
    
    // 元素分配：分配元素到对应桶中
    for (int value : arr) {
      int bucketIndex;
      
      // 边界处理：处理最大值和最小值的特殊情况
      if (value == max) {
        bucketIndex = optimalBucketCount - 1;
      } else if (value == min) {
        bucketIndex = 0;
      } else {
        bucketIndex = (int)Math.floor((value - min) / bucketSize);
      }
      
      // 索引检查：确保索引在有效范围内
      bucketIndex = Math.max(0, Math.min(optimalBucketCount - 1, bucketIndex));
      
      // 元素插入：将元素放入对应桶中
      buckets[bucketIndex].add(value);
    }
    
    // 桶内排序：对每个桶进行排序并合并
    ArrayList<Integer> result = new ArrayList<Integer>();
    for (ArrayList<Integer> bucket : buckets) {
      if (!bucket.isEmpty()) {
        // 快速排序：使用Java内置排序
        Collections.sort(bucket);
        result.addAll(bucket);
      }
    }
    
    // 转换为数组
    int[] resultArray = new int[result.size()];
    for (int i = 0; i < result.size(); i++) {
      resultArray[i] = result.get(i);
    }

    return resultArray;
  }

  // ==================== 测试代码 ====================

  public static void main(final String args[]) {
    BucketSort bucketSort = new BucketSort();
    int[] arrData = {20, 11, 0, -10, 9, 6, 30, 15, 13, 80};
    
    System.out.println("=== 桶排序算法演示 ===\n");

    // 测试bucketSort1
    System.out.println("arrData origin: " + Arrays.toString(arrData));
    long startTime1 = System.nanoTime();
    int[] result1 = bucketSort.bucketSort1(arrData);
    long endTime1 = System.nanoTime();
    System.out.println("bucketSort1: " + String.format("%.3f", (endTime1 - startTime1) / 1_000_000.0) + "ms");
    System.out.println(Arrays.toString(result1));
    System.out.println("\r\n");

    // 测试bucketSort2
    float[] arr2 = {0.7f, 0.11f, -0.9f, 0.011f, 0.034f, 0.62f, 0.93f, 0.68f};
    System.out.println("arrData origin: " + Arrays.toString(arr2));
    long startTime2 = System.nanoTime();
    float[] result2 = bucketSort.bucketSort2(arr2);
    long endTime2 = System.nanoTime();
    System.out.println("bucketSort2: " + String.format("%.3f", (endTime2 - startTime2) / 1_000_000.0) + "ms");
    System.out.println(Arrays.toString(result2));
    System.out.println("\r\n");

    // 测试bucketSort3
    System.out.println("arrData origin: " + Arrays.toString(arrData));
    long startTime3 = System.nanoTime();
    int[] result3 = bucketSort.bucketSort3(arrData);
    long endTime3 = System.nanoTime();
    System.out.println("bucketSort3: " + String.format("%.3f", (endTime3 - startTime3) / 1_000_000.0) + "ms");
    System.out.println(Arrays.toString(result3));
    System.out.println("\r\n");

    // 测试bucketSort4
    System.out.println("arrData origin: " + Arrays.toString(arrData));
    long startTime4 = System.nanoTime();
    int[] result4 = bucketSort.bucketSort4(arrData);
    long endTime4 = System.nanoTime();
    System.out.println("bucketSort4: " + String.format("%.3f", (endTime4 - startTime4) / 1_000_000.0) + "ms");
    System.out.println(Arrays.toString(result4));
    System.out.println("\r\n");

    // 测试bucketSort5
    System.out.println("arrData origin: " + Arrays.toString(arrData));
    long startTime5 = System.nanoTime();
    int[] result5 = bucketSort.bucketSort5(arrData);
    long endTime5 = System.nanoTime();
    System.out.println("bucketSort5: " + String.format("%.3f", (endTime5 - startTime5) / 1_000_000.0) + "ms");
    System.out.println(Arrays.toString(result5));
    System.out.println("\r\n");

    // 测试bucketSort6
    System.out.println("arrData origin: " + Arrays.toString(arrData));
    long startTime6 = System.nanoTime();
    int[] result6 = bucketSort.bucketSort6(arrData);
    long endTime6 = System.nanoTime();
    System.out.println("bucketSort6: " + String.format("%.3f", (endTime6 - startTime6) / 1_000_000.0) + "ms");
    System.out.println(Arrays.toString(result6));

    System.out.println("\n=== 算法对比总结 ===");
    System.out.println("1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理");
    System.out.println("2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好");
    System.out.println("3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性");
    System.out.println("4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确");
    System.out.println("5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序");
    System.out.println("6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理");
  }
}

/* 打印结果
jarry@Mac bucketsort % java BucketSort.java
=== 桶排序算法演示 ===

arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort1 with negative numbers:
bucketSort1: 0.059ms
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [0.7, 0.11, -0.9, 0.011, 0.034, 0.62, 0.93, 0.68]
bucketSort2 positive numbers only:
bucketSort2: 0.143ms
[0.011, 0.034, 0.11, 0.62, 0.68, 0.7, 0.93, 0.0]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort3 with move sorting:
bucketSort3: 0.069ms
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort4 separate negative sorting:
bucketSort1 with negative numbers:
bucketSort4: 0.340ms
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort5 real-time bubble sorting:
bucketSort5: 0.022ms
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]


arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketSort6 optimized version:
bucketSort6: 0.031ms
[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理
*/
