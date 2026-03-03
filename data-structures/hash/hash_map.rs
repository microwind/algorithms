use std::collections::hash_map::DefaultHasher;
use std::ffi::CString;
use std::hash::{Hash, Hasher};

const INITIAL_CAPACITY: usize = 10;
const LOAD_FACTOR: f32 = 0.75;

#[derive(Debug)]
struct Entry {
    key: CString, // 使用 CString 存储键，保证在 C 兼容场景下可用
    value: i32,   // 存储的值
    next: Option<Box<Entry>>, // 链表的下一个节点
}

#[derive(Debug)]
struct HashMap {
    table: Vec<Option<Box<Entry>>>, // 哈希表，存储链地址法的链表头结点
    size: usize, // 当前存储的键值对数量
    capacity: usize, // 哈希表的容量
}

impl HashMap {
    /// 创建一个新的哈希表
    fn new() -> Self {
        let mut table = Vec::with_capacity(INITIAL_CAPACITY);
        for _ in 0..INITIAL_CAPACITY {
            table.push(None);
        }
        HashMap {
            table,
            size: 0,
            capacity: INITIAL_CAPACITY,
        }
    }

    /// 计算哈希值并转换为索引
    fn hash(key: &str, capacity: usize) -> usize {
        let mut hasher = DefaultHasher::new();
        key.hash(&mut hasher);
        (hasher.finish() as usize) % capacity
    }

    /// 扩容哈希表，容量变为原来的两倍
    fn resize(&mut self) {
        let new_capacity = self.capacity * 2;
        let mut new_table = Vec::with_capacity(new_capacity);
        for _ in 0..new_capacity {
            new_table.push(None);
        }

        // 重新分配旧哈希表的元素到新表
        for i in 0..self.capacity {
            let mut entry = self.table[i].take();
            while let Some(mut node) = entry {
                let new_index = HashMap::hash(&node.key.to_str().unwrap(), new_capacity);
                let next = node.next.take(); // 先断开 next 避免循环引用
                new_table[new_index] = Some(Box::new(Entry {
                    key: node.key,
                    value: node.value,
                    next,
                }));
                entry = node.next.take();
            }
        }

        self.table = new_table;
        self.capacity = new_capacity;
    }

    /// 插入键值对，若键已存在则更新值
    fn put(&mut self, key: &str, value: i32) {
        // 判断是否需要扩容
        if (self.size as f32 / self.capacity as f32) > LOAD_FACTOR {
            self.resize();
        }

        let index = HashMap::hash(key, self.capacity);
        let mut entry = self.table[index].take();

        while let Some(mut node) = entry {
            if node.key.to_str().unwrap() == key {
                node.value = value; // 更新已有键的值
                self.table[index] = Some(node);
                return;
            }
            entry = node.next.take();
        }

        // 头插法插入新节点
        let new_entry = Box::new(Entry {
            key: CString::new(key).unwrap(),
            value,
            next: self.table[index].take(),
        });
        self.table[index] = Some(new_entry);
        self.size += 1;
    }

    /// 获取指定键的值，若不存在返回 -1
    fn get(&self, key: &str) -> i32 {
        let index = HashMap::hash(key, self.capacity);
        let mut entry = self.table[index].as_ref();

        while let Some(node) = entry {
            if node.key.to_str().unwrap() == key {
                return node.value;
            }
            entry = node.next.as_ref();
        }

        -1 // 表示未找到
    }

    /// 删除指定键的键值对
    fn delete(&mut self, key: &str) {
        let index = HashMap::hash(key, self.capacity);
        let mut entry = self.table[index].take();
        let mut prev: Option<Box<Entry>> = None;

        while let Some(mut node) = entry {
            let next = node.next.take(); // 先获取 next
            if node.key.to_str().unwrap() == key {
                if let Some(mut prev_node) = prev {
                    prev_node.next = next; // 连接前后节点
                    self.table[index] = Some(prev_node);
                } else {
                    self.table[index] = next; // 删除头结点
                }
                self.size -= 1;
                return;
            }
            prev = Some(node); // 再移动 node
            entry = next; // 继续遍历
        }
    }
}

fn main() {
    let mut map = HashMap::new();

    map.put("apple", 10);
    map.put("banana", 20);
    map.put("orange", 30);

    println!("apple: {}", map.get("apple"));
    println!("banana: {}", map.get("banana"));
    println!("grape: {} (not found)", map.get("grape"));

    map.delete("banana");
    println!("banana after delete: {}", map.get("banana"));
}

/*
jarry@MacBook-Pro hash % rustc --version
rustc 1.84.0 (9fc6b4312 2025-01-07)
jarry@MacBook-Pro hash % rustc ./hash_map.rs 
jarry@MacBook-Pro hash % ./hash_map 
apple: 10
banana: 20
grape: -1 (not found)
banana after delete: -1
*/
