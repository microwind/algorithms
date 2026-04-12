/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树链式构建器 - Java实现
 */

/*
实现泛型节点并生成满二叉树
一个带泛型的节点类 DoubleDirectNode<T>，节点包含 father、leftChild、rightChild 指针和 value 值；
并实现方法 createTree，根据给定深度 depth 递归生成一棵 N 层的空值满二叉树。
*/
class DoubleDirectNode<T> {
  public DoubleDirectNode<T> head, left, right;
  public int depth;

  public DoubleDirectNode(int depth) {
    this.depth = depth;
  }
}

public class LinkedBuilder {

  public static DoubleDirectNode<Integer> create(DoubleDirectNode<Integer> head, int depth) {
    if (depth == 0)
      return null;
    DoubleDirectNode<Integer> node = new DoubleDirectNode<>(depth);
    node.head = node;
    node.left = LinkedBuilder.create(node, depth - 1);
    node.right = LinkedBuilder.create(node, depth - 1);
    return node;
  }

  public static void main(String[] args) {
    DoubleDirectNode<Integer> root = new DoubleDirectNode<>(0);
    DoubleDirectNode<Integer> tree = LinkedBuilder.create(root, 5);
    System.out.println("Tree created with depth: " + tree.depth);
    printNode(tree);
  }

  public static void printNode(DoubleDirectNode<Integer> node) {
    if (node == null)
      return;
    System.out.println("Node depth: " + node.depth);
    if (node.left != null) {
      System.out.println("Left child depth: " + node.left.depth);
      printNode(node.left);
    }

    if (node.right != null) {
      System.out.println("Right child depth: " + node.right.depth);
      printNode(node.right);
    }
  }
}