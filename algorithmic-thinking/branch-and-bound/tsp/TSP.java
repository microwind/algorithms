/**
 * 旅行商题 - 分支定界算法 (Java)
 * 找到伺寻回路的最小成本
 */

public class TSP {
    private int[][] dist;
    private int n;
    private int minCost;
    private int[] bestPath;
    private int[] currentPath;
    private boolean[] visited;
    
    public TSP(int[][] distMatrix) {
        this.dist = distMatrix;
        this.n = distMatrix.length;
        this.minCost = Integer.MAX_VALUE;
        this.bestPath = new int[n];
        this.currentPath = new int[n];
        this.visited = new boolean[n];
    }
    
    private int lowerBound(int node, int level) {
        int bound = 0;
        int minEdge = Integer.MAX_VALUE;
        
        // 从当前节点到未访问城市找最小边
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                minEdge = Math.min(minEdge, dist[node][i]);
            }
        }
        
        if (minEdge != Integer.MAX_VALUE) {
            bound += minEdge;
        }
        
        // 估计剩余城市的但最小成本
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int min1 = Integer.MAX_VALUE, min2 = Integer.MAX_VALUE;
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && i != j) {
                        if (dist[i][j] < min1) {
                            min2 = min1;
                            min1 = dist[i][j];
                        } else if (dist[i][j] < min2) {
                            min2 = dist[i][j];
                        }
                    }
                }
                if (min2 != Integer.MAX_VALUE) {
                    bound += min1;
                }
            }
        }
        
        return bound;
    }
    
    private void branchAndBound(int node, int level, int cost) {
        // 剪枝
        if (lowerBound(node, level) >= minCost) {
            return;
        }
        
        // 基础情况
        if (level == n - 1) {
            int totalCost = cost + dist[node][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                System.arraycopy(currentPath, 0, bestPath, 0, n);
            }
            return;
        }
        
        // 分支
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = true;
                currentPath[level] = i;
                branchAndBound(i, level + 1, cost + dist[node][i]);
                visited[i] = false;
            }
        }
    }
    
    public int solve() {
        visited[0] = true;
        currentPath[0] = 0;
        branchAndBound(0, 1, 0);
        return minCost;
    }
    
    public int[] getPath() {
        int[] path = new int[n + 1];
        System.arraycopy(bestPath, 0, path, 0, n);
        path[n] = 0;
        return path;
    }
    
    public static void main(String[] args) {
        int[][] graph = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
        };
        
        System.out.println("TSP - Traveling Salesman Problem (Java)");
        System.out.println("=========================================");
        
        TSP solver = new TSP(graph);
        int minCost = solver.solve();
        int[] path = solver.getPath();
        
        System.out.println("\nDistance Matrix:");
        for (int[] row : graph) {
            for (int val : row) {
                System.out.printf("%3d ", val);
            }
            System.out.println();
        }
        
        System.out.printf("\nMinimum Tour Cost: %d\n", minCost);
        System.out.print("Tour: ");
        for (int i = 0; i < path.length; i++) {
            if (i > 0) System.out.print(" -> ");
            System.out.print(path[i]);
        }
        System.out.println();
    }
}
