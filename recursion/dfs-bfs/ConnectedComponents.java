/**
 * 图的DFS - 连通分量检测
 * 使用递归DFS找出图中的所有连通分量
 */
public class ConnectedComponents {
    
    private static final int MAX_VERTICES = 100;
    private int[][] graph;
    private boolean[] visited;
    private int numVertices;
    
    public ConnectedComponents(int numVertices) {
        this.numVertices = numVertices;
        this.graph = new int[MAX_VERTICES][MAX_VERTICES];
        this.visited = new boolean[MAX_VERTICES];
    }
    
    /**
     * DFS递归遍历
     * @param vertex 当前顶点
     */
    private void dfs(int vertex) {
        // 标记当前顶点为已访问
        visited[vertex] = true;
        System.out.print(vertex + " ");
        
        // 递归访问所有未访问的邻居
        for (int i = 0; i < numVertices; i++) {
            if (graph[vertex][i] == 1 && !visited[i]) {
                dfs(i);
            }
        }
    }
    
    /**
     * 查找所有连通分量
     */
    public void findConnectedComponents() {
        int componentCount = 0;
        
        System.out.println("连通分量检测:\n");
        
        // 初始化访问数组
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
        
        // 遍历所有顶点，对每个未访问的顶点进行DFS
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                componentCount++;
                System.out.print("连通分量 " + componentCount + ": ");
                dfs(i);
                System.out.println();
            }
        }
        
        System.out.println("\n总共找到 " + componentCount + " 个连通分量");
    }
    
    /**
     * 添加边
     * @param from 起始顶点
     * @param to 目标顶点
     */
    public void addEdge(int from, int to) {
        graph[from][to] = 1;
        graph[to][from] = 1;
    }
    
    public static void main(String[] args) {
        // 创建一个示例图（两个连通分量）
        // 分量1: 0-1-2
        // 分量2: 3-4
        int numVertices = 5;
        ConnectedComponents cc = new ConnectedComponents(numVertices);
        
        // 添加边
        cc.addEdge(0, 1);
        cc.addEdge(1, 2);
        cc.addEdge(3, 4);
        
        System.out.println("图结构:");
        System.out.println("  分量1: 0 -- 1 -- 2");
        System.out.println("  分量2: 3 -- 4\n");
        
        cc.findConnectedComponents();
    }
}
