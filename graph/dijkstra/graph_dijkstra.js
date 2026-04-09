/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * Dijkstra最短路径算法实现
 * 使用贪心策略，适用于非负权重的图
 * 
 * 时间复杂度: O(V²)，使用优先队列可优化至O((V+E)logV)
 * 空间复杂度: O(V)，用于存储距离和访问标记
 */

const V = 6;
const INF = Number.MAX_SAFE_INTEGER;

/**
 * 找到距离最小的未处理顶点
 * @param {number[]} dist 距离数组
 * @param {boolean[]} visited 访问标记数组
 * @returns {number} 最小距离顶点的索引
 */
function minDistance(dist, visited) {
    let min = INF;
    let minIndex = -1;
    
    for (let v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

/**
 * Dijkstra算法实现
 * @param {number[][]} graph 邻接矩阵表示的图
 * @param {number} src 源顶点
 */
function dijkstra(graph, src) {
    const dist = new Array(V).fill(INF);    // 存储最短距离
    const visited = new Array(V).fill(false); // 访问标记
    
    dist[src] = 0;
    
    // 遍历所有顶点
    for (let count = 0; count < V - 1; count++) {
        // 选择距离最小的未处理顶点
        const u = minDistance(dist, visited);
        visited[u] = true;
        
        // 更新邻接顶点的距离
        for (let v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] !== 0 && 
                dist[u] !== INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    // 打印结果
    printSolution(dist);
}

function printSolution(dist) {
    console.log("Vertex \t Distance from Source");
    for (let i = 0; i < V; i++) {
        console.log(i + " \t " + dist[i]);
    }
}

function main() {
    const graph = [
        [0, 4, 0, 0, 0, 0],
        [4, 0, 8, 0, 0, 0],
        [0, 8, 0, 7, 0, 4],
        [0, 0, 7, 0, 9, 14],
        [0, 0, 0, 9, 0, 10],
        [0, 0, 4, 14, 10, 0]
    ];
    
    dijkstra(graph, 0);
}

main();

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { dijkstra, minDistance };
}
