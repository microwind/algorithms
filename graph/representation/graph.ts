/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 图的邻接表表示实现
 * 使用链表存储图的邻接关系
 */

const V: number = 5;

class Node {
    dest: number;
    next: Node | null;
    
    constructor(dest: number) {
        this.dest = dest;
        this.next = null;
    }
}

class Graph {
    adjList: (Node | null)[];
    
    constructor() {
        this.adjList = new Array(V).fill(null);
    }
    
    addEdge(src: number, dest: number): void {
        const newNode = new Node(dest);
        newNode.next = this.adjList[src];
        this.adjList[src] = newNode;
    }
    
    printGraph(): void {
        for (let i = 0; i < V; i++) {
            let result = `Adjacency list of vertex ${i}: `;
            let temp = this.adjList[i];
            while (temp !== null) {
                result += ` -> ${temp.dest}`;
                temp = temp.next;
            }
            console.log(result);
        }
    }
}

function main(): void {
    const graph = new Graph();
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    
    graph.printGraph();
}

main();
export { Graph, Node };
