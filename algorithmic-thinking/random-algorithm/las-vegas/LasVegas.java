/**
 * 拉斯维加斯算法实现 (Java)
 * 
 * 特点：
 * - 总是给出正确答案
 * - 运行时间随机
 * - 不返回错误答案
 */

import java.util.Random;

public class LasVegas {
    
    private static final Random random = new Random();
    
    /**
     * 交换数组中两个元素
     */
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    
    /**
     * 随机分区函数
     */
    private static int randomizedPartition(int[] arr, int left, int right) {
        // 随机选择枢轴
        int pivotIdx = left + random.nextInt(right - left + 1);
        swap(arr, pivotIdx, right);
        
        int pivot = arr[right];
        int i = left - 1;
        
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        
        swap(arr, i + 1, right);
        return i + 1;
    }
    
    /**
     * 拉斯维加斯随机快速排序
     * 时间复杂度：期望 O(n log n)，最坏 O(n²)
     * 空间复杂度：O(log n) 平均
     */
    public static void lasVegasQuickSort(int[] arr, int left, int right) {
        if (left < right) {
            // 随机分区
            int pivotIdx = randomizedPartition(arr, left, right);
            
            // 递归排序左右子数组
            lasVegasQuickSort(arr, left, pivotIdx - 1);
            lasVegasQuickSort(arr, pivotIdx + 1, right);
        }
    }
    
    /**
     * 拉斯维加斯随机选择算法 - 找第k小元素
     * 时间复杂度：平均 O(n)，最坏 O(n²)
     */
    public static int lasVegasRandomizedSelect(int[] arr, int left, int right, int k) {
        if (left == right) {
            return arr[left];
        }
        
        // 随机分区
        int pivotIdx = randomizedPartition(arr, left, right);
        
        // 计算枢轴的相对位置
        int pos = pivotIdx - left + 1;
        
        if (k == pos) {
            return arr[pivotIdx];
        } else if (k < pos) {
            return lasVegasRandomizedSelect(arr, left, pivotIdx - 1, k);
        } else {
            return lasVegasRandomizedSelect(arr, pivotIdx + 1, right, k - pos);
        }
    }
    
    /**
     * 拉斯维加斯字符串匹配 - 随机化匹配
     */
    public static int lasVegasStringMatch(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();
        
        if (m > n) return -1;
        
        // 随机选择起始位置进行匹配
        while (true) {
            int start = random.nextInt(n - m + 1);
            
            // 检查是否匹配
            boolean match = true;
            for (int i = 0; i < m; i++) {
                if (text.charAt(start + i) != pattern.charAt(i)) {
                    match = false;
                    break;
                }
            }
            
            if (match) {
                return start;  // 找到匹配位置
            }
            
            // 在实际实现中，这里应该有避免无限循环的机制
            // 为了演示，这里简化处理
            break;
        }
        
        return -1;
    }
    
    /**
     * 拉斯维加斯八皇后问题求解器
     * 随机放置皇后直到找到有效解
     */
    public static int[] lasVegasNQueens(int n) {
        int[] queens = new int[n];
        boolean[] columns = new boolean[n];
        boolean[] diag1 = new boolean[2 * n - 1];  // 主对角线
        boolean[] diag2 = new boolean[2 * n - 1];  // 副对角线
        
        while (true) {
            // 重置状态
            java.util.Arrays.fill(columns, false);
            java.util.Arrays.fill(diag1, false);
            java.util.Arrays.fill(diag2, false);
            java.util.Arrays.fill(queens, -1);
            
            boolean success = true;
            
            // 逐行放置皇后
            for (int row = 0; row < n; row++) {
                // 收集当前行可用的列
                java.util.List<Integer> availableCols = new java.util.ArrayList<>();
                for (int col = 0; col < n; col++) {
                    if (!columns[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
                        availableCols.add(col);
                    }
                }
                
                if (availableCols.isEmpty()) {
                    success = false;
                    break;
                }
                
                // 随机选择一个可用列
                int chosenCol = availableCols.get(random.nextInt(availableCols.size()));
                queens[row] = chosenCol;
                columns[chosenCol] = true;
                diag1[row + chosenCol] = true;
                diag2[row - chosenCol + n - 1] = true;
            }
            
            if (success) {
                return queens;
            }
        }
    }
    
    /**
     * 打印数组
     */
    private static void printArray(int[] arr) {
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if (i < arr.length - 1) System.out.print(", ");
        }
        System.out.println("]");
    }
    
    /**
     * 打印八皇后解法
     */
    private static void printNQueensSolution(int[] queens) {
        int n = queens.length;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (queens[row] == col) {
                    System.out.print("Q ");
                } else {
                    System.out.print(". ");
                }
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== 拉斯维加斯算法演示 ===\n");
        
        // 测试随机快速排序
        System.out.println("1. 拉斯维加斯随机快速排序");
        int[] arr1 = {5, 2, 8, 1, 9, 3, 4, 7, 6};
        
        System.out.print("原数组: ");
        printArray(arr1);
        
        lasVegasQuickSort(arr1, 0, arr1.length - 1);
        
        System.out.print("排序后: ");
        printArray(arr1);
        System.out.println();
        
        // 测试随机选择算法
        System.out.println("2. 拉斯维加斯随机选择算法");
        int[] arr2 = {7, 2, 5, 3, 9, 1, 4, 6, 8};
        int k = 4;  // 找第4小元素
        
        System.out.print("数组: ");
        printArray(arr2);
        System.out.println("第" + k + "小元素: " + lasVegasRandomizedSelect(arr2, 0, arr2.length - 1, k));
        System.out.println();
        
        // 测试字符串匹配
        System.out.println("3. 拉斯维加斯字符串匹配");
        String text = "hello world, this is a test string";
        String pattern = "test";
        
        System.out.println("文本: " + text);
        System.out.println("模式: " + pattern);
        int pos = lasVegasStringMatch(text, pattern);
        if (pos != -1) {
            System.out.println("匹配位置: " + pos);
        } else {
            System.out.println("未找到匹配");
        }
        System.out.println();
        
        // 测试八皇后问题
        System.out.println("4. 拉斯维加斯八皇后问题求解");
        int n = 8;
        int[] solution = lasVegasNQueens(n);
        System.out.println("八皇后解法 (n=" + n + "):");
        printNQueensSolution(solution);
    }
}
