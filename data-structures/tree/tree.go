/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 二叉树数据结构 - Go实现
 */

package main

import "fmt"

// 二叉树节点结构体
type Node struct {
  value int       // 节点值
  left  *Node     // 左子节点
  right *Node     // 右子节点
}

func createNode(value int) *Node {
  return &Node{value: value}
}

// 前序遍历：根 -> 左 -> 右
func preorderTraversal(root *Node) {
  if root == nil {
    return
  }
  fmt.Print(root.value, " ") // 访问根
  preorderTraversal(root.left) // 遍历左子树
  preorderTraversal(root.right) // 遍历右子树
}

// 中序遍历：左 -> 根 -> 右
func inorderTraversal(root *Node) {
  if root == nil {
    return
  }
  inorderTraversal(root.left) // 遍历左子树
  fmt.Print(root.value, " ") // 访问根
  inorderTraversal(root.right) // 遍历右子树
}

// 后序遍历：左 -> 右 -> 根
func postorderTraversal(root *Node) {
  if root == nil {
    return
  }
  postorderTraversal(root.left) // 遍历左子树
  postorderTraversal(root.right) // 遍历右子树
  fmt.Print(root.value, " ") // 访问根
}

func main() {
  // 构建示例二叉树
  //        1
  //       / \
  //      2   3
  //     / \   /
  //    4   5 6
  root := createNode(1)
  root.left = createNode(2)
  root.right = createNode(3)
  root.left.left = createNode(4)
  root.left.right = createNode(5)
  root.right.left = createNode(6)

  // 输出三种遍历结果
  fmt.Print("前序遍历：")
  preorderTraversal(root)
  fmt.Println()

  fmt.Print("中序遍历：")
  inorderTraversal(root)
  fmt.Println()

  fmt.Print("后序遍历：")
  postorderTraversal(root)
  fmt.Println()
}

/*
jarry@MacBook-Pro tree % go run tree.go
前序遍历：1 2 4 5 3 6
中序遍历：4 2 5 1 6 3
后序遍历：4 5 2 6 3 1
*/
