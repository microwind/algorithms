/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  带权图及最短路径算法实现（TypeScript）
 *  功能：使用邻接表存储带权图，实现Dijkstra最短路径算法
 *  用途：学习图的最短路径算法，理解优先队列在图算法中的应用
 */

// 边类 - 表示图中的边（目标节点，边的权重）
class Edge {
  private end: string;
  private distance: number;

  constructor(end: string, distance: number) {
    this.end = end;
    this.distance = distance;
  }

  getEnd(): string {
    return this.end;
  }

  getDistance(): number {
    return this.distance;
  }
}

// 带权图类 - 支持Dijkstra最短路径算法
class GraphPath {
  private adjacencyList: Map<string, Edge[]>;

  // 构造函数，初始化图
  constructor() {
    this.adjacencyList = new Map();
  }

  // 添加边 (起点, 终点, 距离)
  addEdge(start: string, end: string, distance: number): void {
    if (!this.adjacencyList.has(start)) {
      this.adjacencyList.set(start, []);
    }
    this.adjacencyList.get(start)!.push(new Edge(end, distance));
    
    // 保证终点也在图中（处理孤立节点情况）
    if (!this.adjacencyList.has(end)) {
      this.adjacencyList.set(end, []);
    }
  }

  // Dijkstra算法寻找最短路径
  dijkstra(start: string): Map<string, number> {
    // 存储最短路径的距离
    const distances = new Map<string, number>();
    for (const vertex of this.adjacencyList.keys()) {
      distances.set(vertex, Infinity); // 初始设置为无穷大
    }
    distances.set(start, 0);

    // 优先队列按距离排序（使用数组模拟最小堆）
    const priorityQueue: Edge[] = [];
    priorityQueue.push(new Edge(start, 0));

    while (priorityQueue.length > 0) {
      // 找出距离最小的节点
      priorityQueue.sort((a, b) => a.getDistance() - b.getDistance());
      const current = priorityQueue.shift()!;
      const currentVertex = current.getEnd();
      const currentDistance = current.getDistance();

      // 如果当前距离大于已知最短距离，跳过
      if (currentDistance > distances.get(currentVertex)!) {
        continue;
      }

      // 遍历相邻节点
      const neighbors = this.adjacencyList.get(currentVertex) || [];
      for (const edge of neighbors) {
        const newDist = currentDistance + edge.getDistance();
        if (newDist < distances.get(edge.getEnd())!) {
          distances.set(edge.getEnd(), newDist);
          priorityQueue.push(new Edge(edge.getEnd(), newDist));
        }
      }
    }

    return distances;
  }

  // 输出最短路径及其距离
  printShortestPath(start: string, end: string): void {
    const distances = this.dijkstra(start);
    const distance = distances.get(end);
    if (distance === Infinity) {
      console.log(`从 ${start} 到 ${end} 没有路径`);
    } else {
      console.log(`从 ${start} 到 ${end} 的最短距离是: ${distance} 公里`);
    }
  }

  // 获取邻接表
  getAdjacencyList(): Map<string, Edge[]> {
    return this.adjacencyList;
  }
}

// 测试代码
const graphPath = new GraphPath();
graphPath.addEdge("A", "B", 4);
graphPath.addEdge("A", "C", 2);
graphPath.addEdge("B", "C", 1);
graphPath.addEdge("B", "D", 5);
graphPath.addEdge("C", "D", 8);
graphPath.addEdge("C", "E", 10);
graphPath.addEdge("D", "E", 2);

console.log("各节点最短距离：");
const distances = graphPath.dijkstra("A");
distances.forEach((dist, vertex) => {
  console.log(`A -> ${vertex}: ${dist}`);
});

graphPath.printShortestPath("A", "E");

export { GraphPath, Edge };
