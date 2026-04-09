// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

/**
 * 树算法 - AVL树实现 (Adelson-Velsky and Landis Tree)
 * 自平衡二叉搜索树，确保高度差不超过1
 * 保证查找、插入、删除都是O(log n)时间复杂度
 */

package main

import "fmt"

// AVL节点结构
type AVLNode struct {
	data   int
	height int
	left   *AVLNode
	right  *AVLNode
}

// 获取节点高度
func getHeight(node *AVLNode) int {
	if node == nil {
		return 0
	}
	return node.height
}

// 计算平衡因子
func getBalance(node *AVLNode) int {
	if node == nil {
		return 0
	}
	return getHeight(node.left) - getHeight(node.right)
}

// 更新节点高度
func updateHeight(node *AVLNode) {
	if node != nil {
		leftHeight := getHeight(node.left)
		rightHeight := getHeight(node.right)
		node.height = 1 + max(leftHeight, rightHeight)
	}
}

// 辅助函数：返回两个数中的较大值
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// 右旋转
func rightRotate(y *AVLNode) *AVLNode {
	x := y.left
	T2 := x.right

	// 旋转
	x.right = y
	y.left = T2

	// 更新高度
	updateHeight(y)
	updateHeight(x)

	return x
}

// 左旋转
func leftRotate(x *AVLNode) *AVLNode {
	y := x.right
	T2 := y.left

	// 旋转
	y.left = x
	x.right = T2

	// 更新高度
	updateHeight(x)
	updateHeight(y)

	return y
}

// 插入节点
func insert(root *AVLNode, data int) *AVLNode {
	// 1. 标准BST插入
	if root == nil {
		return &AVLNode{data: data, height: 1}
	}

	if data < root.data {
		root.left = insert(root.left, data)
	} else if data > root.data {
		root.right = insert(root.right, data)
	} else {
		// 重复值不允许
		return root
	}

	// 2. 更新高度
	updateHeight(root)

	// 3. 获取平衡因子
	balance := getBalance(root)

	// 4. 如果不平衡，有4种情况

	// 左左情况
	if balance > 1 && data < root.left.data {
		return rightRotate(root)
	}

	// 右右情况
	if balance < -1 && data > root.right.data {
		return leftRotate(root)
	}

	// 左右情况
	if balance > 1 && data > root.left.data {
		root.left = leftRotate(root.left)
		return rightRotate(root)
	}

	// 右左情况
	if balance < -1 && data < root.right.data {
		root.right = rightRotate(root.right)
		return leftRotate(root)
	}

	return root
}

// 中序遍历
func inOrder(root *AVLNode) {
	if root != nil {
		inOrder(root.left)
		fmt.Printf("%d ", root.data)
		inOrder(root.right)
	}
}

// 打印平衡因子
func printBalanceFactor(root *AVLNode) {
	if root != nil {
		printBalanceFactor(root.left)
		fmt.Printf("节点 %d: 平衡因子 = %d\n", root.data, getBalance(root))
		printBalanceFactor(root.right)
	}
}

// 主函数 - 测试AVL树
func main() {
	var root *AVLNode

	fmt.Println("=== AVL树测试 ===")

	// 插入测试数据
	testData := []int{10, 20, 30, 40, 50, 25}
	fmt.Printf("插入数据: %v\n", testData)

	for _, data := range testData {
		root = insert(root, data)
		fmt.Printf("插入 %d 后的中序遍历:\n", data)
		inOrder(root)
		fmt.Println()
	}

	fmt.Println("最终平衡因子:")
	printBalanceFactor(root)
}

// 打印结果
/*
jarry@Mac avl % go run avl.go
=== AVL树测试 ===
插入数据: [10 20 30 40 50 25]
插入 10 后的中序遍历:
10 
插入 20 后的中序遍历:
10 20 
插入 30 后的中序遍历:
10 20 30 
插入 40 后的中序遍历:
10 20 30 40 
插入 50 后的中序遍历:
10 20 30 40 50 
插入 25 后的中序遍历:
10 20 25 30 40 50 
最终平衡因子:
节点 10: 平衡因子 = 0
节点 20: 平衡因子 = 0
节点 25: 平衡因子 = 0
节点 30: 平衡因子 = -1
节点 40: 平衡因子 = 0
节点 50: 平衡因子 = 0
*/
