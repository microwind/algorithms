/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 拓扑排序 (Topological Sort)
 * 使用Kahn算法（基于BFS）对有向无环图进行拓扑排序
 */

/**
 * Kahn算法实现拓扑排序
 * @param graph 邻接表表示的有向图
 * @param numVertices 顶点数量
 * @returns 拓扑排序结果列表，如果存在环则返回空列表
 */
function topologicalSort(graph: Map<number, number[]>, numVertices: number): number[] {
    const inDegree: number[] = new Array(numVertices).fill(0);
    
    // 计算每个顶点的入度
    for (const neighbors of graph.values()) {
        for (const v of neighbors) {
            inDegree[v]++;
        }
    }
    
    // 将所有入度为0的顶点加入队列
    const queue: number[] = [];
    for (let i = 0; i < numVertices; i++) {
        if (inDegree[i] === 0) {
            queue.push(i);
        }
    }
    
    const result: number[] = [];
    
    while (queue.length > 0) {
        const u = queue.shift()!;
        result.push(u);
        
        // 将u的所有邻居的入度减1
        const neighbors = graph.get(u) || [];
        for (const v of neighbors) {
            inDegree[v]--;
            if (inDegree[v] === 0) {
                queue.push(v);
            }
        }
    }
    
    // 检查是否存在环
    if (result.length !== numVertices) {
        return []; // 存在环
    }
    
    return result;
}

function main(): void {
    const graph = new Map<number, number[]>();
    graph.set(0, [1]);
    graph.set(1, [2, 3]);
    graph.set(2, [3]);
    graph.set(3, []);
    
    const numVertices = 4;
    
    console.log("=".repeat(50));
    console.log("拓扑排序 (Topological Sort)");
    console.log("=".repeat(50));
    
    const result = topologicalSort(graph, numVertices);
    
    if (result.length > 0) {
        console.log("\n拓扑排序结果: " + result);
    } else {
        console.log("\n图中存在环，无法进行拓扑排序");
    }
}

main();
export { topologicalSort };
