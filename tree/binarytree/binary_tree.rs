/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二叉树实现 (Binary Tree)
 * 基本的二叉树数据结构，支持插入、搜索、遍历等操作
 * 时间复杂度：查找O(n)，插入O(n)，删除O(n)
 * 空间复杂度：O(n)
 */

use std::collections::VecDeque;

// 二叉树节点
#[derive(Debug, Clone)]
struct BinaryTreeNode {
    data: i32,
    left: Option<Box<BinaryTreeNode>>,
    right: Option<Box<BinaryTreeNode>>,
}

impl BinaryTreeNode {
    fn new(data: i32) -> Self {
        BinaryTreeNode {
            data,
            left: None,
            right: None,
        }
    }
    
    // 插入节点
    fn insert(&mut self, data: i32) {
        if data < self.data {
            if let Some(ref mut left) = self.left {
                left.insert(data);
            } else {
                self.left = Some(Box::new(BinaryTreeNode::new(data)));
            }
        } else if data > self.data {
            if let Some(ref mut right) = self.right {
                right.insert(data);
            } else {
                self.right = Some(Box::new(BinaryTreeNode::new(data)));
            }
        }
        // 重复值不插入
    }
    
    // 搜索节点
    fn search(&self, data: i32) -> bool {
        if data == self.data {
            true
        } else if data < self.data {
            self.left.as_ref().map_or(false, |node| node.search(data))
        } else {
            self.right.as_ref().map_or(false, |node| node.search(data))
        }
    }
    
    // 前序遍历
    fn preorder_traversal(&self, result: &mut Vec<i32>) {
        result.push(self.data);
        if let Some(ref left) = self.left {
            left.preorder_traversal(result);
        }
        if let Some(ref right) = self.right {
            right.preorder_traversal(result);
        }
    }
    
    // 中序遍历
    fn inorder_traversal(&self, result: &mut Vec<i32>) {
        if let Some(ref left) = self.left {
            left.inorder_traversal(result);
        }
        result.push(self.data);
        if let Some(ref right) = self.right {
            right.inorder_traversal(result);
        }
    }
    
    // 后序遍历
    fn postorder_traversal(&self, result: &mut Vec<i32>) {
        if let Some(ref left) = self.left {
            left.postorder_traversal(result);
        }
        if let Some(ref right) = self.right {
            right.postorder_traversal(result);
        }
        result.push(self.data);
    }
    
    // 层次遍历
    fn level_order_traversal(&self, result: &mut Vec<i32>) {
        let mut queue = VecDeque::new();
        queue.push_back(self);
        
        while let Some(node) = queue.pop_front() {
            result.push(node.data);
            
            if let Some(ref left) = node.left {
                queue.push_back(left);
            }
            if let Some(ref right) = node.right {
                queue.push_back(right);
            }
        }
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
    
    // 查找最小值
    fn find_min(&self) -> i32 {
        self.left.as_ref().map_or(self.data, |node| node.find_min())
    }
    
    // 查找最大值
    fn find_max(&self) -> i32 {
        self.right.as_ref().map_or(self.data, |node| node.find_max())
    }
}

// 二叉树类
#[derive(Debug)]
struct BinaryTree {
    root: Option<Box<BinaryTreeNode>>,
}

impl BinaryTree {
    fn new() -> Self {
        BinaryTree { root: None }
    }
    
    fn insert(&mut self, data: i32) {
        if let Some(ref mut root) = self.root {
            root.insert(data);
        } else {
            self.root = Some(Box::new(BinaryTreeNode::new(data)));
        }
    }
    
    fn search(&self, data: i32) -> bool {
        self.root.as_ref().map_or(false, |node| node.search(data))
    }
    
    fn preorder_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        if let Some(ref root) = self.root {
            root.preorder_traversal(&mut result);
        }
        result
    }
    
    fn inorder_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        if let Some(ref root) = self.root {
            root.inorder_traversal(&mut result);
        }
        result
    }
    
    fn postorder_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        if let Some(ref root) = self.root {
            root.postorder_traversal(&mut result);
        }
        result
    }
    
    fn level_order_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        if let Some(ref root) = self.root {
            root.level_order_traversal(&mut result);
        }
        result
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

// 主函数 - 测试二叉树
fn main() {
    let mut tree = BinaryTree::new();
    
    println!("=== 二叉树测试 ===");
    
    // 插入测试数据
    let test_data = [50, 30, 70, 20, 40, 60, 80];
    println!("插入数据: {:?}", test_data);
    
    for &data in &test_data {
        tree.insert(data);
        println!("插入 {}", data);
    }
    
    println!();
    
    // 遍历测试
    println!("=== 遍历测试 ===");
    println!("前序遍历: {:?}", tree.preorder_traversal());
    println!("中序遍历: {:?}", tree.inorder_traversal());
    println!("后序遍历: {:?}", tree.postorder_traversal());
    println!("层次遍历: {:?}", tree.level_order_traversal());
    
    println!();
    
    // 搜索测试
    println!("=== 搜索测试 ===");
    let search_keys = [40, 90];
    for &key in &search_keys {
        let found = tree.search(key);
        println!("搜索 {}: {}", key, if found { "找到" } else { "未找到" });
    }
    
    println!();
    
    // 树属性测试
    println!("=== 树属性测试 ===");
    println!("树的高度: {}", tree.height());
    println!("节点数量: {}", tree.node_count());
    println!("最小值: {:?}", tree.find_min());
    println!("最大值: {:?}", tree.find_max());
}

/*打印结果
jarry@Mac binarytree % rustc binary_tree.rs && binary_tree
=== 二叉树测试 ===
插入数据: [50, 30, 70, 20, 40, 60, 80]
插入 50
插入 30
插入 70
插入 20
插入 40
插入 60
插入 80

=== 遍历测试 ===
前序遍历: [50, 30, 20, 40, 70, 60, 80]
中序遍历: [20, 30, 40, 50, 60, 70, 80]
后序遍历: [20, 40, 30, 60, 80, 70, 50]
层次遍历: [50, 30, 70, 20, 40, 60, 80]

=== 搜索测试 ===
搜索 40: 找到
搜索 90: 未找到

=== 树属性测试 ===
树的高度: 3
节点数量: 7
最小值: Some(20)
最大值: Some(80)
*/
