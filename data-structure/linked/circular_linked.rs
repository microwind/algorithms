// 定义节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: *mut Node,
}

// 定义循环链表结构体
#[derive(Debug)]
struct CircularLinkedList {
    head: *mut Node,
}

impl CircularLinkedList {
    // 创建一个新的空循环链表
    fn new() -> Self {
        CircularLinkedList { head: std::ptr::null_mut() }
    }

    // 打印循环链表
    fn print_list(&self) {
        if self.head.is_null() {
            return;
        }

        let mut current = self.head;
        loop {
            unsafe {
                print!("{} -> ", (*current).data);
                current = (*current).next;
                if current == self.head {
                    break;
                }
            }
        }
        println!("(back to head)");
    }

    // 插入节点到尾部
    fn append_node(&mut self, data: i32) {
        let new_node = Node {
            data,
            next: std::ptr::null_mut(),
        };

        let new_node_ptr = Box::into_raw(Box::new(new_node));

        if self.head.is_null() {
            self.head = new_node_ptr;
            unsafe {
                (*new_node_ptr).next = new_node_ptr;
            }
            return;
        }

        let mut current = self.head;
        unsafe {
            while (*current).next != self.head {
                current = (*current).next;
            }
            (*current).next = new_node_ptr;
            (*new_node_ptr).next = self.head;
        }
    }
}

fn main() {
    let mut list = CircularLinkedList::new();

    // 插入节点
    list.append_node(1);
    list.append_node(2);
    list.append_node(3);

    // 打印链表
    list.print_list();
}

/*
jarry@MacBook-Pro linked % rustc circular_linked.rs
jarry@MacBook-Pro linked % ./circular_linked 
1 -> 2 -> 3 -> (back to head)
*/