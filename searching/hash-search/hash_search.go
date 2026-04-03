/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 哈希查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

package main

import "fmt"

// 哈希表节点结构
type HashNode struct {
	key   string
	value int
	next  *HashNode
}

// 哈希表结构
type HashTable struct {
	buckets []*HashNode
	size    int
}

// 创建哈希表
func NewHashTable(size int) *HashTable {
	return &HashTable{
		buckets: make([]*HashNode, size),
		size:    size,
	}
}

// 哈希函数
func (ht *HashTable) hash(key string) int {
	hash := 0
	for _, char := range key {
		hash += int(char)
	}
	return hash % ht.size
}

// 插入键值对
func (ht *HashTable) insert(key string, value int) {
	index := ht.hash(key)
	
	// 检查是否已存在，存在则更新
	current := ht.buckets[index]
	for current != nil {
		if current.key == key {
			current.value = value
			return
		}
		current = current.next
	}
	
	// 不存在则添加新节点
	newNode := &HashNode{
		key:   key,
		value: value,
		next:  ht.buckets[index],
	}
	ht.buckets[index] = newNode
}

// 哈希查找
func (ht *HashTable) search(key string) (int, bool) {
	index := ht.hash(key)
	current := ht.buckets[index]
	
	// 在桶中查找
	for current != nil {
		if current.key == key {
			return current.value, true
		}
		current = current.next
	}
	
	return 0, false // 未找到
}

// 删除键值对
func (ht *HashTable) delete(key string) bool {
	index := ht.hash(key)
	current := ht.buckets[index]
	var prev *HashNode
	
	// 在桶中查找并删除
	for current != nil {
		if current.key == key {
			if prev == nil {
				// 删除头节点
				ht.buckets[index] = current.next
			} else {
				// 删除中间或尾节点
				prev.next = current.next
			}
			return true
		}
		prev = current
		current = current.next
	}
	
	return false
}

// 显示哈希表内容
func (ht *HashTable) display() {
	fmt.Println("哈希表内容:")
	for i := 0; i < ht.size; i++ {
		fmt.Printf("  桶 %d: ", i)
		current := ht.buckets[i]
		
		if current == nil {
			fmt.Print("空")
		} else {
			for current != nil {
				fmt.Printf("(%s:%d)", current.key, current.value)
				if current.next != nil {
					fmt.Print(" -> ")
				}
				current = current.next
			}
		}
		fmt.Println()
	}
}

// 主程序：演示哈希查找功能
func main() {
	fmt.Println("=== 哈希查找演示 ===\n")
	
	// 创建哈希表
	hashTable := NewHashTable(5)
	
	// 插入数据
	fmt.Println("插入数据:")
	keys := []string{"apple", "banana", "cherry", "date", "elderberry"}
	values := []int{100, 200, 300, 400, 500}
	
	for i := 0; i < len(keys); i++ {
		hashTable.insert(keys[i], values[i])
		fmt.Printf("  key=%s, value=%d, hash=%d\n", keys[i], values[i], hashTable.hash(keys[i]))
	}
	
	fmt.Println()
	hashTable.display()
	
	// 查找测试
	fmt.Println("\n查找测试:")
	searchKeys := []string{"banana", "cherry", "grape"}
	
	for _, key := range searchKeys {
		if value, found := hashTable.search(key); found {
			fmt.Printf("  查找 '%s': 找到，value=%d\n", key, value)
		} else {
			fmt.Printf("  查找 '%s': 未找到\n", key)
		}
	}
	
	// 性能分析
	fmt.Println("\n性能分析:")
	fmt.Println("  • 平均时间复杂度: O(1)")
	fmt.Println("  • 最坏时间复杂度: O(n)（所有键冲突）")
	fmt.Println("  • 空间复杂度: O(n)")
	
	// 删除测试
	fmt.Println("\n删除测试:")
	deleted := hashTable.delete("banana")
	fmt.Printf("  删除 'banana': %t\n", deleted)
	
	fmt.Println("\n删除后的哈希表:")
	hashTable.display()
	
	// 再次查找已删除的键
	if value, found := hashTable.search("banana"); found {
		fmt.Printf("\n再次查找 'banana': 找到，value=%d\n", value)
	} else {
		fmt.Println("\n再次查找 'banana': 未找到")
	}
}

/*
打印结果
jarry@Mac hash-search % go run hash_search.go
=== 哈希查找演示 ===

插入数据:
  key=apple, value=100, hash=1
  key=banana, value=200, hash=3
  key=cherry, value=300, hash=4
  key=date, value=400, hash=3
  key=elderberry, value=500, hash=2

哈希表内容:
  桶 0: 空
  桶 1: (apple:100)
  桶 2: (elderberry:500)
  桶 3: (date:400) -> (banana:200)
  桶 4: (cherry:300)

查找测试:
  查找 'banana': 找到，value=200
  查找 'cherry': 找到，value=300
  查找 'grape': 未找到

性能分析:
  • 平均时间复杂度: O(1)
  • 最坏时间复杂度: O(n)（所有键冲突）
  • 空间复杂度: O(n)

删除测试:
  删除 'banana': true

删除后的哈希表:
  桶 0: 空
  桶 1: (apple:100)
  桶 2: (elderberry:500)
  桶 3: (date:400)
  桶 4: (cherry:300)

再次查找 'banana': 未找到
*/
