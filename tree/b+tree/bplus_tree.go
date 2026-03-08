/*
 * B+树 - Go语言实现
 */
package main

import (
	"fmt"
)

const ORDER = 3 // B+树阶数

// BPlusNode B+树节点
type BPlusNode struct {
	keys     []int
	children []*BPlusNode
	next     *BPlusNode
	isLeaf   bool
}

// NewBPlusNode 创建新节点
func NewBPlusNode(isLeaf bool) *BPlusNode {
	return &BPlusNode{
		keys:     make([]int, 0),
		children: make([]*BPlusNode, 0),
		next:     nil,
		isLeaf:   isLeaf,
	}
}

// BPlusTree B+树结构
type BPlusTree struct {
	root *BPlusNode
}

// NewBPlusTree 创建B+树
func NewBPlusTree() *BPlusTree {
	return &BPlusTree{
		root: NewBPlusNode(true),
	}
}

// FindLeaf 查找叶节点
func (bpt *BPlusTree) FindLeaf(node *BPlusNode, key int) *BPlusNode {
	if node.isLeaf {
		return node
	}

	i := 0
	for i < len(node.keys) && key > node.keys[i] {
		i++
	}

	return bpt.FindLeaf(node.children[i], key)
}

// Search 搜索键值
func (bpt *BPlusTree) Search(key int) bool {
	leaf := bpt.FindLeaf(bpt.root, key)
	for _, k := range leaf.keys {
		if k == key {
			return true
		}
	}
	return false
}

// SplitChild 分裂子节点
func (bpt *BPlusTree) SplitChild(parent *BPlusNode, i int, child *BPlusNode) {
	newChild := NewBPlusNode(child.isLeaf)
	mid := ORDER - 1

	// 复制后半部分键
	for j := 0; j < ORDER-1; j++ {
		newChild.keys = append(newChild.keys, child.keys[j+mid+1])
	}

	// 处理子节点或链表指针
	if !child.isLeaf {
		for j := 0; j < ORDER; j++ {
			newChild.children = append(newChild.children, child.children[j+mid+1])
		}
	} else {
		newChild.next = child.next
		child.next = newChild
	}

	// 在父节点中插入中间键
	parent.keys = append(parent.keys[:i], append([]int{child.keys[mid]}, parent.keys[i:]...)...)
	parent.children = append(parent.children[:i+1], append([]*BPlusNode{newChild}, parent.children[i+1:]...)...)
}

// InsertNonFull 在非满节点中插入
func (bpt *BPlusTree) InsertNonFull(node *BPlusNode, key int) {
	if node.isLeaf {
		// 叶节点直接插入
		i := len(node.keys) - 1
		node.keys = append(node.keys, 0)
		for i >= 0 && key < node.keys[i] {
			node.keys[i+1] = node.keys[i]
			i--
		}
		node.keys[i+1] = key
	} else {
		// 内部节点
		i := len(node.keys) - 1
		for i >= 0 && key < node.keys[i] {
			i--
		}
		i++

		if len(node.children[i].keys) == 2*ORDER-1 {
			bpt.SplitChild(node, i, node.children[i])
			if key > node.keys[i] {
				i++
			}
		}
		bpt.InsertNonFull(node.children[i], key)
	}
}

// Insert 插入键值
func (bpt *BPlusTree) Insert(key int) {
	if len(bpt.root.keys) == 2*ORDER-1 {
		newRoot := NewBPlusNode(false)
		newRoot.children = append(newRoot.children, bpt.root)
		bpt.SplitChild(newRoot, 0, bpt.root)
		bpt.root = newRoot
	}
	bpt.InsertNonFull(bpt.root, key)
}

// Traverse 中序遍历
func (bpt *BPlusTree) Traverse(node *BPlusNode, result *[]int) {
	if node.isLeaf {
		*result = append(*result, node.keys...)
	} else {
		for i := 0; i < len(node.keys); i++ {
			bpt.Traverse(node.children[i], result)
			*result = append(*result, node.keys[i])
		}
		bpt.Traverse(node.children[len(node.keys)], result)
	}
}

func main() {
	fmt.Println("=" + string(make([]byte, 50)))
	fmt.Println("B+树实现 (B+ Tree)")
	fmt.Println("=" + string(make([]byte, 50)))

	bpt := NewBPlusTree()

	values := []int{10, 20, 5, 6, 12, 30, 7, 17}
	fmt.Println("\n插入数据:")
	for _, val := range values {
		fmt.Printf("%d ", val)
		bpt.Insert(val)
	}
	fmt.Println()

	result := []int{}
	bpt.Traverse(bpt.root, &result)
	fmt.Println("\n中序遍历结果:", result)

	fmt.Println("\n搜索测试:")
	testKeys := []int{6, 15, 30}
	for _, key := range testKeys {
		found := bpt.Search(key)
		if found {
			fmt.Printf("  查找 %d: 找到\n", key)
		} else {
			fmt.Printf("  查找 %d: 未找到\n", key)
		}
	}

	fmt.Println("\nB+树特点:")
	fmt.Println("  • 所有数据存储在叶节点")
	fmt.Println("  • 叶节点形成有序链表")
	fmt.Println("  • 适合磁盘存储和范围查询")
	fmt.Println("  • 查找、插入、删除: O(log n)")
	fmt.Println("  • 应用于数据库索引、文件系统")
}
