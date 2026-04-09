// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

// Package graphbfs implements BFS traversal for graphs
// 图的广度优先搜索（BFS）算法实现
// 使用队列数据结构，按层次遍历图
//
// 时间复杂度: O(V + E)，其中V是顶点数，E是边数
// 空间复杂度: O(V)，用于存储访问标记和队列
package graphbfs

import "fmt"

const V = 5

// BFS 广度优先搜索遍历
// graph: 邻接矩阵表示的图
// start: 起始顶点
func BFS(graph [V][V]int, start int) {
	// 使用切片作为队列存储待访问的顶点
	queue := make([]int, 0, V)
	// 访问标记数组
	visited := make([]bool, V)

	// 将起始顶点入队并标记为已访问
	queue = append(queue, start)
	visited[start] = true

	fmt.Println("BFS traversal:")

	// 当队列不为空时继续遍历
	for len(queue) > 0 {
		// 出队一个顶点
		vertex := queue[0]
		queue = queue[1:]
		fmt.Printf("Visited %d\n", vertex)

		// 遍历所有邻接顶点
		for i := 0; i < V; i++ {
			// 如果存在边且未被访问，则入队
			if graph[vertex][i] == 1 && !visited[i] {
				queue = append(queue, i)
				visited[i] = true
			}
		}
	}
}

func ExampleBFS() {
	// 邻接矩阵表示的无向图
	graph := [V][V]int{
		{0, 1, 0, 1, 0},
		{1, 0, 1, 1, 1},
		{0, 1, 0, 0, 1},
		{1, 1, 0, 0, 1},
		{0, 1, 1, 1, 0},
	}

	BFS(graph, 0)
}
