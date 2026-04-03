/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 哈希查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

use std::collections::HashMap;

/**
 * 哈希表结构
 * 使用标准库的HashMap实现
 */
struct HashTable {
    map: HashMap<String, i32>,
}

impl HashTable {
    /**
     * 创建新的哈希表
     */
    fn new() -> Self {
        HashTable {
            map: HashMap::new(),
        }
    }
    
    /**
     * 插入键值对
     * @param key - 键
     * @param value - 值
     */
    fn insert(&mut self, key: String, value: i32) {
        self.map.insert(key, value);
    }
    
    /**
     * 哈希查找
     * @param key - 要查找的键
     * @return - 找到的值（Option类型），未找到返回None
     */
    fn search(&self, key: &str) -> Option<&i32> {
        self.map.get(key)
    }
    
    /**
     * 删除键值对
     * @param key - 要删除的键
     * @return - 删除成功返回true，失败返回false
     */
    fn delete(&mut self, key: &str) -> bool {
        self.map.remove(key).is_some()
    }
    
    /**
     * 显示哈希表内容
     */
    fn display(&self) {
        println!("哈希表内容:");
        if self.map.is_empty() {
            println!("  空");
        } else {
            for (key, value) in &self.map {
                println!("  {}: {}", key, value);
            }
        }
    }
}

/**
 * 主程序：演示哈希查找功能
 */
fn main() {
    println!("=== 哈希查找演示 ===\n");
    
    // 创建哈希表
    let mut hash_table = HashTable::new();
    
    // 插入数据
    println!("插入数据:");
    let keys = vec!["apple", "banana", "cherry", "date", "elderberry"];
    let values = vec![100, 200, 300, 400, 500];
    
    for (i, &key) in keys.iter().enumerate() {
        hash_table.insert(key.to_string(), values[i]);
        println!("  key={}, value={}", key, values[i]);
    }
    
    println!();
    hash_table.display();
    
    // 查找测试
    println!("\n查找测试:");
    let search_keys = vec!["banana", "cherry", "grape"];
    
    for key in &search_keys {
        match hash_table.search(key) {
            Some(value) => println!("  查找 '{}': 找到，value={}", key, value),
            None => println!("  查找 '{}': 未找到", key),
        }
    }
    
    // 性能分析
    println!("\n性能分析:");
    println!("  • 平均时间复杂度: O(1)");
    println!("  • 最坏时间复杂度: O(n)（所有键冲突）");
    println!("  • 空间复杂度: O(n)");
    
    // 删除测试
    println!("\n删除测试:");
    let deleted = hash_table.delete("banana");
    println!("  删除 'banana': {}", if deleted { "成功" } else { "失败" });
    
    println!("\n删除后的哈希表:");
    hash_table.display();
    
    // 再次查找已删除的键
    match hash_table.search("banana") {
        Some(value) => println!("\n再次查找 'banana': 找到，value={}", value),
        None => println!("\n再次查找 'banana': 未找到"),
    }
}

/*
打印结果
jarry@Mac hash-search % rustc hash_search.rs && ./hash_search
=== 哈希查找演示 ===

插入数据:
  key=apple, value=100
  key=banana, value=200
  key=cherry, value=300
  key=date, value=400
  key=elderberry, value=500

哈希表内容:
  banana: 200
  apple: 100
  cherry: 300
  date: 400
  elderberry: 500

查找测试:
  查找 'banana': 找到，value=200
  查找 'cherry': 找到，value=300
  查找 'grape': 未找到

性能分析:
  • 平均时间复杂度: O(1)
  • 最坏时间复杂度: O(n)（所有键冲突）
  • 空间复杂度: O(n)

删除测试:
  删除 'banana': 成功

删除后的哈希表:
  apple: 100
  cherry: 300
  date: 400
  elderberry: 500

再次查找 'banana': 未找到
*/
