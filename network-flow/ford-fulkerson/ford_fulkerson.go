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

package main

import (
	"fmt"
)

const MAX_V = 100

var graph [MAX_V][MAX_V]int
var V int

func dfs(rGraph *[MAX_V][MAX_V]int, u int, t int, visited []bool, min_flow int) int {
	if u == t {
		return min_flow
	}

	visited[u] = true

	for v := 0; v < V; v++ {
		if !visited[v] && rGraph[u][v] > 0 {
			flow := dfs(rGraph, v, t, visited, min_flow)
			if rGraph[u][v] < flow {
				flow = rGraph[u][v]
			}

			if flow > 0 {
				rGraph[u][v] -= flow
				rGraph[v][u] += flow
				return flow
			}
		}
	}

	return 0
}

func fordFulkerson(s int, t int) int {
	rGraph := [MAX_V][MAX_V]int{}
	max_flow := 0

	for u := 0; u < V; u++ {
		for v := 0; v < V; v++ {
			rGraph[u][v] = graph[u][v]
		}
	}

	for {
		visited := make([]bool, V)
		path_flow := dfs(&rGraph, s, t, visited, 1<<30)

		if path_flow == 0 {
			break
		}

		max_flow += path_flow
	}

	return max_flow
}

func main() {
	fmt.Println("=== Ford-Fulkerson算法 ===")

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
	max_flow := fordFulkerson(s, t)

	fmt.Printf("最大流量: %d\n", max_flow)
}
