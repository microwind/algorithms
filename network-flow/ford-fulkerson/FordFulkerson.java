/*
*
 * Ford-Fulkerson算法 - 使用DFS的最大流算法
 *
 * 问题：在流网络中找到从源点到汇点的最大流量
 *
 * 核心思想：
 * - 使用DFS寻找增广路径
 * - 沿增广路径增加流量
 * - 更新残差网络
 *
 * 时间复杂度: O(E * max_flow)
 * 空间复杂度: O(V + E)
*/

public class FordFulkerson {
    private int[][] graph;
    private int V;

    public FordFulkerson(int V) {
        this.V = V;
        this.graph = new int[V][V];
    }

    public void addEdge(int u, int v, int capacity) {
        graph[u][v] = capacity;
    }

    private int dfs(int rGraph[][], int u, int t, boolean visited[], int min_flow) {
        if (u == t) {
            return min_flow;
        }

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                int flow = dfs(rGraph, v, t, visited, Math.min(min_flow, rGraph[u][v]));

                if (flow > 0) {
                    rGraph[u][v] -= flow;
                    rGraph[v][u] += flow;
                    return flow;
                }
            }
        }

        return 0;
    }

    public int maxFlow(int s, int t) {
        int rGraph[][] = new int[V][V];
        int max_flow = 0;

        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                rGraph[u][v] = graph[u][v];
            }
        }

        while (true) {
            boolean visited[] = new boolean[V];
            int path_flow = dfs(rGraph, s, t, visited, Integer.MAX_VALUE);

            if (path_flow == 0) {
                break;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }

    public static void main(String[] args) {
        System.out.println("=== Ford-Fulkerson算法 ===");

        FordFulkerson ff = new FordFulkerson(6);

        ff.addEdge(0, 1, 16);
        ff.addEdge(0, 2, 13);
        ff.addEdge(1, 2, 10);
        ff.addEdge(1, 3, 12);
        ff.addEdge(2, 1, 4);
        ff.addEdge(2, 4, 14);
        ff.addEdge(3, 2, 9);
        ff.addEdge(3, 5, 20);
        ff.addEdge(4, 3, 7);
        ff.addEdge(4, 5, 4);

        int s = 0, t = 5;
        int max_flow = ff.maxFlow(s, t);

        System.out.println("最大流量: " + max_flow);
    }
}
