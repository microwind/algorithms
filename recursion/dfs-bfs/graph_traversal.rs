/**
 * 图的深度优先搜索 (DFS) 和广度优先搜索 (BFS)
 * 使用递归实现DFS，使用队列实现BFS
 */
use std::collections::{HashMap, HashSet, VecDeque};

/**
 * 深度优先搜索 - 递归实现
 * 沿着一条路径尽可能深地搜索，直到无法继续才回溯
 */
fn dfs_recursive(graph: &HashMap<String, Vec<String>>, node: &str, visited: &mut HashSet<String>) {
    // 访问当前节点
    visited.insert(node.to_string());
    println!("DFS访问: {}", node);
    
    // 递归访问所有未访问的邻居
    if let Some(neighbors) = graph.get(node) {
        for neighbor in neighbors {
            if !visited.contains(neighbor) {
                dfs_recursive(graph, neighbor, visited);
            }
        }
    }
}

/**
 * 广度优先搜索 - 迭代实现（使用队列）
 * 逐层遍历，先访问所有邻居，再访问邻居的邻居
 */
fn bfs_iterative(graph: &HashMap<String, Vec<String>>, start: &str) -> HashSet<String> {
    let mut visited: HashSet<String> = HashSet::new();
    let mut queue: VecDeque<String> = VecDeque::new();
    
    visited.insert(start.to_string());
    queue.push_back(start.to_string());
    
    println!("\nBFS遍历:");
    while !queue.is_empty() {
        let node = queue.pop_front().unwrap();
        println!("BFS访问: {}", node);
        
        // 将所有未访问的邻居加入队列
        if let Some(neighbors) = graph.get(&node) {
            for neighbor in neighbors {
                if !visited.contains(neighbor) {
                    visited.insert(neighbor.clone());
                    queue.push_back(neighbor.clone());
                }
            }
        }
    }
    
    visited
}

fn main() {
    // 示例图（邻接表表示）
    let mut graph: HashMap<String, Vec<String>> = HashMap::new();
    
    graph.insert("A".to_string(), vec!["B".to_string(), "C".to_string()]);
    graph.insert("B".to_string(), vec!["A".to_string(), "D".to_string(), "E".to_string()]);
    graph.insert("C".to_string(), vec!["A".to_string(), "F".to_string()]);
    graph.insert("D".to_string(), vec!["B".to_string()]);
    graph.insert("E".to_string(), vec!["B".to_string(), "F".to_string()]);
    graph.insert("F".to_string(), vec!["C".to_string(), "E".to_string()]);
    
    println!("图结构:");
    println!("    A");
    println!("   / \\");
    println!("  B---C");
    println!("  |   |");
    println!("  D E--F");
    println!();
    
    println!("==============================");
    println!("DFS深度优先遍历:");
    
    // 初始化访问标记
    let mut visited: HashSet<String> = HashSet::new();
    dfs_recursive(&graph, "A", &mut visited);
    
    bfs_iterative(&graph, "A");
}
