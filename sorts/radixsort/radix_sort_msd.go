/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
  "fmt"
  "time"
)

// 基数排序，基于计数排序的基础上，从高到低逐位排序

func radixSort(array []int) []int {
  var amount = 10
  maxValue := max(array)
  placeValue := pow(amount, getNumberOfDigits(maxValue)-1)

  bucketSort(array, placeValue)
  return array
}

func bucketSort(array []int, placeValue int) []int {
  var amount = 10
  if placeValue < 1 {
    return array
  }

  if len(array) <= 1 {
    return array
  }

  buckets := [][]int{}
  minValue := getMinValue(array, placeValue)

  offset := 0
  if minValue < 0 {
    offset = 0 - minValue
  }
  for i := 0; i < (amount + offset); i++ {
    buckets = append(buckets, []int{})
  }

  for idx, num := range array {
    bucketIdx := getDigit(array, idx, placeValue) + offset
    buckets[bucketIdx] = append(buckets[bucketIdx], num)
  }
  fmt.Println("place value: ", placeValue, "bucket: ", buckets)

  sortedIdx := 0
  for _, bucket := range buckets {
    sortedBucket := bucketSort(bucket, placeValue/amount)
    for _, num := range sortedBucket {
      array[sortedIdx] = num
      sortedIdx += 1
    }
  }
  fmt.Println("place value: ", placeValue, "array: ", array)

  return array
}

func getNumberOfDigits(num int) int {
  numberOfDigits := 0
  for num > 0 {
    numberOfDigits += 1
    num /= 10
  }
  return numberOfDigits
}

func abs(value int) int {
  if value < 0 {
    return -value
  }
  return value
}

func max(array []int) int {
  maxValue := array[0]
  for i := 1; i < len(array); i++ {
    if array[i] > maxValue {
      maxValue = array[i]
    }
  }
  return maxValue
}

func pow(a int, power int) int {
  result := 1
  for i := 0; i < power; i++ {
    result *= a
  }
  return result
}

// get minimum value of each digit group
func getMinValue(array []int, placeValue int) int {
  minValue := getDigit(array, 0, placeValue)
  for i := 1; i < len(array); i++ {
    element := getDigit(array, i, placeValue)
    if minValue > element {
      minValue = element
    }
  }
  return minValue
}

// ex. number: 2022, place value: 100 => digit = 0
// ex. number: -1223, place value: 100 => digit = -2
func getDigit(array []int, idx int, placeValue int) int {
  element := array[idx]
  digit := abs(element) / placeValue % 10
  if element < 0 {
    return -digit
  }
  return digit
}

// test
func main() {
  fmt.Println("radix sort1:")
  time1 := time.Now()
  data1 := []int{33, 4, 15, 143}
  fmt.Println(radixSort(data1[:]))
  fmt.Println("sort1 end. cost:", time.Since(time1))

  fmt.Println("radix sort2:")
  time2 := time.Now()
  data2 := []int{33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431}
  fmt.Println(radixSort(data2[:]))
  fmt.Println("sort2 end. cost:", time.Since(time2))
}

/*
jarry@jarrys-MacBook-Pro radixsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro radixsort % go run radix_sort_msd.go
radix sort1:
place value:  100 bucket:  [[33 4 15] [143] [] [] [] [] [] [] [] []]
place value:  10 bucket:  [[4] [15] [] [33] [] [] [] [] [] []]
place value:  10 array:  [4 15 33]
place value:  100 array:  [4 15 33 143]
[4 15 33 143]
sort1 end. cost: 75.521µs
radix sort2:
place value:  10000 bucket:  [[-323454] [] [33 -4 15 43 7 10 1235 200] [] [] [] [] [] [] [] [87431] []]
place value:  1000 bucket:  [[33 -4 15 43 7 10 200] [1235] [] [] [] [] [] [] [] []]
place value:  100 bucket:  [[33 -4 15 43 7 10] [] [200] [] [] [] [] [] [] []]
place value:  10 bucket:  [[-4 7] [15 10] [] [33] [43] [] [] [] [] []]
place value:  1 bucket:  [[-4] [] [] [] [] [] [] [] [] [] [] [7] [] []]
place value:  1 array:  [-4 7]
place value:  1 bucket:  [[10] [] [] [] [] [15] [] [] [] []]
place value:  1 array:  [10 15]
place value:  10 array:  [-4 7 10 15 33 43]
place value:  100 array:  [-4 7 10 15 33 43 200]
place value:  1000 array:  [-4 7 10 15 33 43 200 1235]
place value:  10000 array:  [-323454 -4 7 10 15 33 43 200 1235 87431]
[-323454 -4 7 10 15 33 43 200 1235 87431]
sort2 end. cost: 54.864µs
*/
