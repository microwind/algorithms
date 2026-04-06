// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

/**
 * 树递归算法示例 - 二叉树遍历
 *
 * 算法特点：
 * - 二叉树的遍历是递归的典型应用
 * - 包含前序、中序、后序遍历
 * - 时间复杂度: O(n)，空间复杂度: O(h)
 *
 * 学习重点：理解递归在树结构中的应用
 */
package main

import "fmt"

// 定义二叉树节点
type Node struct {
	data  int
	left  *Node
	right *Node
}

// 创建新节点
// @param data 节点数据
// @return 新节点
func newNode(data int) *Node {
	return &Node{data: data, left: nil, right: nil}
}

// 前序遍历
// 时间复杂度: O(n)，空间复杂度: O(h)
// @param node 根节点
func preOrder(node *Node) {
	// 基本情况：空节点
	if node == nil {
		return
	}

	// 访问根节点
	fmt.Printf("%d ", node.data)

	// 递归遍历左子树
	preOrder(node.left)

	// 递归遍历右子树
	preOrder(node.right)
}

// 主函数 - 测试二叉树遍历
func main() {
	// 测试1：创建二叉树
	root := newNode(1)
	root.left = newNode(2)
	root.right = newNode(3)
	root.left.left = newNode(4)
	root.left.right = newNode(5)

	// 输出调用过程示例
	fmt.Println("调用过程示例：")
	fmt.Println("preOrder(root)")
	fmt.Println("   |")
	fmt.Println("   v")
	fmt.Println("printf(1)")
	fmt.Println("preOrder(root.left)")
	fmt.Println("   |")
	fmt.Println("   v")
	fmt.Println("printf(2)")
	fmt.Println("preOrder(root.left.left)")
	fmt.Println("   |")
	fmt.Println("   v")
	fmt.Println("printf(4)")
	fmt.Println("preOrder(root.left.right)")
	fmt.Println("   |")
	fmt.Println("   v")
	fmt.Println("printf(5)")
	fmt.Println("preOrder(root.right)")
	fmt.Println("   |")
	fmt.Println("   v")
	fmt.Println("printf(3)")
	fmt.Println()

	// 测试2：执行前序遍历
	fmt.Println("Preorder traversal of binary tree is")
	preOrder(root)
}

/*打印结果
jarry@Mac tree-recursion % go run tree.go
调用过程示例：
preOrder(root)
   |
   v
printf(1)
preOrder(root.left)
   |
   v
printf(2)
preOrder(root.left.left)
   |
   v
printf(4)
preOrder(root.left.right)
   |
   v
printf(5)
preOrder(root.right)
   |
   v
printf(3)

Preorder traversal of binary tree is
1 2 4 5 3
*/

// 打印结果示例
/*
jarry@Mac tree-recursion % go run tree.go
调用过程示例：
preOrder(root)
   |
   v
printf(1)
preOrder(root.left)
   |
   v
printf(2)
preOrder(root.left.left)
   |
   v
printf(4)
preOrder(root.left.right)
   |
   v
printf(5)
preOrder(root.right)
   |
   v
printf(3)

Preorder traversal of binary tree is
1 2 4 5 3
*/
