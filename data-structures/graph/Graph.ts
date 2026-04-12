/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 
 *  图数据结构基础实现（TypeScript）
 *  功能：使用邻接表表示无向图，支持添加边和打印图结构
 *  用途：学习图的基本概念，理解邻接表存储方式
 */

// 图类 - 使用邻接表实现
class Graph {
  private numVertices: number;
  private adjLists: number[][];

  constructor(vertices: number) {
    this.numVertices = vertices;
    this.adjLists = Array.from({ length: vertices }, () => []);
  }

  // 添加边（无向图：双向添加）
  addEdge(src: number, dest: number): void {
    this.adjLists[src].push(dest);
    this.adjLists[dest].push(src);
  }

  // 打印图的邻接表
  printGraph(): void {
    console.log(this.adjLists);
    for (let v = 0; v < this.numVertices; v++) {
      let str = `Vertex ${v}:`;
      this.adjLists[v].forEach(dest => {
        str += ` -> ${dest}`;
      });
      console.log(str);
    }
  }

  // 获取顶点数量
  getNumVertices(): number {
    return this.numVertices;
  }

  // 获取邻接表
  getAdjLists(): number[][] {
    return this.adjLists;
  }
}

// 测试代码
const graph = new Graph(4);
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.addEdge(1, 2);
graph.addEdge(2, 3);

graph.printGraph();

export { Graph };
