/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向循环链表基础实现（JavaScript）
 *  功能：结合双向链表和循环链表特性，支持双向循环遍历
 *  用途：学习最复杂的链表结构，实现双向循环播放列表等功能
 */

// 节点类
class Node {
  constructor(data) {
    this.data = data;    // 节点数据
    this.next = null;    // 指向下一个节点
    this.prev = null;    // 指向上一个节点
  }
}

// 双向循环链表类
class DoublyCircularLinkedList {
  constructor() {
    this.head = null;
  }

  // 向链表尾部添加节点
  append(data) {
    const newNode = new Node(data);
    if (this.head === null) {
      this.head = newNode;  // 链表为空，新节点作为头节点
      newNode.next = newNode;  // 指向自己，形成环
      newNode.prev = newNode;  // 指向自己，形成环
      return;
    }
    let last = this.head;
    while (last.next !== this.head) {
      last = last.next;  // 找到最后一个节点（其next指向头节点）
    }
    last.next = newNode;  // 将新节点链接到尾部
    newNode.prev = last;  // 设置新节点的前驱指针
    this.head.prev = newNode;  // 更新头节点的前驱指针
    newNode.next = this.head;  // 新节点的next指向头节点，维持环状结构
  }

  // 打印链表内容
  printList() {
    if (this.head === null) return;
    let current = this.head;
    let result = '';
    do {
      result += current.data + ' <-> ';
      current = current.next;  // 移动到下一个节点
    } while (current !== this.head);  // 循环直到回到头节点
    console.log(result + '(back to head)');
  }
}

const dcll = new DoublyCircularLinkedList();
dcll.append(1);
dcll.append(2);
dcll.append(3);
dcll.printList();

/*
jarry@MacBook-Pro linked % node doubly_circular_linked.js
1 <-> 2 <-> 3 <-> (back to head)
*/