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

package main

import (
	"fmt"
)

const MAX_V = 100

var graph [MAX_V][MAX_V]int
var V int

func bfs(rGraph [MAX_V][MAX_V]int, s int, t int, parent []int) bool {
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

func edmondsKarp(s int, t int) int {
	rGraph := [MAX_V][MAX_V]int{}
	parent := make([]int, V)
	max_flow := 0

	for u := 0; u < V; u++ {
		for v := 0; v < V; v++ {
			rGraph[u][v] = graph[u][v]
		}
	}

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

func main() {
	fmt.Println("=== Edmonds-Karp算法 ===")

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
	max_flow := edmondsKarp(s, t)

	fmt.Printf("最大流量: %d\n", max_flow)
}
