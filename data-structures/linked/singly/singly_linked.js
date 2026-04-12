/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  单向链表基础实现（JavaScript ES6）
 *  功能：节点插入、链表遍历、打印输出
 *  用途：前端算法学习，理解链表数据结构
 */

// 节点类：数据、下一个节点
class Node {
  constructor(data) {
    this.data = data;    // 节点数据
    this.next = null;    // 指向下一个节点
  }
}

class SinglyLinkedList {
  constructor() {
    this.head = null;
  }

  // 向链表尾部添加节点
  append(data) {
    const newNode = new Node(data);
    if (this.head === null) {
      this.head = newNode; // 链表为空，新节点作为头节点
      return;
    }
    let last = this.head;
    while (last.next !== null) {
      last = last.next; // 找到最后一个节点
    }
    last.next = newNode; // 将新节点链接到尾部
  }

  // 打印链表内容
  printList() {
    let current = this.head;
    let result = '';
    while (current !== null) {
      result += current.data + ' -> ';
      current = current.next; // 移动到下一个节点
    }
    console.log(result + 'NULL');
  }
}

const list = new SinglyLinkedList();
list.append(1);
list.append(2);
list.append(3);
list.printList();

/*
jarry@MacBook-Pro linked % node singly_linked.js
1 -> 2 -> 3 -> NULL
*/
