import java.util.*;

/**
 * 图的深度优先搜索 (DFS) 和广度优先搜索 (BFS)
 * 使用递归实现DFS，使用队列实现BFS
 */
public class GraphTraversal {
    
    private Map<Character, List<Character>> graph;
    
    public GraphTraversal() {
        this.graph = new HashMap<>();
    }
    
    /**
     * 添加边
     * @param src 源顶点
     * @param dest 目标顶点
     */
    public void addEdge(char src, char dest) {
        // 添加 src -> dest
        graph.computeIfAbsent(src, k -> new ArrayList<>()).add(dest);
        // 添加 dest -> src (无向图)
        graph.computeIfAbsent(dest, k -> new ArrayList<>()).add(src);
    }
    
    /**
     * 深度优先搜索 - 递归实现
     * 沿着一条路径尽可能深地搜索，直到无法继续才回溯
     * @param node 当前节点
     * @param visited 已访问节点集合
     */
    public Set<Character> dfsRecursive(char node, Set<Character> visited) {
        // 访问当前节点
        visited.add(node);
        System.out.println("DFS访问: " + node);
        
        // 递归访问所有未访问的邻居
        for (char neighbor : graph.getOrDefault(node, new ArrayList<>())) {
            if (!visited.contains(neighbor)) {
                dfsRecursive(neighbor, visited);
            }
        }
        
        return visited;
    }
    
    public Set<Character> dfsRecursive(char node) {
        return dfsRecursive(node, new HashSet<>());
    }
    
    /**
     * 广度优先搜索 - 迭代实现（使用队列）
     * 逐层遍历，先访问所有邻居，再访问邻居的邻居
     * @param start 起始节点
     * @return 已访问节点集合
     */
    public Set<Character> bfsIterative(char start) {
        Set<Character> visited = new HashSet<>();
        Queue<Character> queue = new LinkedList<>();
        
        visited.add(start);
        queue.add(start);
        
        System.out.println("\nBFS遍历:");
        while (!queue.isEmpty()) {
            char node = queue.poll();
            System.out.println("BFS访问: " + node);
            
            // 将所有未访问的邻居加入队列
            for (char neighbor : graph.getOrDefault(node, new ArrayList<>())) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                }
            }
        }
        
        return visited;
    }
    
    public static void main(String[] args) {
        GraphTraversal gt = new GraphTraversal();
        
        // 创建示例图
        gt.addEdge('A', 'B');
        gt.addEdge('A', 'C');
        gt.addEdge('B', 'D');
        gt.addEdge('B', 'E');
        gt.addEdge('C', 'F');
        gt.addEdge('E', 'F');
        
        System.out.println("图结构:");
        System.out.println("    A");
        System.out.println("   / \\");
        System.out.println("  B---C");
        System.out.println("  |   |");
        System.out.println("  D E--F");
        System.out.println();
        
        System.out.println("==============================");
        System.out.println("DFS深度优先遍历:");
        gt.dfsRecursive('A');
        
        gt.bfsIterative('A');
    }
}
