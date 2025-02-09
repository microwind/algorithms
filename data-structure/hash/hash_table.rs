use std::collections::LinkedList;

const TABLE_SIZE: usize = 10;

#[derive(Clone)]
struct HashTable {
    table: Vec<LinkedList<Entry>>,
}

#[derive(Clone)]
struct Entry {
    key: i32,
    value: i32,
}

impl HashTable {
    fn new() -> HashTable {
        let mut table = Vec::with_capacity(TABLE_SIZE);
        for _ in 0..TABLE_SIZE {
            table.push(LinkedList::new());
        }
        HashTable { table }
    }

    fn hash(&self, key: i32) -> usize {
        (key % TABLE_SIZE as i32) as usize
    }

    fn insert(&mut self, key: i32, value: i32) {
        let index = self.hash(key);
        let entry = Entry { key, value };
        self.table[index].push_front(entry);
    }

    fn search(&self, key: i32) -> Option<i32> {
        let index = self.hash(key);
        for entry in &self.table[index] {
            if entry.key == key {
                return Some(entry.value);
            }
        }
        None
    }

    fn delete(&mut self, key: i32) {
        let index = self.hash(key);
        // 使用 filter 重新构建 LinkedList，只保留不匹配的元素
        let filtered: LinkedList<Entry> = self.table[index]
            .iter()
            .filter(|entry| entry.key != key)
            .cloned()
            .collect();
        self.table[index] = filtered;
    }

    fn print_table(&self) {
        for (i, bucket) in self.table.iter().enumerate() {
            if !bucket.is_empty() {
                print!("Index {}: ", i);
                for entry in bucket {
                    print!("[{}:{}] ", entry.key, entry.value);
                }
                println!();
            }
        }
    }
}

fn main() {
    let mut hash_table = HashTable::new();

    hash_table.insert(1, 100);
    hash_table.insert(2, 200);
    hash_table.insert(3, 300);

    println!("Search key 2: {:?}", hash_table.search(2));

    hash_table.delete(2);
    println!("After deleting key 2:");
    hash_table.print_table();
}

/*
jarry@MacBook-Pro hash % rustc hash_table.rs
jarry@MacBook-Pro hash % ./hash_table 
Search key 2: Some(200)
After deleting key 2:
Index 1: [1:100] 
Index 3: [3:300] 
*/