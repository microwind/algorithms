/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  本文件实现通用单向链表数据结构，使用ES6 Class语法。
 *  解决的问题：
 *  1. 动态数据集合 - 适合元素数量频繁变化的场景
 *  2. 高效头部操作 - 插入删除无需移动其他元素
 *  3. 内存自动管理 - 利用JS垃圾回收机制，无需手动释放
 *  
 *  提供的功能：
 *  - insertHead/insertTail: 头部/尾部插入
 *  - delete: 删除指定数据节点
 *  - find: 查找节点是否存在
 *  - printList: 打印链表
 *  - getSize: 获取链表长度
 *  
 *  适用场景：前端数据处理、算法练习、需要频繁增删的数据集合
 */

// 节点类
class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

// 链表类
class LinkedList {
    constructor() {
        this.head = null;
        this.size = 0;
    }
    
    // 在头部插入
    insertHead(data) {
        const newNode = new Node(data);
        newNode.next = this.head;
        this.head = newNode;
        this.size++;
    }
    
    // 在尾部插入
    insertTail(data) {
        const newNode = new Node(data);
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
    delete(data) {
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
    find(data) {
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
    printList() {
        let current = this.head;
        let result = '';
        while (current) {
            result += current.data + ' -> ';
            current = current.next;
        }
        console.log(result + 'NULL');
    }
    
    // 获取链表大小
    getSize() {
        return this.size;
    }
}

// 测试
const list = new LinkedList();
list.insertTail(1);
list.insertTail(2);
list.insertHead(0);
list.insertTail(3);

console.log('链表内容:');
list.printList();
console.log('链表大小:', list.getSize());
console.log('查找节点2:', list.find(2) ? '找到' : '未找到');

console.log('删除节点2');
list.delete(2);
console.log('链表内容:');
list.printList();
