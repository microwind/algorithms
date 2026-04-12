/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树数据结构 - Rust实现
 */

use std::rc::Rc;
use std::cell::RefCell;

// 树节点结构体
type TreeNodeRef = Rc<RefCell<TreeNode>>;

#[derive(Clone)]
struct TreeNode {
    left: Option<TreeNodeRef>,
    right: Option<TreeNodeRef>,
    parent: Option<TreeNodeRef>,
    next: Option<TreeNodeRef>,
    value: i32,
}

impl TreeNode {
    fn new(value: i32) -> TreeNodeRef {
        Rc::new(RefCell::new(TreeNode {
            left: None,
            right: None,
            parent: None,
            next: None,
            value,
        }))
    }
}

// 按 idx 作为根节点的"占位"值，buildHeight 为层数构造满二叉树，并设置 parent 指针
fn build_full_tree(idx: i32, height: i32) -> Option<TreeNodeRef> {
    if height <= 0 {
        return None;
    }
    let node = TreeNode::new(idx);
    if let Some(left) = build_full_tree(idx * 2, height - 1) {
        left.borrow_mut().parent = Some(node.clone());
        node.borrow_mut().left = Some(left);
    }
    if let Some(right) = build_full_tree(idx * 2 + 1, height - 1) {
        right.borrow_mut().parent = Some(node.clone());
        node.borrow_mut().right = Some(right);
    }
    Some(node)
}

// 先序遍历（根→左→右）
fn print_pre_order(node: &Option<TreeNodeRef>) {
    if let Some(n) = node {
        println!("value: {}", n.borrow().value);
        print_pre_order(&n.borrow().left);
        print_pre_order(&n.borrow().right);
    }
}

// 广度优先遍历（BFS）打印
fn print_bfs(root: &Option<TreeNodeRef>) {
    if let Some(r) = root {
        let mut queue = vec![r.clone()];
        let mut i = 0;
        while i < queue.len() {
            let n = queue[i].clone();
            print!("{} ", n.borrow().value);
            if let Some(ref left) = n.borrow().left {
                queue.push(left.clone());
            }
            if let Some(ref right) = n.borrow().right {
                queue.push(right.clone());
            }
            i += 1;
        }
        println!();
    }
}

// 找到当前节点所在树的根
fn find_root(node: &TreeNodeRef) -> TreeNodeRef {
    let mut current = node.clone();
    loop {
        let borrowed = current.borrow();
        if let Some(ref parent) = borrowed.parent {
            let parent = parent.clone();
            drop(borrowed);
            current = parent;
        } else {
            return current;
        }
    }
}

// 无额外空间遍历单棵树（含 parent 指针），中序风格打印
fn traverse_tree(root: &TreeNodeRef) {
    let mut prev: Option<TreeNodeRef> = None;
    let mut current: Option<TreeNodeRef> = Some(root.clone());
    
    while let Some(ref curr) = current {
        let borrowed = curr.borrow();
        let next = if let Some(ref prev_node) = prev {
            if let Some(ref parent) = borrowed.parent {
                if Rc::ptr_eq(prev_node, parent) {
                    // 从 parent 下来：优先下探左子
                    if let Some(ref left) = borrowed.left {
                        drop(borrowed);
                        Some(left.clone())
                    } else {
                        // 否则中序访问自己
                        print!("{} ", borrowed.value);
                        drop(borrowed);
                        borrowed.right.clone().or_else(|| borrowed.parent.clone())
                    }
                } else if let Some(ref left) = borrowed.left {
                    if Rc::ptr_eq(prev_node, left) {
                        // 从左子回到 current：中序访问自己
                        print!("{} ", borrowed.value);
                        drop(borrowed);
                        borrowed.right.clone().or_else(|| borrowed.parent.clone())
                    } else {
                        // 从右子回到 current：回父节点
                        drop(borrowed);
                        borrowed.parent.clone()
                    }
                } else {
                    drop(borrowed);
                    borrowed.parent.clone()
                }
            } else {
                drop(borrowed);
                borrowed.parent.clone()
            }
        } else {
            // prev is None, 从 parent 下来
            if let Some(ref left) = borrowed.left {
                drop(borrowed);
                Some(left.clone())
            } else {
                print!("{} ", borrowed.value);
                drop(borrowed);
                borrowed.right.clone().or_else(|| borrowed.parent.clone())
            }
        };
        prev = current.clone();
        current = next;
    }
}

// 从任意节点开始遍历串联在一起的多棵树
fn traverse_from_any_node(any: &TreeNodeRef) {
    let mut root = find_root(any);
    loop {
        traverse_tree(&root);
        let borrowed = root.borrow();
        if let Some(ref next) = borrowed.next {
            let next = next.clone();
            drop(borrowed);
            root = next;
        } else {
            break;
        }
    }
    println!();
}

// 对单棵树按层序（BFS）重新赋连续值
fn assign_level_order_values(root: &TreeNodeRef, start_val: i32) -> i32 {
    let mut queue = vec![root.clone()];
    let mut val = start_val;
    
    while !queue.is_empty() {
        let n = queue.remove(0);
        n.borrow_mut().value = val;
        val += 1;
        if let Some(ref left) = n.borrow().left {
            queue.push(left.clone());
        }
        if let Some(ref right) = n.borrow().right {
            queue.push(right.clone());
        }
    }
    val
}

fn main() {
    let height = 4;

    // 1) 构造形状（value暂时无意义）
    let t1 = build_full_tree(1, height).unwrap();
    let t2 = build_full_tree(1, height).unwrap();
    let t3 = build_full_tree(1, height).unwrap();

    // 2) 按层序给每棵树分别连续编号：T1 → 1..15, T2 → 16..30, T3 → 31..45
    let mut next_id = assign_level_order_values(&t1, 1);
    next_id = assign_level_order_values(&t2, next_id);
    assign_level_order_values(&t3, next_id);

    // 3) 串联根：T1 → T2 → T3
    t1.borrow_mut().next = Some(t2.clone());
    t2.borrow_mut().next = Some(t3.clone());
    t3.borrow_mut().next = None;

    println!("=== 先序遍历 T1 ===");
    print_pre_order(&Some(t1.clone()));

    println!("\n=== 广度优先遍历 T1 ===");
    print_bfs(&Some(t1.clone()));

    // 4) 从任意节点遍历
    println!("\n=== 从任意节点遍历 ===");
    traverse_from_any_node(&t3.borrow().left.as_ref().unwrap());

    // 5) 从 T2 的某个子节点开始，无额外空间遍历整片"森林"
    let any = t2.borrow().left.as_ref().unwrap().borrow().left.as_ref().unwrap().clone();
    println!("\n=== 从节点 {} 开始无栈遍历 ===", any.borrow().value);
    traverse_from_any_node(&any);
}
