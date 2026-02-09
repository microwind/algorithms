package main

import (
	"fmt"
	"sort"
)

/*
 * Activity Selection Problem - Select maximum compatible activities
 *
 * Algorithm:
 * - Given activities with start and end times
 * - Select the maximum number of non-overlapping activities
 * - Strategy: Sort by end time, then greedily select activities
 *
 * Time Complexity: O(n log n) - due to sorting
 * Space Complexity: O(n) - for storing results
 */

type Activity struct {
	ID    int
	Start int
	End   int
}

// ActivityByEndTime implements sort.Interface for sorting by end time
type ActivityByEndTime []Activity

func (a ActivityByEndTime) Len() int           { return len(a) }
func (a ActivityByEndTime) Less(i, j int) bool { return a[i].End < a[j].End }
func (a ActivityByEndTime) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

// SelectActivities selects the maximum number of non-overlapping activities
func SelectActivities(activities []Activity) []Activity {
	if len(activities) == 0 {
		return []Activity{}
	}

	// Sort by end time
	sort.Sort(ActivityByEndTime(activities))

	selected := []Activity{activities[0]}
	lastEndTime := activities[0].End

	// Greedily select remaining activities
	for i := 1; i < len(activities); i++ {
		if activities[i].Start >= lastEndTime {
			selected = append(selected, activities[i])
			lastEndTime = activities[i].End
		}
	}

	return selected
}

func testBasicExample() {
	fmt.Println("\n[Test 1] Basic example with overlapping activities")

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
	fmt.Println("\n[Test 2] All activities compatible (non-overlapping)")

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
	fmt.Println("\n[Test 3] All activities overlapping")

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
	fmt.Println("\n[Test 4] Single activity")

	activities := []Activity{{1, 5, 10}}
	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testEmpty() {
	fmt.Println("\n[Test 5] Empty input")

	activities := []Activity{}
	selected := SelectActivities(activities)

	fmt.Printf("Selected activities: %v\n", selected)
	fmt.Printf("Count: %d\n", len(selected))
}

func testComplexScheduling() {
	fmt.Println("\n[Test 6] Complex scheduling scenario")

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
	fmt.Println("ACTIVITY SELECTION - Greedy Algorithm (Go)")
	fmt.Println("==================================================")

	testBasicExample()
	testAllCompatible()
	testAllOverlapping()
	testSingleActivity()
	testEmpty()
	testComplexScheduling()
}
