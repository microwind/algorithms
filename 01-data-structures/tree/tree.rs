// 定义树的节点结构
#[derive(Debug)]
struct Node {
    value: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

// 创建新节点
fn create_node(value: i32) -> Option<Box<Node>> {
    Some(Box::new(Node {
        value,
        left: None,
        right: None,
    }))
}

// 前序遍历：根 -> 左 -> 右
fn preorder_traversal(root: &Option<Box<Node>>) {
    if let Some(node) = root {
        print!("{} ", node.value);
        preorder_traversal(&node.left);
        preorder_traversal(&node.right);
    }
}

// 中序遍历：左 -> 根 -> 右
fn inorder_traversal(root: &Option<Box<Node>>) {
    if let Some(node) = root {
        inorder_traversal(&node.left);
        print!("{} ", node.value);
        inorder_traversal(&node.right);
    }
}

// 后序遍历：左 -> 右 -> 根
fn postorder_traversal(root: &Option<Box<Node>>) {
    if let Some(node) = root {
        postorder_traversal(&node.left);
        postorder_traversal(&node.right);
        print!("{} ", node.value);
    }
}

fn main() {
    // 创建树
    /*
          1
         / \
        2   3
       / \   /
      4   5 6
    */
    let mut root = create_node(1).unwrap();
    root.left = create_node(2);
    root.right = create_node(3);
    if let Some(left_node) = &mut root.left {
        left_node.left = create_node(4);
        left_node.right = create_node(5);
    }
    if let Some(right_node) = &mut root.right {
        right_node.left = create_node(6);
    }

    // 输出树的遍历结果
    println!("前序遍历：");
    preorder_traversal(&Some(root));
    println!();

    // 重新构建树，因为上面 preorder_traversal 转移了 root 的所有权
    let mut root = create_node(1).unwrap();
    root.left = create_node(2);
    root.right = create_node(3);
    if let Some(left_node) = &mut root.left {
        left_node.left = create_node(4);
        left_node.right = create_node(5);
    }
    if let Some(right_node) = &mut root.right {
        right_node.left = create_node(6);
    }
    println!("中序遍历：");
    inorder_traversal(&Some(root));
    println!();

    // 再次重新构建树
    let mut root = create_node(1).unwrap();
    root.left = create_node(2);
    root.right = create_node(3);
    if let Some(left_node) = &mut root.left {
        left_node.left = create_node(4);
        left_node.right = create_node(5);
    }
    if let Some(right_node) = &mut root.right {
        right_node.left = create_node(6);
    }
    println!("后序遍历：");
    postorder_traversal(&Some(root));
    println!();
}

/*
jarry@MacBook-Pro tree % rustc tree.rs
jarry@MacBook-Pro tree % ./tree 
前序遍历：
1 2 4 5 3 6 
中序遍历：
4 2 5 1 6 3 
后序遍历：
4 5 2 6 3 1 
*/