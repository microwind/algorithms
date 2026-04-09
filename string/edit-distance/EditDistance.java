/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
 * 
 * 算法原理：
 * 1. 计算将一个字符串转换为另一个字符串所需的最少操作次数。
 * 2. 允许的操作包括：插入一个字符、删除一个字符、替换一个字符。
 * 3. 使用动态规划（DP）求解，状态转移方程考虑三种操作的最小值。
 * 
 * 时间复杂度：O(m * n)，其中 m 和 n 分别是两个字符串的长度。
 * 空间复杂度：O(m * n)，可以通过滚动数组优化到 O(min(m, n))。
 */
public class EditDistance {

    /**
     * 动态规划版本 - 计算编辑距离
     * 
     * 算法过程：
     * 1. 创建 (m+1)x(n+1) 的二维数组 dp。
     * 2. dp[i][j] 表示 word1 的前 i 个字符转换为 word2 的前 j 个字符所需的步数。
     * 3. 第一行和第一列进行初始化，表示与空字符串的距离。
     * 4. 遍历字符串，若当前字符相等，则继承左上角的值；若不等，取插入、删除、替换中的最小值 + 1。
     * 
     * @param word1 源字符串
     * @param word2 目标字符串
     * @return 最小编辑距离
     */
    public static int editDistance(String word1, String word2) {
        int n = word1.length();
        int m = word2.length();
        
        // dp[i][j] 表示 word1[0..i-1] 转换为 word2[0..j-1] 的最小操作数
        int[][] dp = new int[n + 1][m + 1];
        
        // 初始化基础情况：第一列
        for (int i = 0; i <= n; i++) {
            dp[i][0] = i; // 从 word1[0..i-1] 变为空串需要 i 次删除
        }
        // 初始化基础情况：第一行
        for (int j = 0; j <= m; j++) {
            dp[0][j] = j; // 从空串变为 word2[0..j-1] 需要 j 次插入
        }
        
        // 填充 DP 表
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // 如果字符相同，不需要任何操作
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 如果字符不同，取三种操作中的最小值
                    dp[i][j] = 1 + Math.min(
                        Math.min(dp[i - 1][j],    // 删除操作
                        dp[i][j - 1]),           // 插入操作
                        dp[i - 1][j - 1]        // 替换操作
                    );
                }
            }
        }
        
        return dp[n][m];
    }
    
    /**
     * 空间优化的动态规划版本
     * 
     * 优化思路：
     * 由于 dp[i][j] 仅依赖于上一行 dp[i-1] 和当前行 dp[i] 的前一个值，
     * 因此可以使用一维数组（或两行数组）来降低空间复杂度。
     * 
     * 时间复杂度：O(m * n)
     * 空间复杂度：O(min(m, n))
     * 
     * @param word1 源字符串
     * @param word2 目标字符串
     * @return 最小编辑距离
     */
    public static int editDistanceOptimized(String word1, String word2) {
        // 确保 word2 是较短的字符串，以优化空间
        if (word1.length() < word2.length()) {
            return editDistanceOptimizedHelper(word2, word1);
        }
        return editDistanceOptimizedHelper(word1, word2);
    }
    
    private static int editDistanceOptimizedHelper(String longer, String shorter) {
        int n = longer.length();
        int m = shorter.length();
        
        int[] prev = new int[m + 1];
        int[] curr = new int[m + 1];
        
        // 初始化第一行
        for (int j = 0; j <= m; j++) {
            prev[j] = j;
        }
        
        for (int i = 1; i <= n; i++) {
            curr[0] = i; // 每行开头表示删除 word1 的前 i 个字符
            for (int j = 1; j <= m; j++) {
                if (longer.charAt(i - 1) == shorter.charAt(j - 1)) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + Math.min(
                        Math.min(prev[j],    // 删除
                        curr[j - 1]),        // 插入
                        prev[j - 1]          // 替换
                    );
                }
            }
            // 交换数组，准备下一轮
            System.arraycopy(curr, 0, prev, 0, m + 1);
        }
        
        return prev[m];
    }
    
    /**
     * 递归版本（结合备忘录优化）
     * 
     * 算法思路：
     * 1. 自顶向下递归分解子问题。
     * 2. 使用二维数组 memo 存储已计算的结果，避免重复计算。
     * 
     * 时间复杂度：O(m * n)
     * 空间复杂度：O(m * n) (递归栈深度 + 备忘录)
     * 
     * @param word1 源字符串
     * @param word2 目标字符串
     * @return 最小编辑距离
     */
    public static int editDistanceRecursive(String word1, String word2) {
        int[][] memo = new int[word1.length() + 1][word2.length() + 1];
        // 数组初始化为 -1 表示未计算
        for (int i = 0; i <= word1.length(); i++) {
            for (int j = 0; j <= word2.length(); j++) {
                memo[i][j] = -1;
            }
        }
        return editDistanceRecursiveHelper(word1, word2, word1.length(), word2.length(), memo);
    }
    
    private static int editDistanceRecursiveHelper(String word1, String word2, int i, int j, int[][] memo) {
        // 基础情况：其中一个字符串为空
        if (i == 0) return j;
        if (j == 0) return i;
        
        // 查备忘录
        if (memo[i][j] != -1) return memo[i][j];
        
        if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
            memo[i][j] = editDistanceRecursiveHelper(word1, word2, i - 1, j - 1, memo);
        } else {
            memo[i][j] = 1 + Math.min(
                Math.min(
                    editDistanceRecursiveHelper(word1, word2, i - 1, j, memo),     // 删除
                    editDistanceRecursiveHelper(word1, word2, i, j - 1, memo)      // 插入
                ),
                editDistanceRecursiveHelper(word1, word2, i - 1, j - 1, memo)      // 替换
            );
        }
        
        return memo[i][j];
    }
    
    /**
     * 重建编辑操作步骤
     * 
     * 算法过程：
     * 1. 重新计算 DP 表。
     * 2. 从右下角向左上角回溯。
     * 3. 根据值推断当前位置是由哪种操作（插入、删除、替换或无操作）得到的。
     * 
     * @param word1 源字符串
     * @param word2 目标字符串
     * @return 编辑操作的字符串描述
     */
    public static String getEditOperations(String word1, String word2) {
        int n = word1.length();
        int m = word2.length();
        int[][] dp = new int[n + 1][m + 1];
        
        // 填充 DP 表
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(Math.min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
                }
            }
        }
        
        // 回溯还原操作
        StringBuilder operations = new StringBuilder();
        int i = n, j = m;
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && word1.charAt(i - 1) == word2.charAt(j - 1)) {
                i--; j--; // 字符相同，向左上角回退
            } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
                operations.insert(0, String.format("替换 '%c' 为 '%c'\n", word1.charAt(i - 1), word2.charAt(j - 1)));
                i--; j--;
            } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
                operations.insert(0, String.format("删除 '%c'\n", word1.charAt(i - 1)));
                i--;
            } else {
                operations.insert(0, String.format("插入 '%c'\n", word2.charAt(j - 1)));
                j--;
            }
        }
        return operations.toString();
    }
    
    /**
     * 计算相似度
     * 公式：1 - (编辑距离 / 最大长度)
     * 
     * @param word1 字符串1
     * @param word2 字符串2
     * @return 0.0 到 1.0 之间的相似度
     */
    public static double getSimilarityRatio(String word1, String word2) {
        int distance = editDistance(word1, word2);
        int maxLength = Math.max(word1.length(), word2.length());
        return maxLength == 0 ? 1.0 : 1.0 - (double) distance / maxLength;
    }
    
    /**
     * 打印 DP 表（调试用）
     */
    public static void printDPTable(String word1, String word2) {
        int n = word1.length();
        int m = word2.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = 1 + Math.min(Math.min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
            }
        }
        
        System.out.println("\nDP 状态表:");
        System.out.print("    ");
        for (int j = 0; j < m; j++) System.out.print(word2.charAt(j) + " ");
        System.out.println();
        for (int i = 0; i <= n; i++) {
            if (i == 0) System.out.print("  ");
            else System.out.print(word1.charAt(i - 1) + " ");
            for (int j = 0; j <= m; j++) System.out.print(dp[i][j] + " ");
            System.out.println();
        }
    }
    
    /**
     * 主函数 - 测试编辑距离算法
     */
    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("编辑距离 (Levenshtein Distance) - Java 实现");
        System.out.println("====================================================");
        
        String[][] testCases = {
            {"kitten", "sitting"},
            {"sunday", "saturday"},
            {"intention", "execution"},
            {"abc", ""},
            {"", "abc"},
            {"same", "same"}
        };
        
        for (String[] testCase : testCases) {
            String s1 = testCase[0];
            String s2 = testCase[1];
            
            System.out.println("\n源字符串: \"" + s1 + "\"");
            System.out.println("目标字符串: \"" + s2 + "\"");
            System.out.println("最小编辑距离 (DP): " + editDistance(s1, s2));
            System.out.println("最小编辑距离 (优化DP): " + editDistanceOptimized(s1, s2));
            System.out.println("最小编辑距离 (递归): " + editDistanceRecursive(s1, s2));
            System.out.printf("相似度: %.2f%%\n", getSimilarityRatio(s1, s2) * 100);
            
            if (s1.length() < 10 && s2.length() < 10) {
                System.out.println("编辑操作步骤:");
                System.out.print(getEditOperations(s1, s2));
            }
        }
        
        System.out.println("\n=== DP 表展示 (kitten -> sitting) ===");
        printDPTable("kitten", "sitting");
    }
}
