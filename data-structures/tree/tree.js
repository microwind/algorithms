/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 二叉树数据结构 - JavaScript实现
 */
// 二叉树节点类：值、左子节点、右子节点
class TreeNode {
  constructor(value) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

// 前序遍历：根 -> 左 -> 右
function preorderTraversal(root) {
  if (root === null) return;
  process.stdout.write(root.value + " "); // 访问根节点
  preorderTraversal(root.left);           // 遍历左子树
  preorderTraversal(root.right);          // 遍历右子树
}

// 中序遍历：左 -> 根 -> 右
function inorderTraversal(root) {
  if (root === null) return;
  inorderTraversal(root.left);            // 遍历左子树
  process.stdout.write(root.value + " "); // 访问根节点
  inorderTraversal(root.right);           // 遍历右子树
}

// 后序遍历：左 -> 右 -> 根
function postorderTraversal(root) {
  if (root === null) return;
  postorderTraversal(root.left);          // 遍历左子树
  postorderTraversal(root.right);         // 遍历右子树
  process.stdout.write(root.value + " "); // 访问根节点
}

// 测试函数：构建二叉树并输出三种遍历结果
function test() {
  // 构建示例二叉树
  //       1
  //      / \
  //     2   3
  //    / \ /
  //   4  5 6
  let root = new TreeNode(1);
  root.left = new TreeNode(2);
  root.right = new TreeNode(3);
  root.left.left = new TreeNode(4);
  root.left.right = new TreeNode(5);
  root.right.left = new TreeNode(6);

  process.stdout.write("前序遍历：");
  preorderTraversal(root);
  console.log();

  process.stdout.write("中序遍历：");
  inorderTraversal(root);
  console.log();

  process.stdout.write("后序遍历：");
  postorderTraversal(root);
  console.log();
}

test();

/*
jarry@MacBook-Pro tree % node tree.js
前序遍历：1 2 4 5 3 6 
中序遍历：4 2 5 1 6 3 
后序遍历：4 5 2 6 3 1 
*/