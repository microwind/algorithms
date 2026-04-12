/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树数据结构 - Go实现
 */

package main

import "fmt"

// 树节点结构体
type TreeNode struct {
	left   *TreeNode
	right  *TreeNode
	parent *TreeNode
	next   *TreeNode
	value  int
}

// 创建新节点
func createNode(value int) *TreeNode {
	return &TreeNode{
		value: value,
	}
}

// 按 idx 作为根节点的"占位"值，buildHeight 为层数构造满二叉树，并设置 parent 指针
func buildFullTree(idx, height int) *TreeNode {
	if height <= 0 {
		return nil
	}
	node := createNode(idx)
	node.left = buildFullTree(idx*2, height-1)
	if node.left != nil {
		node.left.parent = node
	}
	node.right = buildFullTree(idx*2+1, height-1)
	if node.right != nil {
		node.right.parent = node
	}
	return node
}

// 先序遍历（根→左→右）
func printPreOrder(node *TreeNode) {
	if node == nil {
		return
	}
	fmt.Println("value:", node.value)
	printPreOrder(node.left)
	printPreOrder(node.right)
}

// 广度优先遍历（BFS）打印
func printBFS(root *TreeNode) {
	if root == nil {
		return
	}
	queue := []*TreeNode{root}
	for i := 0; i < len(queue); i++ {
		n := queue[i]
		fmt.Print(n.value, " ")
		if n.left != nil {
			queue = append(queue, n.left)
		}
		if n.right != nil {
			queue = append(queue, n.right)
		}
	}
	fmt.Println()
}

// 找到当前节点所在树的根
func findRoot(node *TreeNode) *TreeNode {
	for node.parent != nil {
		node = node.parent
	}
	return node
}

// 无额外空间遍历单棵树（含 parent 指针），中序风格打印
func traverseTree(root *TreeNode) {
	var prev, current *TreeNode = nil, root
	for current != nil {
		var next *TreeNode
		if prev == current.parent {
			// 从 parent 下来：优先下探左子
			if current.left != nil {
				next = current.left
			} else {
				// 否则中序访问自己
				fmt.Print(current.value, " ")
				if current.right != nil {
					next = current.right
				} else {
					next = current.parent
				}
			}
		} else if prev == current.left {
			// 从左子回到 current：中序访问自己
			fmt.Print(current.value, " ")
			if current.right != nil {
				next = current.right
			} else {
				next = current.parent
			}
		} else {
			// 从右子回到 current：回父节点
			next = current.parent
		}
		prev = current
		current = next
	}
}

// 从任意节点开始遍历串联在一起的多棵树
func traverseFromAnyNode(any *TreeNode) {
	root := findRoot(any)
	for root != nil {
		traverseTree(root)
		root = root.next
	}
	fmt.Println()
}

// 对单棵树按层序（BFS）重新赋连续值
func assignLevelOrderValues(root *TreeNode, startVal int) int {
	queue := []*TreeNode{root}
	val := startVal
	for len(queue) > 0 {
		n := queue[0]
		queue = queue[1:]
		n.value = val
		val++
		if n.left != nil {
			queue = append(queue, n.left)
		}
		if n.right != nil {
			queue = append(queue, n.right)
		}
	}
	return val
}

func main() {
	height := 4

	// 1) 构造形状（value暂时无意义）
	T1 := buildFullTree(1, height)
	T2 := buildFullTree(1, height)
	T3 := buildFullTree(1, height)

	// 2) 按层序给每棵树分别连续编号：T1 → 1..15, T2 → 16..30, T3 → 31..45
	nextId := assignLevelOrderValues(T1, 1)
	nextId = assignLevelOrderValues(T2, nextId)
	assignLevelOrderValues(T3, nextId)

	// 3) 串联根：T1 → T2 → T3
	T1.next = T2
	T2.next = T3
	T3.next = nil

	fmt.Println("=== 先序遍历 T1 ===")
	printPreOrder(T1)

	fmt.Println("\n=== 广度优先遍历 T1 ===")
	printBFS(T1)

	// 4) 从任意节点遍历
	fmt.Println("\n=== 从任意节点遍历 ===")
	traverseFromAnyNode(T3.left)

	// 5) 从 T2 的某个子节点开始，无额外空间遍历整片"森林"
	any := T2.left.left
	fmt.Println("\n=== 从节点", any.value, "开始无栈遍历 ===")
	traverseFromAnyNode(any)
}
