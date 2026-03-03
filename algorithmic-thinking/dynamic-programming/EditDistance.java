import java.util.*;

/*
*
 * 编辑距离 (Edit Distance / Levenshtein Distance) - 动态规划应用
 *
 * 问题描述：
 * 给定两个字符串，计算从一个字符串转换到另一个字符串所需的最少编辑操作数
 *
 * 动态规划方程：
 * if s1[i-1] == s2[j-1]:
 *     dp[i][j] = dp[i-1][j-1]
 * else:
 *     dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
 *
 * 时间复杂度: O(m * n)
 * 空间复杂度: O(m * n)
*/
public class EditDistance {
    /*
*
     * 编辑距离 - 求最少操作数
*/
    public static int editDistance(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();

        // dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
        int[][] dp = new int[m + 1][n + 1];

        // 初始化
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        // 填充 DP 表
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    // 字符相同，不需要操作
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 字符不同，选择最少操作数的方案
                    dp[i][j] = 1 + Math.min(
                        Math.min(dp[i - 1][j], dp[i][j - 1]),  // 删除或插入
                        dp[i - 1][j - 1]                        // 替换
                    );
                }
            }
        }

        return dp[m][n];
    }

    /*
*
     * 编辑距离 - 空间优化版本
*/
    public static int editDistanceOptimized(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();

        // 确保 s1 是较短的字符串
        if (m > n) {
            String temp = s1;
            s1 = s2;
            s2 = temp;
            int tmp = m;
            m = n;
            n = tmp;
        }

        // 使用两行数组来计算
        int[] prev = new int[n + 1];
        int[] curr = new int[n + 1];

        // 初始化 prev 行
        for (int j = 0; j <= n; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            curr[0] = i;

            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + Math.min(
                        Math.min(prev[j], curr[j - 1]),  // 删除或插入
                        prev[j - 1]                       // 替换
                    );
                }
            }

            // 交换行
            int[] temp = prev;
            prev = curr;
            curr = temp;
        }

        return prev[n];
    }

    /*
*
     * 测试函数
*/
    public static void main(String[] args) {
        System.out.println("=== 编辑距离问题 ===\n");

        // 测试用例1：基本编辑距离
        System.out.println("1. 基本编辑距离");
        String s1_1 = "horse";
        String s2_1 = "ros";
        System.out.println("字符串1: " + s1_1);
        System.out.println("字符串2: " + s2_1);
        System.out.println("编辑距离: " + editDistance(s1_1, s2_1) + "\n");

        // 测试用例2：相同字符串
        System.out.println("2. 相同字符串");
        String s1_2 = "hello";
        String s2_2 = "hello";
        System.out.println("字符串1: " + s1_2);
        System.out.println("字符串2: " + s2_2);
        System.out.println("编辑距离: " + editDistance(s1_2, s2_2) + "\n");

        // 测试用例3：空字符串
        System.out.println("3. 空字符串");
        String s1_3 = "abc";
        String s2_3 = "";
        System.out.println("字符串1: " + s1_3);
        System.out.println("字符串2: " + s2_3);
        System.out.println("编辑距离: " + editDistance(s1_3, s2_3) + "\n");

        // 测试用例4：不同长度的字符串
        System.out.println("4. 不同长度的字符串");
        String s1_4 = "intention";
        String s2_4 = "execution";
        System.out.println("字符串1: " + s1_4);
        System.out.println("字符串2: " + s2_4);
        System.out.println("编辑距离: " + editDistance(s1_4, s2_4));
        System.out.println("编辑距离（优化）: " + editDistanceOptimized(s1_4, s2_4));
    }
}
