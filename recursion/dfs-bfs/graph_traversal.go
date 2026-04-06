package main

import "fmt"

/**
 * 图的深度优先搜索 (DFS) 和广度优先搜索 (BFS)
 * 使用递归实现DFS，使用队列实现BFS
 */

// 邻接表表示图
type Graph map[string][]string

// 全局访问标记
var visited map[string]bool

// 深度优先搜索 - 递归实现
// 沿着一条路径尽可能深地搜索，直到无法继续才回溯
func dfsRecursive(graph Graph, node string) {
	// 访问当前节点
	visited[node] = true
	fmt.Printf("DFS访问: %s\n", node)
	
	// 递归访问所有未访问的邻居
	for _, neighbor := range graph[node] {
		if !visited[neighbor] {
			dfsRecursive(graph, neighbor)
		}
	}
}

// 广度优先搜索 - 迭代实现（使用队列）
// 逐层遍历，先访问所有邻居，再访问邻居的邻居
func bfsIterative(graph Graph, start string) {
	visited := make(map[string]bool)
	visited[start] = true
	queue := []string{start}
	
	fmt.Println("\nBFS遍历:")
	for len(queue) > 0 {
		// 出队
		node := queue[0]
		queue = queue[1:]
		fmt.Printf("BFS访问: %s\n", node)
		
		// 将所有未访问的邻居加入队列
		for _, neighbor := range graph[node] {
			if !visited[neighbor] {
				visited[neighbor] = true
				queue = append(queue, neighbor)
			}
		}
	}
}

func main() {
	// 示例图（邻接表表示）
	graph := Graph{
		"A": []string{"B", "C"},
		"B": []string{"A", "D", "E"},
		"C": []string{"A", "F"},
		"D": []string{"B"},
		"E": []string{"B", "F"},
		"F": []string{"C", "E"},
	}
	
	fmt.Println("图结构:")
	fmt.Println("    A")
	fmt.Println("   / \\")
	fmt.Println("  B---C")
	fmt.Println("  |   |")
	fmt.Println("  D E--F")
	fmt.Println()
	
	fmt.Println("==============================")
	fmt.Println("DFS深度优先遍历:")
	
	// 初始化访问标记
	visited = make(map[string]bool)
	dfsRecursive(graph, "A")
	
	bfsIterative(graph, "A")
}
