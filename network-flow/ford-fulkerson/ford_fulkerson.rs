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

const MAX_V: usize = 100;

fn dfs(r_graph: &mut Vec<Vec<i32>>, u: usize, t: usize, visited: &mut Vec<bool>, min_flow: i32) -> i32 {
    if u == t {
        return min_flow;
    }

    visited[u] = true;

    for v in 0..r_graph.len() {
        if !visited[v] && r_graph[u][v] > 0 {
            let flow = dfs(r_graph, v, t, visited, min_flow.min(r_graph[u][v]));

            if flow > 0 {
                r_graph[u][v] -= flow;
                r_graph[v][u] += flow;
                return flow;
            }
        }
    }

    0
}

fn ford_fulkerson(graph: &Vec<Vec<i32>>, s: usize, t: usize) -> i32 {
    let mut r_graph = graph.clone();
    let mut max_flow = 0;

    loop {
        let mut visited = vec![false; graph.len()];
        let path_flow = dfs(&mut r_graph, s, t, &mut visited, i32::MAX);

        if path_flow == 0 {
            break;
        }

        max_flow += path_flow;
    }

    max_flow
}

fn main() {
    println!("=== Ford-Fulkerson算法 ===");

    let v = 6;
    let mut graph = vec![vec![0; v]; v];

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

    let s = 0;
    let t = 5;
    let max_flow = ford_fulkerson(&graph, s, t);

    println!("最大流量: {}", max_flow);
}
