// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// 拓扑排序 (Topological Sort)
/// 使用Kahn算法（基于BFS）对有向无环图进行拓扑排序

use std::collections::HashMap;
use std::collections::VecDeque;

/// Kahn算法实现拓扑排序
pub fn topological_sort(graph: &HashMap<usize, Vec<usize>>, num_vertices: usize) -> Vec<usize> {
    let mut in_degree = vec![0; num_vertices];
    
    // 计算每个顶点的入度
    for neighbors in graph.values() {
        for &v in neighbors {
            in_degree[v] += 1;
        }
    }
    
    // 将所有入度为0的顶点加入队列
    let mut queue = VecDeque::new();
    for i in 0..num_vertices {
        if in_degree[i] == 0 {
            queue.push_back(i);
        }
    }
    
    let mut result = Vec::new();
    
    while let Some(u) = queue.pop_front() {
        result.push(u);
        
        // 将u的所有邻居的入度减1
        if let Some(neighbors) = graph.get(&u) {
            for &v in neighbors {
                in_degree[v] -= 1;
                if in_degree[v] == 0 {
                    queue.push_back(v);
                }
            }
        }
    }
    
    // 检查是否存在环
    if result.len() != num_vertices {
        return Vec::new(); // 存在环
    }
    
    result
}

fn main() {
    let mut graph = HashMap::new();
    graph.insert(0, vec![1]);
    graph.insert(1, vec![2, 3]);
    graph.insert(2, vec![3]);
    graph.insert(3, vec![]);
    
    let num_vertices = 4;
    
    println!("==================================================");
    println!("拓扑排序 (Topological Sort)");
    println!("==================================================");
    
    let result = topological_sort(&graph, num_vertices);
    
    if !result.is_empty() {
        println!("\n拓扑排序结果: {:?}", result);
    } else {
        println!("\n图中存在环，无法进行拓扑排序");
    }
}
