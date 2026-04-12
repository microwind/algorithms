/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  单向链表基础实现（Rust）
 *  功能：节点追加、链表打印
 *  用途：学习Rust所有权系统，Option<Box<T>>智能指针使用
 */

// 节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: Option<Box<Node>>,
}

// 单链表结构体
#[derive(Debug)]
struct LinkedList {
    head: Option<Box<Node>>,
}

impl LinkedList {
    fn new() -> Self {
        LinkedList { head: None }
    }

    // 打印链表内容
    fn print_list(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} -> ", node.data);
            current = &node.next;  // 移动到下一个节点
        }
        println!("NULL");
    }

    // 向链表尾部添加节点
    fn append_node(&mut self, data: i32) {
        let new_node = Box::new(Node {
            data,
            next: None,
        });

        if self.head.is_none() {
            self.head = Some(new_node);  // 链表为空，新节点作为头节点
            return;
        }

        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.next.is_none() {
                node.next = Some(new_node);  // 将新节点链接到尾部
                break;
            }
            current = &mut node.next;  // 移动到下一个节点
        }
    }
}

fn main() {
    let mut list = LinkedList::new();

    list.append_node(1);
    list.append_node(2);
    list.append_node(3);

    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc singly_linked.rs
jarry@MacBook-Pro linked % ./singly_linked 
1 -> 2 -> 3 -> NULL
*/