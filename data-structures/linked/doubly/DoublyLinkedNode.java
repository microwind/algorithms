/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向链表泛型实现与节点删除（Java）
 *  功能：支持泛型的双向链表，实现指定值节点的删除操作
 *  用途：学习双向链表删除操作，理解前后指针重连逻辑
 */

class DoublyNode<T> {
  T value;
  DoublyNode<T> prev;
  DoublyNode<T> next;
}

public class DoublyLinkedNode<T> {
  private DoublyNode<T> head;
  private DoublyNode<T> tail;

  // 添加节点实现，
  public void add(T value) {
    DoublyNode<T> newNode = new DoublyNode<>();
    newNode.value = value;
    if (head == null) {
      head = tail = newNode;
    } else {
      tail.next = newNode;
      newNode.prev = tail;
      tail = newNode;
    }
  }

  public void remove(T value) {
    DoublyNode<T> current = head;
    while (current != null) {
      if (current.value.equals(value)) {
        if (current.prev != null) {
          current.prev.next = current.next;
        } else {
          head = current.next; // Removing head
        }
        if (current.next != null) {
          current.next.prev = current.prev;
        } else {
          tail = current.prev; // Removing tail
        }
        break;
      }
      current = current.next;
    }
  }

  public static void main(String[] args) {
    DoublyLinkedNode<Integer> list = new DoublyLinkedNode<>();
    list.add(1);
    list.add(2);
    list.add(3);
    list.remove(2);
  }
}

