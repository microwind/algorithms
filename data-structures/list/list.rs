// use std::ptr;

const INITIAL_CAPACITY: usize = 10;

struct List {
    data: Vec<i32>,
    size: usize,
}

impl List {
    // 初始化 List
    fn new() -> Self {
        List {
            data: Vec::with_capacity(INITIAL_CAPACITY),
            size: 0,
        }
    }

    // 扩展 List 容量
    fn resize(&mut self, new_capacity: usize) {
        if new_capacity > self.data.capacity() {
            self.data.reserve(new_capacity - self.data.capacity());
        }
    }

    // 添加元素
    fn add(&mut self, value: i32) {
        // Vec<T> 是一个动态数组，它会自动扩容，这里仅作演示。
        if self.size == self.data.capacity() {
            self.resize(self.data.capacity() * 2); // 容量翻倍
        }
        if self.size < self.data.len() {
            self.data[self.size] = value;
        } else {
            self.data.push(value);
        }
        self.size += 1;
    }

    // 删除最后一个元素
    fn remove(&mut self) {
        if self.size > 0 {
            self.size -= 1;
        }
    }

    // 获取指定索引的元素
    fn get(&self, index: usize) -> Option<i32> {
        if index < self.size {
            Some(self.data[index])
        } else {
            None
        }
    }

    // 打印所有元素
    fn print(&self) {
        print!("List: ");
        for i in 0..self.size {
            print!("{} ", self.data[i]);
        }
        println!();
    }

    // 获取 List 的大小
    fn size(&self) -> usize {
        self.size
    }

    // 获取 List 的容量
    fn capacity(&self) -> usize {
        self.data.capacity()
    }
}

fn main() {
    let mut list = List::new();

    // 添加元素
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    // 打印列表
    list.print(); // 输出：List: 10 20 30 40

    // 获取元素
    match list.get(2) {
        Some(value) => println!("Element at index 2: {}", value), // 输出：Element at index 2: 30
        None => println!("Index out of range"),
    }

    // 删除最后一个元素
    list.remove();
    list.print(); // 输出：List: 10 20 30

    // 获取大小和容量
    println!("Size: {}", list.size()); // 输出：Size: 3
    println!("Capacity: {}", list.capacity()); // 输出：Capacity: 10（或者更高，视情况而定）

    // 调整容量
    list.resize(20);
    println!("New Capacity: {}", list.capacity()); // 输出：New Capacity: 20（可能更大，取决于 Vec 的策略）
}


/*
jarry@MacBook-Pro list % rustc list.rs
jarry@MacBook-Pro list % ./list 
List: 10 20 30 40 
Element at index 2: 30
List: 10 20 30 
Size: 3
Capacity: 10
New Capacity: 20
*/
