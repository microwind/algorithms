package main

import "fmt"

const MAX_VERTICES = 100

// 邻接矩阵表示图
var graph [MAX_VERTICES][MAX_VERTICES]int
var visited [MAX_VERTICES]bool
var numVertices int

// DFS递归遍历
func dfs(vertex int) {
	// 标记当前顶点为已访问
	visited[vertex] = true
	fmt.Printf("%d ", vertex)
	
	// 递归访问所有未访问的邻居
	for i := 0; i < numVertices; i++ {
		if graph[vertex][i] == 1 && !visited[i] {
			dfs(i)
		}
	}
}

// 查找所有连通分量
func findConnectedComponents() {
	componentCount := 0
	
	fmt.Println("连通分量检测:\n")
	
	// 初始化访问数组
	for i := 0; i < numVertices; i++ {
		visited[i] = false
	}
	
	// 遍历所有顶点，对每个未访问的顶点进行DFS
	for i := 0; i < numVertices; i++ {
		if !visited[i] {
			componentCount++
			fmt.Printf("连通分量 %d: ", componentCount)
			dfs(i)
			fmt.Println()
		}
	}
	
	fmt.Printf("\n总共找到 %d 个连通分量\n", componentCount)
}

// 添加边
func addEdge(from, to int) {
	graph[from][to] = 1
	graph[to][from] = 1
}

func main() {
	// 创建一个示例图（两个连通分量）
	// 分量1: 0-1-2
	// 分量2: 3-4
	numVertices = 5
	
	// 添加边
	addEdge(0, 1)
	addEdge(1, 2)
	addEdge(3, 4)
	
	fmt.Println("图结构:")
	fmt.Println("  分量1: 0 -- 1 -- 2")
	fmt.Println("  分量2: 3 -- 4\n")
	
	findConnectedComponents()
}
