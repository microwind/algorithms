package main

import (
	"fmt"
	"sort"
)

/*
* 活动选择问题 - 贪心选择最多不重叠活动
 *
 * 算法思路：
 * - 给定一组活动，每个活动有开始和结束时间
 * - 选择最多数量的互不重叠活动
 * - 策略：按结束时间排序，贪心选择结束最早的活动
 *
 * 时间复杂度：O(n log n)（排序）
 * 空间复杂度：O(n)（存储结果）
*/

type Activity struct {
	ID    int
	Start int
	End   int
}

// ActivityByEndTime 实现按结束时间排序的接口
type ActivityByEndTime []Activity

func (a ActivityByEndTime) Len() int           { return len(a) }
func (a ActivityByEndTime) Less(i, j int) bool { return a[i].End < a[j].End }
func (a ActivityByEndTime) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

// SelectActivities 选择最多数量的不重叠活动（贪心算法）
func SelectActivities(activities []Activity) []Activity {
	if len(activities) == 0 {
		return []Activity{}
	}

	// 按结束时间排序
	sort.Sort(ActivityByEndTime(activities))

	selected := []Activity{activities[0]}
	lastEndTime := activities[0].End

	// 贪心选择剩余活动
	for i := 1; i < len(activities); i++ {
		if activities[i].Start >= lastEndTime {
			selected = append(selected, activities[i])
			lastEndTime = activities[i].End
		}
	}

	return selected
}

func testBasicExample() {
	fmt.Println("\n[测试1] 基本重叠活动")

	activities := []Activity{
		{1, 1, 3},
		{2, 2, 5},
		{3, 4, 6},
		{4, 6, 7},
		{5, 5, 8},
		{6, 8, 9},
	}

	selected := SelectActivities(activities)

	fmt.Printf("Input activities: %v\n", activities)
	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testAllCompatible() {
	fmt.Println("\n[测试2] 全部活动不重叠")

	activities := []Activity{
		{1, 1, 2},
		{2, 2, 3},
		{3, 3, 4},
		{4, 4, 5},
	}

	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testAllOverlapping() {
	fmt.Println("\n[测试3] 全部活动重叠")

	activities := []Activity{
		{1, 1, 10},
		{2, 2, 9},
		{3, 3, 8},
		{4, 4, 7},
	}

	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testSingleActivity() {
	fmt.Println("\n[测试4] 单个活动")

	activities := []Activity{{1, 5, 10}}
	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testEmpty() {
	fmt.Println("\n[测试5] 空输入")

	activities := []Activity{}
	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testComplexScheduling() {
	fmt.Println("\n[测试6] 复杂调度场景")

	activities := []Activity{
		{1, 0, 6},
		{2, 1, 4},
		{3, 3, 5},
		{4, 5, 7},
		{5, 8, 9},
		{6, 5, 9},
	}

	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func main() {
	fmt.Println("==================================================")
	fmt.Println("活动选择问题 - 贪心算法 (Go)")
	fmt.Println("==================================================")

	testBasicExample()
	testAllCompatible()
	testAllOverlapping()
	testSingleActivity()
	testEmpty()
	testComplexScheduling()
}
