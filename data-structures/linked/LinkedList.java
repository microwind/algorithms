/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  本文件实现通用单向链表数据结构，使用Java面向对象编程。
 *  解决的问题：
 *  1. 动态数据集合 - 元素数量可自由增减，无需预先确定容量
 *  2. 高效插入删除 - 头部操作O(1)，无需像ArrayList那样移动元素
 *  3. 内存自动管理 - 利用Java垃圾回收机制，删除的节点自动回收
 *  
 *  提供的功能：
 *  - insertHead/insertTail: 在链表头部/尾部插入元素
 *  - delete: 删除指定值的节点
 *  - find: 查找指定值是否存在
 *  - printList: 遍历并打印链表所有元素
 *  - getSize: 返回链表当前节点数量
 *  
 *  时间复杂度分析：
 *  - 头部插入/删除: O(1)
 *  - 尾部插入/查找/删除: O(n)
 *  
 *  适用场景：需要频繁在头部进行增删操作、数据量动态变化的场景
 */

// 链表类：单向链表实现
public class LinkedList {
    // 节点类：私有内部类，封装节点数据
    private static class Node {
        int data;        // 节点存储的数据
        Node next;       // 指向下一个节点的引用
        
        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }
    
    private Node head;   // 头节点引用，指向链表第一个节点
    private int size;    // 链表节点数量（空间换时间的优化）
    
    // 构造方法：初始化空链表
    public LinkedList() {
        this.head = null;
        this.size = 0;
    }
    
    /**
     * 在头部插入节点
     * 时间复杂度: O(1)
     * 操作：新节点 -> 原头节点 -> 链表其余部分
     */
    public void insertHead(int data) {
        Node newNode = new Node(data);
        newNode.next = head;  // 新节点的next指向当前头节点
        head = newNode;       // 更新头指针指向新节点
        size++;
    }
    
    /**
     * 在尾部插入节点
     * 时间复杂度: O(n)，需要遍历到链表末尾
     * 优化建议：维护tail指针可将复杂度降为O(1)
     */
    public void insertTail(int data) {
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;   // 空链表时，新节点成为头节点
        } else {
            Node current = head;
            while (current.next != null) {  // 遍历到链表末尾
                current = current.next;
            }
            current.next = newNode;  // 将新节点链接到尾部
        }
        size++;
    }
    
    /**
     * 删除指定数据的节点
     * 时间复杂度: O(n)，需要先查找再删除
     * @param data 要删除的目标数据
     * @return 是否成功删除
     */
    public boolean delete(int data) {
        if (head == null) return false;  // 空链表检查
        
        // 删除头节点的情况（特殊情况处理）
        if (head.data == data) {
            head = head.next;  // 头指针后移，原头节点被GC回收
            size--;
            return true;
        }
        
        // 查找目标节点及其前驱节点
        Node current = head;
        while (current.next != null && current.next.data != data) {
            current = current.next;
        }
        
        // 找到目标节点，执行删除（解除链接）
        if (current.next != null) {
            current.next = current.next.next;  // 跳过目标节点
            size--;
            return true;
        }
        return false;  // 未找到目标节点
    }
    
    /**
     * 查找节点
     * 时间复杂度: O(n)，线性遍历查找
     * @param data 要查找的目标数据
     * @return 是否找到
     */
    public boolean find(int data) {
        Node current = head;
        while (current != null) {
            if (current.data == data) {
                return true;
            }
            current = current.next;
        }
        return false;
    }
    
    /**
     * 打印链表：遍历输出所有节点
     * 格式: data1 -> data2 -> ... -> NULL
     */
    public void printList() {
        Node current = head;
        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }
        System.out.println("NULL");
    }
    
    // 获取链表大小：O(1) 直接返回维护的size字段
    public int getSize() {
        return size;
    }
    
    public static void main(String[] args) {
        LinkedList list = new LinkedList();
        
        list.insertTail(1);
        list.insertTail(2);
        list.insertHead(0);
        list.insertTail(3);
        
        System.out.print("链表内容: ");
        list.printList();
        System.out.println("链表大小: " + list.getSize());
        
        System.out.println("查找节点2: " + (list.find(2) ? "找到" : "未找到"));
        
        System.out.println("删除节点2");
        list.delete(2);
        System.out.print("链表内容: ");
        list.printList();
    }
}
