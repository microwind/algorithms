import java.util.LinkedList;

/**
 * 在Java中，可以使用类和链表来实现图的邻接表
 */

class Graph {
  private int numVertices;
  private LinkedList<Integer>[] adjLists;

  @SuppressWarnings("unchecked")
  Graph(int vertices) {
    numVertices = vertices;
    adjLists = new LinkedList[vertices];
    for (int i = 0; i < vertices; i++) {
      adjLists[i] = new LinkedList<>();
    }
  }

  void addEdge(int src, int dest) {
    adjLists[src].add(dest);
    adjLists[dest].add(src);
  }

  void printGraph() {
    for (int v = 0; v < numVertices; v++) {
      System.out.print("Vertex " + v + ": ");
      for (Integer pCrawl : adjLists[v]) {
        System.out.print(" -> " + pCrawl);
      }
      System.out.println();
    }
  }

  public static void main(String[] args) {
    Graph graph = new Graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    graph.printGraph();

    for (LinkedList<Integer> v : graph.adjLists) {
      System.out.println(v);
    }

  }
}

/**
jarry@jarrys-MacBook-Pro graph % javac Graph.java
jarry@jarrys-MacBook-Pro graph % java Graph 
Vertex 0:  -> 1 -> 2
Vertex 1:  -> 0 -> 2
Vertex 2:  -> 0 -> 1 -> 3
Vertex 3:  -> 2
[1, 2]
[0, 2]
[0, 1, 3]
[2]
 */