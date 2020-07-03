
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

// Node data structure
class Node {
  public Integer value;
  public Node left;
  public Node right;

  Node() {
  }

  Node(Integer value) {
    this.value = value;
  }

  public Node getLeft() {
    return this.left;
  }

  public Node getRight() {
    return this.right;
  }

  public void setLeft(Node left) {
    this.left = left;
  }

  public void setRight(Node right) {
    this.right = right;
  }

  public void setValue(Integer value) {
    this.value = value;
  }

  public void print() {
    System.out.println(this.value);
  }
}

/**
 * binary tree traverse class
 */
public class BinaryTree {
  // 1. 先序优先遍历DLR递归版
  public List<Integer> preOrderTraverse(Node tree, List<Integer> result) {
    if (tree != null) {
      result.add(tree.value);
      this.preOrderTraverse(tree.left, result);
      this.preOrderTraverse(tree.right, result);
    }
    return result;
  }

  // 2. 中序优先遍历LDR递归版
  public List<Integer> inOrderTraverse(Node tree, List<Integer> result) {
    if (tree != null) {
      this.inOrderTraverse(tree.left, result);
      result.add(tree.value);
      this.inOrderTraverse(tree.right, result);
    }
    return result;
  }

  // 3. 后序优先遍历LRD递归版
  public List<Integer> postOrderTraverse(Node tree, List<Integer> result) {
    if (tree != null) {
      this.postOrderTraverse(tree.left, result);
      this.postOrderTraverse(tree.right, result);
      result.add(tree.value);
    }
    return result;
  }

  // 4. 广度优先(层级遍历)，自左往右，利用队列暂存数据
  public List<Integer> levelOrder(Node tree) {
    List<Integer> result = new ArrayList<Integer>();
    List<Node> queue = new ArrayList<Node>();
    if (tree != null) {
      queue.add(tree);
      while (queue.size() > 0) {
        tree = queue.get(0);
        queue.remove(0);
        result.add(tree.value);
        // 追加到当前队列
        if (tree.left != null) {
          queue.add(tree.left);
        }
        if (tree.right != null) {
          queue.add(tree.right);
        }
      }
    }
    return result;
  }

  // 5. 深度遍历(先序优先非递归版)
  public List<Integer> preOrderUnRecursive(Node tree) {
    List<Integer> result = new ArrayList<Integer>();
    List<Node> queue = new ArrayList<Node>();
    if (tree != null) {
      while (queue.size() > 0 || tree != null) {
        if (tree != null) {
          result.add(tree.value);
          queue.add(tree);
          tree = tree.left;
        } else {
          tree = queue.get(queue.size() - 1);
          queue.remove(queue.size() - 1);
          tree = tree.right;
        }
      }
    }
    return result;
  }

  // 6. 深度遍历(中序优先非递归版)
  public List<Integer> inOrderUnRecursive(Node tree) {
    List<Integer> result = new ArrayList<Integer>();
    List<Object> queue = new ArrayList<Object>();
    if (tree != null) {
      while (queue.size() > 0 || tree != null) {
        if (tree != null) {
          queue.add(tree);
          tree = tree.left;
        } else {
          tree = (Node) queue.get(queue.size() - 1);
          queue.remove(queue.size() - 1);
          result.add(tree.value);
          tree = tree.right;
        }
      }
    }
    return result;
  }

  // 7. 深度遍历(后序优先非递归版)
  public List<Integer> postOrderUnRecursive(Node tree) {
    List<Integer> result = new ArrayList<Integer>();
    List<Object> queue = new ArrayList<Object>();
    Node tmp = null;
    if (tree != null) {
      queue.add(tree);
      while (queue.size() > 0) {
        // 先得到最后一项作为比较项
        tmp = (Node) queue.get(queue.size() - 1);
        // 把左子树按深度全部追加到queue
        if (tmp.left != null && tree != tmp.left && tree != tmp.right) {
          queue.add(tmp.left);
          // 把右子树追加到queue
        } else if (tmp.right != null && tree != tmp.right) {
          queue.add(tmp.right);
        } else {
          // 左子树到最底层节点，开始打印left与right
          Node item = (Node) queue.get(queue.size() - 1);
          queue.remove(queue.size() - 1);
          result.add(item.value);
          // 指向上一个节点，直到queue为空，也就是遍历至根节点
          tree = tmp;
        }
      }
    }
    return result;
  }

  public static void main(String[] args) {

    // 二叉树数据
    /*
                 1
            /         \
          2              3
        /   \          /   \
      4      5        6     7
           /   \          /    \
          8     9        10    11
        /   \
      12    13
     */
    
    Node tree = new Node(1);
    Node node2 = new Node(2);
    Node node3 = new Node(3);
    tree.setLeft(node2);
    tree.setRight(node3);

    node2.setLeft(new Node(4));
    node2.setRight(new Node(5));

    node3.setLeft(new Node(6));
    node3.setRight(new Node(7));

    Node node5 = node2.getRight();
    node5.setLeft(new Node(8));
    node5.setRight(new Node(9));

    Node node7 = node3.getRight();
    node7.setLeft(new Node(10));
    node7.setRight(new Node(11));

    Node node8 = node5.getLeft();
    node8.setLeft(new Node(12));
    node8.setRight(new Node(13));

    System.out.println("=== start test ===");
    long startTime = System.currentTimeMillis();
    BinaryTree binaryNode = new BinaryTree();
    List result;
    // 1.
    result = binaryNode.preOrderTraverse(tree, new ArrayList<Integer>());
    // [1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11]
    System.out.println(" 1. binaryNode.preOrderTraverse:" + result.toString());

    // 2.
    result = binaryNode.inOrderTraverse(tree, new ArrayList<Integer>());
    // [4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11]
    System.out.println(" 2. binaryNode.inOrderTraverse:" + result.toString());

    // 3.
    result = binaryNode.postOrderTraverse(tree, new ArrayList<Integer>());
    // [4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1]
    System.out.println(" 3. postOrderTraverse:" + result);

    // 4.
    result = binaryNode.levelOrder(tree);
    // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
    System.out.println(" 4. levelOrder:" + result);

    // 5.
    result = binaryNode.preOrderUnRecursive(tree);
    // [1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11]
    System.out.println(" 5. preOrderUnRecursive:" + result);

    // 6.
    result = binaryNode.inOrderUnRecursive(tree);
    // [4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11]
    System.out.println(" 6. inOrderUnRecursive:" + result);

    // 7.
    result = binaryNode.postOrderUnRecursive(tree);
    // [4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1]
    System.out.println(" 7. postOrderUnRecursive:" + result);

    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }
}
/**
 * jarry@jarrys-MacBook-Pro binarytree % javac BinaryTree.java
 * jarry@jarrys-MacBook-Pro binarytree % java BinaryTree === start test === 1.
 * binaryNode.preOrderTraverse:[1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11] 2.
 * binaryNode.inOrderTraverse:[4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11] 3.
 * postOrderTraverse:[4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1] 4.
 * levelOrder:[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13] 5.
 * preOrderUnRecursive:[1, 2, 4, 5, 8, 12, 13, 9, 3, 6, 7, 10, 11] 6.
 * inOrderUnRecursive:[4, 2, 12, 8, 13, 5, 9, 1, 6, 3, 10, 7, 11] 7.
 * postOrderUnRecursive:[4, 12, 13, 8, 9, 5, 2, 6, 10, 11, 7, 3, 1]
 * 
 * time:9 ms.
 */