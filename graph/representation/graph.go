// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

// 图的邻接表表示实现
// 使用链表存储图的邻接关系

package main

import "fmt"

const V = 5

type Node struct {
	dest int
	next *Node
}

type Graph struct {
	adjList [V]*Node
}

func createGraph() *Graph {
	graph := &Graph{}
	for i := 0; i < V; i++ {
		graph.adjList[i] = nil
	}
	return graph
}

func (g *Graph) addEdge(src, dest int) {
	newNode := &Node{dest: dest, next: g.adjList[src]}
	g.adjList[src] = newNode
}

func (g *Graph) printGraph() {
	for i := 0; i < V; i++ {
		fmt.Printf("Adjacency list of vertex %d: ", i)
		temp := g.adjList[i]
		for temp != nil {
			fmt.Printf(" -> %d", temp.dest)
			temp = temp.next
		}
		fmt.Println()
	}
}

func main() {
	graph := createGraph()
	graph.addEdge(0, 1)
	graph.addEdge(0, 3)
	graph.addEdge(1, 2)
	graph.addEdge(1, 3)
	graph.addEdge(1, 4)
	graph.addEdge(2, 4)
	graph.addEdge(3, 4)
	
	graph.printGraph()
}
