/*
*
 * Edmonds-Karp算法 - 使用BFS的最大流算法
 *
 * 问题：在流网络中找到从源点到汇点的最大流量
 *
 * 核心思想：
 * - 使用BFS寻找最短增广路径
 * - 沿增广路径增加流量
 * - 更新残差网络
 *
 * 时间复杂度: O(VE²)
 * 空间复杂度: O(V + E)
*/

const MAX_V: usize = 100;

fn bfs(r_graph: &Vec<Vec<i32>>, s: usize, t: usize, parent: &mut Vec<i32>) -> bool {
    let mut visited = vec![false; r_graph.len()];
    let mut queue = std::collections::VecDeque::new();

    queue.push_back(s);
    visited[s] = true;
    parent[s] = -1;

    while let Some(u) = queue.pop_front() {
        for v in 0..r_graph.len() {
            if !visited[v] && r_graph[u][v] > 0 {
                queue.push_back(v);
                parent[v] = u as i32;
                visited[v] = true;

                if v == t {
                    return true;
                }
            }
        }
    }

    false
}

fn edmonds_karp(graph: &Vec<Vec<i32>>, s: usize, t: usize) -> i32 {
    let mut r_graph = graph.clone();
    let mut parent = vec![0; graph.len()];
    let mut max_flow = 0;

    while bfs(&r_graph, s, t, &mut parent) {
        let mut path_flow = i32::MAX;

        let mut v = t;
        while v != s {
            let u = parent[v] as usize;
            path_flow = path_flow.min(r_graph[u][v]);
            v = u;
        }

        let mut v = t;
        while v != s {
            let u = parent[v] as usize;
            r_graph[u][v] -= path_flow;
            r_graph[v][u] += path_flow;
            v = u;
        }

        max_flow += path_flow;
    }

    max_flow
}

fn main() {
    println!("=== Edmonds-Karp算法 ===");

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
    let max_flow = edmonds_karp(&graph, s, t);

    println!("最大流量: {}", max_flow);
}
