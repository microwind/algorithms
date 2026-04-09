// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

/**
 * 树算法 - 二叉搜索树实现 (Binary Search Tree)
 * 有序二叉树，左子树 < 根节点 < 右子树
 * 用于快速查找、插入、删除
 */

package main

import "fmt"

// BST节点结构
type BSTNode struct {
	data  int
	left  *BSTNode
	right *BSTNode
}

// BST类
type BST struct {
	root *BSTNode
}

// 创建新节点
func createBSTNode(data int) *BSTNode {
	return &BSTNode{
		data:  data,
		left:  nil,
		right: nil,
	}
}

// 插入节点到BST
func (bst *BST) insert(node *BSTNode, data int) *BSTNode {
	if node == nil {
		return createBSTNode(data)
	}

	if data < node.data {
		node.left = bst.insert(node.left, data)
	} else if data > node.data {
		node.right = bst.insert(node.right, data)
	}
	// 重复值不允许

	return node
}

// 查找节点
func (bst *BST) search(node *BSTNode, data int) bool {
	if node == nil {
		return false
	}

	if data == node.data {
		return true
	} else if data < node.data {
		return bst.search(node.left, data)
	} else {
		return bst.search(node.right, data)
	}
}

// 中序遍历（升序）
func (bst *BST) inOrder(node *BSTNode) {
	if node != nil {
		bst.inOrder(node.left)
		fmt.Printf("%d ", node.data)
		bst.inOrder(node.right)
	}
}

// 前序遍历
func (bst *BST) preOrder(node *BSTNode) {
	if node != nil {
		fmt.Printf("%d ", node.data)
		bst.preOrder(node.left)
		bst.preOrder(node.right)
	}
}

// 后序遍历
func (bst *BST) postOrder(node *BSTNode) {
	if node != nil {
		bst.postOrder(node.left)
		bst.postOrder(node.right)
		fmt.Printf("%d ", node.data)
	}
}

// 查找最小值
func (bst *BST) findMin(node *BSTNode) *BSTNode {
	for node.left != nil {
		node = node.left
	}
	return node
}

// 查找最大值
func (bst *BST) findMax(node *BSTNode) *BSTNode {
	for node.right != nil {
		node = node.right
	}
	return node
}

// 计算树的高度
func (bst *BST) height(node *BSTNode) int {
	if node == nil {
		return 0
	}

	leftHeight := bst.height(node.left)
	rightHeight := bst.height(node.right)

	return 1 + max(leftHeight, rightHeight)
}

// 计算节点数量
func (bst *BST) nodeCount(node *BSTNode) int {
	if node == nil {
		return 0
	}

	return 1 + bst.nodeCount(node.left) + bst.nodeCount(node.right)
}

// 辅助函数：返回两个数中的较大值
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// 主函数 - 测试BST
func main() {
	bst := BST{}

	fmt.Println("=== 二叉搜索树测试 ===")

	// 插入测试数据
	testData := []int{50, 30, 70, 20, 40, 60, 80}
	fmt.Printf("插入数据: ")
	for _, data := range testData {
		fmt.Printf("%d ", data)
		bst.root = bst.insert(bst.root, data)
	}
	fmt.Println()
	fmt.Println()

	// 遍历测试
	fmt.Println("=== 遍历测试 ===")
	fmt.Printf("中序遍历: ")
	bst.inOrder(bst.root)
	fmt.Println()

	fmt.Printf("前序遍历: ")
	bst.preOrder(bst.root)
	fmt.Println()

	fmt.Printf("后序遍历: ")
	bst.postOrder(bst.root)
	fmt.Println()
	fmt.Println()

	// 搜索测试
	fmt.Println("=== 搜索测试 ===")
	searchKeys := []int{40, 90}
	for _, key := range searchKeys {
		found := bst.search(bst.root, key)
		fmt.Printf("搜索 %d: %s\n", key, map[bool]string{true: "找到", false: "未找到"}[found])
	}
	fmt.Println()

	// 树属性测试
	fmt.Println("=== 树属性测试 ===")
	fmt.Printf("树的高度: %d\n", bst.height(bst.root))
	fmt.Printf("节点数量: %d\n", bst.nodeCount(bst.root))

	if bst.root != nil {
		fmt.Printf("最小值: %d\n", bst.findMin(bst.root).data)
		fmt.Printf("最大值: %d\n", bst.findMax(bst.root).data)
	}

	fmt.Println()
	fmt.Println("=== BST特点说明 ===")
	fmt.Println("1. 左子树所有节点 < 根节点 < 右子树所有节点")
	fmt.Println("2. 中序遍历得到有序序列")
	fmt.Println("3. 查找、插入、删除平均时间复杂度 O(log n)")
	fmt.Println("4. 最坏情况（退化为链表）时间复杂度 O(n)")
}

// 打印结果
/*
jarry@Mac bst % go run bst.go
=== 二叉搜索树测试 ===
插入数据: 50 30 70 20 40 60 80 

=== 遍历测试 ===
中序遍历: 20 30 40 50 60 70 80 
前序遍历: 50 30 20 40 70 60 80 
后序遍历: 20 40 30 60 80 70 50 

=== 搜索测试 ===
搜索 40: 找到
搜索 90: 未找到

=== 树属性测试 ===
树的高度: 3
节点数量: 7
最小值: 20
最大值: 80

=== BST特点说明 ===
1. 左子树所有节点 < 根节点 < 右子树所有节点
2. 中序遍历得到有序序列
3. 查找、插入、删除平均时间复杂度 O(log n)
4. 最坏情况（退化为链表）时间复杂度 O(n)
*/
