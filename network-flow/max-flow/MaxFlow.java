/*
*
 * 最大流算法 - 使用Edmonds-Karp (BFS)
 *
 * 问题：在流网络中找到从源点到汇点的最大流量
 *
 * 核心思想：
 * - 使用BFS寻找最短增广路径
 * - 沿增广路径增加流量
 * - 更新残差网络
 *
 * 时间复杂度: O(VE²)
 * 空间复杂度: O(V + E)
*/

import java.util.*;

public class MaxFlow {
    private int[][] graph;
    private int V;

    public MaxFlow(int V) {
        this.V = V;
        this.graph = new int[V][V];
    }

    public void addEdge(int u, int v, int capacity) {
        graph[u][v] = capacity;
    }

    private boolean bfs(int rGraph[][], int s, int t, int parent[]) {
        boolean visited[] = new boolean[V];
        Queue<Integer> queue = new LinkedList<>();

        queue.add(s);
        visited[s] = true;
        parent[s] = -1;

        while (!queue.isEmpty()) {
            int u = queue.poll();

            for (int v = 0; v < V; v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    queue.add(v);
                    parent[v] = u;
                    visited[v] = true;

                    if (v == t) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    public int maxFlow(int s, int t) {
        int u, v;
        int rGraph[][] = new int[V][V];
        int parent[] = new int[V];
        int max_flow = 0;

        for (u = 0; u < V; u++) {
            for (v = 0; v < V; v++) {
                rGraph[u][v] = graph[u][v];
            }
        }

        while (bfs(rGraph, s, t, parent)) {
            int path_flow = Integer.MAX_VALUE;

            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                path_flow = Math.min(path_flow, rGraph[u][v]);
            }

            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }

    public static void main(String[] args) {
        System.out.println("=== 最大流算法 ===");

        MaxFlow mf = new MaxFlow(6);

        mf.addEdge(0, 1, 16);
        mf.addEdge(0, 2, 13);
        mf.addEdge(1, 2, 10);
        mf.addEdge(1, 3, 12);
        mf.addEdge(2, 1, 4);
        mf.addEdge(2, 4, 14);
        mf.addEdge(3, 2, 9);
        mf.addEdge(3, 5, 20);
        mf.addEdge(4, 3, 7);
        mf.addEdge(4, 5, 4);

        int s = 0, t = 5;
        int max_flow = mf.maxFlow(s, t);

        System.out.println("最大流量: " + max_flow);
    }
}
