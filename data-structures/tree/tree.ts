/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 树数据结构 - TypeScript实现
 */

// 二叉树节点类
class TreeNode {
  value: number;      // 节点值
  left: TreeNode | null;   // 左子节点
  right: TreeNode | null;  // 右子节点

  constructor(value: number) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

function createNode(value: number): TreeNode {
  return new TreeNode(value);
}

// 前序遍历：根 -> 左 -> 右
function preorderTraversal(root: TreeNode | null, result: number[] = []): number[] {
  if (root === null) {
    return result;
  }
  result.push(root.value); // 访问根
  preorderTraversal(root.left, result); // 遍历左子树
  preorderTraversal(root.right, result); // 遍历右子树
  return result;
}

// 中序遍历：左 -> 根 -> 右
function inorderTraversal(root: TreeNode | null, result: number[] = []): number[] {
  if (root === null) {
    return result;
  }
  inorderTraversal(root.left, result); // 遍历左子树
  result.push(root.value); // 访问根
  inorderTraversal(root.right, result); // 遍历右子树
  return result;
}

// 后序遍历：左 -> 右 -> 根
function postorderTraversal(root: TreeNode | null, result: number[] = []): number[] {
  if (root === null) {
    return result;
  }
  postorderTraversal(root.left, result); // 遍历左子树
  postorderTraversal(root.right, result); // 遍历右子树
  result.push(root.value); // 访问根
  return result;
}

// 构建示例二叉树
//        1
//       / \
//      2   3
//     / \   /
//    4   5 6
const root = createNode(1);
root.left = createNode(2);
root.right = createNode(3);
root.left.left = createNode(4);
root.left.right = createNode(5);
root.right.left = createNode(6);

// 输出三种遍历结果
console.log("前序遍历：", preorderTraversal(root).join(" "));
console.log("中序遍历：", inorderTraversal(root).join(" "));
console.log("后序遍历：", postorderTraversal(root).join(" "));


/*
 * 输出结果：
 * 前序遍历：1 2 4 5 3 6
 * 中序遍历：4 2 5 1 6 3
 * 后序遍历：4 5 2 6 3 1
 */
