// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

// Package graphdfs implements DFS traversal for graphs
// 图的深度优先搜索（DFS）算法实现
// 使用递归方式遍历图
//
// 时间复杂度: O(V + E)，其中V是顶点数，E是边数
// 空间复杂度: O(V)，用于存储访问标记和递归栈
package graphdfs

import "fmt"

const V = 5

// DFS 深度优先搜索递归函数
// graph: 邻接矩阵表示的图
// visited: 访问标记数组
// vertex: 当前顶点
func DFS(graph [V][V]int, visited []bool, vertex int) {
	// 访问当前顶点
	fmt.Printf("Visited %d\n", vertex)
	visited[vertex] = true

	// 遍历所有邻接顶点
	for i := 0; i < V; i++ {
		// 如果存在边且未被访问，则递归访问
		if graph[vertex][i] == 1 && !visited[i] {
			DFS(graph, visited, i)
		}
	}
}

func ExampleDFS() {
	// 邻接矩阵表示的无向图
	graph := [V][V]int{
		{0, 1, 0, 1, 0},
		{1, 0, 1, 1, 1},
		{0, 1, 0, 0, 1},
		{1, 1, 0, 0, 1},
		{0, 1, 1, 1, 0},
	}
	visited := make([]bool, V)

	fmt.Println("DFS traversal:")
	DFS(graph, visited, 0)
}
