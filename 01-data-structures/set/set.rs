use std::collections::hash_map::DefaultHasher;
use std::hash::{Hash, Hasher};

const INITIAL_CAPACITY: usize = 16; // 初始哈希表容量
const LOAD_FACTOR: f32 = 0.75; // 负载因子

// 哈希表节点结构
struct SetNode<K> {
    key: K,
    next: Option<Box<SetNode<K>>>,
}

// Set 结构体
struct Set<K> {
    buckets: Vec<Option<Box<SetNode<K>>>>,
    capacity: usize,
    size: usize,
}

impl<K> Set<K>
where
    K: Eq + Clone + std::fmt::Debug + Hash, // 需要添加 Hash 约束
{
    // 创建 Set 并初始化
    fn new(capacity: usize) -> Self {
        let mut buckets = Vec::with_capacity(capacity);
        for _ in 0..capacity {
            buckets.push(None);
        }
        Set {
            buckets,
            capacity,
            size: 0,
        }
    }

    // FNV-1a 哈希函数
    fn fnv_hash_func(key: &[u8]) -> u32 {
        let mut hash = 2166136261u32; // FNV-1a 初始值
        for &byte in key {
            hash ^= byte as u32;
            hash = hash.wrapping_mul(16777619); // FNV-1a 乘法常数
        }
        hash
    }

    // 计算哈希值
    fn hash(&self, key: &K) -> usize {
        // 使用标准库的 Hash trait 和 DefaultHasher 计算哈希值
        let mut hasher = DefaultHasher::new();
        key.hash(&mut hasher);
        let hashed_value = hasher.finish();

        // 将哈希值转换为字节切片并使用 FNV-1a 哈希
        let key_bytes = hashed_value.to_le_bytes();
        let fnv_hash = Self::fnv_hash_func(&key_bytes);
        fnv_hash as usize % self.capacity
    }

    // 扩容 Set
    fn resize(&mut self) {
        let new_capacity = self.capacity * 2;
        let mut new_buckets = Vec::with_capacity(new_capacity);
        for _ in 0..new_capacity {
            new_buckets.push(None);
        }

        // 重新哈希所有元素
        for i in 0..self.capacity {
            let mut node = self.buckets[i].take();
            while let Some(mut current_node) = node {
                let index = self.hash(&current_node.key);
                let next_node = current_node.next.take();
                current_node.next = new_buckets[index].take();
                new_buckets[index] = Some(current_node);
                node = next_node;
            }
        }

        // 更新容量和桶数组
        self.buckets = new_buckets;
        self.capacity = new_capacity;
    }

    // 添加元素到 Set
    fn add(&mut self, key: K) {
        // 判断是否需要扩容
        if (self.size as f32 / self.capacity as f32) > LOAD_FACTOR {
            self.resize();
        }

        let index = self.hash(&key);
        let mut node = &mut self.buckets[index];

        // 查找桶中是否已经有相同的元素
        while let Some(ref mut current_node) = node {
            if current_node.key == key {
                return; // 如果找到了相同的元素，则返回
            }
            node = &mut current_node.next;
        }

        // 没有找到相同的元素，进行插入
        let new_node = Box::new(SetNode {
            key: key.clone(),
            next: self.buckets[index].take(),
        });
        self.buckets[index] = Some(new_node);
        self.size += 1;

        // 打印调试信息
        println!("Adding node: index={} key={:?}", index, key);
    }

    // 检查元素是否在 Set 中
    fn contains(&self, key: &K) -> bool {
        let index = self.hash(key);
        let mut node = &self.buckets[index];
        while let Some(ref current_node) = node {
            if current_node.key == *key {
                return true;
            }
            node = &current_node.next;
        }
        false
    }

    // 从 Set 中删除元素
    fn remove(&mut self, key: &K) {
        let index = self.hash(key);
        let mut node = &mut self.buckets[index];

        while let Some(ref mut current_node) = node {
            if current_node.key == *key {
                // 临时保存 next_node，避免修改 node 时发生借用冲突
                let next_node = current_node.next.take();
                // 解除对 node 的借用，修改其内容
                node = &mut current_node.next;
                *node = next_node;
                self.size -= 1;
                return;
            }
            node = &mut current_node.next;
        }
    }

    // 获取 Set 中的元素个数
    fn size(&self) -> usize {
        self.size
    }

    // 打印 Set 中的所有元素
    fn print(&self)
    where
        K: std::fmt::Debug,
    {
        for i in 0..self.capacity {
            let mut node = &self.buckets[i];
            while let Some(ref current_node) = node {
                print!("{:?} ", current_node.key);
                node = &current_node.next;
            }
        }
        println!();
    }
}

fn main() {
    // 创建一个 Set
    let mut set = Set::new(INITIAL_CAPACITY);
    let values = [10, 20, 20, 30, 40, 40, 50];

    // 添加元素
    for &value in &values {
        set.add(value);
    }

    // 打印 Set 内容
    set.print();
    println!("set.size: {}", set.size());

    // 检查元素是否存在
    println!("Contains 30? {}", set.contains(&30));

    // 删除元素
    set.remove(&30);
    set.print();
}

/*
jarry@MacBook-Pro set % rustc set.rs
jarry@MacBook-Pro set % ./set
Adding node: index=3 key=10
Adding node: index=5 key=20
Adding node: index=2 key=30
Adding node: index=14 key=40
Adding node: index=6 key=50
30 10 20 50 40
set.size: 5
Contains 30? true
30 10 20 50 40
*/
