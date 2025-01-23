/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

package main

import (
  "fmt"
)

// TreeNode 定义二叉树节点
type TreeNode struct {
  Value int
  Left  *TreeNode
  Right *TreeNode
}

// 1. 先序优先遍历 DLR 递归版
func preOrderTraverse(tree *TreeNode, result *[]int) {
  if tree != nil {
    *result = append(*result, tree.Value)
    preOrderTraverse(tree.Left, result)
    preOrderTraverse(tree.Right, result)
  }
}

// 2. 中序优先遍历 LDR 递归版
func inOrderTraverse(tree *TreeNode, result *[]int) {
  if tree != nil {
    inOrderTraverse(tree.Left, result)
    *result = append(*result, tree.Value)
    inOrderTraverse(tree.Right, result)
  }
}

// 3. 后序优先遍历 LRD 递归版
func postOrderTraverse(tree *TreeNode, result *[]int) {
  if tree != nil {
    postOrderTraverse(tree.Left, result)
    postOrderTraverse(tree.Right, result)
    *result = append(*result, tree.Value)
  }
}

// 4. 广度优先遍历（层级遍历）
func levelOrder(tree *TreeNode) []int {
  var result []int
  var queue []*TreeNode
  if tree != nil {
    queue = append(queue, tree)
    for len(queue) > 0 {
      node := queue[0]
      queue = queue[1:]
      // append children of current Node to result
      result = append(result, node.Value)
      if node.Left != nil {
        queue = append(queue, node.Left)
      }
      if node.Right != nil {
        queue = append(queue, node.Right)
      }
    }
  }
  return result
}

// 5. 深度遍历（先序非递归版）
func preOrderUnRecursive(tree *TreeNode) []int {
  var result []int
  var stack []*TreeNode
  for tree != nil || len(stack) > 0 {
    if tree != nil {
      result = append(result, tree.Value)
      stack = append(stack, tree)
      tree = tree.Left
    } else {
      tree = stack[len(stack)-1]
      stack = stack[:len(stack)-1]
      tree = tree.Right
    }
  }
  return result
}

// 6. 深度遍历（中序非递归版）
func inOrderUnRecursive(tree *TreeNode) []int {
  var result []int
  var stack []*TreeNode
  for tree != nil || len(stack) > 0 {
    if tree != nil {
      stack = append(stack, tree)
      tree = tree.Left
    } else {
      tree = stack[len(stack)-1]
      stack = stack[:len(stack)-1]
      result = append(result, tree.Value)
      tree = tree.Right
    }
  }
  return result
}

// 7. 深度遍历（后序非递归版）
// 后序遍历顺序：左子树 -> 右子树 -> 根节点。
// 使用栈模拟递归的过程，并通过一个变量 lastVisited 来记录上一次访问的节点。
func postOrderUnRecursive(tree *TreeNode) []int {
  var result []int          // 遍历结果
  var stack []*TreeNode     // 存储节点的栈
  var lastVisited *TreeNode // 最后访问的节点

  // 当前节点不为空或者栈不为空时，继续遍历，否则遍历完成
  for tree != nil || len(stack) > 0 {
    if tree != nil {
      // 如果当前节点不为空，则将其压入栈并遍历左子树
      stack = append(stack, tree)
      tree = tree.Left
    } else {
      // 查看栈顶节点（但不弹出）
      peekNode := stack[len(stack)-1]

      // 如果右子树存在，且右子树还未被访问过
      if peekNode.Right != nil && lastVisited != peekNode.Right {
        // 切换到右子树进行遍历
        tree = peekNode.Right
      } else {
        // 如果右子树不存在，或者右子树已经遍历过，则访问当前节点
        result = append(result, peekNode.Value)

        // 记录当前节点为最后访问的节点
        lastVisited = peekNode

        // 弹出当前节点
        stack = stack[:len(stack)-1]
      }
    }
  }

  // 返回后序遍历结果
  return result
}

/* === test === */

// 测试代码
func main() {
  // 二叉树数据
  /*
             1
         /      \
       2          3
     /   \      /    \
     4     5    6      7
         /  \
         8    9
  */
  tree := &TreeNode{
    Value: 1,
    Left: &TreeNode{
      Value: 2,
      Left:  &TreeNode{Value: 4},
      Right: &TreeNode{
        Value: 5,
        Left:  &TreeNode{Value: 8},
        Right: &TreeNode{Value: 9},
      },
    },
    Right: &TreeNode{
      Value: 3,
      Left:  &TreeNode{Value: 6},
      Right: &TreeNode{Value: 7},
    },
  }

  var result []int

  // 1. 先序优先遍历 DLR
  preOrderTraverse(tree, &result)
  //  [1, 2, 4, 5, 8, 9, 3, 6, 7]
  fmt.Println("1. preOrderTraverse:", result)

  // 2. 中序优先遍历 LDR
  result = []int{}
  inOrderTraverse(tree, &result)
  // [4, 2, 8, 5, 9, 1, 6, 3, 7]
  fmt.Println("2. inOrderTraverse:", result)

  // 3. 后序优先遍历 LRD
  result = []int{}
  postOrderTraverse(tree, &result)
  //  [4, 8, 9, 5, 2, 6, 7, 3, 1]
  fmt.Println("3. postOrderTraverse:", result)

  // 4. 广度优先遍历
  // [1, 2, 3, 4, 5, 6, 7, 8, 9]
  fmt.Println("4. levelOrder:", levelOrder(tree))

  // 5. 深度遍历（先序非递归）
  // [1, 2, 4, 5, 8, 9, 3, 6, 7]
  fmt.Println("5. preOrderUnRecursive:", preOrderUnRecursive(tree))

  // 6. 深度遍历（中序非递归）
  // [4, 2, 8, 5, 9, 1, 6, 3, 7]
  fmt.Println("6. inOrderUnRecursive:", inOrderUnRecursive(tree))

  // 7. 深度遍历（后序非递归）
  // [4, 8, 9, 5, 2, 6, 7, 3, 1]
  fmt.Println("7. postOrderUnRecursive:", postOrderUnRecursive(tree))
}

/**
jarry@MacBook-Pro binarytree % go run ./binary_tree.go
1. preOrderTraverse: [1 2 4 5 8 9 3 6 7]
2. inOrderTraverse: [4 2 8 5 9 1 6 3 7]
3. postOrderTraverse: [4 8 9 5 2 6 7 3 1]
4. levelOrder: [1 2 3 4 5 6 7 8 9]
5. preOrderUnRecursive: [1 2 4 5 8 9 3 6 7]
6. inOrderUnRecursive: [4 2 8 5 9 1 6 3 7]
7. postOrderUnRecursive: [4 8 9 5 2 6 7 3 1]
*/
