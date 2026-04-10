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

const V: number = 5;

/**
 * 广度优先搜索遍历
 * @param graph 邻接矩阵表示的图
 * @param start 起始顶点
 */
function bfs(graph: number[][], start: number): void {
    const queue: number[] = [];
    const visited: boolean[] = new Array(V).fill(false);

    queue.push(start);
    visited[start] = true;

    console.log("BFS traversal:");

    while (queue.length > 0) {
        const vertex = queue.shift()!;
        console.log(`Visited ${vertex}`);

        for (let i = 0; i < V; i++) {
            if (graph[vertex][i] === 1 && !visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
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

    bfs(graph, 0);
}

main();
export { bfs };

/*打印结果
jarry@Mac bfs % ts-node GraphBFS.ts
BFS traversal:
Visited 0
Visited 1
Visited 3
Visited 2
Visited 4
*/