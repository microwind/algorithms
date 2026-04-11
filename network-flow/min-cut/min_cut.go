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

package main

import (
	"fmt"
)

const MAX_V = 100

var graph [MAX_V][MAX_V]int
var V int

func bfs(rGraph *[MAX_V][MAX_V]int, s int, t int, parent []int) bool {
	visited := make([]bool, V)
	queue := []int{s}
	visited[s] = true
	parent[s] = -1

	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]

		for v := 0; v < V; v++ {
			if !visited[v] && rGraph[u][v] > 0 {
				queue = append(queue, v)
				parent[v] = u
				visited[v] = true

				if v == t {
					return true
				}
			}
		}
	}

	return false
}

func maxFlow(s int, t int, rGraph *[MAX_V][MAX_V]int) int {
	parent := make([]int, V)
	max_flow := 0

	for bfs(rGraph, s, t, parent) {
		path_flow := 1 << 30

		for v := t; v != s; v = parent[v] {
			u := parent[v]
			if rGraph[u][v] < path_flow {
				path_flow = rGraph[u][v]
			}
		}

		for v := t; v != s; v = parent[v] {
			u := parent[v]
			rGraph[u][v] -= path_flow
			rGraph[v][u] += path_flow
		}

		max_flow += path_flow
	}

	return max_flow
}

func minCut(s int, t int) {
	rGraph := [MAX_V][MAX_V]int{}

	for u := 0; u < V; u++ {
		for v := 0; v < V; v++ {
			rGraph[u][v] = graph[u][v]
		}
	}

	max_flow := maxFlow(s, t, &rGraph)
	fmt.Printf("最大流量: %d\n", max_flow)

	visited := make([]bool, V)
	queue := []int{s}
	visited[s] = true

	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]

		for v := 0; v < V; v++ {
			if !visited[v] && rGraph[u][v] > 0 {
				queue = append(queue, v)
				visited[v] = true
			}
		}
	}

	fmt.Println("最小割边:")
	for u := 0; u < V; u++ {
		for v := 0; v < V; v++ {
			if visited[u] && !visited[v] && graph[u][v] > 0 {
				fmt.Printf("  %d -> %d (容量: %d)\n", u, v, graph[u][v])
			}
		}
	}
}

func main() {
	fmt.Println("=== 最小割算法 ===")

	V = 6

	graph[0][1] = 16
	graph[0][2] = 13
	graph[1][2] = 10
	graph[1][3] = 12
	graph[2][1] = 4
	graph[2][4] = 14
	graph[3][2] = 9
	graph[3][5] = 20
	graph[4][3] = 7
	graph[4][5] = 4

	s := 0
	t := 5
	minCut(s, t)
}
