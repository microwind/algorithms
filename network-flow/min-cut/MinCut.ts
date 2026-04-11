/*
*
 * 最小割算法 - 基于最大流
 *
 * 问题：找到容量最小的割，使源点和汇点不再连通
 *
 * 核心思想：
 * - 使用最大流算法计算最大流
 * - 在残差网络中从源点BFS标记可达顶点
 * - 从可达集到不可达集的边即为最小割
 *
 * 时间复杂度: O(VE²)
 * 空间复杂度: O(V + E)
*/

const MAX_V = 100;

let graph: number[][] = Array(MAX_V).fill(null).map(() => Array(MAX_V).fill(0));
let V: number = 0;

function bfs(rGraph: number[][], s: number, t: number, parent: number[]): boolean {
    let visited: boolean[] = Array(V).fill(false);
    let queue: number[] = [];

    queue.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (queue.length > 0) {
        let u = queue.shift()!;

        for (let v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue.push(v);
                parent[v] = u;
                visited[v] = true;

                if (v === t) {
                    return true;
                }
            }
        }
    }

    return false;
}

function maxFlow(rGraph: number[][], s: number, t: number): number {
    let parent: number[] = Array(V).fill(-1);
    let max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        let path_flow = Infinity;

        for (let v = t; v !== s; v = parent[v]) {
            let u = parent[v];
            path_flow = Math.min(path_flow, rGraph[u][v]);
        }

        for (let v = t; v !== s; v = parent[v]) {
            let u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

function minCut(s: number, t: number): void {
    let rGraph: number[][] = graph.map(row => [...row]);

    let max_flow = maxFlow(rGraph, s, t);
    console.log(`最大流量: ${max_flow}`);

    let visited: boolean[] = Array(V).fill(false);
    let queue: number[] = [];

    queue.push(s);
    visited[s] = true;

    while (queue.length > 0) {
        let u = queue.shift()!;

        for (let v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue.push(v);
                visited[v] = true;
            }
        }
    }

    console.log("最小割边:");
    for (let u = 0; u < V; u++) {
        for (let v = 0; v < V; v++) {
            if (visited[u] && !visited[v] && graph[u][v] > 0) {
                console.log(`  ${u} -> ${v} (容量: ${graph[u][v]})`);
            }
        }
    }
}

function main(): void {
    console.log("=== 最小割算法 ===");

    V = 6;

    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][2] = 9;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    let s = 0, t = 5;
    minCut(s, t);
}

// 运行测试
main();
