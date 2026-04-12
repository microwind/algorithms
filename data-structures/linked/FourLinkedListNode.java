/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  四项链表节点类（Java泛型实现）
 *  功能：每个节点有四个方向指针（up/down/left/right），可表示二维矩阵
 *  用途：学习高级链表结构，实现稀疏矩阵、跳表、游戏地图等二维数据结构
 */
// 四项链表节点类
public class FourLinkedListNode<T> {
  private T data;
  private FourLinkedListNode<T> up;
  private FourLinkedListNode<T> down;
  private FourLinkedListNode<T> left;
  private FourLinkedListNode<T> right;

  // 构造函数
  public FourLinkedListNode(T data) {
    this.data = data;
  }

  // 将所有Getter Setter生成出来

  public T setData(T data) {
    this.data = data;
    return this.data;
  }

  public T getData() {
    return data;
  }

  public FourLinkedListNode<T> getUp() {
    return up;
  }

  public void setUp(FourLinkedListNode<T> up) {
    this.up = up;
  }

  public FourLinkedListNode<T> getDown() {
    return down;
  }

  public void setDown(FourLinkedListNode<T> down) {
    this.down = down;
  }

  public FourLinkedListNode<T> getLeft() {
    return left;
  }

  public void setLeft(FourLinkedListNode<T> left) {
    this.left = left;
  }

  public FourLinkedListNode<T> getRight() {
    return right;
  }

  public void setRight(FourLinkedListNode<T> right) {
    this.right = right;
  }

  public static <T> FourLinkedListNode<T> create(T data) {
    return new FourLinkedListNode<>(data);
  }

  @Override
  public String toString() {
    return "FourLinkedListNode{" +
        "data=" + data +
        '}';
  }

  // 验证
  public static void main(String[] args) {

    FourLinkedListNode<String> n1 = FourLinkedListNode.create("Node1");
    FourLinkedListNode<String> n2 = FourLinkedListNode.create("Node2");
    FourLinkedListNode<String> n3 = FourLinkedListNode.create("Node3");
    FourLinkedListNode<String> n4 = FourLinkedListNode.create("Node4");

    n1.setRight(n2);
    n2.setLeft(n1);
    n3.setRight(n4);
    n4.setLeft(n3);

    // 垂直链接
    n1.setDown(n3);
    n3.setUp(n1);
    n2.setDown(n4);
    n4.setUp(n2);

    // 打印结构
    System.out.println("四项链表节点:");
    System.out.println(n1 + " right-> " + n1.getRight());
    System.out.println(n1 + " down-> " + n1.getDown());
    System.out.println(n4 + " left-> " + n4.getLeft());
    System.out.println(n4 + " up-> " + n4.getUp());
  }

  
}

/*
jarry@Mac linked % java FourLinkedListNode.java 
四项链表节点:
FourLinkedListNode{data=Node1} right-> FourLinkedListNode{data=Node2}
FourLinkedListNode{data=Node1} down-> FourLinkedListNode{data=Node3}
FourLinkedListNode{data=Node4} left-> FourLinkedListNode{data=Node3}
FourLinkedListNode{data=Node4} up-> FourLinkedListNode{data=Node2}
 */