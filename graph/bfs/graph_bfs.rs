// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// 图的广度优先搜索（BFS）算法实现
/// 使用队列数据结构，按层次遍历图
///
/// 时间复杂度: O(V + E)，其中V是顶点数，E是边数
/// 空间复杂度: O(V)，用于存储访问标记和队列

const V: usize = 5;

/// 广度优先搜索遍历
pub fn bfs(graph: &[[i32; V]; V], start: usize) {
    let mut queue = Vec::new();
    let mut visited = [false; V];

    queue.push(start);
    visited[start] = true;

    println!("BFS traversal:");

    while !queue.is_empty() {
        let vertex = queue.remove(0);
        println!("Visited {}", vertex);

        for i in 0..V {
            if graph[vertex][i] == 1 && !visited[i] {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
}

pub fn test_bfs() {
    let graph = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 1, 1],
        [0, 1, 0, 0, 1],
        [1, 1, 0, 0, 1],
        [0, 1, 1, 1, 0],
    ];

    bfs(&graph, 0);
}
