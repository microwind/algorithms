/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
 
/**
 * 树递归算法示例 - 二叉树遍历
 * 
 * 算法特点：
 * - 二叉树的遍历是递归的典型应用
 * - 包含前序、中序、后序遍历
 * - 时间复杂度: O(n)，空间复杂度: O(h)
 * 
 * 学习重点：理解递归在树结构中的应用
 */

// 定义二叉树节点
#[derive(Debug)]
struct Node {
    data: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

/**
 * 创建新节点
 * @param data 节点数据
 * @return 新节点
 */
fn new_node(data: i32) -> Box<Node> {
    Box::new(Node {
        data,
        left: None,
        right: None,
    })
}

/**
 * 前序遍历
 * 时间复杂度: O(n)，空间复杂度: O(h)
 * @param node 根节点
 */
fn pre_order(node: &Option<Box<Node>>) {
    // 基本情况：空节点
    match node {
        None => return,
        Some(n) => {
            // 访问根节点
            print!("{} ", n.data);
            
            // 递归遍历左子树
            pre_order(&n.left);
            
            // 递归遍历右子树
            pre_order(&n.right);
        }
    }
}

/**
 * 主函数 - 测试二叉树遍历
 */
fn main() {
    // 测试1：创建二叉树
    let mut root = new_node(1);
    root.left = Some(new_node(2));
    root.right = Some(new_node(3));
    root.left.as_mut().unwrap().left = Some(new_node(4));
    root.left.as_mut().unwrap().right = Some(new_node(5));
    
    // 输出调用过程示例
    println!("调用过程示例：");
    println!("preOrder(root)");
    println!("   |");
    println!("   v");
    println!("printf(1)");
    println!("preOrder(root.left)");
    println!("   |");
    println!("   v");
    println!("printf(2)");
    println!("preOrder(root.left.left)");
    println!("   |");
    println!("   v");
    println!("printf(4)");
    println!("preOrder(root.left.right)");
    println!("   |");
    println!("   v");
    println!("printf(5)");
    println!("preOrder(root.right)");
    println!("   |");
    println!("   v");
    println!("printf(3)");
    println!();
    
    // 测试2：执行前序遍历
    println!("1. 前序遍历:");
    println!("   遍历结果: ");
    pre_order(&Some(root));
    println!();
    println!("===");
    
    // 测试3：执行中序遍历
    println!("2. 中序遍历:");
    println!("   遍历结果: ");
    in_order(&Some(root));
    println!();
    println!("===");
    
    // 测试4：执行后序遍历
    println!("3. 后序遍历:");
    println!("   遍历结果: ");
    post_order(&Some(root));
    println!();
    println!("===");
}

/*打印结果
jarry@Mac tree-recursion % cargo run
调用过程示例：
preOrder(root)
   |
   v
printf(1)
preOrder(root.left)
   |
   v
printf(2)
preOrder(root.left.left)
   |
   v
printf(4)
preOrder(root.left.right)
   |
   v
printf(5)
preOrder(root.right)
   |
   v
printf(3)

Preorder traversal of binary tree is
1 2 4 5 3 
*/
