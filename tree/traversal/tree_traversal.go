/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树遍历 - 二叉树遍历实现
 * 实现前序、中序、后序遍历（递归和迭代）
 * 用于树操作、排序、搜索等
 */

package main

import (
	"fmt"
	"strings"
)

// 二叉树节点
type TreeNode struct {
	val   int    // 节点值
	left  *TreeNode // 左子节点
	right *TreeNode // 右子节点
}

// 创建新树节点
func NewTreeNode(val int) *TreeNode {
	return &TreeNode{
		val:   val,  // 节点值
		left:  nil,  // 左子节点初始化为空
		right: nil,  // 右子节点初始化为空
	}
}

// 树遍历函数

/**
 * 前序遍历 - 递归：根-左-右
 */
func preorderRecursive(root *TreeNode) []int {
	var result []int
	
	var traverse func(node *TreeNode)
	traverse = func(node *TreeNode) {
		if node == nil {
			return
		}
		result = append(result, node.val) // 访问根节点
		traverse(node.left)               // 遍历左子树
		traverse(node.right)              // traverse right subtree
	}
	
	traverse(root)
	return result
}

/**
 * 中序遍历 - 递归：左-根-右
 */
func inorderRecursive(root *TreeNode) []int {
	var result []int
	
	var traverse func(node *TreeNode)
	traverse = func(node *TreeNode) {
		if node == nil {
			return
		}
		traverse(node.left)               // 遍历左子树
		result = append(result, node.val) // 访问根节点
		traverse(node.right)              // 遍历右子树
	}
	
	traverse(root)
	return result
}

/**
 * 后序遍历 - 递归：左-右-根
 */
func postorderRecursive(root *TreeNode) []int {
	var result []int
	
	var traverse func(node *TreeNode)
	traverse = func(node *TreeNode) {
		if node == nil {
			return
		}
		traverse(node.left)               // 遍历左子树
		traverse(node.right)              // 遍历右子树
		result = append(result, node.val) // 访问根节点
	}
	
	traverse(root)
	return result
}

/**
 * 前序遍历 - 迭代
 */
func preorderIterative(root *TreeNode) []int {
	var result []int
	var stack []*TreeNode // 使用栈模拟递归
	
	if root != nil {
		stack = append(stack, root) // 根节点入栈
	}
	
	for len(stack) > 0 {
		// 从栈中弹出
		n := len(stack) - 1
		node := stack[n]
		stack = stack[:n]
		
		result = append(result, node.val) // 访问根节点
		
		// 先右后左入栈（这样左节点先处理）
		if node.right != nil {
			stack = append(stack, node.right) // 右子节点入栈
		}
		if node.left != nil {
			stack = append(stack, node.left) // 左子节点入栈
		}
	}
	
	return result
}

/**
 * 中序遍历 - 迭代
 */
func inorderIterative(root *TreeNode) []int {
	var result []int
	var stack []*TreeNode // 使用栈模拟递归
	current := root
	
	for current != nil || len(stack) > 0 {
		// 到达最左节点
		for current != nil {
			stack = append(stack, current) // 节点入栈
			current = current.left // 向左移动
		}
		
		// current为nil，从栈中弹出
		n := len(stack) - 1
		current = stack[n]
		stack = stack[:n]
		
		result = append(result, current.val) // 访问节点
		current = current.right              // 转到右子树
	}
	
	return result
}

/**
 * 后序遍历 - 迭代
 */
func postorderIterative(root *TreeNode) []int {
	var result []int
	var stack1 []*TreeNode // 第一个栈
	var stack2 []*TreeNode // 第二个栈，用于反转顺序
	
	if root != nil {
		stack1 = append(stack1, root) // 根节点入栈
	}
	
	for len(stack1) > 0 {
		// 从栈1弹出
		n := len(stack1) - 1
		node := stack1[n]
		stack1 = stack1[:n]
		
		stack2 = append(stack2, node) // 节点入栈2
		
		// 先左后右入栈（反转顺序）
		if node.left != nil {
			stack1 = append(stack1, node.left) // 左子节点入栈1
		}
		if node.right != nil {
			stack1 = append(stack1, node.right)
		}
	}
	
	// 从栈2弹出得到后序遍历
	for len(stack2) > 0 {
		n := len(stack2) - 1
		result = append(result, stack2[n].val)
		stack2 = stack2[:n]
	}
	
	return result
}

/**
 * 层序遍历（BFS）
 */
func levelOrder(root *TreeNode) []int {
	var result []int
	var queue []*TreeNode // 使用队列进行层序遍历
	
	if root != nil {
		queue = append(queue, root) // 根节点入队
	}
	
	for len(queue) > 0 {
		// 出队
		node := queue[0]
		queue = queue[1:]
		
		result = append(result, node.val)
		
		if node.left != nil {
			queue = append(queue, node.left) // 左子节点入队
		}
		if node.right != nil {
			queue = append(queue, node.right) // 右子节点入队
		}
	}
	
	return result
}

/**
 * 打印树结构
 */
func printTree() {
	fmt.Println("树结构:")
	fmt.Println("      1")
	fmt.Println("     / \\")
	fmt.Println("    2   3")
	fmt.Println("   / \\  /")
	fmt.Println("  4   5 6")
	fmt.Println()
}

/**
 * 打印切片
 */
func printSlice(name string, slice []int) {
	fmt.Printf("%s: [", name)
	for i, val := range slice {
		if i > 0 {
			fmt.Printf(", ")
		}
		fmt.Printf("%d", val)
	}
	fmt.Println("]")
}

/**
 * 主函数 - 测试树遍历
 */
func main() {
	fmt.Println(strings.Repeat("=", 50))
	fmt.Println("树遍历实现")
	fmt.Println(strings.Repeat("=", 50))
	
	// 构建示例树
	//       1
	//      / \\
	//     2   3
	//    / \\  /
	//   4   5 6
	
	root := NewTreeNode(1)
	root.left = NewTreeNode(2)
	root.right = NewTreeNode(3)
	root.left.left = NewTreeNode(4)
	root.left.right = NewTreeNode(5)
	root.right.left = NewTreeNode(6)
	
	printTree()
	
	fmt.Println("递归遍历:")
	printSlice("前序遍历（根-左-右）", preorderRecursive(root))
	printSlice("中序遍历（左-根-右）", inorderRecursive(root))
	printSlice("后序遍历（左-右-根）", postorderRecursive(root))
	fmt.Println()
	
	fmt.Println("迭代遍历:")
	printSlice("前序遍历（根-左-右）", preorderIterative(root))
	printSlice("中序遍历（左-根-右）", inorderIterative(root))
	printSlice("后序遍历（左-右-根）", postorderIterative(root))
	fmt.Println()
	
	fmt.Println("层序遍历（BFS）:")
	printSlice("层序遍历", levelOrder(root))
	fmt.Println()
	
	fmt.Println("遍历特性:")
	fmt.Println("  前序遍历：根节点优先访问")
	fmt.Println("  中序遍历：二叉搜索树中序遍历得到有序序列")
	fmt.Println("  后序遍历：适合树删除")
	fmt.Println("  层序遍历：广度优先遍历")
	fmt.Println()
	
	fmt.Println("时间复杂度:")
	fmt.Println("  所有遍历：O(n)时间，O(n)空间")
	fmt.Println("  迭代方法使用显式栈")
	fmt.Println("  递归方法使用调用栈")
}
