/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  循环链表基础实现（Rust）
 *  功能：尾节点指向头节点形成环形结构，使用原始指针实现
 *  用途：学习循环链表，理解Rust中的unsafe指针操作
 */

// 节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: *mut Node,
}

// 循环链表结构体
#[derive(Debug)]
struct CircularLinkedList {
    head: *mut Node,
}

impl CircularLinkedList {
    fn new() -> Self {
        CircularLinkedList { head: std::ptr::null_mut() }
    }

    // 打印链表内容
    fn print_list(&self) {
        if self.head.is_null() {
            return;
        }

        let mut current = self.head;
        loop {
            unsafe {
                print!("{} -> ", (*current).data);
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
        };

        let new_node_ptr = Box::into_raw(Box::new(new_node));

        if self.head.is_null() {
            self.head = new_node_ptr;  // 链表为空，新节点作为头节点
            unsafe {
                (*new_node_ptr).next = new_node_ptr;  // 指向自己，形成环
            }
            return;
        }

        let mut current = self.head;
        unsafe {
            while (*current).next != self.head {
                current = (*current).next;  // 找到最后一个节点（其next指向头节点）
            }
            (*current).next = new_node_ptr;  // 将新节点链接到尾部
            (*new_node_ptr).next = self.head;  // 新节点的next指向头节点，维持环状结构
        }
    }
}

fn main() {
    let mut list = CircularLinkedList::new();

    list.append_node(1);
    list.append_node(2);
    list.append_node(3);

    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc circular_linked.rs
jarry@MacBook-Pro linked % ./circular_linked 
1 -> 2 -> 3 -> (back to head)
*/