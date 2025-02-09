// 定义节点结构体
#[derive(Debug)]
struct Node {
    data: i32,
    next: Option<Box<Node>>,
}

// 定义链表结构体
#[derive(Debug)]
struct LinkedList {
    head: Option<Box<Node>>,
}

impl LinkedList {
    // 初始化一个空链表
    fn new() -> Self {
        LinkedList { head: None }
    }

    // 打印链表
    fn print_list(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} -> ", node.data);
            current = &node.next;
        }
        println!("NULL");
    }

    // 插入新节点到链表尾部
    fn append_node(&mut self, data: i32) {
        let new_node = Box::new(Node {
            data,
            next: None,
        });

        if self.head.is_none() {
            self.head = Some(new_node);
            return;
        }

        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.next.is_none() {
                node.next = Some(new_node);
                break;
            }
            current = &mut node.next;
        }
    }
}

fn main() {
    let mut list = LinkedList::new();

    // 插入节点
    list.append_node(1);
    list.append_node(2);
    list.append_node(3);

    list.print_list(); // 输出：1 -> 2 -> 3 -> NULL
}

/*
jarry@MacBook-Pro linked % rustc singly_linked.rs
jarry@MacBook-Pro linked % ./singly_linked 
1 -> 2 -> 3 -> NULL
*/