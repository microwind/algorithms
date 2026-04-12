/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  单向链表基础实现（Java）
 *  功能：节点追加、链表打印
 *  用途：学习Java链表实现，面向对象编程练习
 */

// 单链表类
class SinglyLinked {
  // 节点类
  static class Node {
      int data;       // 节点数据
      Node next;      // 指向下一个节点

      Node(int data) {
          this.data = data;
          this.next = null;
      }
  }

  private Node head;

  public SinglyLinked() {
      this.head = null;
  }

  // 向链表尾部添加节点
  public void append(int data) {
      Node newNode = new Node(data);
      if (head == null) {
          head = newNode;  // 链表为空，新节点作为头节点
          return;
      }
      Node last = head;
      while (last.next != null) {
          last = last.next;  // 找到最后一个节点
      }
      last.next = newNode;  // 将新节点链接到尾部
  }

  // 打印链表内容
  public void printList() {
      Node current = head;
      while (current != null) {
          System.out.print(current.data + " -> ");
          current = current.next;  // 移动到下一个节点
      }
      System.out.println("NULL");
  }

  public static void main(String[] args) {
      SinglyLinked list = new SinglyLinked();
      list.append(1);
      list.append(2);
      list.append(3);
      list.printList();
  }
}

/*
jarry@MacBook-Pro linked % javac SinglyLinked.java
jarry@MacBook-Pro linked % java SinglyLinked      
1 -> 2 -> 3 -> NULL
*/