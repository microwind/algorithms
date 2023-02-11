/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
  "fmt"
  "time"
)

/**
 * 桶标准排序，支持正负整数
 */
func bucketSort1(arr []int) []int {
  var arrLen = len(arr)
  var output = make([]int, arrLen)
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

  if max < 0 {
    max = -max
  }
  if min < 0 {
    min = -min
  }

  // 每个桶的容量大小，也就是桶的间隔，用最大减去最小，也可以自定义
  var bucketSize = (max-min)/min + 1
  // 桶的数量，可以任意，也可以根据容量大小计算
  var bucketNumber = (max-min)/bucketSize + 1
  // fmt.Println("bucketSize, bucketNumber:", "|", bucketSize, bucketNumber)

  // 定义桶二维数组，每个桶都是一个数组
  var buckets [][]int = make([][]int, bucketNumber)
  // 用来记录每个桶实际存入的数据长度，以便最后导出
  var bucketsMemberLength = make([]int, bucketNumber)

  // 设置每个桶的长度，默认为数组长度
  for i := 0; i < bucketNumber; i++ {
    buckets[i] = make([]int, arrLen)
  }
  // 确定桶的下标
  for i := 0; i < arrLen; i++ {
    var item = arr[i]
    var idx int = (item - min) / bucketSize
    // 下标最小为0
    if idx < 0 {
      idx = 0
    }
    // 确定排序项对应的桶
    var bucket []int = buckets[idx]
    var bucketLen int = bucketsMemberLength[idx]
    fmt.Println("i, item, bucketSize, bucketNumber, idx, bucket:", i, "|", item, "|", bucketSize, "|", bucketNumber, "|", idx, " ", bucket)
    // 桶里的第一个数据，直接插入
    if bucketLen == 0 {
      bucket[bucketLen] = item
    } else {
      // 桶里后来的数据，按插入排序
      for bucketLen > 0 {
        bucketLen -= 1
        // 如果插入项小于成员项，则将成员项逐个挪动
        if item < bucket[bucketLen] {
          bucket[bucketLen+1] = bucket[bucketLen]
          if bucketLen == 0 {
            bucket[bucketLen] = item
          }
        } else {
          // 如果插入项大于成员向，则追加在之后
          bucket[bucketLen+1] = item
          break
        }
      }
    }
    bucketsMemberLength[idx]++
  }

  var idx = 0
  for i := 0; i < bucketNumber; i++ {
    for j := 0; j < bucketsMemberLength[i]; j++ {
      output[idx] = buckets[i][j]
      idx++
    }
  }

  return output
}

/**
 * 桶标准排序，支持浮点数，利用copy复制切片
 */
func bucketSort2(arr []float64) []float64 {
  var arrLen = len(arr)
  if arrLen <= 0 {
    return arr
  }

  // Set bucket number, Can use any number
  var bucketNumber int
  if arrLen >= 3 {
    bucketNumber = arrLen / 3
  } else {
    bucketNumber = arrLen
  }

  var buckets = make([][]float64, bucketNumber)
  // Create empty buckets
  for i := 0; i < bucketNumber; i++ {
    // Default length is empty
    buckets[i] = make([]float64, 0)
  }

  // Add elements into the buckets
  for i := 0; i < arrLen; i++ {
    // Get bucket index
    var bucketIndex = int(arr[i] / float64(bucketNumber))
    // The bucketIndex less then bucketNumber and more than zero
    if bucketIndex < 0 {
      bucketIndex = 0
    } else if bucketIndex >= bucketNumber {
      bucketIndex = bucketNumber - 1
    }

    // Sort the elements of each bucket
    var bucket = buckets[bucketIndex]
    // var bucketLen int = bucketsMemberLength[bucketIndex]
    var bucketLen = len(bucket)

    var item = arr[i]
    fmt.Println("i, item, bucketNumber, bucketIndex, bucket:", i, "|", item, "|", bucketNumber, "|", bucketIndex, "|", bucket)
    // Insert the first element to the bucket
    if bucketLen == 0 {
      bucket = append(bucket, item)
    } else {

      for j := 0; j < bucketLen; j++ {
        if item < bucket[j] {
          // Expand a position to the bucket
          bucket = append(bucket, -1)
          // All elements move back one step
          copy(bucket[j+1:bucketLen+1], bucket[j:bucketLen])
          // Insert item
          bucket[j] = item
          break
        }
        // Append to end of bucket if item is max
        if j == bucketLen-1 && item >= bucket[j] {
          bucket = append(bucket, item)
        }
      }
    }
    buckets[bucketIndex] = bucket
  }

  // Get all buckets to origin arr
  var index = 0
  for i := 0; i < bucketNumber; i++ {
    size := len(buckets[i])
    for j := 0; j < size; j++ {
      arr[index] = buckets[i][j]
      index++
    }
  }
  return arr
}

// test
func main() {
  fmt.Println("bucket sort1:")
  time1 := time.Now()
  data1 := []int{20, 11, 0, -10, 9, 6, 30, 15, 13, 80}
  fmt.Println(bucketSort1(data1[:]))
  fmt.Println("sort1 end. cost:", time.Since(time1))

  fmt.Println("bucket sort2:")
  time2 := time.Now()
  data2 := []float64{20.11, 13.32, 0.12323, -10.3243, 9.3244, -10.3243, 13.32, 8.43}
  fmt.Println(bucketSort2(data2[:]))
  fmt.Println("sort2 end. cost:", time.Since(time2))
}

/*
jarry@jarrys-MacBook-Pro bucketsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro bucketsort % go run bucket_sort.go
bucket sort1:
i, item, bucketSize, bucketNumber, idx, bucket: 0 | 20 | 8 | 9 | 1   [0 0 0 0 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 1 | 11 | 8 | 9 | 0   [0 0 0 0 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 2 | 0 | 8 | 9 | 0   [11 0 0 0 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 3 | -10 | 8 | 9 | 0   [0 11 0 0 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 4 | 9 | 8 | 9 | 0   [-10 0 11 0 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 5 | 6 | 8 | 9 | 0   [-10 0 9 11 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 6 | 30 | 8 | 9 | 2   [0 0 0 0 0 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 7 | 15 | 8 | 9 | 0   [-10 0 6 9 11 0 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 8 | 13 | 8 | 9 | 0   [-10 0 6 9 11 15 0 0 0 0]
i, item, bucketSize, bucketNumber, idx, bucket: 9 | 80 | 8 | 9 | 8   [0 0 0 0 0 0 0 0 0 0]
[-10 0 6 9 11 13 15 20 30 80]
sort1 end. cost: 52.758µs
bucket sort2:
i, item, bucketNumber, bucketIndex, bucket: 0 | 20.11 | 2 | 1 | []
i, item, bucketNumber, bucketIndex, bucket: 1 | 13.32 | 2 | 1 | [20.11]
i, item, bucketNumber, bucketIndex, bucket: 2 | 0.12323 | 2 | 0 | []
i, item, bucketNumber, bucketIndex, bucket: 3 | -10.3243 | 2 | 0 | [0.12323]
i, item, bucketNumber, bucketIndex, bucket: 4 | 9.3244 | 2 | 1 | [13.32 20.11]
i, item, bucketNumber, bucketIndex, bucket: 5 | -10.3243 | 2 | 0 | [-10.3243 0.12323]
i, item, bucketNumber, bucketIndex, bucket: 6 | 13.32 | 2 | 1 | [9.3244 13.32 20.11]
i, item, bucketNumber, bucketIndex, bucket: 7 | 8.43 | 2 | 1 | [9.3244 13.32 13.32 20.11]
[-10.3243 -10.3243 0.12323 8.43 9.3244 13.32 13.32 20.11]
sort2 end. cost: 140.123µs
*/
