/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 拓扑排序 (Topological Sort)
 * 使用Kahn算法（基于BFS）对有向无环图进行拓扑排序
 */

import java.util.*;

class TopologicalSort {
    
    /**
     * Kahn算法实现拓扑排序
     * @param graph 邻接表表示的有向图
     * @param numVertices 顶点数量
     * @return 拓扑排序结果列表，如果存在环则返回空列表
     */
    public static List<Integer> topologicalSort(Map<Integer, List<Integer>> graph, int numVertices) {
        int[] inDegree = new int[numVertices];
        
        // 计算每个顶点的入度
        for (List<Integer> neighbors : graph.values()) {
            for (int v : neighbors) {
                inDegree[v]++;
            }
        }
        
        // 将所有入度为0的顶点加入队列
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numVertices; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
            }
        }
        
        List<Integer> result = new ArrayList<>();
        
        while (!queue.isEmpty()) {
            int u = queue.poll();
            result.add(u);
            
            // 将u的所有邻居的入度减1
            for (int v : graph.getOrDefault(u, new ArrayList<>())) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue.offer(v);
                }
            }
        }
        
        // 检查是否存在环
        if (result.size() != numVertices) {
            return new ArrayList<>(); // 存在环
        }
        
        return result;
    }
    
    public static void main(String[] args) {
        Map<Integer, List<Integer>> graph = new HashMap<>();
        graph.put(0, Arrays.asList(1));
        graph.put(1, Arrays.asList(2, 3));
        graph.put(2, Arrays.asList(3));
        graph.put(3, new ArrayList<>());
        
        int numVertices = 4;
        
        System.out.println("=".repeat(50));
        System.out.println("拓扑排序 (Topological Sort)");
        System.out.println("=".repeat(50));
        
        List<Integer> result = topologicalSort(graph, numVertices);
        
        if (!result.isEmpty()) {
            System.out.println("\n拓扑排序结果: " + result);
        } else {
            System.out.println("\n图中存在环，无法进行拓扑排序");
        }
    }
}
