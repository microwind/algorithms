/*
*
 * Edmonds-Karp算法 - 使用BFS的最大流算法
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

public class EdmondsKarp {
    private int[][] graph;
    private int V;

    public EdmondsKarp(int V) {
        this.V = V;
        this.graph = new int[V][V];
    }

    public void addEdge(int u, int v, int capacity) {
        graph[u][v] = capacity;
    }

    /*
    *
     * BFS寻找增广路径
    */
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

    /*
    *
     * Edmonds-Karp算法
    */
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

    /*
    *
     * 主函数
    */
    public static void main(String[] args) {
        System.out.println("=== Edmonds-Karp算法 ===");

        EdmondsKarp ek = new EdmondsKarp(6);

        ek.addEdge(0, 1, 16);
        ek.addEdge(0, 2, 13);
        ek.addEdge(1, 2, 10);
        ek.addEdge(1, 3, 12);
        ek.addEdge(2, 1, 4);
        ek.addEdge(2, 4, 14);
        ek.addEdge(3, 2, 9);
        ek.addEdge(3, 5, 20);
        ek.addEdge(4, 3, 7);
        ek.addEdge(4, 5, 4);

        int s = 0, t = 5;
        int max_flow = ek.maxFlow(s, t);

        System.out.println("最大流量: " + max_flow);
    }
}
