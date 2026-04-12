/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树数据结构 - Java实现
 */

package full_binary_tree;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class TreeNode {
  TreeNode left;
  TreeNode right;
  TreeNode parent;
  TreeNode next;
  int value;

  TreeNode(int value) {
    this.value = value;
  }
}

public class FullBinaryTree {

  /**
   * 按 idx 作为根节点的“占位”值，buildHeight 为层数构造满二叉树，
   * 并设置 parent 指针。（value 会被后续 BFS 覆盖）
   */
  static TreeNode buildFullTree(int idx, int height) {
    if (height <= 0) {
      return null;
    }
    TreeNode node = new TreeNode(idx);
    node.left = buildFullTree(idx * 2, height - 1);
    if (node.left != null)
      node.left.parent = node;
    node.right = buildFullTree(idx * 2 + 1, height - 1);
    if (node.right != null)
      node.right.parent = node;
    return node;
  }

  /** 先序遍历（根→左→右），保留示例 */
  public static void printPreOrder(TreeNode node) {
    if (node == null) {
      return;
    }
    System.out.println("value: " + node.value);
    printPreOrder(node.left);
    printPreOrder(node.right);
  }

  /** 广度优先遍历（BFS）打印，最后加上换行 */
  public static void printBFS(TreeNode root) {
    if (root == null)
      return;
    List<TreeNode> queue = new ArrayList<>();
    queue.add(root);
    for (int i = 0; i < queue.size(); i++) {
      TreeNode n = queue.get(i);
      System.out.print(n.value + " ");
      if (n.left != null)
        queue.add(n.left);
      if (n.right != null)
        queue.add(n.right);
    }
    System.out.println();
  }

  /** 找到当前节点所在树的根 */
  private static TreeNode findRoot(TreeNode node) {
    while (node.parent != null) {
      node = node.parent;
    }
    return node;
  }

  /**
   * 无额外空间遍历单棵树（含 parent 指针），
   * 中序风格打印，保持原样
   */
  private static void traverseTree(TreeNode root) {
    TreeNode prev = null, current = root;
    while (current != null) {
      TreeNode next;
      if (prev == current.parent) {
        // 从 parent 下来：优先下探左子
        if (current.left != null) {
          next = current.left;
        } else {
          // 否则中序访问自己
          System.out.print(current.value + " ");
          next = (current.right != null ? current.right : current.parent);
        }
      } else if (prev == current.left) {
        // 从左子回到 current：中序访问自己
        System.out.print(current.value + " ");
        next = (current.right != null ? current.right : current.parent);
      } else {
        // 从右子回到 current：回父节点
        next = current.parent;
      }
      prev = current;
      current = next;
    }
  }

  /** 从任意节点开始遍历串联在一起的多棵树 */
  public static void traverseFromAnyNode(TreeNode any) {
    TreeNode root = findRoot(any);
    while (root != null) {
      traverseTree(root);
      root = root.next;
    }
    System.out.println();
  }

  /**
   * 新增：对单棵树按层序（BFS）重新赋连续值
   * 
   * @param root     要编号的树
   * @param startVal 起始编号（inclusive）
   * @return 下一个可用编号（即最后一个+1）
   */
  private static int assignLevelOrderValues(TreeNode root, int startVal) {
    Queue<TreeNode> q = new LinkedList<>();
    q.offer(root);
    int val = startVal;
    while (!q.isEmpty()) {
      TreeNode n = q.poll();
      n.value = val++;
      if (n.left != null)
        q.offer(n.left);
      if (n.right != null)
        q.offer(n.right);
    }
    return val;
  }

  public static void main(String[] args) {
    int height = 4;

    // 1) 构造形状（value暂时无意义）
    TreeNode T1 = buildFullTree(1, height);
    TreeNode T2 = buildFullTree(1, height);
    TreeNode T3 = buildFullTree(1, height);

    // 2) 按层序给每棵树分别连续编号：
    // T1 → 1..15, T2 → 16..30, T3 → 31..45
    int nextId = assignLevelOrderValues(T1, 1);
    nextId = assignLevelOrderValues(T2, nextId);
    assignLevelOrderValues(T3, nextId);

    // 3) 串联根：T1 → T2 → T3
    T1.next = T2;
    T2.next = T3;
    T3.next = null;

    System.out.println("=== 先序遍历 T1 ===");
    printPreOrder(T1);

    System.out.println("\n=== 广度优先遍历 T1 ===");
    printBFS(T1);

    // 4) 从任意节点遍历
    System.out.println("\n=== 从任意节点遍历 ===");
    traverseFromAnyNode(T3.left);


    // 5) 从 T2 的某个子节点开始，无额外空间遍历整片“森林”
    TreeNode any = T2.left.left;
    System.out.println("\n=== 从节点 " + any.value + " 开始无栈遍历 ===");
    traverseFromAnyNode(any);
  }
}
