package main

import (
	"fmt"
	"sort"
)

// ArrayDeduplication 数组去重实现
type ArrayDeduplication struct{}

// RemoveDuplicates 使用Map去重，返回唯一元素
func (a *ArrayDeduplication) RemoveDuplicates(arr []int) []int {
	seen := make(map[int]bool)
	var result []int
	for _, num := range arr {
		if !seen[num] {
			seen[num] = true
			result = append(result, num)
		}
	}
	return result
}

// FindDuplicates 找出所有重复的元素
func (a *ArrayDeduplication) FindDuplicates(arr []int) []int {
	seen := make(map[int]bool)
	duplicates := make(map[int]bool)
	for _, num := range arr {
		if seen[num] {
			duplicates[num] = true
		} else {
			seen[num] = true
		}
	}
	var result []int
	for num := range duplicates {
		result = append(result, num)
	}
	sort.Ints(result)
	return result
}

// LogDeduplication 日志去重系统
type LogDeduplication struct {
	errorLogs map[string]bool
	logCount  map[string]int
}

func NewLogDeduplication() *LogDeduplication {
	return &LogDeduplication{
		errorLogs: make(map[string]bool),
		logCount:  make(map[string]int),
	}
}

func (l *LogDeduplication) AddErrorLog(errorMsg string) {
	if !l.errorLogs[errorMsg] {
		l.errorLogs[errorMsg] = true
	}
	l.logCount[errorMsg]++
}

func (l *LogDeduplication) GetUniqueErrorCount() int {
	return len(l.errorLogs)
}

func (l *LogDeduplication) PrintErrorFrequency() {
	type kv struct {
		Key   string
		Value int
	}
	var sorted []kv
	for k, v := range l.logCount {
		sorted = append(sorted, kv{k, v})
	}
	sort.Slice(sorted, func(i, j int) bool {
		return sorted[i].Value > sorted[j].Value
	})
	for _, kv := range sorted {
		fmt.Printf("  %s: %d次\n", kv.Key, kv.Value)
	}
}

// UserAnalytics 用户活跃度统计
type UserAnalytics struct {
	dailyActiveUsers map[string]map[int]bool
}

func NewUserAnalytics() *UserAnalytics {
	return &UserAnalytics{
		dailyActiveUsers: make(map[string]map[int]bool),
	}
}

func (u *UserAnalytics) RecordUserActivity(date string, userID int) {
	if u.dailyActiveUsers[date] == nil {
		u.dailyActiveUsers[date] = make(map[int]bool)
	}
	u.dailyActiveUsers[date][userID] = true
}

func (u *UserAnalytics) GetDAU(date string) int {
	return len(u.dailyActiveUsers[date])
}

func (u *UserAnalytics) GetMAU(month string) int {
	allUsers := make(map[int]bool)
	for date, users := range u.dailyActiveUsers {
		if len(date) >= len(month) && date[:len(month)] == month {
			for userID := range users {
				allUsers[userID] = true
			}
		}
	}
	return len(allUsers)
}

// IPTracker IP去重和统计
type IPTracker struct {
	uniqueIps map[string]bool
	ipCount   map[string]int
}

func NewIPTracker() *IPTracker {
	return &IPTracker{
		uniqueIps: make(map[string]bool),
		ipCount:   make(map[string]int),
	}
}

func (i *IPTracker) RecordIP(ip string) {
	i.uniqueIps[ip] = true
	i.ipCount[ip]++
}

func (i *IPTracker) GetUniqueIPCount() int {
	return len(i.uniqueIps)
}

func (i *IPTracker) PrintTopIPs(n int) {
	type kv struct {
		Key   string
		Value int
	}
	var sorted []kv
	for k, v := range i.ipCount {
		sorted = append(sorted, kv{k, v})
	}
	sort.Slice(sorted, func(i, j int) bool {
		return sorted[i].Value > sorted[j].Value
	})
	if n > len(sorted) {
		n = len(sorted)
	}
	for i := 0; i < n; i++ {
		fmt.Printf("  %s: %d次\n", sorted[i].Key, sorted[i].Value)
	}
}

func main() {
	fmt.Println("=== 数组去重实际应用 ===\n")

	// 基础去重
	ad := &ArrayDeduplication{}
	arr := []int{1, 2, 2, 3, 3, 3, 4}
	fmt.Printf("原数组: %v\n", arr)
	fmt.Printf("去重后: %v\n", ad.RemoveDuplicates(arr))
	fmt.Printf("重复元素: %v\n\n", ad.FindDuplicates(arr))

	// 日志去重
	fmt.Println("--- 日志系统去重 ---")
	logger := NewLogDeduplication()
	errors := []string{
		"Connection timeout",
		"Database error",
		"Connection timeout",
		"File not found",
		"Database error",
		"Database error",
	}
	for _, err := range errors {
		logger.AddErrorLog(err)
	}
	fmt.Printf("唯一错误数: %d\n", logger.GetUniqueErrorCount())
	fmt.Println("错误频率:")
	logger.PrintErrorFrequency()

	// 用户统计
	fmt.Println("\n--- 活跃用户统计 ---")
	analytics := NewUserAnalytics()
	users := []int{1, 2, 2, 3, 3, 3, 4, 5, 5}
	for _, userID := range users {
		analytics.RecordUserActivity("2024-03-01", userID)
	}
	fmt.Printf("日活跃用户数 (DAU): %d\n", analytics.GetDAU("2024-03-01"))

	// IP统计
	fmt.Println("\n--- IP去重统计 ---")
	ipTracker := NewIPTracker()
	ips := []string{"192.168.1.1", "192.168.1.2", "192.168.1.1", "192.168.1.3", "192.168.1.1"}
	for _, ip := range ips {
		ipTracker.RecordIP(ip)
	}
	fmt.Printf("唯一IP数: %d\n", ipTracker.GetUniqueIPCount())
	fmt.Printf("总访问次数: %d\n", len(ips))
	fmt.Println("IP访问频率 (Top 3):")
	ipTracker.PrintTopIPs(3)
}
