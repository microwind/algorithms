/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  本文件实现通用单向链表数据结构，使用TypeScript强类型系统。
 *  解决的问题：
 *  1. 类型安全 - 利用TS类型系统，在编译时发现类型错误
 *  2. 动态数据存储 - 元素数量可自由增减，无需预先分配空间
 *  3. 高效插入删除 - 特别是在链表头部进行操作时仅需O(1)
 *  
 *  提供的功能：
 *  - insertHead/insertTail: 在链表头部/尾部插入元素
 *  - delete: 删除指定值的节点
 *  - find: 查找指定值是否存在
 *  - printList: 遍历并打印链表所有元素
 *  - getSize: 返回链表当前节点数量
 *  
 *  技术要点：使用联合类型 ListNode | null 表示可能为空的节点链接
 *  
 *  适用场景：前端类型安全编程、大型应用的数据结构基础、算法学习
 */

// 节点类
class ListNode {
    data: number;
    next: ListNode | null;

    constructor(data: number) {
        this.data = data;
        this.next = null;
    }
}

// 链表类
class LinkedList {
    private head: ListNode | null;
    private size: number;

    constructor() {
        this.head = null;
        this.size = 0;
    }

    // 在头部插入
    insertHead(data: number): void {
        const newNode = new ListNode(data);
        newNode.next = this.head;
        this.head = newNode;
        this.size++;
    }

    // 在尾部插入
    insertTail(data: number): void {
        const newNode = new ListNode(data);
        if (!this.head) {
            this.head = newNode;
        } else {
            let current = this.head;
            while (current.next) {
                current = current.next;
            }
            current.next = newNode;
        }
        this.size++;
    }

    // 删除节点
    delete(data: number): boolean {
        if (!this.head) return false;

        if (this.head.data === data) {
            this.head = this.head.next;
            this.size--;
            return true;
        }

        let current = this.head;
        while (current.next && current.next.data !== data) {
            current = current.next;
        }

        if (current.next) {
            current.next = current.next.next;
            this.size--;
            return true;
        }
        return false;
    }

    // 查找节点
    find(data: number): boolean {
        let current = this.head;
        while (current) {
            if (current.data === data) {
                return true;
            }
            current = current.next;
        }
        return false;
    }

    // 打印链表
    printList(): void {
        let current = this.head;
        let result = '';
        while (current) {
            result += current.data + ' -> ';
            current = current.next;
        }
        console.log(result + 'NULL');
    }

    // 获取链表大小
    getSize(): number {
        return this.size;
    }
}

// 测试
const linkedList = new LinkedList();
linkedList.insertTail(1);
linkedList.insertTail(2);
linkedList.insertHead(0);
linkedList.insertTail(3);

console.log('链表内容:');
linkedList.printList();
console.log('链表大小:', linkedList.getSize());
console.log('查找节点2:', linkedList.find(2) ? '找到' : '未找到');

console.log('删除节点2');
linkedList.delete(2);
console.log('链表内容:');
linkedList.printList();
