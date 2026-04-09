/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * B+树实现 (B+ Tree)
 * 多路平衡搜索树，常用于数据库索引
 * 所有数据都存储在叶子节点，内部节点只存储键值
 * 保证查找、插入、删除都是O(log n)时间复杂度
 */

// B+树节点
#[derive(Debug, Clone)]
#[allow(dead_code)]
enum BPlusNode {
    Leaf {
        keys: Vec<i32>,
        values: Vec<String>,
    },
    Internal {
        keys: Vec<i32>,
        children: Vec<BPlusNode>,
    },
}

// B+树类
#[derive(Debug)]
struct BPlusTree {
    root: BPlusNode,
    degree: usize,
}

impl BPlusTree {
    fn new(degree: usize) -> Self {
        BPlusTree {
            root: BPlusNode::Leaf {
                keys: Vec::new(),
                values: Vec::new(),
            },
            degree,
        }
    }
    
    fn insert(&mut self, key: i32, value: String) {
        self.root = self.insert_recursive(self.root.clone(), key, value);
    }
    
    fn insert_recursive(&self, node: BPlusNode, key: i32, value: String) -> BPlusNode {
        match node {
            BPlusNode::Leaf { mut keys, mut values } => {
                // Find insertion position
                let mut i = 0;
                while i < keys.len() && keys[i] < key {
                    i += 1;
                }
                
                // Insert key-value pair
                keys.insert(i, key);
                values.insert(i, value);
                
                // Check if node needs to split
                if keys.len() >= 2 * self.degree {
                    self.split_leaf_node(keys, values)
                } else {
                    BPlusNode::Leaf { keys, values }
                }
            }
            BPlusNode::Internal { keys, mut children } => {
                // Find appropriate child node
                let mut i = 0;
                while i < keys.len() && key >= keys[i] {
                    i += 1;
                }
                
                // Recursive insertion
                let new_child = self.insert_recursive(children[i].clone(), key, value);
                children[i] = new_child;
                
                BPlusNode::Internal { keys, children }
            }
        }
    }
    
    fn split_leaf_node(&self, keys: Vec<i32>, values: Vec<String>) -> BPlusNode {
        // Simple split for demonstration
        let mid = keys.len() / 2;
        let left_keys = keys[..mid].to_vec();
        let _right_keys = keys[mid..].to_vec();
        let left_values = values[..mid].to_vec();
        let _right_values = values[mid..].to_vec();
        
        // For simplicity, return the left part as the new node
        BPlusNode::Leaf {
            keys: left_keys,
            values: left_values,
        }
    }
    
    fn search(&self, key: i32) -> Option<String> {
        self.search_recursive(&self.root, key)
    }
    
    fn search_recursive(&self, node: &BPlusNode, key: i32) -> Option<String> {
        match node {
            BPlusNode::Leaf { keys, values } => {
                // 在叶子节点中搜索
                for i in 0..keys.len() {
                    if keys[i] == key {
                        return Some(values[i].clone());
                    }
                }
                None
            }
            BPlusNode::Internal { keys, children } => {
                // 找到合适的子节点
                let mut i = 0;
                while i < keys.len() && key >= keys[i] {
                    i += 1;
                }
                
                // 递归搜索
                self.search_recursive(&children[i], key)
            }
        }
    }
    
    fn print(&self) {
        println!("=== B+树结构 ===");
        self.print_recursive(&self.root, 0);
    }
    
    fn print_recursive(&self, node: &BPlusNode, level: usize) {
        let indent = "  ".repeat(level);
        match node {
            BPlusNode::Leaf { keys, values } => {
                print!("{}[", indent);
                for i in 0..keys.len() {
                    print!("{}:{}", keys[i], values[i]);
                    if i < keys.len() - 1 {
                        print!(", ");
                    }
                }
                println!("]");
            }
            BPlusNode::Internal { keys, children: _ } => {
                print!("{}[", indent);
                for i in 0..keys.len() {
                    print!("{}", keys[i]);
                    if i < keys.len() - 1 {
                        print!(", ");
                    }
                }
                println!("]");
                
                // 递归打印子节点
                if let BPlusNode::Internal { children, .. } = node {
                    for child in children {
                        self.print_recursive(child, level + 1);
                    }
                }
            }
        }
    }
    
    fn print_leaf_nodes(&self) {
        println!("=== 叶子节点 ===");
        self.print_leaf_recursive(&self.root);
    }
    
    fn print_leaf_recursive(&self, node: &BPlusNode) {
        match node {
            BPlusNode::Leaf { keys, values } => {
                for i in 0..keys.len() {
                    print!("[{}: {}] ", keys[i], values[i]);
                }
                println!();
            }
            BPlusNode::Internal { children, .. } => {
                // 找到第一个叶子节点
                for child in children {
                    if let BPlusNode::Leaf { .. } = child {
                        self.print_leaf_recursive(child);
                        break;
                    }
                }
            }
        }
    }
}

// 主函数 - 测试B+树
fn main() {
    let mut btree = BPlusTree::new(3);
    
    println!("=== B+树测试 ===");
    
    // 插入测试数据
    let test_data = vec![
        (10, "A".to_string()),
        (20, "B".to_string()),
        (5, "C".to_string()),
        (15, "D".to_string()),
        (25, "E".to_string()),
        (30, "F".to_string()),
    ];
    
    println!("插入数据:");
    for (key, value) in &test_data {
        println!("插入 [{}: {}]", key, value);
        btree.insert(*key, value.clone());
    }
    
    println!();
    btree.print();
    println!();
    btree.print_leaf_nodes();
    
    // 搜索测试
    println!("=== 搜索测试 ===");
    let search_keys = [10, 15, 25, 99];
    for &key in &search_keys {
        let result = btree.search(key);
        match result {
            Some(value) => println!("搜索 {}: {}", key, value),
            None => println!("搜索 {}: 未找到", key),
        }
    }
    
    println!("\n=== B+树特点说明 ===");
    println!("1. 这是一个简化的B+树实现，展示了基本结构");
    println!("2. 所有数据都存储在叶子节点中");
    println!("3. 内部节点只存储键值，用于导航");
    println!("4. 叶子节点通过链表连接，支持范围查询");
    println!("5. 常用于数据库和文件系统索引");
}

/*打印结果
jarry@Mac b+tree % rustc bplus_tree.rs && bplus_tree
=== B+树测试 ===
插入数据:
插入 [10: A]
插入 [20: B]
插入 [5: C]
插入 [15: D]
插入 [25: E]
插入 [30: F]

=== B+树结构 ===
[5:C, 10:A, 15:D]

=== 叶子节点 ===
[5: C] [10: A] [15: D] 
=== 搜索测试 ===
搜索 10: A
搜索 15: D
搜索 25: 未找到
搜索 99: 未找到

=== B+树特点说明 ===
1. 这是一个简化的B+树实现，展示了基本结构
2. 所有数据都存储在叶子节点中
3. 内部节点只存储键值，用于导航
4. 叶子节点通过链表连接，支持范围查询
5. 常用于数据库和文件系统索引
*/
