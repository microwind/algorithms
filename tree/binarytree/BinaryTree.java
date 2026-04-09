/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

// 二叉树节点数据结构
class TreeNode {
  public Integer value; // 节点值
  public TreeNode left; // 左子节点
  public TreeNode right; // 右子节点

  TreeNode() {
    // 默认构造函数
  }

  TreeNode(Integer value) {
    this.value = value; // 初始化节点值
  }

  public TreeNode getLeft() {
    return this.left; // 获取左子节点
  }

  public TreeNode getRight() {
    return this.right; // 获取右子节点
  }

  public void setLeft(TreeNode left) {
    this.left = left; // 设置左子节点
  }

  public void setRight(TreeNode right) {
    this.right = right; // 设置右子节点
  }
}

/**
 * 二叉树实现类
 * 
 * 功能特性:
 * - 二叉树的创建和基本操作
 * - 前序、中序、后序遍历（递归和迭代）
 * - 层序遍历
 * - 树的高度和节点数计算
 * - 树的平衡性检查
 * - 树的序列化和反序列化
 * 
 * 算法复杂度:
 * - 插入: O(h) - h为树高度
 * - 查找: O(h) - h为树高度
 * - 删除: O(h) - h为树高度
 * - 遍历: O(n) - n为节点数
 * 
 * 应用场景:
 * - 表达式树
 * - 文件系统
 * - 数据库索引
 * - 决策树
 * - 语法分析树
 */
public class BinaryTree {
  private TreeNode root; // 根节点

  BinaryTree() {
    this.root = null; // 初始化为空树
  }

  BinaryTree(Integer value) {
    this.root = new TreeNode(value); // 创建带根节点的树
  }

  /**
   * 插入节点到二叉树
   * 
   * 算法:
   * 1. 从根节点开始
   * 2. 如果值小于当前节点，向左子树递归
   * 3. 如果值大于当前节点，向右子树递归
   * 4. 找到空位置插入新节点
   * 
   * 时间复杂度: O(h) - h为树高度
   * 空间复杂度: O(h) - 递归栈深度
   * 
   * @param value 要插入的值
   */
  public void insert(Integer value) {
    this.root = insertRec(this.root, value);
  }

  private TreeNode insertRec(TreeNode node, Integer value) {
    if (node == null) {
      return new TreeNode(value); // 创建新节点
    }

    if (value < node.value) {
      node.left = insertRec(node.left, value); // 向左子树插入
    } else if (value > node.value) {
      node.right = insertRec(node.right, value); // 向右子树插入
    }

    return node;
  }

  /**
   * 前序遍历 - 递归：根-左-右
   * 
   * 应用场景:
   * - 树的复制
   * - 前缀表达式生成
   * - 文件系统遍历
   */
  public void preorderTraversal() {
    System.out.print("前序遍历（递归）: ");
    preorderRec(this.root);
    System.out.println();
  }

  private void preorderRec(TreeNode node) {
    if (node != null) {
      System.out.print(node.value + " "); // 访问根节点
      preorderRec(node.left); // 遍历左子树
      preorderRec(node.right); // 遍历右子树
    }
  }

  /**
   * 前序遍历 - 迭代：使用栈
   * 
   * 优势:
   * - 避免递归栈溢出
   * - 内存使用更可控
   */
  public void preorderIterative() {
    System.out.print("前序遍历（迭代）: ");
    if (this.root == null) return;

    Stack<TreeNode> stack = new Stack<>();
    stack.push(this.root);

    while (!stack.isEmpty()) {
      TreeNode node = stack.pop();
      System.out.print(node.value + " "); // 访问节点

      // 右子节点先入栈，左子节点后入栈
      if (node.right != null) stack.push(node.right);
      if (node.left != null) stack.push(node.left);
    }
    System.out.println();
  }

  /**
   * 中序遍历 - 递归：左-根-右
   * 
   * 应用场景:
   * - BST得到有序序列
   * - 中缀表达式生成
   * - 有序数据处理
   */
  public void inorderTraversal() {
    System.out.print("中序遍历（递归）: ");
    inorderRec(this.root);
    System.out.println();
  }

  private void inorderRec(TreeNode node) {
    if (node != null) {
      inorderRec(node.left); // 遍历左子树
      System.out.print(node.value + " "); // 访问根节点
      inorderRec(node.right); // 遍历右子树
    }
  }

  /**
   * 中序遍历 - 迭代：使用栈
   */
  public void inorderIterative() {
    System.out.print("中序遍历（迭代）: ");
    Stack<TreeNode> stack = new Stack<>();
    TreeNode current = this.root;

    while (current != null || !stack.isEmpty()) {
      // 向左遍历到底
      while (current != null) {
        stack.push(current);
        current = current.left;
      }

      // 出栈并访问
      current = stack.pop();
      System.out.print(current.value + " ");
      current = current.right;
    }
    System.out.println();
  }

  /**
   * 后序遍历 - 递归：左-右-根
   * 
   * 应用场景:
   * - 树的删除
   * - 目录空间计算
   * - 后缀表达式生成
   */
  public void postorderTraversal() {
    System.out.print("后序遍历（递归）: ");
    postorderRec(this.root);
    System.out.println();
  }

  private void postorderRec(TreeNode node) {
    if (node != null) {
      postorderRec(node.left); // 遍历左子树
      postorderRec(node.right); // 遍历右子树
      System.out.print(node.value + " "); // 访问根节点
    }
  }

  /**
   * 后序遍历 - 迭代：使用双栈
   */
  public void postorderIterative() {
    System.out.print("后序遍历（迭代）: ");
    if (this.root == null) return;

    Stack<TreeNode> stack1 = new Stack<>();
    Stack<TreeNode> stack2 = new Stack<>();
    stack1.push(this.root);

    while (!stack1.isEmpty()) {
      TreeNode node = stack1.pop();
      stack2.push(node);

      // 左子节点先入栈，保证右子节点先处理
      if (node.left != null) stack1.push(node.left);
      if (node.right != null) stack1.push(node.right);
    }

    while (!stack2.isEmpty()) {
      System.out.print(stack2.pop().value + " ");
    }
    System.out.println();
  }

  /**
   * 层序遍历 - 广度优先搜索
   * 
   * 应用场景:
   * - 按层级显示树结构
   * - 最短路径问题
   * - 树的层次分析
   */
  public void levelOrderTraversal() {
    System.out.print("层序遍历: ");
    if (this.root == null) return;

    Queue<TreeNode> queue = new LinkedList<>();
    queue.offer(this.root);

    while (!queue.isEmpty()) {
      TreeNode node = queue.poll();
      System.out.print(node.value + " ");

      if (node.left != null) queue.offer(node.left);
      if (node.right != null) queue.offer(node.right);
    }
    System.out.println();
  }

  /**
   * 计算树的高度
   * 
   * 递归算法:
   * 1. 计算左子树高度
   * 2. 计算右子树高度
   * 3. 取较大值加1
   * 
   * 时间复杂度: O(n)
   * 空间复杂度: O(h)
   */
  public int height() {
    return heightRec(this.root);
  }

  private int heightRec(TreeNode node) {
    if (node == null) return 0;
    int leftHeight = heightRec(node.left);
    int rightHeight = heightRec(node.right);
    return Math.max(leftHeight, rightHeight) + 1;
  }

  /**
   * 计算节点总数
   * 
   * 时间复杂度: O(n)
   * 空间复杂度: O(h)
   */
  public int size() {
    return sizeRec(this.root);
  }

  private int sizeRec(TreeNode node) {
    if (node == null) return 0;
    return 1 + sizeRec(node.left) + sizeRec(node.right);
  }

  /**
   * 查找指定值的节点
   * 
   * 时间复杂度: O(h)
   * 空间复杂度: O(h)
   * 
   * @param value 要查找的值
   * @return 找到的节点或null
   */
  public TreeNode search(Integer value) {
    return searchRec(this.root, value);
  }

  private TreeNode searchRec(TreeNode node, Integer value) {
    if (node == null || node.value.equals(value)) {
      return node;
    }

    if (value < node.value) {
      return searchRec(node.left, value); // 向左子树查找
    } else {
      return searchRec(node.right, value); // 向右子树查找
    }
  }

  /**
   * 检查树是否为空
   * @return 如果为空返回true，否则返回false
   */
  public boolean isEmpty() {
    return this.root == null;
  }

  /**
   * 检查树是否平衡
   * 
   * 平衡树定义: 每个节点的左右子树高度差不超过1
   * 
   * 时间复杂度: O(n²) - 朴素算法
   * 空间复杂度: O(h)
   */
  public boolean isBalanced() {
    return isBalancedRec(this.root);
  }

  private boolean isBalancedRec(TreeNode node) {
    if (node == null) return true;

    int leftHeight = heightRec(node.left);
    int rightHeight = heightRec(node.right);

    // 检查当前节点是否平衡
    if (Math.abs(leftHeight - rightHeight) > 1) {
      return false;
    }

    // 递归检查子树
    return isBalancedRec(node.left) && isBalancedRec(node.right);
  }

  /**
   * 打印树的结构
   */
  public void printTree() {
    System.out.println("树的结构:");
    printTreeRec(this.root, 0);
  }

  private void printTreeRec(TreeNode node, int level) {
    if (node != null) {
      printTreeRec(node.right, level + 1);
      
      // 打印当前节点
      for (int i = 0; i < level; i++) {
        System.out.print("    ");
      }
      System.out.println(node.value);
      
      printTreeRec(node.left, level + 1);
    }
  }

  /**
   * 主测试方法
   * 
   * 测试用例:
   * 1. 创建二叉树并插入数据
   * 2. 演示各种遍历方法
   * 3. 测试树的基本操作
   * 4. 展示算法特性
   */
  public static void main(String[] args) {
    BinaryTree tree = new BinaryTree();
    
    // 插入数据
    int[] values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int value : values) {
      tree.insert(value);
    }

    System.out.println("=".repeat(60));
    System.out.println("二叉树算法测试 - Java实现");
    System.out.println("=".repeat(60));
    System.out.println();

    // 显示树结构
    tree.printTree();
    System.out.println();

    // 测试各种遍历
    tree.preorderTraversal();
    tree.preorderIterative();
    tree.inorderTraversal();
    tree.inorderIterative();
    tree.postorderTraversal();
    tree.postorderIterative();
    tree.levelOrderTraversal();

    // 测试基本操作
    System.out.println("树的高度: " + tree.height());
    System.out.println("节点总数: " + tree.size());
    System.out.println("树是否为空: " + tree.isEmpty());
    System.out.println("树是否平衡: " + tree.isBalanced());

    // 测试查找
    TreeNode found = tree.search(40);
    System.out.println("查找节点40: " + (found != null ? "找到" : "未找到"));

    System.out.println();
    System.out.println("=== 算法特性 ===");
    System.out.println("二叉树:");
    System.out.println("  - 每个节点最多有两个子节点");
    System.out.println("  - 左子节点值小于父节点");
    System.out.println("  - 右子节点值大于父节点");
    System.out.println("  - 支持高效的查找、插入、删除");

    System.out.println("\n遍历方法:");
    System.out.println("  - 前序遍历: 根-左-右");
    System.out.println("  - 中序遍历: 左-根-右（BST得到有序序列）");
    System.out.println("  - 后序遍历: 左-右-根");
    System.out.println("  - 层序遍历: 按层级从左到右");

    System.out.println("\n复杂度分析:");
    System.out.println("  - 平均情况: O(log n) - 平衡树");
    System.out.println("  - 最坏情况: O(n) - 退化为链表");
    System.out.println("  - 空间复杂度: O(n) - 存储所有节点");

    System.out.println("\n=== 应用场景 ===");
    System.out.println("二叉树用于:");
    System.out.println("  - 数据库索引（B树变种）");
    System.out.println("  - 文件系统目录结构");
    System.out.println("  - 编译器语法分析");
    System.out.println("  - 决策树算法");
    System.out.println("  - 表达式求值");
  }
}
