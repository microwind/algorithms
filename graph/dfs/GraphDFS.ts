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

const V: number = 5;

/**
 * 深度优先搜索递归函数
 * @param graph 邻接矩阵表示的图
 * @param visited 访问标记数组
 * @param vertex 当前顶点
 */
function dfs(graph: number[][], visited: boolean[], vertex: number): void {
    console.log(`Visited ${vertex}`);
    visited[vertex] = true;

    for (let i = 0; i < V; i++) {
        if (graph[vertex][i] === 1 && !visited[i]) {
            dfs(graph, visited, i);
        }
    }
}

function main(): void {
    const graph: number[][] = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 1, 1],
        [0, 1, 0, 0, 1],
        [1, 1, 0, 0, 1],
        [0, 1, 1, 1, 0]
    ];
    const visited: boolean[] = new Array(V).fill(false);

    console.log("DFS traversal:");
    dfs(graph, visited, 0);
}

main();
export { dfs };
