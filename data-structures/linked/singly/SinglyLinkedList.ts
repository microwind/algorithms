/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 单向链表数据结构 - TypeScript实现
 */

// 节点类
class ListNode {
  data: number;           // 节点数据
  next: ListNode | null;  // 指向下一个节点

  constructor(data: number) {
    this.data = data;
    this.next = null;
  }
}

// 单链表类
class SinglyLinkedList {
  head: ListNode | null;

  constructor() {
    this.head = null;
  }

  // 向链表尾部添加节点
  append(data: number): void {
    const newNode = new ListNode(data);
    if (this.head === null) {
      this.head = newNode;  // 链表为空，新节点作为头节点
      return;
    }
    let last = this.head;
    while (last.next !== null) {
      last = last.next;  // 找到最后一个节点
    }
    last.next = newNode;  // 将新节点链接到尾部
  }

  // 打印链表内容
  printList(): void {
    let current = this.head;
    let output = "";
    while (current !== null) {
      output += current.data + " -> ";
      current = current.next;  // 移动到下一个节点
    }
    console.log(output + "NULL");
  }
}

const list = new SinglyLinkedList();
list.append(1);
list.append(2);
list.append(3);
list.printList();

/*
 * 输出结果：
 * 1 -> 2 -> 3 -> NULL
 */
