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
  process.stdout.write(root.value + " ");
  preorderTraversal(root.left);
  preorderTraversal(root.right);
}

// 中序遍历：左 -> 根 -> 右
function inorderTraversal(root) {
  if (root === null) return;
  inorderTraversal(root.left);
  process.stdout.write(root.value + " ");
  inorderTraversal(root.right);
}

// 后序遍历：左 -> 右 -> 根
function postorderTraversal(root) {
  if (root === null) return;
  postorderTraversal(root.left);
  postorderTraversal(root.right);
  process.stdout.write(root.value + " ");
}

// 测试函数
function test() {
  let root = new TreeNode(1);
  root.left = new TreeNode(2);
  root.right = new TreeNode(3);
  root.left.left = new TreeNode(4);
  root.left.right = new TreeNode(5);
  root.right.left = new TreeNode(6);

  process.stdout.write("前序遍历：");
  preorderTraversal(root);
  console.log(); // 换行

  process.stdout.write("中序遍历：");
  inorderTraversal(root);
  console.log(); // 换行

  process.stdout.write("后序遍历：");
  postorderTraversal(root);
  console.log(); // 换行
}

// 调用测试函数
test();

/*
jarry@MacBook-Pro tree % node tree.js
前序遍历：1 2 4 5 3 6 
中序遍历：4 2 5 1 6 3 
后序遍历：4 5 2 6 3 1 
*/