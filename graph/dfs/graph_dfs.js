/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 图的深度优先搜索（DFS）算法实现
 * 使用递归方式遍历图
 * 
 * 时间复杂度: O(V + E)，其中V是顶点数，E是边数
 * 空间复杂度: O(V)，用于存储访问标记和递归栈
 */

const V = 5;

/**
 * 深度优先搜索递归函数
 * @param {number[][]} graph 邻接矩阵表示的图
 * @param {boolean[]} visited 访问标记数组
 * @param {number} vertex 当前顶点
 */
function dfs(graph, visited, vertex) {
    // 访问当前顶点
    console.log("Visited " + vertex);
    visited[vertex] = true;
    
    // 遍历所有邻接顶点
    for (let i = 0; i < V; i++) {
        // 如果存在边且未被访问，则递归访问
        if (graph[vertex][i] === 1 && !visited[i]) {
            dfs(graph, visited, i);
        }
    }
}

function main() {
    // 邻接矩阵表示的无向图
    const graph = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 1, 1],
        [0, 1, 0, 0, 1],
        [1, 1, 0, 0, 1],
        [0, 1, 1, 1, 0]
    ];
    
    const visited = new Array(V).fill(false);
    
    console.log("DFS traversal:");
    dfs(graph, visited, 0);
}

main();

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { dfs };
}
