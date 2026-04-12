/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向链表基础实现（JavaScript）
 *  功能：支持双向遍历的链表，包含prev和next指针
 *  用途：学习双向链表，实现浏览器前进后退等功能
 */

// 节点类
class Node {
    constructor(data) {
        this.data = data;    // 节点数据
        this.next = null;    // 指向下一个节点
        this.prev = null;    // 指向上一个节点
    }
}

// 双链表类
class DoublyLinkedList {
    constructor() {
        this.head = null;
    }

    // 向链表尾部添加节点
    append(data) {
        const newNode = new Node(data);
        if (this.head === null) {
            this.head = newNode;  // 链表为空，新节点作为头节点
            return;
        }
        let last = this.head;
        while (last.next !== null) {
            last = last.next;  // 找到最后一个节点
        }
        last.next = newNode;  // 将新节点链接到尾部
        newNode.prev = last;  // 设置新节点的前驱指针
    }

    // 打印链表内容
    printList() {
        let current = this.head;
        let result = '';
        while (current !== null) {
            result += current.data + ' <-> ';
            current = current.next;  // 移动到下一个节点
        }
        console.log(result + 'NULL');
    }
}

const list = new DoublyLinkedList();
list.append(1);
list.append(2);
list.append(3);
list.printList();

/*
jarry@MacBook-Pro linked % node doubly_linked.js
1 <-> 2 <-> 3 <-> NULL
*/