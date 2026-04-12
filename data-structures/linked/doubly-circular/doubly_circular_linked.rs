/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  双向循环链表基础实现（Rust）
 *  功能：结合双向链表和循环链表特性，使用原始指针实现
 *  用途：学习最复杂的链表结构，理解Rust unsafe代码
 */

// 节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: *mut Node,
    prev: *mut Node,
}

// 双向循环链表结构体
#[derive(Debug)]
struct DoublyCircularLinkedList {
    head: *mut Node,
}

impl DoublyCircularLinkedList {
    fn new() -> Self {
        DoublyCircularLinkedList {
            head: std::ptr::null_mut(),
        }
    }

    // 打印链表内容
    fn print_list(&self) {
        if self.head.is_null() {
            return;
        }
        let mut current = self.head;
        loop {
            unsafe {
                print!("{} <-> ", (*current).data);
                current = (*current).next;  // 移动到下一个节点
                if current == self.head {  // 循环直到回到头节点
                    break;
                }
            }
        }
        println!("(back to head)");
    }

    // 向链表尾部添加节点
    fn append_node(&mut self, data: i32) {
        let new_node = Node {
            data,
            next: std::ptr::null_mut(),
            prev: std::ptr::null_mut(),
        };
        let new_node_ptr = Box::into_raw(Box::new(new_node));

        if self.head.is_null() {
            self.head = new_node_ptr;  // 链表为空，新节点作为头节点
            unsafe {
                (*new_node_ptr).next = new_node_ptr;  // 指向自己，形成环
                (*new_node_ptr).prev = new_node_ptr;  // 指向自己，形成环
            }
        } else {
            unsafe {
                let last = (*self.head).prev;  // 通过头节点的prev直接获取尾节点
                (*last).next = new_node_ptr;  // 将新节点链接到尾部
                (*new_node_ptr).prev = last;  // 设置新节点的前驱指针
                (*new_node_ptr).next = self.head;  // 新节点的next指向头节点
                (*self.head).prev = new_node_ptr;  // 更新头节点的前驱指针
            }
        }
    }
}

fn main() {
    let mut list = DoublyCircularLinkedList::new();
    list.append_node(1);
    list.append_node(2);
    list.append_node(3);
    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc doubly_circular_linked.rs
jarry@MacBook-Pro linked % ./doubly_circular_linked 
1 <-> 2 <-> 3 <-> (back to head)
*/