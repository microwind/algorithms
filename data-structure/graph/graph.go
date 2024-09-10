package main

import "fmt"

/** 在Go语言中，可以使用切片和结构体来实现图的邻接表 */

type Graph struct {
  numVertices int
  adjLists    [][]int
}

func createGraph(vertices int) *Graph {
  graph := &Graph{
    numVertices: vertices,
    adjLists:    make([][]int, vertices),
  }
  return graph
}

func (g *Graph) addEdge(src, dest int) {
  g.adjLists[src] = append(g.adjLists[src], dest)
  g.adjLists[dest] = append(g.adjLists[dest], src)
}

func (g *Graph) printGraph() {
  for v := 0; v < g.numVertices; v++ {
    fmt.Printf("Vertex %d: ", v)
    for _, dest := range g.adjLists[v] {
      fmt.Printf(" -> %d", dest)
    }
    fmt.Println()
  }
}

func main() {
  graph := createGraph(4)
  graph.addEdge(0, 1)
  graph.addEdge(0, 2)
  graph.addEdge(1, 2)
  graph.addEdge(2, 3)
  graph.printGraph()

  for _, value := range graph.adjLists {
    fmt.Printf("%d\n", value)
  }
}

/**
jarry@jarrys-MacBook-Pro graph % go run graph.go
Vertex 0:  -> 1 -> 2
Vertex 1:  -> 0 -> 2
Vertex 2:  -> 0 -> 1 -> 3
Vertex 3:  -> 2
[1 2]
[0 2]
[0 1 3]
[2]
*/
