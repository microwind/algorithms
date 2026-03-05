package search.bfs;

import java.util.*;

/**
 * 广度优先搜索（BFS）- Java 版本
 *
 * - bfsTraversal: 从起点开始按层遍历所有可达节点
 * - bfsShortestPath: 在无权图中找到起点到终点的一条最短路径
 *
 * 时间复杂度：O(V + E)
 * 空间复杂度：O(V)
 */
public class Bfs {

    // BFS 遍历
    public static List<String> bfsTraversal(Map<String, List<String>> graph, String start) {
        List<String> order = new ArrayList<>();
        Set<String> visited = new HashSet<>();
        Queue<String> queue = new ArrayDeque<>();

        visited.add(start);
        queue.offer(start);

        while (!queue.isEmpty()) {
            String node = queue.poll();
            order.add(node);
            for (String neighbor : graph.getOrDefault(node, Collections.emptyList())) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.offer(neighbor);
                }
            }
        }
        return order;
    }

    // BFS 最短路径（无权图）
    public static List<String> bfsShortestPath(Map<String, List<String>> graph, String start, String end) {
        if (start.equals(end)) {
            return Collections.singletonList(start);
        }
        Queue<List<String>> queue = new ArrayDeque<>();
        Set<String> visited = new HashSet<>();

        queue.offer(Collections.singletonList(start));
        visited.add(start);

        while (!queue.isEmpty()) {
            List<String> path = queue.poll();
            String node = path.get(path.size() - 1);

            for (String neighbor : graph.getOrDefault(node, Collections.emptyList())) {
                if (!visited.contains(neighbor)) {
                    List<String> newPath = new ArrayList<>(path);
                    newPath.add(neighbor);
                    if (neighbor.equals(end)) {
                        return newPath;
                    }
                    visited.add(neighbor);
                    queue.offer(newPath);
                }
            }
        }
        return null;
    }

    public static void main(String[] args) {
        System.out.println("========== BFS (Java) ==========");
        Map<String, List<String>> graph = new HashMap<>();
        graph.put("A", Arrays.asList("B", "C"));
        graph.put("B", Arrays.asList("A", "D", "E"));
        graph.put("C", Arrays.asList("A", "F"));
        graph.put("D", Collections.singletonList("B"));
        graph.put("E", Arrays.asList("B", "F"));
        graph.put("F", Arrays.asList("C", "E"));

        System.out.println("图: " + graph);
        System.out.println("BFS 遍历从 A 开始 -> " + bfsTraversal(graph, "A"));
        System.out.println("A 到 F 的最短路径 -> " + bfsShortestPath(graph, "A", "F"));
    }
}

