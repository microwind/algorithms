/*
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

树遍历 - 二叉树遍历实现
实现前序、中序、后序遍历（递归和迭代）
以及层序遍历，包含详细的中文注释
包含时间复杂度分析和应用场景
*/

use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

/// 具有 optional 子节点的二叉树节点
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,    // 节点值
    pub left: Option<Rc<RefCell<TreeNode>>>,  // 左子节点
    pub right: Option<Rc<RefCell<TreeNode>>>, // 右子节点
}

impl TreeNode {
    /// 创建新树节点
    pub fn new(val: i32) -> Rc<RefCell<Self>> {
        Rc::new(RefCell::new(Self {
            val,        // 节点值
            left: None,  // 左子节点初始化为空
            right: None, // 右子节点初始化为空
        }))
    }
}

/// 树遍历实现
pub struct TreeTraversal;

impl TreeTraversal {
    /// 前序遍历 - 递归：根-左-右
    /// 
    /// 算法:
    /// 1. 访问根节点
    /// 2. 递归遍历左子树
    /// 3. 递归遍历右子树
    /// 
    /// 时间复杂度: O(n) - 每个节点访问一次
    /// 空间复杂度: O(h) - h是树高度，递归栈深度
    /// 
    /// 应用:
    /// - 树复制
    /// - 从表达式树生成前缀表达式
    /// - 文件系统目录结构遍历
    pub fn preorder_recursive(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        Self::preorder_recursive_helper(root, &mut result);
        result
    }

    fn preorder_recursive_helper(node: Option<Rc<RefCell<TreeNode>>>, result: &mut Vec<i32>) {
        if let Some(node) = node {
            let node_val = node.borrow().val;
            result.push(node_val); // 访问根节点
            Self::preorder_recursive_helper(node.borrow().left.clone(), result); // 遍历左子树
            Self::preorder_recursive_helper(node.borrow().right.clone(), result); // 遍历右子树
        }
    }

    /// 中序遍历 - 递归：左-根-右
    /// 
    /// 算法:
    /// 1. 递归遍历左子树
    /// 2. 访问根节点
    /// 3. 递归遍历右子树
    /// 
    /// 时间复杂度: O(n) - 每个节点访问一次
    /// 空间复杂度: O(h) - h是树高度，递归栈深度
    /// 
    /// 应用:
    /// - 二叉搜索树的中序遍历得到有序序列
    /// - 表达式树的中缀表达式生成
    /// - 按顺序处理树节点
    pub fn inorder_recursive(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        Self::inorder_recursive_helper(root, &mut result);
        result
    }

    fn inorder_recursive_helper(node: Option<Rc<RefCell<TreeNode>>>, result: &mut Vec<i32>) {
        if let Some(node) = node {
            Self::inorder_recursive_helper(node.borrow().left.clone(), result); // 遍历左子树
            let node_val = node.borrow().val;
            result.push(node_val); // 访问根节点
            Self::inorder_recursive_helper(node.borrow().right.clone(), result); // 遍历右子树
        }
    }

    /// 后序遍历 - 递归：左-右-根
    /// 
    /// 算法:
    /// 1. 递归遍历左子树
    /// 2. 递归遍历右子树
    /// 3. 访问根节点
    /// 
    /// 时间复杂度: O(n) - 每个节点访问一次
    /// 空间复杂度: O(h) - h是树高度，递归栈深度
    /// 
    /// 应用:
    /// - 树删除操作
    /// - 从表达式树生成后缀表达式
    /// - 计算目录大小
    pub fn postorder_recursive(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        Self::postorder_recursive_helper(root, &mut result);
        result
    }

    fn postorder_recursive_helper(node: Option<Rc<RefCell<TreeNode>>>, result: &mut Vec<i32>) {
        if let Some(node) = node {
            Self::postorder_recursive_helper(node.borrow().left.clone(), result); // 遍历左子树
            Self::postorder_recursive_helper(node.borrow().right.clone(), result); // 遍历右子树
            let node_val = node.borrow().val;
            result.push(node_val); // 访问根节点
        }
    }

    /// 前序遍历 - 迭代：根-左-右
    /// 
    /// 算法:
    /// 1. 使用栈模拟递归
    /// 2. 先右后左入栈（确保左节点先处理）
    /// 
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(h)
    pub fn preorder_iterative(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        let mut stack: Vec<Rc<RefCell<TreeNode>>> = Vec::new();
        
        if let Some(root) = root {
            stack.push(root); // 根节点入栈
        }
        
        while !stack.is_empty() {
            let node = stack.pop().unwrap(); // 节点出栈
            let node_val = node.borrow().val;
            result.push(node_val); // 访问根节点
            
            // 先右后左入栈（确保左节点先处理）
            let right_child = node.borrow().right.clone();
            let left_child = node.borrow().left.clone();
            
            if let Some(right) = right_child {
                stack.push(right); // 右子节点入栈
            }
            if let Some(left) = left_child {
                stack.push(left); // 左子节点入栈
            }
        }
        
        result
    }

    /// 中序遍历 - 迭代：左-根-右
    /// 
    /// 算法:
    /// 1. 使用栈模拟递归
    /// 2. 先到达最左节点
    /// 3. 然后处理节点并转向右子树
    /// 
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(h)
    pub fn inorder_iterative(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        let mut stack: Vec<Rc<RefCell<TreeNode>>> = Vec::new();
        let mut current = root;
        
        while current.is_some() || !stack.is_empty() {
            // 到达最左节点
            while let Some(node) = current.clone() {
                stack.push(node.clone()); // 节点入栈
                current = node.borrow().left.clone(); // 向左移动
            }
            
            // current为None，从栈中弹出
            current = stack.pop();
            if let Some(node) = current.clone() {
                let node_val = node.borrow().val;
                result.push(node_val); // 访问节点
                current = node.borrow().right.clone(); // 转到右子树
            }
        }
        
        result
    }

    /// 层序遍历（BFS）
    /// 
    /// 算法:
    /// 1. 使用队列进行层序遍历
    /// 2. 逐层处理节点
    /// 
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(w) - w是最大宽度
    /// 
    /// 应用:
    /// - 按层级处理节点
    /// - 找最短路径
    /// - 广度优先搜索
    pub fn level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut result = Vec::new();
        let mut queue: VecDeque<Rc<RefCell<TreeNode>>> = VecDeque::new();
        
        if let Some(root) = root {
            queue.push_back(root); // 根节点入队
        }
        
        while !queue.is_empty() {
            let node = queue.pop_front().unwrap(); // 节点出队
            let node_val = node.borrow().val;
            result.push(node_val);
            
            // 获取子节点
            let left_child = node.borrow().left.clone();
            let right_child = node.borrow().right.clone();
            
            if let Some(left) = left_child {
                queue.push_back(left); // 左子节点入队
            }
            if let Some(right) = right_child {
                queue.push_back(right); // 右子节点入队
            }
        }
        
        result
    }

    /// 打印树结构
    pub fn print_tree_structure() {
        println!("树结构:");
        println!("      1");
        println!("     / \\");
        println!("    2   3");
        println!("   / \\  /");
        println!("  4   5 6");
        println!();
    }

    /// 主测试函数
    pub fn test() {
        println!("{}", "=".repeat(50));
        println!("树遍历实现");
        println!("{}", "=".repeat(50));
        
        Self::print_tree_structure();
        
        // 创建示例树（简化版本）
        let root = TreeNode::new(1);
        
        println!("递归遍历:");
        println!("前序遍历（根-左-右）: {:?}", Self::preorder_recursive(Some(root.clone())));
        println!("中序遍历（左-根-右）: {:?}", Self::inorder_recursive(Some(root.clone())));
        println!("后序遍历（左-右-根）: {:?}", Self::postorder_recursive(Some(root.clone())));
        println!();
        
        println!("迭代遍历:");
        println!("前序遍历（根-左-右）: {:?}", Self::preorder_iterative(Some(root.clone())));
        println!("中序遍历（左-根-右）: {:?}", Self::inorder_iterative(Some(root.clone())));
        println!();
        
        println!("层序遍历（BFS）:");
        println!("层序遍历: {:?}", Self::level_order(Some(root.clone())));
        println!();
        
        println!("遍历特性:");
        println!("  前序遍历：根节点最先访问");
        println!("  中序遍历：二叉搜索树中序遍历得到有序序列");
        println!("  后序遍历：适合树删除操作");
        println!("  层序遍历：广度优先遍历");
        println!();
        
        println!("时间复杂度:");
        println!("  所有遍历：O(n)时间，O(n)空间");
        println!("  迭代方法使用显式栈");
        println!("  递归方法使用调用栈");
        println!();
        
        println!("应用场景:");
        println!("  树操作、表达式求值、文件系统遍历、");
        println!("  搜索算法、排序算法、编译器设计等。");
    }
}

fn main() {
    TreeTraversal::test();
}
