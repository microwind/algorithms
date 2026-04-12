/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  循环链表基础实现（Java）
 *  功能：尾节点指向头节点形成环形结构，支持循环遍历
 *  用途：学习循环链表，实现进程调度、轮询算法等场景
 */

// 循环链表类
class CircularLinked {
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

  public CircularLinked() {
      this.head = null;
  }

  // 向链表尾部添加节点
  public void append(int data) {
      Node newNode = new Node(data);
      if (head == null) {
          head = newNode;  // 链表为空，新节点作为头节点
          newNode.next = head;  // 指向自己，形成环
          return;
      }
      Node last = head;
      while (last.next != head) {
          last = last.next;  // 找到最后一个节点（其next指向头节点）
      }
      last.next = newNode;  // 将新节点链接到尾部
      newNode.next = head;  // 新节点的next指向头节点，维持环状结构
  }

  // 打印链表内容
  public void printList() {
      if (head == null) {
          return;
      }
      Node current = head;
      do {
          System.out.print(current.data + " -> ");
          current = current.next;  // 移动到下一个节点
      } while (current != head);  // 循环直到回到头节点
      System.out.println("(back to head)");
  }

  public static void main(String[] args) {
      CircularLinked list = new CircularLinked();
      list.append(1);
      list.append(2);
      list.append(3);
      list.printList();
  }
}

/*
jarry@MacBook-Pro linked % javac CircularLinked.java 
jarry@MacBook-Pro linked % java CircularLinked
1 -> 2 -> 3 -> (back to head)
*/