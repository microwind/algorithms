/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import "fmt"

// 插入排序标准版
func insertSort1(arr []int) []int {
  var j int
  var current int
  var l = len(arr)
  // 外循环用于遍历待排序区间
  for i := 0; i < l; i++ {
    // 当前项为第1项
    current = arr[i]
    // 第2项是当前项的下一项
    j = i - 1

    // 内循环用来遍历已排序区间
    // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项时，则将该位置逐项右移
    // 直到遇到小于等于自己的项则停止移动，表示插入成功
    fmt.Println("i=", i, " j=", j, "current=", current, "arr[i]=", arr[i], "arr[]=", arr)
    for j >= 0 && current < arr[j] {
      // 逐项右移，以便空出插入项
      arr[j+1] = arr[j]
      j--
    }

    // 没有比自己大的项了，则插入到当前位置
    arr[j+1] = current
  }
  return arr
}

// // 标准通用版
// function insertSort2(arr) {
//   var j, current, l = arr.length
//   for (var i = 0; i < l; i++) {
//     j = i - 1
//     current = arr[i]
//     // console.log("i=" + i, " j=" + j, "current=" + current, "arr[i]=" + arr[i], "arr[j+1]=" + arr[j + 1], "arr[]=", arr)
//     while (j >= 0 && current < arr[j]) {
//       arr[j + 1] = arr[j]
//       j--
//     }
//     arr[j + 1] = current
//   }
//   return arr
// }

// // splice版本
// function insertSort3(arr) {
//   var j, current, l = arr.length,
//     isMin
//   for (var i = 1; i < l; i++) {
//     j = i - 1
//     current = arr.splice(i, 1)[0]
//     isMin = true
//     while (j >= 0) {
//       if (current > arr[j]) {
//         // console.log("i=" + i, " j=" + j, "current=" + current, "arr[i]=" + arr[i], "arr[j]=" + arr[j], "arr[]=", arr)
//         // 利用splice插入
//         arr.splice(j + 1, 0, current)
//         isMin = false
//         break
//       }
//       j--
//     }
//     if (isMin) {
//       arr.splice(0, 0, current)
//     }
//   }
//   return arr
// }

// // 新建数组版
// function insertSort4(arr) {
//   var j, l = arr.length,
//     len, isMax
//   var newArr = arr.slice(0, 1)
//   console.time("time")
//   for (var i = 1; i < l; i++) {
//     isMax = true
//     for (var j = 0, len = newArr.length; j < len; j++) {
//       // console.log("i=" + i, " j=" + j, "arr[i]=" + arr[i], "newArr[j]=" + newArr[j], "arr[]=", arr)
//       if (arr[i] < newArr[j]) {
//         // 新建数组来插入到某个位置中
//         newArr.splice(j, 0, arr[i])
//         isMax = false
//         break
//       }
//     }
//     if (isMax) {
//       newArr.push(arr[i])
//     }
//   }
//   return newArr
// }

func main() {
  fmt.Println("insert sort1:")
  data := [...]int{7, 11, 9, 10, 12, 13, 8}
  data2 := [...]int{3, 4, 15, -2, -2, -1, 2, 6, 3, -7, 10}
  fmt.Println(insertSort1(data[:]))
  fmt.Println(insertSort1(data2[:]))

  // fmt.Println("insert sort2:")
  // data := = [...]int{7, 11, 9, 10, 12, 13, 8}
  // data2 = [...]int{3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10}
  // fmt.Println(insertSort2(data2[:]))

  // fmt.Println("insert sort3:")
  // data := = [...]int{7, 11, 9, 10, 12, 13, 8}
  // data2 = [...]int{3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10}
  // fmt.Println(insertSort3(data3[:]))
}

/* execute test
jarry@jarrys-MacBook-Pro insertsort % go run insert_sort.go
insert sort1:
i= 0  j= -1 current= 7 arr[i]= 7 arr[]= [7 11 9 10 12 13 8]
i= 1  j= 0 current= 11 arr[i]= 11 arr[]= [7 11 9 10 12 13 8]
i= 2  j= 1 current= 9 arr[i]= 9 arr[]= [7 11 9 10 12 13 8]
i= 3  j= 2 current= 10 arr[i]= 10 arr[]= [7 9 11 10 12 13 8]
i= 4  j= 3 current= 12 arr[i]= 12 arr[]= [7 9 10 11 12 13 8]
i= 5  j= 4 current= 13 arr[i]= 13 arr[]= [7 9 10 11 12 13 8]
i= 6  j= 5 current= 8 arr[i]= 8 arr[]= [7 9 10 11 12 13 8]
[7 8 9 10 11 12 13]
i= 0  j= -1 current= 3 arr[i]= 3 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 1  j= 0 current= 4 arr[i]= 4 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 2  j= 1 current= 15 arr[i]= 15 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 3  j= 2 current= -2 arr[i]= -2 arr[]= [3 4 15 -2 -2 -1 2 6 3 -7 10]
i= 4  j= 3 current= -2 arr[i]= -2 arr[]= [-2 3 4 15 -2 -1 2 6 3 -7 10]
i= 5  j= 4 current= -1 arr[i]= -1 arr[]= [-2 -2 3 4 15 -1 2 6 3 -7 10]
i= 6  j= 5 current= 2 arr[i]= 2 arr[]= [-2 -2 -1 3 4 15 2 6 3 -7 10]
i= 7  j= 6 current= 6 arr[i]= 6 arr[]= [-2 -2 -1 2 3 4 15 6 3 -7 10]
i= 8  j= 7 current= 3 arr[i]= 3 arr[]= [-2 -2 -1 2 3 4 6 15 3 -7 10]
i= 9  j= 8 current= -7 arr[i]= -7 arr[]= [-2 -2 -1 2 3 3 4 6 15 -7 10]
i= 10  j= 9 current= 10 arr[i]= 10 arr[]= [-7 -2 -2 -1 2 3 3 4 6 15 10]
[-7 -2 -2 -1 2 3 3 4 6 10 15]
*/
