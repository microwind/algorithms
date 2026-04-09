/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树搜索算法 - 矩阵节点路径查找
 * 实现BFS和DFS用于二维矩阵中的最短路径查找
 * 用于路径查找、迷宫求解、图遍历等
 * 支持4方向移动和多条最短路径
 */

package main

import (
	"fmt"
)

// 具有4方向连接的矩阵节点
type MatrixNode struct {
	data  int        // 节点存储的数据
	up    *MatrixNode // 上方节点连接
	down  *MatrixNode // 下方节点连接
	left  *MatrixNode // 左侧节点连接
	right *MatrixNode // 右侧节点连接
}

// 路径结构用于存储路径
type Path struct {
	nodes []*MatrixNode // 路径中的节点数组
}

/**
 * 创建n x n的互连矩阵节点
 * 
 * 算法:
 * 1. 创建n x n的节点矩阵
 * 2. 用顺序数据初始化每个节点
 * 3. 建立水平连接（左右）
 * 4. 建立垂直连接（上下）
 * 
 * 时间复杂度: O(n²) - 处理n²个节点
 * 空间复杂度: O(n²) - 存储n²个节点
 * 
 * @param n 矩阵维度 (n x n)
 * @return 头节点（左上角）
 */
func createMatrix(n int) *MatrixNode {
	matrix := make([][]*MatrixNode, n)
	
	// 初始化n x n节点矩阵
	for i := 0; i < n; i++ {
		matrix[i] = make([]*MatrixNode, n)
		for j := 0; j < n; j++ {
			matrix[i][j] = &MatrixNode{
				data:  i*n + j + 1,
				up:    nil,
				down:  nil,
				left:  nil,
				right: nil,
			}
		}
	}
	
	// 连接左右（水平连接）
	for i := 0; i < n; i++ {
		for j := 0; j < n-1; j++ {
			matrix[i][j+1].left = matrix[i][j]   // 设置左连接
			matrix[i][j].right = matrix[i][j+1] // 设置右连接
		}
	}

	// 连接上下
	for i := 0; i < n-1; i++ {
		for j := 0; j < n; j++ {
			matrix[i+1][j].up = matrix[i][j]   // 设置上连接
			matrix[i][j].down = matrix[i+1][j] // 设置下连接
		}
	}

	return matrix[0][0] // 返回头节点（左上角）
}

/**
 * 从头节点开始打印矩阵
 * 
 * 算法:
 * 1. 从头节点开始逐行遍历
 * 2. 使用down指针移动到下一行
 * 3. 使用right指针在每行内遍历
 * 4. 打印每个节点的数据值
 * 
 * @param head 头节点（左上角）
 * @param n 矩阵维度
 */
func printMatrix(head *MatrixNode, n int) {
	currentRow := head
	
	for i := 0; i < n; i++ {
		current := currentRow
		for j := 0; j < n; j++ {
			fmt.Printf("%d ", current.data)
			current = current.right
		}
		fmt.Println()
		currentRow = currentRow.down
	}
}

/**
 * 使用BFS查找最短路径
 * 
 * 算法:
 * 1. 使用队列进行层序遍历
 * 2. 跟踪最短路径长度
 * 3. 探索所有最小长度路径
 * 4. 使用路径跟踪避免循环
 * 
 * 时间复杂度: O(V + E) - V=顶点数, E=边数
 * 空间复杂度: O(V) - 用于队列和路径存储
 * 
 * @param start 起始节点
 * @param end 目标节点
 * @return 最短路径数组
 */
func findShortestPathsBFS(start, end *MatrixNode) [][]*MatrixNode {
	queue := [][]*MatrixNode{{start}}
	paths := [][]*MatrixNode{}
	shortestLength := -1
	
	for len(queue) > 0 {
		currentPath := queue[0]
		queue = queue[1:]
		current := currentPath[len(currentPath)-1]
		
		// 检查是否到达目标
		if current == end {
			if shortestLength == -1 || len(currentPath) < shortestLength {
				shortestLength = len(currentPath)
				paths = [][]*MatrixNode{currentPath}
			} else if len(currentPath) == shortestLength {
				paths = append(paths, currentPath)
			}
			continue
		}
		
		// 如果已找到最短路径且当前路径更长，跳过
		if shortestLength != -1 && len(currentPath) >= shortestLength {
			continue
		}
		
		// 探索邻居节点
		neighbors := []*MatrixNode{current.left, current.up, current.down, current.right}
		
		for _, neighbor := range neighbors {
			if neighbor != nil && !contains(currentPath, neighbor) {
				newPath := make([]*MatrixNode, len(currentPath))
				copy(newPath, currentPath)
				newPath = append(newPath, neighbor)
				queue = append(queue, newPath)
			}
		}
	}
	
	return paths
}

// 检查路径是否包含节点
func contains(path []*MatrixNode, node *MatrixNode) bool {
	for _, n := range path {
		if n == node {
			return true
		}
	}
	return false
}

/**
 * 打印所有找到的路径
 * 
 * @param paths 路径数组
 */
func printPaths(paths [][]*MatrixNode) {
	if len(paths) == 0 {
		fmt.Println("未找到路径")
		return
	}
	
	fmt.Printf("最短路径（长度 %d）:\n", len(paths[0]))
	for i, path := range paths {
		fmt.Printf("  路径 %d: ", i+1)
		for j, node := range path {
			fmt.Printf("%d", node.data)
			if j < len(path)-1 {
				fmt.Print(" -> ")
			}
		}
		fmt.Println()
	}
}

/**
 * 打印分隔线
 */
func printSeparator() {
	for i := 0; i < 60; i++ {
		fmt.Print("=")
	}
	fmt.Println()
}

/**
 * 主测试函数
 * 
 * 测试用例:
 * 1. 创建3x3矩阵网络
 * 2. 演示矩阵结构
 * 3. 使用BFS查找最短路径
 * 4. 比较算法特性
 */
func main() {
	n := 3
	head := createMatrix(n)
	
	printSeparator()
	fmt.Println("树搜索算法 - 矩阵节点路径查找")
	printSeparator()
	fmt.Println()
	
	fmt.Printf("矩阵结构 (%dx%d):\n", n, n)
	printMatrix(head, n)
	fmt.Println()
	
	// 查找特定节点用于演示
	node2 := head.right // 值为2的节点
	node9 := head       // 从头节点开始
	// 导航到节点9（右下角）
	for i := 0; i < n-1; i++ {
		node9 = node9.down
	}
	for i := 0; i < n-1; i++ {
		node9 = node9.right
	}
	
	if node2 != nil && node9 != nil {
		// BFS搜索
		fmt.Printf("从 %d 到 %d 的BFS最短路径:\n", node2.data, node9.data)
		bfsPaths := findShortestPathsBFS(node2, node9)
		printPaths(bfsPaths)
		fmt.Println()
	} else {
		fmt.Println("无法找到所需节点")
	}
	
	fmt.Println("=== 算法特性 ===")
	fmt.Println("BFS（广度优先搜索）:")
	fmt.Println("  - 保证在无权图中找到最短路径")
	fmt.Println("  - 使用队列进行层序遍历")
	fmt.Println("  - 适用于最短路径查找")
	
	fmt.Println("\n复杂度分析:")
	fmt.Println("  - 时间复杂度: O(V + E)，其中V是顶点数，E是边数")
	fmt.Println("  - 空间复杂度: O(V)，用于队列/递归栈")
	fmt.Println("  - 矩阵导航: 4方向移动（上、下、左、右）")
	
	fmt.Println("\n=== 应用场景 ===")
	fmt.Println("矩阵路径查找用于:")
	fmt.Println("  - 迷宫求解和益智游戏")
	fmt.Println("  - 网络路由和导航")
	fmt.Println("  - 游戏AI和路径查找")
	fmt.Println("  - 电路板设计")
	fmt.Println("  - 图像处理和分析")
}
