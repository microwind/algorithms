// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

// 拓扑排序 (Topological Sort)
// 使用Kahn算法（基于BFS）对有向无环图进行拓扑排序

package main

import (
	"fmt"
)

// topologicalSort Kahn算法实现拓扑排序
func topologicalSort(graph map[int][]int, numVertices int) []int {
	inDegree := make([]int, numVertices)
	
	// 计算每个顶点的入度
	for _, neighbors := range graph {
		for _, v := range neighbors {
			inDegree[v]++
		}
	}
	
	// 将所有入度为0的顶点加入队列
	queue := []int{}
	for i := 0; i < numVertices; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}
	
	result := []int{}
	
	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]
		result = append(result, u)
		
		// 将u的所有邻居的入度减1
		for _, v := range graph[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				queue = append(queue, v)
			}
		}
	}
	
	// 检查是否存在环
	if len(result) != numVertices {
		return []int{} // 存在环
	}
	
	return result
}

func main() {
	graph := map[int][]int{
		0: {1},
		1: {2, 3},
		2: {3},
		3: {},
	}
	
	numVertices := 4
	
	fmt.Println("==================================================")
	fmt.Println("拓扑排序 (Topological Sort)")
	fmt.Println("==================================================")
	
	result := topologicalSort(graph, numVertices)
	
	if len(result) > 0 {
		fmt.Printf("\n拓扑排序结果: %v\n", result)
	} else {
		fmt.Println("\n图中存在环，无法进行拓扑排序")
	}
}
