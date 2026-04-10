/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * Dijkstra最短路径算法实现
 * 使用贪心策略，适用于非负权重的图
 * 
 * 时间复杂度: O(V²)，使用优先队列可优化至O((V+E)logV)
 * 空间复杂度: O(V)，用于存储距离和访问标记
 */

class GraphDijkstra {
    
    private static final int V = 6;
    private static final int INF = Integer.MAX_VALUE;
    
    /**
     * 找到距离最小的未处理顶点
     * @param dist 距离数组
     * @param visited 访问标记数组
     * @return 最小距离顶点的索引
     */
    private static int minDistance(int[] dist, boolean[] visited) {
        int min = INF;
        int minIndex = -1;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
    
    /**
     * Dijkstra算法实现
     * @param graph 邻接矩阵表示的图
     * @param src 源顶点
     */
    public static void dijkstra(int[][] graph, int src) {
        int[] dist = new int[V];    // 存储最短距离
        boolean[] visited = new boolean[V]; // 访问标记
        
        // 初始化距离数组
        for (int i = 0; i < V; i++) {
            dist[i] = INF;
            visited[i] = false;
        }
        dist[src] = 0;
        
        // 遍历所有顶点
        for (int count = 0; count < V - 1; count++) {
            // 选择距离最小的未处理顶点
            int u = minDistance(dist, visited);
            visited[u] = true;
            
            // 更新邻接顶点的距离
            for (int v = 0; v < V; v++) {
                if (!visited[v] && graph[u][v] != 0 && 
                    dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
        
        // 打印结果
        printSolution(dist);
    }
    
    private static void printSolution(int[] dist) {
        System.out.println("Vertex \t Distance from Source");
        for (int i = 0; i < V; i++) {
            System.out.println(i + " \t " + dist[i]);
        }
    }
    
    public static void main(String[] args) {
        int[][] graph = {
            {0, 4, 0, 0, 0, 0},
            {4, 0, 8, 0, 0, 0},
            {0, 8, 0, 7, 0, 4},
            {0, 0, 7, 0, 9, 14},
            {0, 0, 0, 9, 0, 10},
            {0, 0, 4, 14, 10, 0}
        };
        
        dijkstra(graph, 0);
    }
}
