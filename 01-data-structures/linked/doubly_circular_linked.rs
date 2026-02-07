// 定义双向循环链表的节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: *mut Node,
    prev: *mut Node,
}

// 定义双向循环链表结构体
#[derive(Debug)]
struct DoublyCircularLinkedList {
    head: *mut Node,
}

impl DoublyCircularLinkedList {
    // 创建一个新的空双向循环链表
    fn new() -> Self {
        DoublyCircularLinkedList {
            head: std::ptr::null_mut(),
        }
    }

    // 打印双向循环链表
    fn print_list(&self) {
        if self.head.is_null() {
            return;
        }
        let mut current = self.head;
        loop {
            unsafe {
                print!("{} <-> ", (*current).data);
                current = (*current).next;
                if current == self.head {
                    break;
                }
            }
        }
        println!("(back to head)");
    }

    // 插入节点到链表尾部
    fn append_node(&mut self, data: i32) {
        let new_node = Node {
            data,
            next: std::ptr::null_mut(),
            prev: std::ptr::null_mut(),
        };
        let new_node_ptr = Box::into_raw(Box::new(new_node));

        if self.head.is_null() {
            self.head = new_node_ptr;
            unsafe {
                (*new_node_ptr).next = new_node_ptr;
                (*new_node_ptr).prev = new_node_ptr;
            }
        } else {
            unsafe {
                let last = (*self.head).prev;
                (*last).next = new_node_ptr;
                (*new_node_ptr).prev = last;
                (*new_node_ptr).next = self.head;
                (*self.head).prev = new_node_ptr;
            }
        }
    }
}

fn main() {
    let mut list = DoublyCircularLinkedList::new();
    // 插入节点
    list.append_node(1);
    list.append_node(2);
    list.append_node(3);
    // 打印链表
    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc doubly_circular_linked.rs
jarry@MacBook-Pro linked % ./doubly_circular_linked 
1 <-> 2 <-> 3 <-> (back to head)
*/