// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// 图的深度优先搜索（DFS）算法实现
/// 使用递归方式遍历图
///
/// 时间复杂度: O(V + E)，其中V是顶点数，E是边数
/// 空间复杂度: O(V)，用于存储访问标记和递归栈

const V: usize = 5;

/// 深度优先搜索递归函数
pub fn dfs(graph: &[[i32; V]; V], visited: &mut [bool], vertex: usize) {
    println!("Visited {}", vertex);
    visited[vertex] = true;

    for i in 0..V {
        if graph[vertex][i] == 1 && !visited[i] {
            dfs(graph, visited, i);
        }
    }
}

pub fn test_dfs() {
    let graph = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 1, 1],
        [0, 1, 0, 0, 1],
        [1, 1, 0, 0, 1],
        [0, 1, 1, 1, 0],
    ];
    let mut visited = [false; V];

    println!("DFS traversal:");
    dfs(&graph, &mut visited, 0);
}
