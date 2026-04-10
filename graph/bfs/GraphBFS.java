/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 图的广度优先搜索（BFS）算法实现
 * 使用队列数据结构，按层次遍历图
 * 
 * 时间复杂度: O(V + E)，其中V是顶点数，E是边数
 * 空间复杂度: O(V)，用于存储访问标记和队列
 */

import java.util.LinkedList;
import java.util.Queue;

class GraphBFS {
    
    private static final int V = 5;
    
    /**
     * 广度优先搜索遍历
     * @param graph 邻接矩阵表示的图
     * @param start 起始顶点
     */
    public static void bfs(int[][] graph, int start) {
        // 使用队列存储待访问的顶点
        Queue<Integer> queue = new LinkedList<>();
        // 访问标记数组
        boolean[] visited = new boolean[V];
        
        // 将起始顶点入队并标记为已访问
        queue.offer(start);
        visited[start] = true;
        
        System.out.println("BFS traversal:");
        
        // 当队列不为空时继续遍历
        while (!queue.isEmpty()) {
            // 出队一个顶点
            int vertex = queue.poll();
            System.out.println("Visited " + vertex);
            
            // 遍历所有邻接顶点
            for (int i = 0; i < V; i++) {
                // 如果存在边且未被访问，则入队
                if (graph[vertex][i] == 1 && !visited[i]) {
                    queue.offer(i);
                    visited[i] = true;
                }
            }
        }
    }
    
    public static void main(String[] args) {
        // 邻接矩阵表示的无向图
        int[][] graph = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1},
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0}
        };
        
        bfs(graph, 0);
    }
}

/*打印结果
jarry@Mac bfs % java GraphBFS.java
BFS traversal:
Visited 0
Visited 1
Visited 3
Visited 2
*/