package main

import(
  "fmt"
  "sort"
)

/**
 * 方式1。将当前项逐个与后项比较，如遇到相同，则删除当前项
 * @params 数组切片
 */
func unique1(arr []int) []int {
  var arr_len int = len(arr)
  for i := 0; i < arr_len; i++ {
    // 拿当前项逐个与后面的每一项进行比较
    for j := i + 1; j < arr_len; j++ {
      if arr[i] == arr[j] {
      	// fmt.Printf("i=%d equals j=%d\n ", arr[i], arr[j])
      	// 如果存在重复项，则将重复项删除，并重新给数组赋值
        arr = append(arr[:i], arr[i+1:]...)
        // 因为删除了当前项，总长度和当前的下标需要各减去1个
        arr_len --
        i--
        break
      }
    }
  }
  return arr[:arr_len]
}

/**
 * 方式2。自后往前逐个对比，如遇到相同，则删除当前项
 * @params 数组切片
 */
func unique2(arr []int) []int {
  var arr_len int = len(arr) - 1
  for ; arr_len > 0; arr_len-- {
  	// 自后往前拿当前项逐个与前面的每一项进行比较
    for j := 0; j < arr_len; j++ {
      if arr[arr_len] == arr[j] {
      	// fmt.Printf("arr_len=%d equals j=%d\n ", arr[arr_len], arr[j])
      	// 如果存在重复项，则将重复项删除，并重新给数组赋值
        arr = append(arr[:arr_len], arr[arr_len + 1:]...)
        // 总长度和当前下标各减去1个
        break
      }
    }
  }
  return arr
}

/**
 * 方式3。新建数组与检查新数组是否包含
 * @params 数组切片
 */
func unique3(arr []int) []int {
  var arr_len int = len(arr)
  // 创建一个新数组，初始长度为原数组长度
  result := make([]int, arr_len)
  // 将第一个赋值给新数组
  result[0] = arr[0]
  // 新数组的下标
  result_idx := 0
  for i := 1; i < arr_len; i++ {
    is_repeat := false
    // 遍历新数组，比较是否包含当前项
    for j := 0; j < len(result); j++ {
      // 如果相同则表示已经存在于新数组中，则跳出循环
      if arr[i] == result[j] {
      	is_repeat = true
      	break
      }
    }
    // 如果遍历一圈之后仍然不重复，则追加到新数组中
    if !is_repeat {
      result[result_idx] = arr[i]
      result_idx++
    }
  }
  // 最后按新数组中真正长度返回
  return result[:result_idx]
}

/**
 * 方式4。新建数组与对比下标是否第一次出现
 * @params 数组切片
 */
func unique4(arr []int) []int {
  var arr_len int = len(arr)
  // 创建一个新数组，初始长度为原数组长度
  result := make([]int, arr_len)
  // 新数组的下标起始为0
  result_idx := 0
  for i := 0; i < arr_len; i++ {
  	// 自前往后将当前项与前面的各项逐个进行对比
    for j := 0; j <= i; j++ {
      // 如果相同再看下是否第一次出现
      if arr[i] == arr[j] {
      // 如果下标也相同表示第一次出现，即可添加到新数组中去
      	if i == j {
      	  // fmt.Printf("i%d = j%d \n", i, j)
      	  result[result_idx] = arr[i]
      	  result_idx++
      	}
      	// 如果不是第一次出现即为重复项，则可以跳出，进行下一项的比较
      	break
      }
    }
  }
  // 最后按新数组中实际长度返回
  return result[:result_idx]
}

/**
 * 方式5。先排序再移除重复项
 * @params 数组切片
 */
func unique5(arr []int) []int {
  // 先排序
  sort.Ints(arr)
  var arr_len int = len(arr)
  for i := 0; i < arr_len - 1; i++ {
  	// 如果当前项与下一项重复，则移除重复项
  	if arr[i] == arr[i + 1] {
      arr = append(arr[:i], arr[i+1:]...)
      arr_len--;
      i--;
  	}
  }
  return arr[:arr_len]
}

/**
 * 方式5。先排序再把不相同的添加到新数组中
 * @params 数组切片
 */
func unique6(arr []int) []int {
  // 先排序
  sort.Ints(arr)
  var arr_len int = len(arr)
  result := make([]int, arr_len)
  result_idx := 0
  for i := 0; i < arr_len - 1; i++ {
  	// 如果当前项与下一项不重复，则添加到新数组中
  	if arr[i] != arr[i + 1] {
  	  result[result_idx] = arr[i]
  	  result_idx++
  	}
  }
  // 把最后一个添加到新数组中
  result[result_idx] = arr[arr_len - 1]
  return result[:result_idx + 1]
}

// test
func main() {
  fmt.Println("== test start ==")
  // 数组切片，移除第3项测试。如果数组没有指定长度(也没有用省略号指定)，则复制时只能是引用
  var arr = []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  i := 3
  // 切片操作，相当于自i起移除了i项
  arr = append(arr[:i], arr[i+i:]...)
  fmt.Println("arr slice:", arr)

  // 数组可以不指定长度，...是初始化时计算确定
  /*
  var a1 = [...]int {1,2,3}
  var a2 = a1
  a3 := a1
  a1[0] = 4
  a2[1] = 5
  fmt.Print("%d %d", a1, a2, a3)
  */

  origin_arr := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  arr1 := origin_arr
  fmt.Println("unique1 result: ", unique1(arr1))

  var arr2 []int = []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr2:", arr2)
  fmt.Println("unique2 result: ", unique2(arr2))

  var arr3 = []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr3:", arr3)
  fmt.Println("unique3 result: ", unique3(arr3))

  arr4 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr4:", arr4)
  fmt.Println("unique4 result: ", unique4(arr4))

  arr5 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr5:", arr5)
  fmt.Println("unique5 result: ", unique5(arr5))

  arr6 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr6:", arr6)
  fmt.Println("unique6 result: ", unique6(arr6))
}

/* Test
jarry@jarrys-MacBook-Pro unique % go run unique.go
*/