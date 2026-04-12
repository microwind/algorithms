/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树数据结构 - JavaScript实现
 */

// 树节点类
class TreeNode {
  constructor(value) {
    this.left = null;
    this.right = null;
    this.parent = null;
    this.next = null;
    this.value = value;
  }
}

// 按 idx 作为根节点的"占位"值，buildHeight 为层数构造满二叉树，并设置 parent 指针
function buildFullTree(idx, height) {
  if (height <= 0) {
    return null;
  }
  const node = new TreeNode(idx);
  node.left = buildFullTree(idx * 2, height - 1);
  if (node.left !== null)
    node.left.parent = node;
  node.right = buildFullTree(idx * 2 + 1, height - 1);
  if (node.right !== null)
    node.right.parent = node;
  return node;
}

// 先序遍历（根→左→右）
function printPreOrder(node) {
  if (node === null) {
    return;
  }
  console.log("value: " + node.value);
  printPreOrder(node.left);
  printPreOrder(node.right);
}

// 广度优先遍历（BFS）打印
function printBFS(root) {
  if (root === null)
    return;
  const queue = [root];
  for (let i = 0; i < queue.length; i++) {
    const n = queue[i];
    process.stdout.write(n.value + " ");
    if (n.left !== null)
      queue.push(n.left);
    if (n.right !== null)
      queue.push(n.right);
  }
  console.log();
}

// 找到当前节点所在树的根
function findRoot(node) {
  while (node.parent !== null) {
    node = node.parent;
  }
  return node;
}

// 无额外空间遍历单棵树（含 parent 指针），中序风格打印
function traverseTree(root) {
  let prev = null, current = root;
  while (current !== null) {
    let next;
    if (prev === current.parent) {
      // 从 parent 下来：优先下探左子
      if (current.left !== null) {
        next = current.left;
      } else {
        // 否则中序访问自己
        process.stdout.write(current.value + " ");
        next = (current.right !== null ? current.right : current.parent);
      }
    } else if (prev === current.left) {
      // 从左子回到 current：中序访问自己
      process.stdout.write(current.value + " ");
      next = (current.right !== null ? current.right : current.parent);
    } else {
      // 从右子回到 current：回父节点
      next = current.parent;
    }
    prev = current;
    current = next;
  }
}

// 从任意节点开始遍历串联在一起的多棵树
function traverseFromAnyNode(any) {
  let root = findRoot(any);
  while (root !== null) {
    traverseTree(root);
    root = root.next;
  }
  console.log();
}

// 对单棵树按层序（BFS）重新赋连续值
function assignLevelOrderValues(root, startVal) {
  const queue = [root];
  let val = startVal;
  while (queue.length > 0) {
    const n = queue.shift();
    n.value = val++;
    if (n.left !== null)
      queue.push(n.left);
    if (n.right !== null)
      queue.push(n.right);
  }
  return val;
}

function main() {
  const height = 4;

  // 1) 构造形状（value暂时无意义）
  const T1 = buildFullTree(1, height);
  const T2 = buildFullTree(1, height);
  const T3 = buildFullTree(1, height);

  // 2) 按层序给每棵树分别连续编号：T1 → 1..15, T2 → 16..30, T3 → 31..45
  let nextId = assignLevelOrderValues(T1, 1);
  nextId = assignLevelOrderValues(T2, nextId);
  assignLevelOrderValues(T3, nextId);

  // 3) 串联根：T1 → T2 → T3
  T1.next = T2;
  T2.next = T3;
  T3.next = null;

  console.log("=== 先序遍历 T1 ===");
  printPreOrder(T1);

  console.log("\n=== 广度优先遍历 T1 ===");
  printBFS(T1);

  // 4) 从任意节点遍历
  console.log("\n=== 从任意节点遍历 ===");
  traverseFromAnyNode(T3.left);

  // 5) 从 T2 的某个子节点开始，无额外空间遍历整片"森林"
  const any = T2.left.left;
  console.log("\n=== 从节点 " + any.value + " 开始无栈遍历 ===");
  traverseFromAnyNode(any);
}

main();
