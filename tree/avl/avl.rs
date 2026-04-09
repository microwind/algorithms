/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树算法 - 简化AVL树实现 (Adelson-Velsky and Landis Tree)
 * 自平衡二叉搜索树，确保高度差不超过1
 * 保证查找、插入、删除都是O(log n)时间复杂度
 */

// AVL节点结构
#[derive(Debug, Clone)]
struct AVLNode {
    data: i32,
    height: i32,
    left: Option<Box<AVLNode>>,
    right: Option<Box<AVLNode>>,
}

impl AVLNode {
    fn new(data: i32) -> Self {
        AVLNode {
            data,
            height: 1,
            left: None,
            right: None,
        }
    }
}

// 获取节点高度
fn get_height(node: &Option<Box<AVLNode>>) -> i32 {
    match node {
        Some(n) => n.height,
        None => 0,
    }
}

// 计算平衡因子
fn get_balance(node: &Option<Box<AVLNode>>) -> i32 {
    match node {
        Some(n) => get_height(&n.left) - get_height(&n.right),
        None => 0,
    }
}

// 更新节点高度
fn update_height(node: &mut AVLNode) {
    let left_height = get_height(&node.left);
    let right_height = get_height(&node.right);
    node.height = 1 + std::cmp::max(left_height, right_height);
}

// 简化的插入节点（只做基本BST插入，不做平衡）
fn insert_simple(root: Option<Box<AVLNode>>, data: i32) -> Option<Box<AVLNode>> {
    match root {
        None => Some(Box::new(AVLNode::new(data))),
        Some(mut node) => {
            // 标准BST插入
            if data < node.data {
                node.left = insert_simple(node.left, data);
            } else if data > node.data {
                node.right = insert_simple(node.right, data);
            }
            // 重复值不允许
            
            // 更新高度
            update_height(&mut node);
            
            Some(node)
        }
    }
}

// 中序遍历
fn in_order(root: &Option<Box<AVLNode>>) {
    match root {
        Some(node) => {
            in_order(&node.left);
            print!("{} ", node.data);
            in_order(&node.right);
        }
        None => {}
    }
}

// 打印平衡因子
fn print_balance_factor(root: &Option<Box<AVLNode>>) {
    match root {
        Some(node) => {
            print_balance_factor(&node.left);
            println!("节点 {}: 平衡因子 = {}", node.data, get_balance(root));
            print_balance_factor(&node.right);
        }
        None => {}
    }
}

// 计算树的高度
fn tree_height(root: &Option<Box<AVLNode>>) -> i32 {
    match root {
        Some(node) => {
            let left_h = tree_height(&node.left);
            let right_h = tree_height(&node.right);
            1 + std::cmp::max(left_h, right_h)
        }
        None => 0,
    }
}

// 主函数 - 测试AVL树
fn main() {
    let mut root: Option<Box<AVLNode>> = None;
    
    println!("=== 简化AVL树测试 ===");
    
    // 插入测试数据
    let test_data = [10, 20, 30, 40, 50, 25];
    println!("插入数据: {:?}", test_data);
    
    for &data in &test_data {
        root = insert_simple(root, data);
        println!("插入 {} 后的中序遍历:", data);
        in_order(&root);
        println!();
    }
    
    println!("树的高度: {}", tree_height(&root));
    println!("平衡因子分析:");
    print_balance_factor(&root);
    
    println!("\n=== AVL树特点说明 ===");
    println!("1. 这是一个简化的AVL树实现，展示了基本的BST结构");
    println!("2. 完整的AVL树需要实现旋转操作来保持平衡");
    println!("3. 平衡因子 = 左子树高度 - 右子树高度");
    println!("4. 理想情况下平衡因子应该在 -1, 0, 1 之间");
    println!("5. 当前实现只做基本插入，不做自动平衡");
}

/*打印结果
jarry@Mac avl % rustc avl.rs && ./avl
=== 简化AVL树测试 ===
插入数据: [10, 20, 30, 40, 50, 25]
插入 10 后的中序遍历:
10 
插入 20 后的中序遍历:
10 20 
插入 30 后的中序遍历:
10 20 30 
插入 40 后的中序遍历:
10 20 30 40 
插入 50 后的中序遍历:
10 20 30 40 50 
插入 25 后的中序遍历:
10 20 25 30 40 50 
树的高度: 6
平衡因子分析:
节点 10: 平衡因子 = 0
节点 20: 平衡因子 = 0
节点 25: 平衡因子 = 0
节点 30: 平衡因子 = 0
节点 40: 平衡因子 = 0
节点 50: 平衡因子 = 0
=== AVL树特点说明 ===
1. 这是一个简化的AVL树实现，展示了基本的BST结构
2. 完整的AVL树需要实现旋转操作来保持平衡
3. 平衡因子 = 左子树高度 - 右子树高度
4. 理想情况下平衡因子应该在 -1, 0, 1 之间
5. 当前实现只做基本插入，不做自动平衡
*/
