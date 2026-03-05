/**
 * 0-1 背包优化 - 分支定界算法 (Java)
 */

public class KnapsackOptimization {
    private int[] weights;
    private int[] values;
    private int capacity;
    private int n;
    private int maxProfit;
    private boolean[] bestItems;
    private boolean[] currentItems;
    
    public KnapsackOptimization(int[] weights, int[] values, int capacity) {
        this.weights = weights;
        this.values = values;
        this.capacity = capacity;
        this.n = weights.length;
        this.maxProfit = 0;
        this.bestItems = new boolean[n];
        this.currentItems = new boolean[n];
    }
    
    private int upperBound(int idx, int weight, int profit) {
        if (weight >= capacity) {
            return profit;
        }
        
        int bound = profit;
        int remainCapacity = capacity - weight;
        
        for (int i = idx; i < n; i++) {
            if (weights[i] <= remainCapacity) {
                bound += values[i];
                remainCapacity -= weights[i];
            } else {
                bound += (int) ((double) values[i] * remainCapacity / weights[i]);
                break;
            }
        }
        
        return bound;
    }
    
    private void branchAndBound(int idx, int weight, int profit) {
        if (upperBound(idx, weight, profit) <= maxProfit) {
            return;
        }
        
        if (idx == n) {
            if (profit > maxProfit) {
                maxProfit = profit;
                System.arraycopy(currentItems, 0, bestItems, 0, n);
            }
            return;
        }
        
        // Include current item
        if (weight + weights[idx] <= capacity) {
            currentItems[idx] = true;
            branchAndBound(idx + 1, weight + weights[idx], profit + values[idx]);
            currentItems[idx] = false;
        }
        
        // Exclude current item
        branchAndBound(idx + 1, weight, profit);
    }
    
    public int solve() {
        branchAndBound(0, 0, 0);
        return maxProfit;
    }
    
    public int[] getSelectedItems() {
        java.util.List<Integer> selected = new java.util.ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (bestItems[i]) {
                selected.add(i);
            }
        }
        return selected.stream().mapToInt(Integer::intValue).toArray();
    }
    
    public static void main(String[] args) {
        int[] weights = {2, 3, 4, 5};
        int[] values = {3, 4, 5, 6};
        int capacity = 8;
        
        System.out.println("============================================================");
        System.out.println("0-1 Knapsack Optimization - Branch and Bound (Java)");
        System.out.println("============================================================");
        
        System.out.println("\nCapacity: " + capacity);
        System.out.print("Weights: ");
        for (int w : weights) System.out.print(w + " ");
        System.out.println();
        System.out.print("Values: ");
        for (int v : values) System.out.print(v + " ");
        System.out.println();
        
        KnapsackOptimization solver = new KnapsackOptimization(weights, values, capacity);
        int maxProfit = solver.solve();
        int[] selected = solver.getSelectedItems();
        
        System.out.println("\nMaximum Profit: " + maxProfit);
        System.out.print("Selected Items: ");
        for (int idx : selected) System.out.print(idx + " ");
        System.out.println();
    }
}
