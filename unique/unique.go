package main

import(
  "fmt"
  "sort"
)

/**
 * 方式1。将当前项逐个与后项比较，如遇到相同，则删除当前项
 * @param arr 数组切片
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
 * @param arr 数组切片
 */
func unique2(arr []int) []int {
  var arr_len int = len(arr) - 1
  for ; arr_len > 0; arr_len-- {
  	// 拿最后项与前面的各项逐个(自后向前)进行比较
    for j := arr_len - 1; j >= 0; j-- {
      if arr[arr_len] == arr[j] {
        arr = append(arr[:arr_len], arr[arr_len + 1:]...)
        break
      }
    }

    /*
    // 或拿最后项与前面的各项逐个(自前向后)进行比较
    for j := 0; j < arr_len; j++ {
      if arr[arr_len] == arr[j] {
      	// fmt.Printf("arr_len=%d equals j=%d\n ", arr[arr_len], arr[j])
      	// 如果存在重复项，则将重复项删除，并重新给数组赋值
        arr = append(arr[:arr_len], arr[arr_len + 1:]...)
        // 总长度和当前下标各减去1个
        break
      }
    }
    */
  }
  return arr
}

/**
 * 方式3。新建数组与检查新数组是否包含
 * @param arr 数组切片
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
 * @param arr 数组切片
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
 * @param arr 数组切片
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
 * 方式6。先排序再把不相同的添加到新切片中
 * @param arr 数组切片
 */
func unique6(arr []int) (result []int) {
  // 先排序
  sort.Ints(arr)
  var arr_len int = len(arr)
  // 第一项直接添加到新数组中
  result = append(result, arr[0])
  for i := 1; i < arr_len; i++ {
  	// 如果前一项与当前项重复，则跳过进入下一项比较
  	if arr[i - 1] == arr [i] {
  	  continue
  	}
  	// 如果不重复则添加当前项到新数组中
  	result = append(result, arr[i])
  }
  return result
}

/**
 * 方式7。先排序再把不相同的添加到新切片中
 * @param arr 数组切片
 */
func unique7(arr []int) (result []int) {
  // 先排序
  sort.Ints(arr)
  var arr_len int = len(arr)
  for i := 0; i < arr_len; i++ {
  	// 如果当前项与下一项不重复，则添加到新数组中
  	if i < arr_len - 1 && arr[i] != arr[i + 1] {
  	  result = append(result, arr[i])
  	}
  }
  // 添加最后一项
  result = append(result, arr[arr_len - 1])
  return result
}


/**
 * 方式8。先排序再把不相同的添加到新建数组中
 * @param arr 数组切片
 */
func unique8(arr []int) []int {
  // 先排序
  sort.Ints(arr)
  var arr_len int = len(arr)
  // 这里采用新创建数组法
  result := make([]int, arr_len)
  result_idx := 0
  for i := 0; i < arr_len; i++ {
  	// 如果当前项与下一项不重复，则添加到新数组中
  	if i < arr_len - 1 && arr[i] != arr[i + 1] {
  	  result[result_idx] = arr[i]
  	  result_idx++
  	}
  }
  // 把最后一个添加到新数组中
  result[result_idx] = arr[arr_len - 1]
  return result[:result_idx + 1]
}

/**
 * 方式9。利用map数据结构来去重复
 * @param arr 数组切片
 */
func unique9(arr []int) (result []int) {
  // 新建临时map，用于存放去重结果
  temp_map := make(map[int]bool)
  // 遍历数组
  for _, item :=range arr {
  	// 以数组项为key，来判断是否存在于map中
  	_, ok := temp_map[item]
  	// 如果不存在则添加key到map中，value可随意赋值
  	if !ok {
      temp_map[item] = true
    }
  }
  // 将map转换为切片
  for k, _ := range temp_map {
    result = append(result, k)
  }
  return result
}

/**
 * 方式10。利用struct和map构建Set类型来去重
 * @param arr 数组切片
 */
// 构建空结构作为值，可不占内存
type None struct {}
var none None
// Set是个去重的列表
type Set struct {
  // 成员项是一个map
  item map[int] None
}
// 添加到set中
func (s *Set) add(value int) {
  s.item[value] = none
}
func (s *Set) addAll(arr []int) {
  // 将全部内容添加到set中去
  for _, v := range arr {
    // if !s.contains(v) {
    //   fmt.Println("it's included.")
    // }
    s.add(v)
  }
}
// 检查是否包含某项
func (s *Set) contains(value int) (ok bool) {
  _, ok = s.item[value]
  return ok
}
// 将map key转换为切片
func (s *Set) values() (result []int) {
  for k, _ := range s.item {
    result = append(result, k)
  }
  return result
}
// 通过结构体
func unique10(arr []int) (result []int) {
  // 声明一个set结构
  set := &Set{ item: map[int] None{} }
  set.addAll(arr)
  return set.values()
}

/**
 * 方式11。利用递归调用来删除重复项
 * @param arr 数组切片
 */
func unique11(arr []int, arr_len int) []int {
  if arr_len < 0 {
    return arr
  }
  if arr_len == len(arr) {
    arr_len -= 1
  }
  last := arr_len - 1
  for ; last >= 0; last-- {
    // 拿最后一个逐个跟前面比较，如果相同则移除比较项
    if arr[arr_len] == arr[last] {
      arr = append(arr[:arr_len], arr[arr_len + 1:]...)
      break
    }
  }
  // 递归调用，每次减少一个长度
  return unique11(arr, arr_len - 1)
}

/**
 * 方式12。利用递归调用来拼接新数组切片
 * @param arr 数组切片
 */
func unique12(arr []int, arr_len int) (result []int) {
  // 小于1表示比较完成，返回空数组
  if arr_len < 1 {
    return result
  }
  last := arr_len - 1
  prev := last - 1
  is_repeat := false
  // 逐个与前面项目比较，遇到相同则移除最后一项
  for ; prev >= 0; prev-- {
    if arr[last] == arr[prev] {
      // 如果遇到重复则跳过
      is_repeat = true
      break
    }
  }

  // 将不重复则添加到新数组中
  if !is_repeat {
    result = append(result, arr[last])
  }

  // 最后将递归结果逐个拼接起来
  return append(unique12(arr, arr_len - 1), result...)
}


// test
// 数组可以不指定长度，...是初始化时计算确定

func main() {
  fmt.Println("== test start ==")
  /*
  // 数组切片，移除第3项测试。如果数组没有指定长度(也没有用省略号指定)，则复制时只能是引用
  var arr = []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  i := 3
  // 切片操作，相当于自i起移除了i项
  arr = append(arr[:i], arr[i+i:]...)
  fmt.Println("arr slice:", arr)
  var a1 = [...]int {1,2,3}
  var a2 = a1
  a3 := a1
  a1[0] = 4
  a2[1] = 5
  fmt.Printf("a1=%d a2=%d a3=%d\n", a1, a2, a3)
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

  arr7 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr7:", arr7)
  fmt.Println("unique7 result: ", unique7(arr7))

  arr8 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr8:", arr8)
  fmt.Println("unique8 result: ", unique8(arr8))

  arr9 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr9:", arr9)
  fmt.Println("unique9 result: ", unique9(arr9))

  arr10 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr10:", arr10)
  fmt.Println("unique10 result: ", unique10(arr10))

  arr11 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr11:", arr11)
  fmt.Println("unique11 result: ", unique11(arr11, len(arr11)))

  arr12 := []int {2,2,2,5,2,3,4,4,11,11,2,3,4,5,6,4,5,5}
  fmt.Println("arr12:", arr12)
  fmt.Println("unique12 result: ", unique12(arr12, len(arr11)))
}

/* Test
jarry@jarrys-MacBook-Pro unique % go run unique.go
*/