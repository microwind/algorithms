package main

import (
	"fmt"
)

// 深度优先搜索（DFS）实现 (Go语言)
//
// 特点：
// - 优先往纵深方向探索
// - 使用栈或递归
// - 回溯机制
// - 时间复杂度：O(V + E)
// - 空间复杂度：O(V)

// 栈结构
type Stack struct {
	items []int
}

// 初始化栈
func NewStack() *Stack {
	return &Stack{items: []int{}}
}

// 入栈
func (s *Stack) Push(item int) {
	s.items = append(s.items, item)
}

// 出栈
func (s *Stack) Pop() int {
	if len(s.items) == 0 {
		return -1
	}
	item := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return item
}

// 检查栈是否为空
func (s *Stack) IsEmpty() bool {
	return len(s.items) == 0
}

// 图结构（邻接表）
type Graph struct {
	adjLists    [][]int
	numVertices int
}

// 初始化图
func NewGraph(vertices int) *Graph {
	return &Graph{
		adjLists:    make([][]int, vertices),
		numVertices: vertices,
	}
}

// 添加边（无向图）
func (g *Graph) AddEdge(src, dest int) {
	g.adjLists[src] = append(g.adjLists[src], dest)
	g.adjLists[dest] = append(g.adjLists[dest], src) // 无向图
}

// DFS递归实现
func (g *Graph) dfsRecursive(vertex int, visited []bool, result *[]int) {
	// 标记当前顶点为已访问
	visited[vertex] = true
	*result = append(*result, vertex)

	// 递归访问所有未访问的邻接顶点
	for _, adjVertex := range g.adjLists[vertex] {
		if !visited[adjVertex] {
			g.dfsRecursive(adjVertex, visited, result)
		}
	}
}

// DFS递归遍历（包装函数）
func (g *Graph) DFSRecursive(startVertex int) []int {
	visited := make([]bool, g.numVertices)
	var result []int

	g.dfsRecursive(startVertex, visited, &result)
	return result
}

// DFS迭代实现（使用栈）
func (g *Graph) DFSIterative(startVertex int) []int {
	visited := make([]bool, g.numVertices)
	stack := NewStack()
	var result []int

	// 将起始顶点入栈
	stack.Push(startVertex)

	for !stack.IsEmpty() {
		// 出栈一个顶点
		currentVertex := stack.Pop()

		// 如果该顶点未被访问
		if !visited[currentVertex] {
			visited[currentVertex] = true
			result = append(result, currentVertex)

			// 将所有未访问的邻接顶点入栈
			// 注意：为了保持与递归相似的顺序，需要反向入栈
			neighbors := g.adjLists[currentVertex]
			for i := len(neighbors) - 1; i >= 0; i-- {
				adjVertex := neighbors[i]
				if !visited[adjVertex] {
					stack.Push(adjVertex)
				}
			}
		}
	}

	return result
}

// DFS查找路径
func (g *Graph) DFSFindPath(current, target int, visited []bool, path *[]int) bool {
	// 标记当前顶点为已访问
	visited[current] = true
	*path = append(*path, current)

	// 如果找到目标
	if current == target {
		return true
	}

	// 递归访问所有邻接顶点
	for _, adjVertex := range g.adjLists[current] {
		if !visited[adjVertex] {
			if g.DFSFindPath(adjVertex, target, visited, path) {
				return true
			}
		}
	}

	// 回溯：从路径中移除当前顶点
	*path = (*path)[:len(*path)-1]
	return false
}

// 查找两点之间的路径
func (g *Graph) FindPath(start, end int) []int {
	visited := make([]bool, g.numVertices)
	var path []int

	if g.DFSFindPath(start, end, visited, &path) {
		return path
	}
	return nil
}

// DFS检测环
func (g *Graph) dfsDetectCycle(vertex, parent int, visited []bool) bool {
	visited[vertex] = true

	for _, adjVertex := range g.adjLists[vertex] {
		// 如果邻接顶点未被访问，递归检查
		if !visited[adjVertex] {
			if g.dfsDetectCycle(adjVertex, vertex, visited) {
				return true
			}
		} else if adjVertex != parent {
			// 如果邻接顶点已被访问且不是父节点，则存在环
			return true
		}
	}

	return false
}

// 检测图中是否存在环
func (g *Graph) HasCycle() bool {
	visited := make([]bool, g.numVertices)

	for i := 0; i < g.numVertices; i++ {
		if !visited[i] {
			if g.dfsDetectCycle(i, -1, visited) {
				return true
			}
		}
	}

	return false
}

// DFS计算连通分量
func (g *Graph) DFSConnectedComponents() [][]int {
	visited := make([]bool, g.numVertices)
	var components [][]int

	for i := 0; i < g.numVertices; i++ {
		if !visited[i] {
			var component []int
			g.dfsRecursive(i, visited, &component)
			components = append(components, component)
		}
	}

	return components
}

// DFS拓扑排序（用于有向无环图）
func (g *Graph) DFSTopologicalSort() []int {
	visited := make([]bool, g.numVertices)
	stack := NewStack()

	// 对每个未访问的顶点进行DFS
	for i := 0; i < g.numVertices; i++ {
		if !visited[i] {
			g.topologicalSortUtil(i, visited, stack)
		}
	}

	// 弹出栈中的元素得到拓扑排序
	var result []int
	for !stack.IsEmpty() {
		result = append(result, stack.Pop())
	}

	return result
}

// 拓扑排序的辅助函数
func (g *Graph) topologicalSortUtil(vertex int, visited []bool, stack *Stack) {
	visited[vertex] = true

	for _, adjVertex := range g.adjLists[vertex] {
		if !visited[adjVertex] {
			g.topologicalSortUtil(adjVertex, visited, stack)
		}
	}

	// 将顶点入栈
	stack.Push(vertex)
}

// DFS检测强连通分量（用于有向图）
func (g *Graph) DFSStronglyConnectedComponents() [][]int {
	// Kosaraju算法
	visited := make([]bool, g.numVertices)
	stack := NewStack()

	// 第一步：对原图进行DFS，将顶点按完成时间入栈
	for i := 0; i < g.numVertices; i++ {
		if !visited[i] {
			g.fillOrder(i, visited, stack)
		}
	}

	// 第二步：创建转置图
	transposed := g.getTranspose()

	// 第三步：按栈中顺序对转置图进行DFS
	visited = make([]bool, g.numVertices)
	var components [][]int

	for !stack.IsEmpty() {
		vertex := stack.Pop()
		if !visited[vertex] {
			var component []int
			transposed.dfsRecursive(vertex, visited, &component)
			components = append(components, component)
		}
	}

	return components
}

// 填充顺序的辅助函数
func (g *Graph) fillOrder(vertex int, visited []bool, stack *Stack) {
	visited[vertex] = true

	for _, adjVertex := range g.adjLists[vertex] {
		if !visited[adjVertex] {
			g.fillOrder(adjVertex, visited, stack)
		}
	}

	stack.Push(vertex)
}

// 获取转置图
func (g *Graph) getTranspose() *Graph {
	transposed := NewGraph(g.numVertices)

	for v := 0; v < g.numVertices; v++ {
		for _, adjVertex := range g.adjLists[v] {
			transposed.adjLists[adjVertex] = append(transposed.adjLists[adjVertex], v)
		}
	}

	return transposed
}

func main() {
	fmt.Println("=== 深度优先搜索（DFS）演示 ===\n")

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

	// 1. DFS递归遍历
	fmt.Println("1. DFS递归遍历（从顶点0开始）")
	recursiveResult := graph.DFSRecursive(0)
	fmt.Printf("结果: %v\n", recursiveResult)
	fmt.Println()

	// 2. DFS迭代遍历
	fmt.Println("2. DFS迭代遍历（从顶点0开始）")
	iterativeResult := graph.DFSIterative(0)
	fmt.Printf("结果: %v\n", iterativeResult)
	fmt.Println()

	// 3. 查找路径
	fmt.Println("3. 查找路径")
	path := graph.FindPath(0, 7)
	if path != nil {
		fmt.Printf("从 0 到 7 的路径: %v\n", path)
	} else {
		fmt.Println("未找到从 0 到 7 的路径")
	}
	fmt.Println()

	// 4. 检测环
	fmt.Println("4. 检测环")
	if graph.HasCycle() {
		fmt.Println("图中存在环")
	} else {
		fmt.Println("图中不存在环")
	}
	fmt.Println()

	// 5. 计算连通分量
	fmt.Println("5. 计算连通分量")
	components := graph.DFSConnectedComponents()
	fmt.Printf("连通分量数: %d\n", len(components))
	for i, component := range components {
		fmt.Printf("分量 %d: %v\n", i+1, component)
	}
	fmt.Println()

	// 6. 从不同起点开始DFS
	fmt.Println("6. 从不同起点开始DFS")
	fmt.Printf("从顶点3开始（递归）: %v\n", graph.DFSRecursive(3))
	fmt.Printf("从顶点3开始（迭代）: %v\n", graph.DFSIterative(3))
}
