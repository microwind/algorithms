// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// Dijkstra最短路径算法实现
/// 使用贪心策略，适用于非负权重的图
///
/// 时间复杂度: O(V²)，使用优先队列可优化至O((V+E)logV)
/// 空间复杂度: O(V)，用于存储距离和访问标记

const V: usize = 6;
const INF: i32 = i32::MAX;

/// 找到距离最小的未处理顶点
fn min_distance(dist: &[i32], visited: &[bool]) -> usize {
    let mut min = INF;
    let mut min_index = 0;

    for v in 0..V {
        if !visited[v] && dist[v] <= min {
            min = dist[v];
            min_index = v;
        }
    }
    min_index
}

/// Dijkstra算法实现
pub fn dijkstra(graph: &[[i32; V]; V], src: usize) {
    let mut dist = [INF; V];
    let mut visited = [false; V];
    dist[src] = 0;

    for _ in 0..V - 1 {
        let u = min_distance(&dist, &visited);
        visited[u] = true;

        for v in 0..V {
            if !visited[v] && graph[u][v] != 0 &&
               dist[u] != INF && dist[u] + graph[u][v] < dist[v] {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    println!("Vertex \t Distance from Source");
    for i in 0..V {
        println!("{} \t {}", i, dist[i]);
    }
}

pub fn test_dijkstra() {
    let graph = [
        [0, 4, 0, 0, 0, 0],
        [4, 0, 8, 0, 0, 0],
        [0, 8, 0, 7, 0, 4],
        [0, 0, 7, 0, 9, 14],
        [0, 0, 0, 9, 0, 10],
        [0, 0, 4, 14, 10, 0],
    ];

    dijkstra(&graph, 0);
}
