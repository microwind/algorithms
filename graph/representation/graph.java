/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 图的邻接表表示实现
 * 使用链表存储图的邻接关系
 */

class GraphRep {
    private static final int V = 5;
    
    static class Node {
        int dest;
        Node next;
        
        Node(int dest) {
            this.dest = dest;
            this.next = null;
        }
    }
    
    Node[] adjList;
    
    GraphRep() {
        adjList = new Node[V];
        for (int i = 0; i < V; i++) {
            adjList[i] = null;
        }
    }
    
    void addEdge(int src, int dest) {
        Node newNode = new Node(dest);
        newNode.next = adjList[src];
        adjList[src] = newNode;
    }
    
    void printGraph() {
        for (int i = 0; i < V; i++) {
            System.out.print("Adjacency list of vertex " + i + ": ");
            Node temp = adjList[i];
            while (temp != null) {
                System.out.print(" -> " + temp.dest);
                temp = temp.next;
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        GraphRep graph = new GraphRep();
        graph.addEdge(0, 1);
        graph.addEdge(0, 3);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 4);
        graph.addEdge(3, 4);
        
        graph.printGraph();
    }
}
