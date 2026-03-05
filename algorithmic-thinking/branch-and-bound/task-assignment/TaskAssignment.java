/**
 * 任务分配 - 分支定界算法 (Java)
 */

public class TaskAssignment {
    private int[][] cost;
    private int n;
    private int minCost;
    private int[] bestAssignment;
    private int[] currentAssignment;
    private boolean[] assignedWorkers;
    
    public TaskAssignment(int[][] costMatrix) {
        this.cost = costMatrix;
        this.n = costMatrix.length;
        this.minCost = Integer.MAX_VALUE;
        this.bestAssignment = new int[n];
        this.currentAssignment = new int[n];
        this.assignedWorkers = new boolean[n];
    }
    
    private int lowerBound(int taskIdx) {
        int bound = 0;
        // 对于每个未分配任务，添加最小成本下界
        for (int i = taskIdx; i < n; i++) {
            int minCost = Integer.MAX_VALUE;
            for (int j = 0; j < n; j++) {
                if (!assignedWorkers[j]) {
                    minCost = Math.min(minCost, cost[i][j]);
                }
            }
            if (minCost != Integer.MAX_VALUE) {
                bound += minCost;
            }
        }
        return bound;
    }
    
    private void branchAndBound(int taskIdx, int currentCost) {
        if (currentCost + lowerBound(taskIdx) >= minCost) {
            return;
        }
        
        if (taskIdx == n) {
            if (currentCost < minCost) {
                minCost = currentCost;
                System.arraycopy(currentAssignment, 0, bestAssignment, 0, n);
            }
            return;
        }
        
        for (int worker = 0; worker < n; worker++) {
            if (!assignedWorkers[worker]) {
                currentAssignment[taskIdx] = worker;
                assignedWorkers[worker] = true;
                
                branchAndBound(taskIdx + 1, currentCost + cost[taskIdx][worker]);
                
                assignedWorkers[worker] = false;
            }
        }
    }
    
    public int solve() {
        branchAndBound(0, 0);
        return minCost;
    }
    
    public int[] getAssignment() {
        return bestAssignment;
    }
    
    public static void main(String[] args) {
        int[][] costMatrix = {
            {5, 7, 9},
            {6, 8, 4},
            {3, 5, 7}
        };
        
        System.out.println("Task Assignment Problem (Java)");
        System.out.println("==============================\n");
        
        System.out.println("Cost Matrix:");
        System.out.println("Task \\ Worker  0   1   2");
        for (int i = 0; i < costMatrix.length; i++) {
            System.out.printf("   %d         ", i);
            for (int j = 0; j < costMatrix[i].length; j++) {
                System.out.printf("%2d  ", costMatrix[i][j]);
            }
            System.out.println();
        }
        
        TaskAssignment solver = new TaskAssignment(costMatrix);
        int minCost = solver.solve();
        int[] assignment = solver.getAssignment();
        
        System.out.printf("\nMinimum Cost: %d\n", minCost);
        System.out.println("\nOptimal Assignment:");
        System.out.println("Task -> Worker");
        for (int task = 0; task < assignment.length; task++) {
            System.out.printf(" %d   ->   %d    (cost: %d)\n", 
                task, assignment[task], costMatrix[task][assignment[task]]);
        }
    }
}
