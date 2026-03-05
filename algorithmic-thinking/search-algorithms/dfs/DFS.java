/**
 * 深度优先搜索（DFS）实现 (Java)
 * 
 * 特点：
 * - 优先往纵深方向探索
 * - 使用栈或递归
 * - 回溯机制
 * - 时间复杂度：O(V + E)
 * - 空间复杂度：O(V)
 */

import java.util.*;

public class DFS {
    
    // 图结构（邻接表）
    static class Graph {
        private List<List<Integer>> adjLists;
        private int numVertices;
        
        public Graph(int vertices) {
            this.numVertices = vertices;
            this.adjLists = new ArrayList<>(vertices);
            for (int i = 0; i < vertices; i++) {
                this.adjLists.add(new ArrayList<>());
            }
        }
        
        // 添加边（无向图）
        public void addEdge(int src, int dest) {
            adjLists.get(src).add(dest);
            adjLists.get(dest).add(src); // 无向图
        }
        
        // 获取邻接顶点
        public List<Integer> getAdjVertices(int vertex) {
            return adjLists.get(vertex);
        }
        
        public int getNumVertices() {
            return numVertices;
        }
    }
    
    // DFS递归实现
    private static void dfsRecursive(Graph graph, int vertex, boolean[] visited, List<Integer> result) {
        // 标记当前顶点为已访问
        visited[vertex] = true;
        result.add(vertex);
        
        // 递归访问所有未访问的邻接顶点
        for (int adjVertex : graph.getAdjVertices(vertex)) {
            if (!visited[adjVertex]) {
                dfsRecursive(graph, adjVertex, visited, result);
            }
        }
    }
    
    // DFS递归遍历（包装函数）
    public static List<Integer> dfsRecursiveTraversal(Graph graph, int startVertex) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        List<Integer> result = new ArrayList<>();
        
        dfsRecursive(graph, startVertex, visited, result);
        return result;
    }
    
    // DFS迭代实现（使用栈）
    public static List<Integer> dfsIterative(Graph graph, int startVertex) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        Stack<Integer> stack = new Stack<>();
        List<Integer> result = new ArrayList<>();
        
        // 将起始顶点入栈
        stack.push(startVertex);
        
        while (!stack.isEmpty()) {
            // 出栈一个顶点
            int currentVertex = stack.pop();
            
            // 如果该顶点未被访问
            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                result.add(currentVertex);
                
                // 将所有未访问的邻接顶点入栈
                // 注意：为了保持与递归相似的顺序，需要反向入栈
                List<Integer> neighbors = graph.getAdjVertices(currentVertex);
                for (int i = neighbors.size() - 1; i >= 0; i--) {
                    int adjVertex = neighbors.get(i);
                    if (!visited[adjVertex]) {
                        stack.push(adjVertex);
                    }
                }
            }
        }
        
        return result;
    }
    
    // DFS查找路径
    private static boolean dfsFindPath(Graph graph, int current, int target, 
                                      boolean[] visited, List<Integer> path) {
        // 标记当前顶点为已访问
        visited[current] = true;
        path.add(current);
        
        // 如果找到目标
        if (current == target) {
            return true;
        }
        
        // 递归访问所有邻接顶点
        for (int adjVertex : graph.getAdjVertices(current)) {
            if (!visited[adjVertex]) {
                if (dfsFindPath(graph, adjVertex, target, visited, path)) {
                    return true;
                }
            }
        }
        
        // 回溯：从路径中移除当前顶点
        path.remove(path.size() - 1);
        return false;
    }
    
    // 查找两点之间的路径
    public static List<Integer> findPath(Graph graph, int start, int end) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        List<Integer> path = new ArrayList<>();
        
        if (dfsFindPath(graph, start, end, visited, path)) {
            return path;
        }
        return null;
    }
    
    // DFS检测环
    private static boolean dfsDetectCycle(Graph graph, int vertex, int parent, boolean[] visited) {
        visited[vertex] = true;
        
        for (int adjVertex : graph.getAdjVertices(vertex)) {
            // 如果邻接顶点未被访问，递归检查
            if (!visited[adjVertex]) {
                if (dfsDetectCycle(graph, adjVertex, vertex, visited)) {
                    return true;
                }
            }
            // 如果邻接顶点已被访问且不是父节点，则存在环
            else if (adjVertex != parent) {
                return true;
            }
        }
        
        return false;
    }
    
    // 检测图中是否存在环
    public static boolean hasCycle(Graph graph) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        
        for (int i = 0; i < graph.getNumVertices(); i++) {
            if (!visited[i]) {
                if (dfsDetectCycle(graph, i, -1, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    // DFS计算连通分量
    public static List<List<Integer>> dfsConnectedComponents(Graph graph) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        List<List<Integer>> components = new ArrayList<>();
        
        for (int i = 0; i < graph.getNumVertices(); i++) {
            if (!visited[i]) {
                List<Integer> component = new ArrayList<>();
                dfsRecursive(graph, i, visited, component);
                components.add(component);
            }
        }
        
        return components;
    }
    
    // DFS拓扑排序（用于有向无环图）
    public static List<Integer> dfsTopologicalSort(Graph graph) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        Stack<Integer> stack = new Stack<>();
        
        // 对每个未访问的顶点进行DFS
        for (int i = 0; i < graph.getNumVertices(); i++) {
            if (!visited[i]) {
                topologicalSortUtil(graph, i, visited, stack);
            }
        }
        
        // 弹出栈中的元素得到拓扑排序
        List<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            result.add(stack.pop());
        }
        
        return result;
    }
    
    // 拓扑排序的辅助函数
    private static void topologicalSortUtil(Graph graph, int vertex, 
                                           boolean[] visited, Stack<Integer> stack) {
        visited[vertex] = true;
        
        for (int adjVertex : graph.getAdjVertices(vertex)) {
            if (!visited[adjVertex]) {
                topologicalSortUtil(graph, adjVertex, visited, stack);
            }
        }
        
        // 将顶点入栈
        stack.push(vertex);
    }
    
    // DFS检测强连通分量（用于有向图）
    public static List<List<Integer>> dfsStronglyConnectedComponents(Graph graph) {
        // Kosaraju算法
        boolean[] visited = new boolean[graph.getNumVertices()];
        Stack<Integer> stack = new Stack<>();
        
        // 第一步：对原图进行DFS，将顶点按完成时间入栈
        for (int i = 0; i < graph.getNumVertices(); i++) {
            if (!visited[i]) {
                fillOrder(graph, i, visited, stack);
            }
        }
        
        // 第二步：创建转置图
        Graph transposed = getTranspose(graph);
        
        // 第三步：按栈中顺序对转置图进行DFS
        Arrays.fill(visited, false);
        List<List<Integer>> components = new ArrayList<>();
        
        while (!stack.isEmpty()) {
            int vertex = stack.pop();
            if (!visited[vertex]) {
                List<Integer> component = new ArrayList<>();
                dfsRecursive(transposed, vertex, visited, component);
                components.add(component);
            }
        }
        
        return components;
    }
    
    // 填充顺序的辅助函数
    private static void fillOrder(Graph graph, int vertex, boolean[] visited, Stack<Integer> stack) {
        visited[vertex] = true;
        
        for (int adjVertex : graph.getAdjVertices(vertex)) {
            if (!visited[adjVertex]) {
                fillOrder(graph, adjVertex, visited, stack);
            }
        }
        
        stack.push(vertex);
    }
    
    // 获取转置图
    private static Graph getTranspose(Graph graph) {
        Graph transposed = new Graph(graph.getNumVertices());
        
        for (int v = 0; v < graph.getNumVertices(); v++) {
            for (int adjVertex : graph.getAdjVertices(v)) {
                transposed.adjLists.get(adjVertex).add(v);
            }
        }
        
        return transposed;
    }
    
    // 检查是否为二分图
    public static boolean isBipartite(Graph graph) {
        int[] color = new int[graph.getNumVertices()]; // 0: 未染色, 1: 染色A, -1: 染色B
        
        for (int i = 0; i < graph.getNumVertices(); i++) {
            if (color[i] == 0) {
                Stack<Integer> stack = new Stack<>();
                color[i] = 1;
                stack.push(i);
                
                while (!stack.isEmpty()) {
                    int currentVertex = stack.pop();
                    
                    for (int adjVertex : graph.getAdjVertices(currentVertex)) {
                        if (color[adjVertex] == 0) {
                            color[adjVertex] = -color[currentVertex];
                            stack.push(adjVertex);
                        } else if (color[adjVertex] == color[currentVertex]) {
                            return false;
                        }
                    }
                }
            }
        }
        
        return true;
    }
    
    // 打印列表
    private static void printList(List<Integer> list) {
        System.out.print("[");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i));
            if (i < list.size() - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }
    
    // 打印连通分量
    private static void printComponents(List<List<Integer>> components) {
        for (int i = 0; i < components.size(); i++) {
            System.out.print("分量 " + (i + 1) + ": ");
            printList(components.get(i));
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== 深度优先搜索（DFS）演示 ===\n");
        
        // 创建图
        Graph graph = new Graph(8);
        
        // 添加边
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 5);
        graph.addEdge(2, 6);
        graph.addEdge(3, 7);
        graph.addEdge(4, 7);
        graph.addEdge(5, 6);
        
        System.out.println("图结构:");
        System.out.println("0 -- 1 -- 3 -- 7");
        System.out.println("|    |         |");
        System.out.println("|    |         |");
        System.out.println("2 -- 4 --------|");
        System.out.println("|    |");
        System.out.println("|    |");
        System.out.println("5 -- 6\n");
        
        // 1. DFS递归遍历
        System.out.println("1. DFS递归遍历（从顶点0开始）");
        List<Integer> recursiveResult = dfsRecursiveTraversal(graph, 0);
        System.out.print("结果: ");
        printList(recursiveResult);
        System.out.println();
        
        // 2. DFS迭代遍历
        System.out.println("2. DFS迭代遍历（从顶点0开始）");
        List<Integer> iterativeResult = dfsIterative(graph, 0);
        System.out.print("结果: ");
        printList(iterativeResult);
        System.out.println();
        
        // 3. 查找路径
        System.out.println("3. 查找路径");
        List<Integer> path = findPath(graph, 0, 7);
        if (path != null) {
            System.out.print("从 0 到 7 的路径: ");
            printList(path);
        } else {
            System.out.println("未找到从 0 到 7 的路径");
        }
        System.out.println();
        
        // 4. 检测环
        System.out.println("4. 检测环");
        if (hasCycle(graph)) {
            System.out.println("图中存在环");
        } else {
            System.out.println("图中不存在环");
        }
        System.out.println();
        
        // 5. 计算连通分量
        System.out.println("5. 计算连通分量");
        List<List<Integer>> components = dfsConnectedComponents(graph);
        System.out.println("连通分量数: " + components.size());
        printComponents(components);
        System.out.println();
        
        // 6. 从不同起点开始DFS
        System.out.println("6. 从不同起点开始DFS");
        System.out.print("从顶点3开始（递归）: ");
        printList(dfsRecursiveTraversal(graph, 3));
        System.out.print("从顶点3开始（迭代）: ");
        printList(dfsIterative(graph, 3));
        
        // 7. 检查是否为二分图
        System.out.println("\n7. 检查是否为二分图");
        if (isBipartite(graph)) {
            System.out.println("该图是二分图");
        } else {
            System.out.println("该图不是二分图");
        }
    }
}
