/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  本文件实现通用单向链表数据结构，使用Rust智能指针Box管理内存。
 *  解决的问题：
 *  1. 内存安全 - 利用Rust所有权系统，编译时防止内存泄漏和悬垂指针
 *  2. 动态数据存储 - 元素数量可自由增减，无需预先分配空间
 *  3. 高效插入删除 - 头部操作O(1)，无需移动其他元素
 *  
 *  提供的功能：
 *  - insert_head/insert_tail: 在链表头部/尾部插入元素
 *  - delete: 删除指定值的节点
 *  - find: 查找指定值是否存在
 *  - print_list: 遍历并打印链表所有元素
 *  - get_size: 返回链表当前节点数量
 *  
 *  技术要点：使用Option<Box<Node>>表示可能为空的节点链接
 *  
 *  适用场景：对内存安全有严格要求、需要频繁增删的系统级编程
 */

// 节点结构体
struct Node {
    data: i32,
    next: Option<Box<Node>>,
}

// 链表结构体
pub struct LinkedList {
    head: Option<Box<Node>>,
    size: usize,
}

impl LinkedList {
    // 创建链表
    pub fn new() -> Self {
        LinkedList { head: None, size: 0 }
    }

    // 在头部插入
    pub fn insert_head(&mut self, data: i32) {
        let new_node = Box::new(Node {
            data,
            next: self.head.take(),
        });
        self.head = Some(new_node);
        self.size += 1;
    }

    // 在尾部插入
    pub fn insert_tail(&mut self, data: i32) {
        let new_node = Box::new(Node { data, next: None });
        
        match self.head.as_mut() {
            None => self.head = Some(new_node),
            Some(mut current) => {
                while current.next.is_some() {
                    current = current.next.as_mut().unwrap();
                }
                current.next = Some(new_node);
            }
        }
        self.size += 1;
    }

    // 删除节点
    pub fn delete(&mut self, data: i32) -> bool {
        match self.head.as_ref() {
            None => return false,
            Some(node) if node.data == data => {
                self.head = self.head.take().unwrap().next;
                self.size -= 1;
                return true;
            }
            _ => {}
        }

        let mut current = self.head.as_mut().unwrap();
        while current.next.is_some() && current.next.as_ref().unwrap().data != data {
            current = current.next.as_mut().unwrap();
        }

        if current.next.is_some() {
            current.next = current.next.take().unwrap().next;
            self.size -= 1;
            return true;
        }
        false
    }

    // 查找节点
    pub fn find(&self, data: i32) -> bool {
        let mut current = self.head.as_ref();
        while let Some(node) = current {
            if node.data == data {
                return true;
            }
            current = node.next.as_ref();
        }
        false
    }

    // 打印链表
    pub fn print_list(&self) {
        let mut current = self.head.as_ref();
        while let Some(node) = current {
            print!("{} -> ", node.data);
            current = node.next.as_ref();
        }
        println!("NULL");
    }

    // 获取链表大小
    pub fn get_size(&self) -> usize {
        self.size
    }
}

fn main() {
    let mut list = LinkedList::new();

    list.insert_tail(1);
    list.insert_tail(2);
    list.insert_head(0);
    list.insert_tail(3);

    print!("链表内容: ");
    list.print_list();
    println!("链表大小: {}", list.get_size());
    println!("查找节点2: {}", if list.find(2) { "找到" } else { "未找到" });

    println!("删除节点2");
    list.delete(2);
    print!("链表内容: ");
    list.print_list();
}
