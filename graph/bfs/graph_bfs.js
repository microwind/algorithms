/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 图的广度优先搜索（BFS）算法实现
 * 使用队列数据结构，按层次遍历图
 * 
 * 时间复杂度: O(V + E)，其中V是顶点数，E是边数
 * 空间复杂度: O(V)，用于存储访问标记和队列
 */

const V = 5;

/**
 * 广度优先搜索遍历
 * @param {number[][]} graph 邻接矩阵表示的图
 * @param {number} start 起始顶点
 */
function bfs(graph, start) {
    // 使用队列存储待访问的顶点
    const queue = [];
    // 访问标记数组
    const visited = new Array(V).fill(false);
    
    // 将起始顶点入队并标记为已访问
    queue.push(start);
    visited[start] = true;
    
    console.log("BFS traversal:");
    
    // 当队列不为空时继续遍历
    while (queue.length > 0) {
        // 出队一个顶点
        const vertex = queue.shift();
        console.log("Visited " + vertex);
        
        // 遍历所有邻接顶点
        for (let i = 0; i < V; i++) {
            // 如果存在边且未被访问，则入队
            if (graph[vertex][i] === 1 && !visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
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
    
    bfs(graph, 0);
}

main();

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { bfs };
}
