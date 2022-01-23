package main

import(
  "fmt"
  // "strings"
)

/**
 * @desc 将当前项逐个与后项比较，如遇到相同，则删除当前项
 * @params list 数组列表
 */
func unique1(list []int) []int {
  var list_len int = len(list)
  for i := 0; i < list_len; i++ {
    for j := i + 1; j < list_len; j++ {
      if list[i] == list[j] {
      	fmt.Printf("i=%d equals j=%d\n ", list[i], list[j])
      	// 如果存在重复项，则将重复项删除，并重新给数组赋值
        list = append(list[:i], list[i+1:]...)
        // list = append(list[:j], list[j+1:]...)
        // 总长度和当前下标各减去1个
        list_len --
        i--
        break
      }
    }
  }
  return list[:list_len]
}

/**
 * @desc 自后往前逐个对比，如遇到相同，则删除当前项
 * @params list 数组列表
 */
func unique2(list []int) []int {
  var list_len int = len(list) - 1
  for ; list_len > 0; list_len-- {
    for j := 0; j < list_len; j++ {
      if list[list_len] == list[j] {
      	fmt.Printf("list_len=%d equals j=%d\n ", list[list_len], list[j])
      	// 如果存在重复项，则将重复项删除，并重新给数组赋值
        list = append(list[:list_len], list[list_len + 1:]...)
        // 总长度和当前下标各减去1个
        break
      }
    }
  }
  return list
}

/**
 * @desc 新建数组与是否包含对比法
 * @params list 数组列表
 */
func unique3(list []int) []int {
  var list_len int = len(list)
  // 创建一个新数组，初始长度为原数组长度
  result := make([]int, list_len)
  // 将第一个赋值给新数组
  result[0] = list[0]
  // 新数组的下标
  result_idx := 0
  for i := 1; i < list_len; i++ {
    is_repeat := false
    // 遍历新数组，比较是否包含当前项
    for j := 0; j < len(result); j++ {
      // 如果相同则表示已经存在于新数组中，则跳出循环
      if list[i] == result[j] {
      	is_repeat = true
      	break
      }
    }
    // 如果遍历一圈之后仍然不重复，则追加到新数组中
    if !is_repeat {
      result[result_idx] = list[i]
      result_idx++
    }
  }
  // 最后按新数组中真正长度返回
  return result[:result_idx]
}

/**
 * @desc 新建数组与是否包含对比法
 * @params list 数组列表
 */
func unique4(list []int) []int {
  var list_len int = len(list)
  // 创建一个新数组，初始长度为原数组长度
  result := make([]int, list_len)
  // 新数组的下标
  result_idx := 0
  for i := 0; i < list_len; i++ {
    for j := 0; j <= i; j++ {
      // 将当前项逐个与后面项比较,如果相同且下标相同可以认为是第一次出现
      // 则可以添加到新数组中去，如果不是第一次出现则可以跳过
      if list[i] == list[j] {
      	if i == j {
      	  fmt.Printf("i%d = j%d \n", i, j)
      	  result[result_idx] = list[i]
      	  result_idx++
      	}
      	break
      }
    }
  }
  // 最后按新数组中真正长度返回
  return result[:result_idx]
}

// test
func main() {
  fmt.Println("Hello, unique1 start：")
  // 数组切片，移除第3项测试。如果数字没有指定长度(也没有用省略号指定)，则复制时只能是引用
  // var list = [...]int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  // i := 3
  // list = append(list[:1], list[2:]...)
  list1 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("list1:", list1)
  fmt.Println("unique1 result: ", unique1(list1))

  list2 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("list2:", list2)
  fmt.Println("unique2 result: ", unique2(list2))

  list3 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("list3:", list3)
  fmt.Println("unique3 result: ", unique3(list3))

  list4 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("list4:", list4)
  fmt.Println("unique4 result: ", unique4(list4))
}

/* Test
jarry@jarrys-MacBook-Pro unique % go run unique.go
*/