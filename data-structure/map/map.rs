struct Map {
    entries: Vec<Entry>,
    size: usize,
    capacity: usize,
}

struct Entry {
    key: String,
    value: i32,
}

impl Map {
    fn new() -> Map {
        Map {
            entries: Vec::with_capacity(10),
            size: 0,
            capacity: 10,
        }
    }

    // 重新分配容量
    fn resize_map(&mut self, new_capacity: usize) {
        self.capacity = new_capacity;
    }

    // 插入键值对（如果存在则更新）
    fn put(&mut self, key: String, value: i32) {
        for entry in &mut self.entries {
            if entry.key == key {
                entry.value = value; // 更新值
                return;
            }
        }
        if self.size >= self.capacity {
            self.resize_map(self.capacity * 2);
        }
        self.entries.push(Entry { key, value });
        self.size += 1;
    }

    // 查找键
    fn get(&self, key: &str) -> i32 {
        for entry in &self.entries {
            if entry.key == key {
                return entry.value;
            }
        }
        -1 // 未找到
    }

    // 删除键
    fn delete(&mut self, key: &str) {
        if let Some(pos) = self.entries.iter().position(|entry| entry.key == key) {
            self.entries.remove(pos);
            self.size -= 1;
        }
    }
}

fn main() {
    let mut map = Map::new();

    map.put("apple".to_string(), 10);
    map.put("banana".to_string(), 20);
    map.put("orange".to_string(), 30);

    println!("apple: {}", map.get("apple"));
    println!("banana: {}", map.get("banana"));
    println!("grape: {}", map.get("grape"));

    map.delete("banana");
    println!("banana after delete: {}", map.get("banana"));
}

/*
jarry@MacBook-Pro map % rustc map.rs
jarry@MacBook-Pro map % ./map 
apple: 10
banana: 20
grape: -1
banana after delete: -1
*/