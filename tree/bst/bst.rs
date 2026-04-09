/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树算法 - 二叉搜索树实现 (Binary Search Tree)
 * 有序二叉树，左子树 < 根节点 < 右子树
 * 用于快速查找、插入、删除
 */

// BST节点结构
#[derive(Debug, Clone)]
struct BSTNode {
    data: i32,
    left: Option<Box<BSTNode>>,
    right: Option<Box<BSTNode>>,
}

impl BSTNode {
    fn new(data: i32) -> Self {
        BSTNode {
            data,
            left: None,
            right: None,
        }
    }
    
    // 插入节点到BST
    fn insert(&mut self, data: i32) {
        if data < self.data {
            if let Some(ref mut left) = self.left {
                left.insert(data);
            } else {
                self.left = Some(Box::new(BSTNode::new(data)));
            }
        } else if data > self.data {
            if let Some(ref mut right) = self.right {
                right.insert(data);
            } else {
                self.right = Some(Box::new(BSTNode::new(data)));
            }
        }
        // 重复值不允许
    }
    
    // 查找节点
    fn search(&self, data: i32) -> bool {
        if data == self.data {
            true
        } else if data < self.data {
            self.left.as_ref().map_or(false, |node| node.search(data))
        } else {
            self.right.as_ref().map_or(false, |node| node.search(data))
        }
    }
    
    // 中序遍历（升序）
    fn in_order(&self) {
        if let Some(ref left) = self.left {
            left.in_order();
        }
        print!("{} ", self.data);
        if let Some(ref right) = self.right {
            right.in_order();
        }
    }
    
    // 前序遍历
    fn pre_order(&self) {
        print!("{} ", self.data);
        if let Some(ref left) = self.left {
            left.pre_order();
        }
        if let Some(ref right) = self.right {
            right.pre_order();
        }
    }
    
    // 后序遍历
    fn post_order(&self) {
        if let Some(ref left) = self.left {
            left.post_order();
        }
        if let Some(ref right) = self.right {
            right.post_order();
        }
        print!("{} ", self.data);
    }
    
    // 查找最小值
    fn find_min(&self) -> i32 {
        self.left.as_ref().map_or(self.data, |node| node.find_min())
    }
    
    // 查找最大值
    fn find_max(&self) -> i32 {
        self.right.as_ref().map_or(self.data, |node| node.find_max())
    }
    
    // 计算树的高度
    fn height(&self) -> i32 {
        let left_height = self.left.as_ref().map_or(0, |node| node.height());
        let right_height = self.right.as_ref().map_or(0, |node| node.height());
        1 + std::cmp::max(left_height, right_height)
    }
    
    // 计算节点数量
    fn node_count(&self) -> i32 {
        let left_count = self.left.as_ref().map_or(0, |node| node.node_count());
        let right_count = self.right.as_ref().map_or(0, |node| node.node_count());
        1 + left_count + right_count
    }
}

// BST类
#[derive(Debug)]
struct BST {
    root: Option<Box<BSTNode>>,
}

impl BST {
    fn new() -> Self {
        BST { root: None }
    }
    
    fn insert(&mut self, data: i32) {
        if let Some(ref mut root) = self.root {
            root.insert(data);
        } else {
            self.root = Some(Box::new(BSTNode::new(data)));
        }
    }
    
    fn search(&self, data: i32) -> bool {
        self.root.as_ref().map_or(false, |node| node.search(data))
    }
    
    fn in_order(&self) {
        if let Some(ref root) = self.root {
            root.in_order();
        }
    }
    
    fn pre_order(&self) {
        if let Some(ref root) = self.root {
            root.pre_order();
        }
    }
    
    fn post_order(&self) {
        if let Some(ref root) = self.root {
            root.post_order();
        }
    }
    
    fn height(&self) -> i32 {
        self.root.as_ref().map_or(0, |node| node.height())
    }
    
    fn node_count(&self) -> i32 {
        self.root.as_ref().map_or(0, |node| node.node_count())
    }
    
    fn find_min(&self) -> Option<i32> {
        self.root.as_ref().map(|node| node.find_min())
    }
    
    fn find_max(&self) -> Option<i32> {
        self.root.as_ref().map(|node| node.find_max())
    }
}

// 主函数 - 测试BST
fn main() {
    let mut bst = BST::new();
    
    println!("=== 二叉搜索树测试 ===");
    
    // 插入测试数据
    let test_data = [50, 30, 70, 20, 40, 60, 80];
    print!("插入数据: ");
    for &data in &test_data {
        print!("{} ", data);
        bst.insert(data);
    }
    println!();
    println!();
    
    // 遍历测试
    println!("=== 遍历测试 ===");
    print!("中序遍历: ");
    bst.in_order();
    println!();
    
    print!("前序遍历: ");
    bst.pre_order();
    println!();
    
    print!("后序遍历: ");
    bst.post_order();
    println!();
    println!();
    
    // 搜索测试
    println!("=== 搜索测试 ===");
    let search_keys = [40, 90];
    for &key in &search_keys {
        let found = bst.search(key);
        println!("搜索 {}: {}", key, if found { "找到" } else { "未找到" });
    }
    println!();
    
    // 树属性测试
    println!("=== 树属性测试 ===");
    println!("树的高度: {}", bst.height());
    println!("节点数量: {}", bst.node_count());
    
    if let Some(min) = bst.find_min() {
        println!("最小值: {}", min);
    }
    if let Some(max) = bst.find_max() {
        println!("最大值: {}", max);
    }
    
    println!();
    println!("=== BST特点说明 ===");
    println!("1. 左子树所有节点 < 根节点 < 右子树所有节点");
    println!("2. 中序遍历得到有序序列");
    println!("3. 查找、插入、删除平均时间复杂度 O(log n)");
    println!("4. 最坏情况（退化为链表）时间复杂度 O(n)");
}

/*打印结果
jarry@Mac bst % rustc bst.rs && ./bst
=== 二叉搜索树测试 ===
插入数据: 50 30 70 20 40 60 80 

=== 遍历测试 ===
中序遍历: 20 30 40 50 60 70 80 
前序遍历: 50 30 20 40 70 60 80 
后序遍历: 20 40 30 60 80 70 50 

=== 搜索测试 ===
搜索 40: 找到
搜索 90: 未找到

=== 树属性测试 ===
树的高度: 3
节点数量: 7
最小值: 20
最大值: 80

=== BST特点说明 ===
1. 左子树所有节点 < 根节点 < 右子树所有节点
2. 中序遍历得到有序序列
3. 查找、插入、删除平均时间复杂度 O(log n)
4. 最坏情况（退化为链表）时间复杂度 O(n)
*/
