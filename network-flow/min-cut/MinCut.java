/*
*
 * 最小割算法 - 基于最大流
 *
 * 问题：找到容量最小的割，使源点和汇点不再连通
 *
 * 核心思想：
 * - 使用最大流算法计算最大流
 * - 在残差网络中从源点BFS标记可达顶点
 * - 从可达集到不可达集的边即为最小割
 *
 * 时间复杂度: O(VE²)
 * 空间复杂度: O(V + E)
*/

import java.util.*;

public class MinCut {
    private int[][] graph;
    private int V;

    public MinCut(int V) {
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

    private int maxFlow(int s, int t, int rGraph[][]) {
        int parent[] = new int[V];
        int max_flow = 0;

        while (bfs(rGraph, s, t, parent)) {
            int path_flow = Integer.MAX_VALUE;

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                path_flow = Math.min(path_flow, rGraph[u][v]);
            }

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }

    public void minCut(int s, int t) {
        int rGraph[][] = new int[V][V];

        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                rGraph[u][v] = graph[u][v];
            }
        }

        int max_flow = maxFlow(s, t, rGraph);
        System.out.println("最大流量: " + max_flow);

        boolean visited[] = new boolean[V];
        Queue<Integer> queue = new LinkedList<>();

        queue.add(s);
        visited[s] = true;

        while (!queue.isEmpty()) {
            int u = queue.poll();

            for (int v = 0; v < V; v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    queue.add(v);
                    visited[v] = true;
                }
            }
        }

        System.out.println("最小割边:");
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (visited[u] && !visited[v] && graph[u][v] > 0) {
                    System.out.println("  " + u + " -> " + v + " (容量: " + graph[u][v] + ")");
                }
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("=== 最小割算法 ===");

        MinCut mc = new MinCut(6);

        mc.addEdge(0, 1, 16);
        mc.addEdge(0, 2, 13);
        mc.addEdge(1, 2, 10);
        mc.addEdge(1, 3, 12);
        mc.addEdge(2, 1, 4);
        mc.addEdge(2, 4, 14);
        mc.addEdge(3, 2, 9);
        mc.addEdge(3, 5, 20);
        mc.addEdge(4, 3, 7);
        mc.addEdge(4, 5, 4);

        int s = 0, t = 5;
        mc.minCut(s, t);
    }
}
