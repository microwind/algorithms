use std::collections::HashMap;

struct Map {
    entries: Vec<(String, i32)>,  // 存储键值对
    index_map: HashMap<String, usize>,  // 键到索引的映射
    size: usize,  // 当前键值对数量
    capacity: usize,  // 容量
}

impl Map {
    // 初始化 Map
    fn new() -> Map {
        Map {
            entries: Vec::with_capacity(10),
            index_map: HashMap::new(),
            size: 0,
            capacity: 10,
        }
    }

    // 扩容
    fn resize_map(&mut self) {
        self.capacity *= 2;
    }

    // 插入键值对
    fn put(&mut self, key: String, value: i32) {
        if self.index_map.contains_key(&key) {
            // 如果键已存在，更新值
            let index = self.index_map[&key];
            self.entries[index].1 = value;
        } else {
            // 如果容量已满，扩容
            if self.size >= self.capacity {
                self.resize_map();
            }

            // 插入新键值对
            self.entries.push((key.clone(), value));
            self.index_map.insert(key, self.size);
            self.size += 1;
        }
    }

    // 查找键
    fn get(&self, key: &str) -> Option<i32> {
        self.index_map.get(key).map(|&index| self.entries[index].1)
    }

    // 删除键
    fn delete(&mut self, key: &str) {
        if let Some(&index) = self.index_map.get(key) {
            self.entries.remove(index);
            self.index_map.remove(key);

            // 更新后续键的索引
            for i in index..self.size - 1 {
                let key = self.entries[i].0.clone();
                self.index_map.insert(key, i);
            }

            self.size -= 1;
        }
    }

    // 判断键是否存在
    fn has(&self, key: &str) -> bool {
        self.index_map.contains_key(key)
    }

    // 获取键值对个数
    fn get_size(&self) -> usize {
        self.size
    }

    // 清空所有数据
    fn clear(&mut self) {
        self.entries.clear();
        self.index_map.clear();
        self.size = 0;
    }

    // 遍历所有键值对
    fn for_each<F>(&self, mut callback: F)
    where
        F: FnMut(i32, &str),
    {
        for entry in &self.entries {
            callback(entry.1, &entry.0);
        }
    }
}

// 回调函数示例
fn print_entry(value: i32, key: &str) {
    println!("{}: {}", key, value);
}

fn main() {
    let mut map = Map::new();

    map.put("apple".to_string(), 10);
    map.put("banana".to_string(), 20);
    map.put("orange".to_string(), 30);

    println!("apple: {:?}", map.get("apple"));
    println!("banana: {:?}", map.get("banana"));
    println!("grape: {:?}", map.get("grape"));

    println!("map.has(\"grape\"): {:?}", map.has("grape"));
    println!("map.get_size(\"\"): {:?}", map.get_size());

    map.delete("banana");
    println!("banana after delete: {:?}", map.get("banana"));

    map.for_each(print_entry);

    map.clear();
}

/*
jarry@MacBook-Pro map % rustc map2.rs
jarry@MacBook-Pro map % ./map2       
apple: Some(10)
banana: Some(20)
grape: None
map.has("grape"): false
map.get_size(""): 3
banana after delete: None
apple: 10
orange: 30
*/