/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向链表基础实现（Rust）
 *  功能：支持双向遍历的链表，使用智能指针管理内存
 *  用途：学习双向链表，理解Rust复杂所有权和指针类型
 */

// 节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: Option<Box<Node>>,
    prev: Option<*mut Node>,
}

// 双链表结构体
#[derive(Debug)]
struct DoublyLinkedList {
    head: Option<Box<Node>>,
}

impl DoublyLinkedList {
    fn new() -> Self {
        DoublyLinkedList { head: None }
    }

    // 打印链表内容
    fn print_list(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} <-> ", node.data);
            current = &node.next;  // 移动到下一个节点
        }
        println!("NULL");
    }

    // 向链表尾部添加节点
    fn append_node(&mut self, data: i32) {
        let new_node = Box::new(Node {
            data,
            next: None,
            prev: None,
        });

        if self.head.is_none() {
            self.head = Some(new_node);  // 链表为空，新节点作为头节点
            return;
        }

        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.next.is_none() {
                let new_node_ptr = Box::into_raw(new_node);
                node.next = Some(unsafe { Box::from_raw(new_node_ptr) });  // 将新节点链接到尾部
                let prev_ptr = node.as_mut() as *mut Node;
                unsafe { (*new_node_ptr).prev = Some(prev_ptr); }  // 设置新节点的前驱指针
                break;
            }
            current = &mut node.next;  // 移动到下一个节点
        }
    }
}

fn main() {
    let mut list = DoublyLinkedList::new();
    list.append_node(1);
    list.append_node(2);
    list.append_node(3);
    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc doubly_linked.rs
jarry@MacBook-Pro linked % ./doubly_linked 
1 <-> 2 <-> 3 <-> NULL
*/