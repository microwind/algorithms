const MAX_QUEUE_SIZE: usize = 10;

// Queue 结构体
struct Queue {
    data: Vec<i32>,
    size: usize,
}

impl Queue {
    // 初始化队列
    fn new() -> Self {
        Queue {
            data: Vec::with_capacity(MAX_QUEUE_SIZE),
            size: 0,
        }
    }

    // 判断队列是否为空
    fn is_empty(&self) -> bool {
        self.size == 0
    }

    // 判断队列是否已满
    fn is_full(&self) -> bool {
        self.size == MAX_QUEUE_SIZE
    }

    // 入队操作
    fn enqueue(&mut self, value: i32) {
        if self.is_full() {
            println!("Queue is full! Cannot enqueue {}", value);
            return;
        }
        self.data.push(value);
        self.size += 1;
        println!("{} enqueued to queue", value);
    }

    // 出队操作
    fn dequeue(&mut self) -> Option<i32> {
        if self.is_empty() {
            println!("Queue is empty! Cannot dequeue");
            return None;
        }
        self.size -= 1;
        Some(self.data.remove(0))
    }

    // 获取队头元素
    fn peek(&self) -> Option<i32> {
        if self.is_empty() {
            println!("Queue is empty! Cannot peek");
            return None;
        }
        Some(self.data[0])
    }

    // 获取队列大小
    fn get_size(&self) -> usize {
        self.size
    }

    // 打印队列内容
    fn print_queue(&self) {
        if self.is_empty() {
            println!("Queue is empty");
            return;
        }
        println!("Queue contents: {:?}", self.data);
    }
}

fn main() {
    let mut queue = Queue::new();

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.print_queue();

    println!("Dequeued: {:?}", queue.dequeue());
    queue.print_queue();

    println!("Front element: {:?}", queue.peek());
    println!("Queue size: {}", queue.get_size());

    queue.enqueue(60);
    queue.print_queue();
}

/*
jarry@MacBook-Pro queue % rustc queue.rs
jarry@MacBook-Pro queue % ./queue 
10 enqueued to queue
20 enqueued to queue
30 enqueued to queue
40 enqueued to queue
50 enqueued to queue
Queue contents: [10, 20, 30, 40, 50]
Dequeued: Some(10)
Queue contents: [20, 30, 40, 50]
Front element: Some(20)
Queue size: 4
60 enqueued to queue
Queue contents: [20, 30, 40, 50, 60]
*/