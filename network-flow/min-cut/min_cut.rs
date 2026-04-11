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

fn max_flow(r_graph: &mut Vec<Vec<i32>>, s: usize, t: usize) -> i32 {
    let mut parent = vec![0; r_graph.len()];
    let mut max_flow = 0;

    while bfs(r_graph, s, t, &mut parent) {
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

fn min_cut(graph: &Vec<Vec<i32>>, s: usize, t: usize) {
    let mut r_graph = graph.clone();

    let max_flow = max_flow(&mut r_graph, s, t);
    println!("最大流量: {}", max_flow);

    let mut visited = vec![false; graph.len()];
    let mut queue = std::collections::VecDeque::new();

    queue.push_back(s);
    visited[s] = true;

    while let Some(u) = queue.pop_front() {
        for v in 0..graph.len() {
            if !visited[v] && r_graph[u][v] > 0 {
                queue.push_back(v);
                visited[v] = true;
            }
        }
    }

    println!("最小割边:");
    for u in 0..graph.len() {
        for v in 0..graph.len() {
            if visited[u] && !visited[v] && graph[u][v] > 0 {
                println!("  {} -> {} (容量: {})", u, v, graph[u][v]);
            }
        }
    }
}

fn main() {
    println!("=== 最小割算法 ===");

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
    min_cut(&graph, s, t);
}
