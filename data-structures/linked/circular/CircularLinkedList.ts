/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  循环链表基础实现（TypeScript）
 *  功能：尾节点指向头节点形成环形结构，支持循环遍历
 *  用途：学习循环链表，实现环形播放列表、轮询调度等场景
 */

// 节点类
class CircularListNode {
  data: number;                 // 节点数据
  next: CircularListNode | null;  // 指向下一个节点

  constructor(data: number) {
    this.data = data;
    this.next = null;
  }
}

// 循环链表类
class CircularLinkedList {
  head: CircularListNode | null;

  constructor() {
    this.head = null;
  }

  // 向链表尾部添加节点
  append(data: number): void {
    const newNode = new CircularListNode(data);
    if (this.head === null) {
      this.head = newNode;  // 链表为空，新节点作为头节点
      newNode.next = this.head;  // 指向自己，形成环
      return;
    }
    let last = this.head;
    while (last.next !== this.head) {
      last = last.next!;  // 找到最后一个节点（其next指向头节点）
    }
    last.next = newNode;  // 将新节点链接到尾部
    newNode.next = this.head;  // 新节点的next指向头节点，维持环状结构
  }

  // 打印链表内容
  printList(): void {
    if (this.head === null) {
      return;
    }
    let current = this.head;
    let output = "";
    while (true) {
      output += current.data + " -> ";
      current = current.next!;  // 移动到下一个节点
      if (current === this.head) {  // 循环直到回到头节点
        break;
      }
    }
    console.log(output + "(back to head)");
  }
}

const circularList = new CircularLinkedList();
circularList.append(1);
circularList.append(2);
circularList.append(3);
circularList.printList();

/*
 * 输出结果：
 * 1 -> 2 -> 3 -> (back to head)
 */
