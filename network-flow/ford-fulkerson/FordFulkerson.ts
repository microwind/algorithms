/*
*
 * Ford-Fulkerson算法 - 使用DFS的最大流算法
 *
 * 问题：在流网络中找到从源点到汇点的最大流量
 *
 * 核心思想：
 * - 使用DFS寻找增广路径
 * - 沿增广路径增加流量
 * - 更新残差网络
 *
 * 时间复杂度: O(E * max_flow)
 * 空间复杂度: O(V + E)
*/

const MAX_V = 100;

let graph: number[][] = Array(MAX_V).fill(null).map(() => Array(MAX_V).fill(0));
let V: number = 0;

function dfs(rGraph: number[][], u: number, t: number, visited: boolean[], min_flow: number): number {
    if (u === t) {
        return min_flow;
    }

    visited[u] = true;

    for (let v = 0; v < V; v++) {
        if (!visited[v] && rGraph[u][v] > 0) {
            let flow = dfs(rGraph, v, t, visited, Math.min(min_flow, rGraph[u][v]));

            if (flow > 0) {
                rGraph[u][v] -= flow;
                rGraph[v][u] += flow;
                return flow;
            }
        }
    }

    return 0;
}

function fordFulkerson(s: number, t: number): number {
    let rGraph: number[][] = graph.map(row => [...row]);
    let max_flow = 0;

    while (true) {
        let visited: boolean[] = Array(V).fill(false);
        let path_flow = dfs(rGraph, s, t, visited, Infinity);

        if (path_flow === 0) {
            break;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

function main(): void {
    console.log("=== Ford-Fulkerson算法 ===");

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
    let max_flow = fordFulkerson(s, t);

    console.log(`最大流量: ${max_flow}`);
}

// 运行测试
main();
