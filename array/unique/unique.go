/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组去重算法 - Go实现，20种不同思路
 *
 * 算法原理：扫描切片，保留每个值的首次出现，丢弃后续重复
 *
 * 20种实现按5类组织：
 * - 第1类 基础循环（方法1-6）：纯下标遍历，O(n²)
 * - 第2类 map 与 Set（方法7-11）：利用 map 键唯一性，O(n)
 * - 第3类 排序后去重（方法12-14）：相同元素相邻后扫描，O(n log n)
 * - 第4类 泛型与函数式（方法15-17）：Go 1.18+ 泛型与标准库 slices
 * - 第5类 递归与位图（方法18-20）：教学经典与位图法
 *
 * 应用场景：数据清洗、统计唯一值、数据库去重
 */

package main

import (
	"fmt"
	"slices"
	"sort"
)

// ==================== 第1类：基础循环（方法1-6） ====================

/**
 * 方法1：双循环索引比较法
 * 核心原理：对每个元素向前查找，若找到相同值则为重复，否则为唯一值
 * 策略：遍历全部成员，将当前项与左边项逐个对比
 * 如果值相同且下标相同表示唯一，其他则认为是重复项
 *
 * 时间复杂度：O(n²) - 双层循环，最坏所有元素都不重复
 * 空间复杂度：O(n) - 新建切片存储结果
 *
 * @param arr 输入切片
 * @return 去重后的切片，保留首次出现顺序
 */
func unique1(arr []int) []int {
	result := make([]int, 0, len(arr))
	// 当前项跟左侧全量对比，是否首次出现
	for i := 0; i < len(arr); i++ {
		for j := 0; j <= i; j++ {
			if arr[i] == arr[j] {
				// i == j 表示前面没有相同值，是首次出现
				if i == j {
					result = append(result, arr[i])
				}
				break
			}
		}
	}
	return result
}

/**
 * 方法2：新建切片加 contains 检查法
 * 核心原理：维护结果切片，遍历时用线性查找判断是否已存在
 * 策略：未出现的才追加，最直观的新手写法
 *
 * 时间复杂度：O(n²) - 每次 contains 是 O(n) 线性扫描
 * 空间复杂度：O(n) - 结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique2(arr []int) []int {
	result := make([]int, 0, len(arr))
	for _, item := range arr {
		// slices.Contains 内部仍是 O(n) 线性查找
		if !slices.Contains(result, item) {
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法3：从后往前原地删除法
 * 核心原理：倒序遍历，与左侧任一元素相同则删除自身
 * 策略：自后往前扫，删除点之后元素已处理，不影响下标
 *
 * 时间复杂度：O(n²) - 双循环加 append 拼接每次 O(n)
 * 空间复杂度：O(1) - 原地修改
 *
 * @param arr 输入切片（会被原地修改）
 * @return 去重后的切片（保序）
 */
func unique3(arr []int) []int {
	l := len(arr)
	for l > 0 {
		l--
		i := l
		for i > 0 {
			i--
			if arr[l] == arr[i] {
				// append 拼接相当于 splice，删除下标 l 处的元素
				arr = append(arr[:l], arr[l+1:]...)
				break
			}
		}
	}
	return arr
}

/**
 * 方法4：从前往后原地删除法（删除后面相同项）
 * 核心原理：正序遍历，与右侧相同则删除右侧重复项
 * 策略：删除后 j 不前进、长度同步减一，避免漏判
 *
 * 时间复杂度：O(n²) - 双循环加 append 拼接每次 O(n)
 * 空间复杂度：O(1) - 原地修改
 *
 * @param arr 输入切片（会被原地修改）
 * @return 去重后的切片（保序）
 */
func unique4(arr []int) []int {
	l := len(arr)
	for i := 0; i < l; i++ {
		for j := i + 1; j < l; j++ {
			if arr[i] == arr[j] {
				arr = append(arr[:j], arr[j+1:]...)
				j-- // 删除后下标回退
				l-- // 长度同步减一
			}
		}
	}
	return arr[:l]
}

/**
 * 方法5：索引判等法（首次位置法）
 * 核心原理：扫描时用辅助函数找该值首次出现位置，等于当前下标即首次
 * 策略：避免维护额外结果切片，靠"首次位置"性质判重
 *
 * 时间复杂度：O(n²) - indexOf 每次 O(n)
 * 空间复杂度：O(n) - 结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique5(arr []int) []int {
	result := make([]int, 0, len(arr))
	for i, item := range arr {
		// slices.Index 返回首次出现位置，等于 i 表示是首次
		if slices.Index(arr, item) == i {
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法6：从右往左跳过重复法
 * 核心原理：倒序扫描，遇相同时把 i 整体左移跳过这一段重复区
 * 策略：保留下来的 i 是非重复项，倒序写入结果切片
 *
 * 时间复杂度：O(n²) - 双循环
 * 空间复杂度：O(n) - 结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique6(arr []int) []int {
	n := len(arr)
	tmp := make([]int, n)
	x := n
	for i := n - 1; i >= 0; i-- {
		for j := i - 1; j >= 0; j-- {
			if arr[i] == arr[j] {
				i--   // 跳过当前重复项
				j = i // j 复位到 i 左侧重新比较
			}
		}
		x--
		tmp[x] = arr[i]
	}
	return tmp[x:]
}

// ==================== 第2类：map 与 Set（方法7-11） ====================

/**
 * 方法7：map[int]bool 显式判重法
 * 核心原理：利用 map 键的唯一性自动去重
 * 策略：用 bool 值标记是否已见
 *
 * 时间复杂度：O(n) - map 操作 O(1) 平均
 * 空间复杂度：O(n) - map 加结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique7(arr []int) []int {
	seen := make(map[int]bool, len(arr))
	result := make([]int, 0, len(arr))
	for _, item := range arr {
		if !seen[item] {
			seen[item] = true
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法8：map[int]struct{} 空值集合法
 * 核心原理：struct{} 不占内存，是 Go 里实现 Set 的惯用法
 * 策略：键存数据，值用空结构体节省空间
 * 推荐场景：纯判重不需要 value 时
 *
 * 时间复杂度：O(n) - map 操作 O(1) 平均
 * 空间复杂度：O(n) - 比 map[T]bool 略省
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique8(arr []int) []int {
	seen := make(map[int]struct{}, len(arr))
	result := make([]int, 0, len(arr))
	for _, item := range arr {
		if _, ok := seen[item]; !ok {
			seen[item] = struct{}{}
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法9：自定义 Set 结构体法
 * 核心原理：把 map[T]struct{} 封装成有方法的 Set 类型
 * 策略：Add/Contains 接口语义清晰，工程上更易复用
 *
 * 时间复杂度：O(n) - map 操作 O(1) 平均
 * 空间复杂度：O(n) - Set 占用
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
type IntSet struct {
	data map[int]struct{}
}

func newIntSet() *IntSet                 { return &IntSet{data: map[int]struct{}{}} }
func (s *IntSet) Add(v int)              { s.data[v] = struct{}{} }
func (s *IntSet) Contains(v int) (b bool) { _, b = s.data[v]; return }

func unique9(arr []int) []int {
	set := newIntSet()
	result := make([]int, 0, len(arr))
	for _, item := range arr {
		if !set.Contains(item) {
			set.Add(item)
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法10：map 转切片法（不保序）
 * 核心原理：直接以元素为键塞入 map，最后取所有键
 * 策略：写法最短，但 Go map 遍历顺序随机
 *
 * 时间复杂度：O(n) - map 操作 O(1) 平均
 * 空间复杂度：O(n) - map 占用
 *
 * @param arr 输入切片
 * @return 去重后的切片（无序）
 */
func unique10(arr []int) []int {
	m := make(map[int]struct{}, len(arr))
	for _, item := range arr {
		m[item] = struct{}{}
	}
	result := make([]int, 0, len(m))
	for k := range m {
		result = append(result, k)
	}
	return result
}

/**
 * 方法11：频次统计 map 法
 * 核心原理：在去重的同时统计每个值的出现次数
 * 策略：键去重，值累加，配合保序数组遍历键
 * 推荐场景：去重同时需要业务统计的场景
 *
 * 时间复杂度：O(n) - map 操作 O(1) 平均
 * 空间复杂度：O(n) - map 加结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique11(arr []int) []int {
	count := make(map[int]int, len(arr))
	result := make([]int, 0, len(arr))
	for _, item := range arr {
		// 首次出现才追加，频次累加（这里相当于做了频次统计）
		if count[item] == 0 {
			result = append(result, item)
		}
		count[item]++
	}
	return result
}

// ==================== 第3类：排序后去重（方法12-14） ====================

/**
 * 方法12：排序后从后往前删法
 * 核心原理：先排序让相同元素相邻，再倒序删除重复
 * 策略：升序排序后从末尾扫，相邻相同则删后者
 *
 * 时间复杂度：O(n²) - 排序 O(n log n)，每次 append 拼接 O(n)
 * 空间复杂度：O(1) - 原地修改
 *
 * @param arr 输入切片（会被原地排序修改）
 * @return 去重后的切片（升序）
 */
func unique12(arr []int) []int {
	sort.Ints(arr)
	for l := len(arr) - 1; l > 0; l-- {
		if arr[l] == arr[l-1] {
			arr = append(arr[:l], arr[l+1:]...)
		}
	}
	return arr
}

/**
 * 方法13：排序后从前往后删法
 * 核心原理：升序排序后正序扫，相邻相同则删前者
 * 策略：删除后 i 回退、长度减一，避免漏判
 *
 * 时间复杂度：O(n²) - 排序 O(n log n)，每次 append 拼接 O(n)
 * 空间复杂度：O(1) - 原地修改
 *
 * @param arr 输入切片（会被原地排序修改）
 * @return 去重后的切片（升序）
 */
func unique13(arr []int) []int {
	sort.Ints(arr)
	l := len(arr) - 1
	for i := 0; i < l; i++ {
		if arr[i] == arr[i+1] {
			arr = append(arr[:i], arr[i+1:]...)
			i-- // 删除后下标回退
			l-- // 长度同步减一
		}
	}
	return arr
}

/**
 * 方法14：经典双指针法（LeetCode 26）
 * 核心原理：原地排序后双指针扫描，慢指针指向最后一个唯一元素
 * 策略：快指针发现新值，慢指针前进并写入；O(1) 额外空间
 * 推荐场景：切片原地去重，不允许额外存储
 *
 * 时间复杂度：O(n log n) - 排序主导
 * 空间复杂度：O(1) - 原地修改
 *
 * @param arr 输入切片（会被原地排序修改）
 * @return 去重后的切片（升序）
 */
func unique14(arr []int) []int {
	if len(arr) == 0 {
		return arr
	}
	sort.Ints(arr)
	slow := 0
	for fast := 1; fast < len(arr); fast++ {
		// 快指针发现新值，慢指针前进一步并写入
		if arr[fast] != arr[slow] {
			slow++
			arr[slow] = arr[fast]
		}
	}
	return arr[:slow+1]
}

// ==================== 第4类：泛型与函数式（方法15-17） ====================

/**
 * 方法15：泛型去重法（Go 1.18+）
 * 核心原理：用 comparable 类型约束，统一处理任意可比较类型
 * 策略：避免为每种类型重复写代码，map[T]struct{} 集合判重
 * 推荐场景：通用工具库，需要支持多种元素类型
 *
 * 时间复杂度：O(n) - map 操作 O(1) 平均
 * 空间复杂度：O(n) - map 加结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique15[T comparable](arr []T) []T {
	seen := make(map[T]struct{}, len(arr))
	result := make([]T, 0, len(arr))
	for _, item := range arr {
		if _, ok := seen[item]; !ok {
			seen[item] = struct{}{}
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法16：标准库 slices.Compact 法（Go 1.21+）
 * 核心原理：标准库内置的相邻去重，要求先排序
 * 策略：sort.Slice + slices.Compact，等价于 unique 工具
 * 推荐场景：现代 Go 工程首选写法，O(1) 额外空间
 *
 * 时间复杂度：O(n log n) - 排序主导
 * 空间复杂度：O(1) - 原地修改
 *
 * @param arr 输入切片（会被原地排序修改）
 * @return 去重后的切片（升序）
 */
func unique16(arr []int) []int {
	slices.Sort(arr)
	// slices.Compact 删除相邻重复元素，要求已排序
	return slices.Compact(arr)
}

/**
 * 方法17：高阶函数式法
 * 核心原理：用闭包封装"已见"状态，模拟函数式 filter
 * 策略：通用 filter 函数 + 闭包谓词，逻辑解耦
 * 推荐场景：演示 Go 中的函数式风格
 *
 * 时间复杂度：O(n) - HashSet 操作 O(1) 平均
 * 空间复杂度：O(n) - 闭包内 map 加结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func filter[T any](arr []T, pred func(T) bool) []T {
	result := make([]T, 0, len(arr))
	for _, item := range arr {
		if pred(item) {
			result = append(result, item)
		}
	}
	return result
}

/**
 * 方法17：高阶函数式法
 * 核心原理：用闭包封装"已存在"状态，模拟函数式 filter
 * 策略：通用 filter 函数 + 闭包谓词，逻辑解耦
 * 推荐场景：演示 Go 中的函数式风格
 *
 * 时间复杂度：O(n) - HashSet 操作 O(1) 平均
 * 空间复杂度：O(n) - 闭包内 map 加结果切片
 *
 * @param arr 输入切片
 * @return 去重后的切片（保序）
 */
func unique17(arr []int) []int {
	seen := make(map[int]struct{}, len(arr))
	// 闭包捕获 seen，谓词带副作用：首次见到返回 true
	return filter(arr, func(x int) bool {
		if _, ok := seen[x]; ok {
			return false
		}
		seen[x] = struct{}{}
		return true
	})
}

// ==================== 第5类：递归与位图（方法18-20） ====================

/**
 * 方法18：递归原地删除法
 * 核心原理：递归从末尾取元素，重复则丢，递归处理前 length-1 项
 * 策略：自后往前递归处理，相同就用 append 拼接删掉自身
 *
 * 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n) 加 append O(n)
 * 空间复杂度：O(n) - 递归栈深度 n
 *
 * @param arr    输入切片（会被原地修改）
 * @param length 当前处理长度（递归参数）
 * @return 去重后的切片（保序）
 */
func unique18(arr []int, length int) []int {
	// 递归出口：长度小于 1
	if length < 1 {
		return arr
	}
	last := length - 1
	for i := last - 1; i >= 0; i-- {
		// 末尾元素在前面出现过，删除自己
		if arr[last] == arr[i] {
			arr = append(arr[:last], arr[last+1:]...)
			break
		}
	}
	return unique18(arr, length-1)
}

/**
 * 方法19：递归拼接返回法
 * 核心原理：递归处理前 length-1 项，末项不重复则拼到结果末尾
 * 策略：纯函数式风格，不修改原切片
 *
 * 时间复杂度：O(n²) - 递归 n 层，每层扫前面 O(n) 加拼接 O(n)
 * 空间复杂度：O(n) - 递归栈加多次切片复制
 *
 * @param arr    输入切片
 * @param length 当前处理长度（递归参数）
 * @return 去重后的切片（保序）
 */
func unique19(arr []int, length int) []int {
	if length < 1 {
		return []int{}
	}
	last := length - 1
	isRepeat := false
	for i := last - 1; i >= 0; i-- {
		if arr[last] == arr[i] {
			isRepeat = true
			break
		}
	}
	// 递归处理前 length-1 项
	head := unique19(arr, length-1)
	if !isRepeat {
		head = append(head, arr[last])
	}
	return head
}

/**
 * 方法20：BitSet 位图法
 * 核心原理：每个非负整数用一位标记是否出现过
 * 策略：用 []uint64 数组实现位图，遇未置位则视为首次出现
 * 推荐场景：海量非负整数（10亿规模仅需约 128MB）
 *
 * 时间复杂度：O(n) - 位运算 O(1)
 * 空间复杂度：O(max_value/64) - 取决于最大值
 *
 * @param arr 输入切片（非负整数）
 * @return 去重后的切片（保序）
 */
func unique20(arr []int) []int {
	// 找最大值以确定位图大小
	maxVal := 0
	for _, v := range arr {
		if v < 0 {
			panic("BitSet 不支持负数，需要先偏移")
		}
		if v > maxVal {
			maxVal = v
		}
	}
	bits := make([]uint64, maxVal/64+1)
	result := make([]int, 0, len(arr))
	for _, v := range arr {
		// 第 v 位为 0 表示首次出现
		if bits[v/64]&(1<<(v%64)) == 0 {
			bits[v/64] |= 1 << (v % 64)
			result = append(result, v)
		}
	}
	return result
}

// ==================== main 函数 ====================

func main() {
	base := []int{1, 3, -1, 1, 2, 2, 4, 2, 2, -1}
	clone := func() []int {
		c := make([]int, len(base))
		copy(c, base)
		return c
	}

	fmt.Println("unique1 start:", base)
	fmt.Println("unique1 result:", unique1(clone()))

	fmt.Println("unique2 start:", base)
	fmt.Println("unique2 result:", unique2(clone()))

	fmt.Println("unique3 start:", base)
	fmt.Println("unique3 result:", unique3(clone()))

	fmt.Println("unique4 start:", base)
	fmt.Println("unique4 result:", unique4(clone()))

	fmt.Println("unique5 start:", base)
	fmt.Println("unique5 result:", unique5(clone()))

	fmt.Println("unique6 start:", base)
	fmt.Println("unique6 result:", unique6(clone()))

	fmt.Println("unique7 start:", base)
	fmt.Println("unique7 result:", unique7(clone()))

	fmt.Println("unique8 start:", base)
	fmt.Println("unique8 result:", unique8(clone()))

	fmt.Println("unique9 start:", base)
	fmt.Println("unique9 result:", unique9(clone()))

	fmt.Println("unique10 start:", base)
	fmt.Println("unique10 result:", unique10(clone()))

	fmt.Println("unique11 start:", base)
	fmt.Println("unique11 result:", unique11(clone()))

	fmt.Println("unique12 start:", base)
	fmt.Println("unique12 result:", unique12(clone()))

	fmt.Println("unique13 start:", base)
	fmt.Println("unique13 result:", unique13(clone()))

	fmt.Println("unique14 start:", base)
	fmt.Println("unique14 result:", unique14(clone()))

	fmt.Println("unique15 start:", base)
	fmt.Println("unique15 result:", unique15(clone()))

	fmt.Println("unique16 start:", base)
	fmt.Println("unique16 result:", unique16(clone()))

	fmt.Println("unique17 start:", base)
	fmt.Println("unique17 result:", unique17(clone()))

	fmt.Println("unique18 start:", base)
	c := clone()
	fmt.Println("unique18 result:", unique18(c, len(c)))

	fmt.Println("unique19 start:", base)
	c = clone()
	fmt.Println("unique19 result:", unique19(c, len(c)))

	// 20. BitSet（仅非负整数）
	base20 := []int{1, 3, 1, 2, 2, 4, 2, 2}
	fmt.Println("unique20 start:", base20)
	c20 := make([]int, len(base20))
	copy(c20, base20)
	fmt.Println("unique20 result:", unique20(c20))
}

/*
 * 编译运行：
 *   go run unique.go
 *
 * 预期输出：
 *
 * unique1 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique1 result: [1 3 -1 2 4]
 * unique2 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique2 result: [1 3 -1 2 4]
 * unique3 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique3 result: [1 3 -1 2 4]
 * unique4 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique4 result: [1 3 -1 2 4]
 * unique5 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique5 result: [1 3 -1 2 4]
 * unique6 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique6 result: [1 3 -1 2 4]
 * unique7 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique7 result: [1 3 -1 2 4]
 * unique8 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique8 result: [1 3 -1 2 4]
 * unique9 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique9 result: [1 3 -1 2 4]
 * unique10 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique10 result: [2 4 3 -1 1]   // map 遍历顺序随机，每次可能不同
 * unique11 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique11 result: [1 3 -1 2 4]
 * unique12 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique12 result: [-1 1 2 3 4]
 * unique13 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique13 result: [-1 1 2 3 4]
 * unique14 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique14 result: [-1 1 2 3 4]
 * unique15 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique15 result: [1 3 -1 2 4]
 * unique16 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique16 result: [-1 1 2 3 4]
 * unique17 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique17 result: [1 3 -1 2 4]
 * unique18 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique18 result: [1 3 -1 2 4]
 * unique19 start: [1 3 -1 1 2 2 4 2 2 -1]
 * unique19 result: [1 3 -1 2 4]
 * unique20 start: [1 3 1 2 2 4 2 2]
 * unique20 result: [1 3 2 4]
 */
