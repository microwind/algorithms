/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向链表泛型实现（Java）
 *  功能：支持头尾指针的双向链表，提供添加操作
 *  用途：学习双向链表完整实现，理解头尾指针维护
 */

class DoubleLinkedNode<T> {
  int data;
  DoubleLinkedNode<T> next;
  DoubleLinkedNode<T> prev;

  public DoubleLinkedNode(int data) {
    this.data = data;
  }
}

public class DoubleLinkedList {
  private DoubleLinkedNode<Integer> head;
  private DoubleLinkedNode<Integer> tail;

  public void add(int data) {
    DoubleLinkedNode<Integer> newNode = new DoubleLinkedNode<>(data);
    if (head == null) {
      head = tail = newNode;
    } else {
      tail.next = newNode;
      newNode.prev = tail;
      tail = newNode;
    }
  }

  public void remove(int data) {
    DoubleLinkedNode<Integer> current = head;
    while (current != null && current.data != data) {
      current = current.next;
    }


    if (current != null) {
      if (current.prev != null) {
        current.prev.next = current.next;
      } else {
        head = current.next;
      }
      if (current.next != null) {
        current.next.prev = current.prev;
      } else {
        tail = current.prev;
      }
    }
  }

  public void printNode() {
    DoubleLinkedNode<Integer> current = head;
    while (current != null) {
      System.out.print(current.data + " ");
      current = current.next;
    }
    System.out.println();
  }

  public static void main(String[] args) {
    DoubleLinkedList doubleLinkedList = new DoubleLinkedList();
    doubleLinkedList.add(1);
    doubleLinkedList.add(2);
    doubleLinkedList.add(3);
    doubleLinkedList.add(3);
    doubleLinkedList.add(4);
    doubleLinkedList.add(5);
    doubleLinkedList.printNode();
    doubleLinkedList.remove(3);
    doubleLinkedList.printNode();
  }
}
