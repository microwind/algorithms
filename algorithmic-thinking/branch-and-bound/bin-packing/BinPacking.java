/**
 * 装箱问题 - 分支定界算法 (Java)
 */

import java.util.*;

public class BinPacking {
    private int[] items;
    private int binCapacity;
    private int n;
    private int minBins;
    private List<List<Integer>> bestPacking;
    private List<List<Integer>> currentBins;
    
    public BinPacking(int[] items, int capacity) {
        this.items = items.clone();
        Arrays.sort(this.items);
        reverseArray(this.items);
        this.binCapacity = capacity;
        this.n = items.length;
        this.minBins = n;
        this.bestPacking = new ArrayList<>();
        this.currentBins = new ArrayList<>();
    }
    
    private void reverseArray(int[] arr) {
        int left = 0, right = arr.length - 1;
        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    
    private int lowerBound(int itemIdx) {
        int totalWeight = 0;
        for (int i = itemIdx; i < n; i++) {
            totalWeight += items[i];
        }
        return (totalWeight + binCapacity - 1) / binCapacity;
    }
    
    private int sumBin(List<Integer> bin) {
        int sum = 0;
        for (int item : bin) {
            sum += item;
        }
        return sum;
    }
    
    private void branchAndBound(int itemIdx) {
        if (currentBins.size() + lowerBound(itemIdx) >= minBins) {
            return;
        }
        
        if (itemIdx == n) {
            if (currentBins.size() < minBins) {
                minBins = currentBins.size();
                bestPacking.clear();
                for (List<Integer> bin : currentBins) {
                    bestPacking.add(new ArrayList<>(bin));
                }
            }
            return;
        }
        
        int item = items[itemIdx];
        boolean placed = false;
        
        for (List<Integer> bin : currentBins) {
            if (sumBin(bin) + item <= binCapacity) {
                bin.add(item);
                branchAndBound(itemIdx + 1);
                bin.remove(bin.size() - 1);
                placed = true;
                break;
            }
        }
        
        if (!placed && currentBins.size() < minBins) {
            List<Integer> newBin = new ArrayList<>();
            newBin.add(item);
            currentBins.add(newBin);
            branchAndBound(itemIdx + 1);
            currentBins.remove(currentBins.size() - 1);
        }
    }
    
    public int solve() {
        branchAndBound(0);
        return minBins;
    }
    
    public List<List<Integer>> getPacking() {
        return bestPacking;
    }
    
    public static void main(String[] args) {
        int[] items = {7, 5, 5, 3, 3, 3, 2};
        int capacity = 10;
        
        System.out.println("============================================================");
        System.out.println("Bin Packing Problem (Java)");
        System.out.println("============================================================");
        
        System.out.println("\nItems: " + Arrays.toString(items));
        System.out.println("Capacity: " + capacity);
        
        int totalWeight = 0;
        for (int item : items) totalWeight += item;
        System.out.println("Total Weight: " + totalWeight);
        
        BinPacking solver = new BinPacking(items, capacity);
        int minBins = solver.solve();
        List<List<Integer>> packing = solver.getPacking();
        
        System.out.println("\nMinimum Bins: " + minBins);
        System.out.println("\nPacking:");
        for (int i = 0; i < packing.size(); i++) {
            List<Integer> bin = packing.get(i);
            int binWeight = 0;
            for (int item : bin) binWeight += item;
            System.out.printf("Bin %d: %s (weight: %d/%d)\n", i, bin, binWeight, capacity);
        }
    }
}
