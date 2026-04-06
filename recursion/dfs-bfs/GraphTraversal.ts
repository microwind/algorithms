/**
 * 图的深度优先搜索 (DFS) 和广度优先搜索 (BFS)
 * 使用递归实现DFS，使用队列实现BFS
 */

/**
 * 深度优先搜索 - 递归实现
 * 沿着一条路径尽可能深地搜索，直到无法继续才回溯
 * @param graph 图的邻接表表示
 * @param node 当前节点
 * @param visited 已访问节点集合
 * @returns 已访问节点集合
 */
function dfsRecursive(graph: { [key: string]: string[] }, node: string, visited: Set<string> = new Set()): Set<string> {
    // 访问当前节点
    visited.add(node);
    console.log(`DFS访问: ${node}`);
    
    // 递归访问所有未访问的邻居
    for (const neighbor of graph[node] || []) {
        if (!visited.has(neighbor)) {
            dfsRecursive(graph, neighbor, visited);
        }
    }
    
    return visited;
}

/**
 * 广度优先搜索 - 迭代实现（使用队列）
 * 逐层遍历，先访问所有邻居，再访问邻居的邻居
 * @param graph 图的邻接表表示
 * @param start 起始节点
 * @returns 已访问节点集合
 */
function bfsIterative(graph: { [key: string]: string[] }, start: string): Set<string> {
    const visited: Set<string> = new Set([start]);
    const queue: string[] = [start];
    
    console.log("\nBFS遍历:");
    while (queue.length > 0) {
        const node = queue.shift()!;
        console.log(`BFS访问: ${node}`);
        
        // 将所有未访问的邻居加入队列
        for (const neighbor of graph[node] || []) {
            if (!visited.has(neighbor)) {
                visited.add(neighbor);
                queue.push(neighbor);
            }
        }
    }
    
    return visited;
}

// 示例图（邻接表表示）
const graph: { [key: string]: string[] } = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
};

console.log("图结构:");
console.log("    A");
console.log("   / \\");
console.log("  B---C");
console.log("  |   |");
console.log("  D E--F");
console.log();

console.log("==============================");
console.log("DFS深度优先遍历:");
dfsRecursive(graph, 'A');

bfsIterative(graph, 'A');
