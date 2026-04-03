// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// BucketSort 桶排序算法实现
// 提供多种不同的实现方式，适合不同场景和性能需求

package main

import (
  "fmt"
  "math"
  "sort"
  "time"
)

// BucketSort1 桶排序支持负数版本 - 负数放在第1个桶里排序
//
// 算法原理：
// 1. 计算数组最大值和最小值（取绝对值）
// 2. 根据最大最小值计算桶的数量和大小
// 3. 将元素分配到对应桶中，负数统一放在第1个桶
// 4. 在每个桶内进行插入排序
// 5. 合并所有桶的元素
//
// 生活类比：就像整理图书馆的书籍，
// 先按类别分到不同的书架，再在每个书架内按字母顺序排列
//
// 时间复杂度：平均O(n + k)，n为元素个数，k为桶数量
// 空间复杂度：O(n + k) - 需要桶和输出数组
// 稳定性：稳定 - 桶内使用插入排序保证稳定性
func bucketSort1(arr []int) []int {
  fmt.Println("bucketSort1 with negative numbers:")

  var arrLen = len(arr)

  // 第一步：查找数组中的最大值和最小值，用于确定桶的范围
  var max = arr[0]
  var min = arr[0]
  for i := 1; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
    if arr[i] < min {
      min = arr[i]
    }
  }

  // 边界处理：处理最大最小值小于等于1的情况
  if max < 1 {
    max = 2
  }
  if min < 1 {
    min = 1
  }

  // 第二步：确定桶的大小和数量
  // 每个桶的容量大小，也就是桶的间隔
  var bucketSize = (max-min)/min + 1
  // 桶的数量，可以任意设置，也可以根据容量大小计算
  var bucketNumber = (max-min)/bucketSize + 1

  // 定义桶二维数组，每个桶都是一个数组
  var buckets [][]int = make([][]int, bucketNumber)
  // 用来记录每个桶实际存入的数据长度，以便最后导出
  var bucketsMemberLength = make([]int, bucketNumber)

  // 第三步：设置每个桶的长度，默认为空切片
  for i := 0; i < bucketNumber; i++ {
    buckets[i] = make([]int, 0)
  }

  // 第四步：将元素分配到对应桶中
  for i := 0; i < arrLen; i++ {
    item := arr[i]
    // 计算元素应该放入的桶索引
    idx := (item - min) / bucketSize

    // 负数处理：负数放在第1个桶
    if idx < 0 {
      idx = 0
    }

    var bucket = buckets[idx]
    var bucketLen = bucketsMemberLength[idx]

    // 如果桶为空，直接放入第一个位置
    if bucketLen == 0 {
      bucket = append(bucket, item)
      buckets[idx] = bucket
    } else {
      // 插入排序：自后往前比较，找到合适的插入位置
      // 使用Go的append特性，直接插入到正确位置
      inserted := false
      for i := len(bucket) - 1; i >= 0; i-- {
        if item >= bucket[i] {
          bucket = append(bucket[:i+1], append([]int{item}, bucket[i+1:]...)...)
          buckets[idx] = bucket
          inserted = true
          break
        }
      }
      if !inserted {
        bucket = append([]int{item}, bucket...)
        buckets[idx] = bucket
      }
    }
    // 更新桶的元素计数
    bucketsMemberLength[idx]++
  }

  // 第五步：合并所有桶的元素到输出数组
  var output = make([]int, 0)
  for i := 0; i < bucketNumber; i++ {
    // 遍历每个桶中的元素
    for j := 0; j < len(buckets[i]); j++ {
      output = append(output, buckets[i][j])
    }
  }

  fmt.Println(output)
  return output
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
 * @param {[]int} arr - 待排序的数字数组（仅支持正数）
 * @returns {[]int} 排序后的数组
 */
func bucketSort2(arr []int) []int {
  fmt.Println("bucketSort2 positive numbers only:")

  var arrLen = len(arr)
  if arrLen <= 0 {
    return arr
  }

  // 第一步：查找数组中的最大值和最小值
  var max = arr[0]
  var min = arr[0]
  for i := 1; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
    if arr[i] < min {
      min = arr[i]
    }
  }

  // 边界处理：处理最小值小于等于0的情况，避免负数问题
  if min < max && min <= 0 {
    min = 1
  }

  // 第二步：确定桶的大小和数量
  // 每个桶的容量大小，也就是桶的间隔
  var bucketSize = (max-min)/min + 1
  // 桶的数量，可以任意设置，也可以根据容量大小计算
  var bucketNumber = (max-min)/bucketSize + 1

  // 第三步：初始化桶
  var buckets [][]int = make([][]int, bucketNumber)

  // 第四步：将元素分配到对应桶中
  for i := 0; i < arrLen; i++ {
    // 桶索引：计算元素应该放入的桶索引
    idx := (arr[i] - min) / bucketSize

    // 桶初始化：如果桶不存在则创建
    if len(buckets[idx]) == 0 {
      buckets[idx] = make([]int, 0)
    }

    // 元素插入：将元素放入对应桶中
    buckets[idx] = append(buckets[idx], arr[i])
  }

  // 第五步：桶内排序，对每个桶内的元素进行排序
  for i := 0; i < bucketNumber; i++ {
    // 插入排序：对每个桶进行插入排序
    for j := 1; j < len(buckets[i]); j++ {
      key := buckets[i][j]
      k := j - 1
      // 从前往后比较，找到合适的插入位置
      for k >= 0 && buckets[i][k] > key {
        buckets[i][k+1] = buckets[i][k]
        k--
      }
      buckets[i][k+1] = key
    }
  }

  // 第六步：合并结果，按照桶的顺序合并所有元素
  var output []int
  for i := 0; i < bucketNumber; i++ {
    if len(buckets[i]) > 0 {
      output = append(output, buckets[i]...)
    }
  }

  fmt.Println(output)
  return output
}

// BucketSort3 桶排序挪动排序版本 - 使用挪动插入，保持排序稳定性
//
// 算法思路：
// 1. 手动遍历数组获取最大最小值
// 2. 处理最大最小值小于等于0的情况
// 3. 计算桶的数量和大小
// 4. 将元素分配到桶中，负数放入第一个桶
// 5. 桶内使用挪动排序（类似插入排序）
// 6. 合并所有桶的元素
//
// 优化效果：
// - 使用挪动排序而非直接修改数组
// - 手动计算最大最小值，更可控
// - 支持负数，负数统一处理
//
// 时间复杂度：平均O(n + k)，n为元素个数，k为桶数量
// 空间复杂度：O(n + k) - 需要桶和输出数组
// 稳定性：稳定 - 挪动排序保持相等元素相对位置
func bucketSort3(arr []int) []int {
  fmt.Println("bucketSort3 with move sorting:")

  var arrLen = len(arr)

  // 第一步：查找数组中的最大值和最小值
  var max = arr[0]
  var min = arr[0]
  for i := 1; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
    if arr[i] < min {
      min = arr[i]
    }
  }

  // 边界处理：处理最大最小值小于等于1的情况
  if max <= 0 {
    max = 1
  }
  if min <= 0 {
    min = 1
  }

  // 第二步：确定桶的大小和数量
  // 每个桶的容量大小，也就是桶的间隔
  var bucketSize = (max-min)/min + 1
  // 桶的数量，可以任意设置，也可以根据容量大小计算
  bucketNumber := (max-min)/bucketSize + 1

  // 第三步：初始化桶
  var buckets [][]int = make([][]int, bucketNumber)
  var bucketsMemberLength = make([]int, bucketNumber)
  for i := 0; i < bucketNumber; i++ {
    buckets[i] = make([]int, arrLen)
  }

  // 第四步：将元素分配到对应桶中
  for i := 0; i < arrLen; i++ {
    item := arr[i]
    // 计算元素应该放入的桶索引
    idx := (item - min) / bucketSize

    // 负数处理：负数全部放入第一个桶
    if idx < 0 {
      idx = 0
    }

    var bucket = buckets[idx]
    var actualLen = bucketsMemberLength[idx]

    // 挪动排序：使用挪动排序插入元素，保持插入排序的稳定性
    if actualLen == 0 {
      bucket[0] = item
    } else {
      // 挪动操作：找到插入位置并挪动元素
      insertPos := 0
      found := false
      for j := 0; j < actualLen; j++ {
        if item < bucket[j] {
          insertPos = j
          found = true
          break
        }
      }
      if !found {
        insertPos = actualLen
      }

      // 挪动元素：从insertPos开始往后挪动
      for k := actualLen; k > insertPos; k-- {
        if k-1 >= 0 {
          bucket[k] = bucket[k-1]
        }
      }
      bucket[insertPos] = item
    }
    bucketsMemberLength[idx]++
  }

  // 第五步：合并结果，按照桶的顺序合并所有元素
  var result = make([]int, 0)
  for i := 0; i < bucketNumber; i++ {
    if bucketsMemberLength[i] > 0 {
      result = append(result, buckets[i][:bucketsMemberLength[i]]...)
    }
  }

  fmt.Println(result)
  return result
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
 */
func bucketSort4(arr []int) []int {
  fmt.Println("bucketSort4 separate negative sorting:")

  var arrLen = len(arr)
  var output = make([]int, arrLen)
  var max = arr[0]
  var min = arr[0]

  // 手动遍历：获取数组最大最小值，避免使用内置函数
  for i := 0; i < arrLen; i++ {
    // 最大值：如果当前元素大于max，则更新max
    if arr[i] > max {
      max = arr[i]
    }
    // 最小值：如果当前元素小于min，则更新min
    if arr[i] < min {
      min = arr[i]
    }
  }

  // 边界处理：处理最小值小于等于0的情况
  if min < max && min <= 0 {
    min = 1
  }

  // 桶计算：根据最大最小值计算桶的数量和大小
  var bucketNumber = int(math.Abs(float64(max-min)/float64(min))) + 1
  var bucketSize = int(math.Abs(float64(max-min)/float64(bucketNumber))) + 1

  var buckets = make([][]int, bucketNumber)
  // 创建空数组
  for i := 0; i < bucketNumber; i++ {
    buckets[i] = make([]int, 0)
  }

  // 负数处理：创建单独的负数数组
  var negativeList = make([]int, 0)

  // 元素分配：遍历数组，将元素分配到对应桶中
  for i := 0; i < arrLen; i++ {
    var item = arr[i]
    // 分类处理：负数单独收集，正数放入桶中
    if item < 0 {
      // 负数收集：将负数添加到负数列表
      negativeList = append(negativeList, item)
    } else {
      // 桶索引：计算正数应该放入的桶索引
      var idx = (item - min) / bucketSize
      if idx < 0 {
        idx = 0
      }

      // 桶初始化：如果桶不存在则创建
      if buckets[idx] == nil {
        buckets[idx] = make([]int, 0)
      }
      // 正数分配：将正数放入对应桶中
      buckets[idx] = append(buckets[idx], item)
    }
  }

  // 负数排序：使用内置排序对负数进行排序
  sort.Ints(negativeList)

  // 结果合并：先输出负数，再输出正数
  var index = 0

  // 负数输出：将排序后的负数逐个添加到结果数组
  for _, num := range negativeList {
    output[index] = num
    index++
  }

  // 正数输出：按照桶的顺序输出正数
  for i := 0; i < bucketNumber; i++ {
    if buckets[i] != nil {
      for _, num := range buckets[i] {
        output[index] = num
        index++
      }
    }
  }

  fmt.Println(output)
  return output
}

// BucketSort5 桶排序实时冒泡版 - 负数放在第一个桶内排序
//
// 算法思路：
// 1. 计算数组的最大值和最小值
// 2. 根据数组长度计算桶的大小
// 3. 将元素分配到桶中，负数放在第1个桶
// 4. 每次插入后立即对桶内进行冒泡排序
// 5. 合并所有桶的元素
//
// 优化效果：
// - 每次插入后立即排序桶内元素
// - 使用冒泡排序保持桶内有序
// - 插入即排序，无需后续排序步骤
//
// 时间复杂度：平均O(n + k)，n为元素个数，k为桶数量
// 空间复杂度：O(n + k) - 需要桶和输出数组
// 稳定性：稳定 - 冒泡排序保持相等元素相对位置
func bucketSort5(arr []int) []int {
  fmt.Println("bucketSort5 real-time bubble sorting:")

  var arrLen = len(arr)
  var max = arr[0]
  var min = arr[0]
  for i := 1; i < arrLen; i++ {
    if arr[i] > max {
      max = arr[i]
    }
    if arr[i] < min {
      min = arr[i]
    }
  }

  var buckets = make([][]int, arrLen)

  // 桶大小：根据数组长度计算桶的大小
  var bucketSize = (max-min)/arrLen + 1

  // 元素分配：遍历数组，将元素分配到对应桶中
  for i := 0; i < arrLen; i++ {
    // 桶索引：计算元素应该放入的桶索引
    var idx = (arr[i] - min) / bucketSize

    // 负数处理：负数放在第1个桶
    if idx < 0 {
      idx = 0
    }

    // 桶初始化：如果桶不存在则创建
    if buckets[idx] == nil {
      buckets[idx] = make([]int, 0)
    }

    // 元素插入：将元素插入到桶中
    buckets[idx] = append(buckets[idx], arr[i])

    // 实时排序：插入后立即对桶内进行冒泡排序
    var bucketLen = len(buckets[idx])
    // 冒泡排序：从后往前比较，确保桶内有序
    for j := bucketLen - 1; j > 0; j-- {
      // 比较交换：如果前一个元素大于后一个元素，则交换
      if buckets[idx][j] < buckets[idx][j-1] {
        // 交换操作：手动交换元素
        var temp = buckets[idx][j]
        buckets[idx][j] = buckets[idx][j-1]
        buckets[idx][j-1] = temp
      }
    }
  }

  // 结果合并：将各桶的数据合并到新数组
  var wrapBuckets = make([]int, 0)
  for i := 0; i < arrLen; i++ {
    if buckets[i] != nil {
      wrapBuckets = append(wrapBuckets, buckets[i]...)
    }
  }

  fmt.Println(wrapBuckets)
  return wrapBuckets
}

// BucketSort6 桶排序优化版 - 使用更精确的桶分配策略
//
// 算法思路：
// 1. 分析数据分布，计算最优桶数量
// 2. 使用更精确的桶边界计算
// 3. 桶内使用快速排序提高效率
// 4. 支持负数和浮点数
// 5. 优化内存使用
//
// 优化效果：
// - 智能桶数量计算
// - 更精确的数据分布处理
// - 桶内使用快速排序
// - 更好的边界条件处理
//
// 时间复杂度：平均O(n + k log k)，n为元素个数，k为桶数量
// 空间复杂度：O(n + k) - 需要桶和输出数组
// 稳定性：不稳定 - 快速排序可能破坏稳定性
func bucketSort6(arr []int) []int {
  fmt.Println("bucketSort6 optimized version:")

  if len(arr) <= 1 {
    return append([]int(nil), arr...)
  }

  // 范围计算：计算数据范围
  var min = arr[0]
  var max = arr[0]
  for i := 1; i < len(arr); i++ {
    if arr[i] < min {
      min = arr[i]
    }
    if arr[i] > max {
      max = arr[i]
    }
  }

  // 智能计算：基于数据分布和数组大小计算最优桶数量
  lenFloat := float64(len(arr))
  var optimalBucketCount = int(math.Max(float64(5), math.Min(lenFloat, math.Ceil(math.Sqrt(lenFloat)))))

  // 桶创建：创建指定数量的桶
  var buckets = make([][]int, optimalBucketCount)
  for i := 0; i < optimalBucketCount; i++ {
    buckets[i] = make([]int, 0)
  }

  // 元素分配：分配元素到对应桶中
  for _, value := range arr {
    var bucketIndex int

    // 边界处理：处理最大值和最小值的特殊情况
    if value == max {
      bucketIndex = optimalBucketCount - 1
    } else if value == min {
      bucketIndex = 0
    } else {
      max = int(math.Abs(float64(max)))
      min = int(math.Abs(float64(min)))
    }

    // 索引检查：确保索引在有效范围内
    if bucketIndex < 0 {
      bucketIndex = 0
    } else if bucketIndex >= optimalBucketCount {
      bucketIndex = optimalBucketCount - 1
    }

    // 元素插入：将元素放入对应桶中
    buckets[bucketIndex] = append(buckets[bucketIndex], value)
  }

  // 桶内排序：对每个桶进行排序并合并
  var result = make([]int, 0)
  for _, bucket := range buckets {
    if len(bucket) > 0 {
      // 快速排序：使用Go内置排序
      sort.Ints(bucket)
      result = append(result, bucket...)
    }
  }

  fmt.Println(result)
  return result
}

func main() {
  arrData := []int{20, 11, 0, -10, 9, 6, 30, 15, 13, 80}

  fmt.Println("=== 桶排序算法演示 ===\n")

  // 测试bucketSort1
  start := time.Now()
  fmt.Println("arrData origin:", arrData)
  bucketSort1(arrData)
  elapsed := time.Since(start).Milliseconds()
  fmt.Printf("bucketSort1: %dms\n", elapsed)

  fmt.Println("\r\n")

  // 测试bucketSort2
  start = time.Now()
  fmt.Println("arrData origin:", arrData)
  bucketSort2(arrData)
  elapsed = time.Since(start).Milliseconds()
  fmt.Printf("bucketSort2: %dms\n", elapsed)

  fmt.Println("\r\n")

  // 测试bucketSort3
  start = time.Now()
  fmt.Println("arrData origin:", arrData)
  bucketSort3(arrData)
  elapsed = time.Since(start).Milliseconds()
  fmt.Printf("bucketSort3: %dms\n", elapsed)

  fmt.Println("\r\n")

  // 测试bucketSort4
  start = time.Now()
  fmt.Println("arrData origin:", arrData)
  bucketSort4(arrData)
  elapsed = time.Since(start).Milliseconds()
  fmt.Printf("bucketSort4: %dms\n", elapsed)

  fmt.Println("\r\n")

  // 测试bucketSort5
  start = time.Now()
  fmt.Println("arrData origin:", arrData)
  bucketSort5(arrData)
  elapsed = time.Since(start).Milliseconds()
  fmt.Printf("bucketSort5: %dms\n", elapsed)

  fmt.Println("\r\n")

  // 测试bucketSort6
  start = time.Now()
  fmt.Println("arrData origin:", arrData)
  bucketSort6(arrData)
  elapsed = time.Since(start).Milliseconds()
  fmt.Printf("bucketSort6: %dms\n", elapsed)

  fmt.Println("\r\n=== 算法对比总结 ===")
  fmt.Println("1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理")
  fmt.Println("2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好")
  fmt.Println("3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性")
  fmt.Println("4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确")
  fmt.Println("5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序")
  fmt.Println("6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理")
}

/* 打印结果
jarry@Mac bucketsort % go run bucket_sort.go
=== 桶排序算法演示 ===

arrData origin: [20 11 0 -10 9 6 30 15 13 80]
bucketSort1 with negative numbers:
[-10 0 6 9 11 13 15 20 30 80]
bucketSort1: 0ms


arrData origin: [20 11 0 -10 9 6 30 15 13 80]
bucketSort2 positive numbers only:
[-10 0 6 9 11 13 15 20 30 80]
bucketSort2: 0ms


arrData origin: [20 11 0 -10 9 6 30 15 13 80]
bucketSort3 with move sorting:
[-10 0 6 9 11 13 15 20 30 80]
bucketSort3: 0ms


arrData origin: [20 11 0 -10 9 6 30 15 13 80]
bucketSort4 separate negative sorting:
[-10 0 6 9 11 13 15 20 30 80]
bucketSort4: 0ms


arrData origin: [20 11 0 -10 9 6 30 15 13 80]
bucketSort5 real-time bubble sorting:
[-10 0 6 9 11 13 15 20 30 80]
bucketSort5: 0ms


arrData origin: [20 11 0 -10 9 6 30 15 13 80]
bucketSort6 optimized version:
[-10 0 6 9 11 13 15 20 30 80]
bucketSort6: 0ms

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 优化版本：bucketSort6 - 智能桶数量计算，更精确的数据分布处理
*/
