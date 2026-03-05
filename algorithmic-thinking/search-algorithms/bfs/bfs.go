package main

import (
	"fmt"
)

// 广度优先搜索（BFS）实现 (Go语言)
//
// 特点：
// - 逐层探索，由近到远
// - 使用队列（FIFO）
// - 找到的第一条路径就是最短路径
// - 时间复杂度：O(V + E)
// - 空间复杂度：O(V)

// 队列结构
type Queue struct {
	items []int
}

// 初始化队列
func NewQueue() *Queue {
	return &Queue{items: []int{}}
}

// 入队
func (q *Queue) Enqueue(item int) {
	q.items = append(q.items, item)
}

// 出队
func (q *Queue) Dequeue() int {
	if len(q.items) == 0 {
		return -1
	}
	item := q.items[0]
	q.items = q.items[1:]
	return item
}

// 检查队列是否为空
func (q *Queue) IsEmpty() bool {
	return len(q.items) == 0
}

// 图结构（邻接表）
type Graph struct {
	adjLists [][]int
	numVertices int
}

// 初始化图
func NewGraph(vertices int) *Graph {
	return &Graph{
		adjLists:   make([][]int, vertices),
		numVertices: vertices,
	}
}

// 添加边（无向图）
func (g *Graph) AddEdge(src, dest int) {
	g.adjLists[src] = append(g.adjLists[src], dest)
	g.adjLists[dest] = append(g.adjLists[dest], src) // 无向图
}

// BFS遍历
func (g *Graph) BFS(startVertex int) {
	visited := make([]bool, g.numVertices)
	queue := NewQueue()

	// 标记起始顶点为已访问并入队
	visited[startVertex] = true
	queue.Enqueue(startVertex)

	fmt.Print("BFS遍历结果: ")

	for !queue.IsEmpty() {
		// 出队一个顶点
		currentVertex := queue.Dequeue()
		fmt.Printf("%d ", currentVertex)

		// 访问所有邻接顶点
		for _, adjVertex := range g.adjLists[currentVertex] {
			if !visited[adjVertex] {
				visited[adjVertex] = true
				queue.Enqueue(adjVertex)
			}
		}
	}

	fmt.Println()
}

// BFS查找最短路径
func (g *Graph) BFSShortestPath(startVertex, endVertex int) {
	visited := make([]bool, g.numVertices)
	distance := make([]int, g.numVertices)
	parent := make([]int, g.numVertices)
	queue := NewQueue()

	// 初始化
	for i := 0; i < g.numVertices; i++ {
		parent[i] = -1
	}

	// 标记起始顶点为已访问并入队
	visited[startVertex] = true
	queue.Enqueue(startVertex)

	for !queue.IsEmpty() {
		currentVertex := queue.Dequeue()

		// 如果找到目标顶点，停止搜索
		if currentVertex == endVertex {
			break
		}

		// 访问所有邻接顶点
		for _, adjVertex := range g.adjLists[currentVertex] {
			if !visited[adjVertex] {
				visited[adjVertex] = true
				distance[adjVertex] = distance[currentVertex] + 1
				parent[adjVertex] = currentVertex
				queue.Enqueue(adjVertex)
			}
		}
	}

	// 输出最短路径
	if visited[endVertex] {
		fmt.Printf("从 %d 到 %d 的最短路径长度: %d\n", startVertex, endVertex, distance[endVertex])

		// 重建路径
		var path []int
		current := endVertex
		for current != -1 {
			path = append([]int{current}, path...)
			current = parent[current]
		}

		fmt.Print("路径: ")
		for i, v := range path {
			fmt.Printf("%d", v)
			if i < len(path)-1 {
				fmt.Print(" -> ")
			}
		}
		fmt.Println()
	} else {
		fmt.Printf("从 %d 到 %d 没有路径\n", startVertex, endVertex)
	}
}

// BFS计算连通分量
func (g *Graph) BFSConnectedComponents() {
	visited := make([]bool, g.numVertices)
	componentCount := 0

	fmt.Println("连通分量:")

	for i := 0; i < g.numVertices; i++ {
		if !visited[i] {
			componentCount++
			fmt.Printf("分量 %d: ", componentCount)

			queue := NewQueue()
			visited[i] = true
			queue.Enqueue(i)

			for !queue.IsEmpty() {
				currentVertex := queue.Dequeue()
				fmt.Printf("%d ", currentVertex)

				for _, adjVertex := range g.adjLists[currentVertex] {
					if !visited[adjVertex] {
						visited[adjVertex] = true
						queue.Enqueue(adjVertex)
					}
				}
			}

			fmt.Println()
		}
	}

	fmt.Printf("总连通分量数: %d\n", componentCount)
}

// BFS层序遍历（返回每层的节点）
func (g *Graph) BFSLevels(startVertex int) [][]int {
	visited := make([]bool, g.numVertices)
	queue := NewQueue()
	var levels [][]int

	// 标记起始顶点为已访问并入队
	visited[startVertex] = true
	queue.Enqueue(startVertex)

	for !queue.IsEmpty() {
		levelSize := len(queue.items)
		var currentLevel []int

		for i := 0; i < levelSize; i++ {
			currentVertex := queue.Dequeue()
			currentLevel = append(currentLevel, currentVertex)

			// 访问所有邻接顶点
			for _, adjVertex := range g.adjLists[currentVertex] {
				if !visited[adjVertex] {
					visited[adjVertex] = true
					queue.Enqueue(adjVertex)
				}
			}
		}

		levels = append(levels, currentLevel)
	}

	return levels
}

// BFS检测二分图
func (g *Graph) IsBipartite() bool {
	color := make([]int, g.numVertices)
	// 0: 未染色, 1: 染色A, -1: 染色B

	for i := 0; i < g.numVertices; i++ {
		if color[i] == 0 {
			queue := NewQueue()
			color[i] = 1
			queue.Enqueue(i)

			for !queue.IsEmpty() {
				currentVertex := queue.Dequeue()

				for _, adjVertex := range g.adjLists[currentVertex] {
					if color[adjVertex] == 0 {
						color[adjVertex] = -color[currentVertex]
						queue.Enqueue(adjVertex)
					} else if color[adjVertex] == color[currentVertex] {
						return false
					}
				}
			}
		}
	}

	return true
}

func main() {
	fmt.Println("=== 广度优先搜索（BFS）演示 ===\n")

	// 创建图
	graph := NewGraph(8)

	// 添加边
	graph.AddEdge(0, 1)
	graph.AddEdge(0, 2)
	graph.AddEdge(1, 3)
	graph.AddEdge(1, 4)
	graph.AddEdge(2, 5)
	graph.AddEdge(2, 6)
	graph.AddEdge(3, 7)
	graph.AddEdge(4, 7)
	graph.AddEdge(5, 6)

	fmt.Println("图结构:")
	fmt.Println("0 -- 1 -- 3 -- 7")
	fmt.Println("|    |         |")
	fmt.Println("|    |         |")
	fmt.Println("2 -- 4 --------|")
	fmt.Println("|    |")
	fmt.Println("|    |")
	fmt.Println("5 -- 6\n")

	// 1. 基本BFS遍历
	fmt.Println("1. 基本BFS遍历（从顶点0开始）")
	graph.BFS(0)
	fmt.Println()

	// 2. BFS查找最短路径
	fmt.Println("2. BFS查找最短路径")
	graph.BFSShortestPath(0, 7)
	fmt.Println()

	// 3. BFS计算连通分量
	fmt.Println("3. BFS计算连通分量")
	graph.BFSConnectedComponents()
	fmt.Println()

	// 4. BFS层序遍历
	fmt.Println("4. BFS层序遍历（从顶点0开始）")
	levels := graph.BFSLevels(0)
	for i, level := range levels {
		fmt.Printf("第%d层: %v\n", i, level)
	}
	fmt.Println()

	// 5. BFS检测二分图
	fmt.Println("5. BFS检测二分图")
	if graph.IsBipartite() {
		fmt.Println("该图是二分图")
	} else {
		fmt.Println("该图不是二分图")
	}

	// 6. 从不同起点开始BFS
	fmt.Println("\n6. 从不同起点开始BFS")
	fmt.Print("从顶点3开始: ")
	graph.BFS(3)
}
