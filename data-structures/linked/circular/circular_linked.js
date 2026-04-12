/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  循环链表基础实现（JavaScript）
 *  功能：尾节点指向头节点形成环形结构，支持循环遍历
 *  用途：学习循环链表，实现轮询调度、环形播放列表等场景
 */

// 节点类
class Node {
  constructor(data) {
    this.data = data;    // 节点数据
    this.next = null;    // 指向下一个节点
  }
}

// 循环链表类
class CircularLinkedList {
  constructor() {
    this.head = null;
  }

  // 向链表尾部添加节点
  append(data) {
    const newNode = new Node(data);
    if (this.head === null) {
      this.head = newNode;  // 链表为空，新节点作为头节点
      newNode.next = this.head;  // 指向自己，形成环
      return;
    }
    let last = this.head;
    while (last.next !== this.head) {
      last = last.next;  // 找到最后一个节点（其next指向头节点）
    }
    last.next = newNode;  // 将新节点链接到尾部
    newNode.next = this.head;  // 新节点的next指向头节点，维持环状结构
  }

  // 打印链表内容
  printList() {
    if (this.head === null) return;
    let current = this.head;
    let result = '';
    do {
      result += current.data + ' -> ';
      current = current.next;  // 移动到下一个节点
    } while (current !== this.head);  // 循环直到回到头节点
    console.log(result + '(back to head)');
  }
}

const list = new CircularLinkedList();
list.append(1);
list.append(2);
list.append(3);
list.printList();

/*
jarry@MacBook-Pro linked % node circular_linked.js 
1 -> 2 -> 3 -> (back to head)
*/