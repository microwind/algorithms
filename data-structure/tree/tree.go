package main

import "fmt"

// 定义树的节点结构
type Node struct {
  value int
  left  *Node
  right *Node
}

// 创建新节点
func createNode(value int) *Node {
  return &Node{value: value}
}

// 前序遍历：根 -> 左 -> 右
func preorderTraversal(root *Node) {
  if root == nil {
    return
  }
  fmt.Print(root.value, " ")
  preorderTraversal(root.left)
  preorderTraversal(root.right)
}

// 中序遍历：左 -> 根 -> 右
func inorderTraversal(root *Node) {
  if root == nil {
    return
  }
  inorderTraversal(root.left)
  fmt.Print(root.value, " ")
  inorderTraversal(root.right)
}

// 后序遍历：左 -> 右 -> 根
func postorderTraversal(root *Node) {
  if root == nil {
    return
  }
  postorderTraversal(root.left)
  postorderTraversal(root.right)
  fmt.Print(root.value, " ")
}

func main() {
  // 创建树
  /*
         1
        / \
       2   3
      / \   /
     4   5 6
  */
  root := createNode(1)
  root.left = createNode(2)
  root.right = createNode(3)
  root.left.left = createNode(4)
  root.left.right = createNode(5)
  root.right.left = createNode(6)

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
