/** 在JavaScript中，使用对象和数组来实现图的邻接表 */
class Graph {
  constructor(vertices) {
    this.numVertices = vertices;
    this.adjLists = Array.from({
      length: vertices
    }, () => []);
  }

  addEdge(src, dest) {
    this.adjLists[src].push(dest);
    this.adjLists[dest].push(src);
  }

  printGraph() {
    console.log(this.adjLists)
    for (let v = 0; v < this.numVertices; v++) {
      let str = `Vertex ${v}:`;
      this.adjLists[v].forEach(dest => {
        str += ` -> ${dest}`;
      });
      console.log(str);
    }
  }
}

const graph = new Graph(4);
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.addEdge(1, 2);
graph.addEdge(2, 3);

graph.printGraph();

/**
jarry@jarrys-MacBook-Pro graph % node graph.js   
[ [ 1, 2 ], [ 0, 2 ], [ 0, 1, 3 ], [ 2 ] ]
Vertex 0: -> 1 -> 2
Vertex 1: -> 0 -> 2
Vertex 2: -> 0 -> 1 -> 3
Vertex 3: -> 2
 */