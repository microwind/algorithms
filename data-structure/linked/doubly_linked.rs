// 定义双向链表节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: Option<Box<Node>>,
    prev: Option<*mut Node>,
}

// 定义双向链表结构体
#[derive(Debug)]
struct DoublyLinkedList {
    head: Option<Box<Node>>,
}

impl DoublyLinkedList {
    // 创建一个新的空双向链表
    fn new() -> Self {
        DoublyLinkedList { head: None }
    }

    // 打印双向链表
    fn print_list(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} <-> ", node.data);
            current = &node.next;
        }
        println!("NULL");
    }

    // 向双向链表尾部添加节点
    fn append_node(&mut self, data: i32) {
        let new_node = Box::new(Node {
            data,
            next: None,
            prev: None,
        });

        if self.head.is_none() {
            self.head = Some(new_node);
            return;
        }

        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.next.is_none() {
                let new_node_ptr = Box::into_raw(new_node);
                node.next = Some(unsafe { Box::from_raw(new_node_ptr) });
                let prev_ptr = node.as_mut() as *mut Node;
                unsafe { (*new_node_ptr).prev = Some(prev_ptr); }
                break;
            }
            current = &mut node.next;
        }
    }
}

fn main() {
    let mut list = DoublyLinkedList::new();
    // 插入节点
    list.append_node(1);
    list.append_node(2);
    list.append_node(3);
    // 打印链表
    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc doubly_linked.rs
jarry@MacBook-Pro linked % ./doubly_linked 
1 <-> 2 <-> 3 <-> NULL
*/