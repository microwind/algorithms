package main

import "fmt"

const V = 6
const INF = int(^uint(0) >> 1)

func minDistance(dist []int, visited []bool) int {
    min := INF
    minIndex := -1
    for v := 0; v < V; v++ {
        if !visited[v] && dist[v] <= min {
            min = dist[v]
            minIndex = v
        }
    }
    return minIndex
}

func dijkstra(graph [V][V]int, src int) {
    dist := make([]int, V)
    visited := make([]bool, V)
    for i := 0; i < V; i++ {
        dist[i] = INF
    }
    dist[src] = 0

    for count := 0; count < V-1; count++ {
        u := minDistance(dist, visited)
        visited[u] = true
        for v := 0; v < V; v++ {
            if !visited[v] && graph[u][v] != 0 && dist[u] != INF && dist[u]+graph[u][v] < dist[v] {
                dist[v] = dist[u] + graph[u][v]
            }
        }
    }

    fmt.Println("Vertex Distance from Source")
    for i := 0; i < V; i++ {
        fmt.Printf("%d %d\n", i, dist[i])
    }
}

func main() {
    graph := [V][V]int{
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0},
    }
    dijkstra(graph, 0)
}
