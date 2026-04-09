/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 最长公共子序列 (Longest Common Subsequence, LCS)
 * 
 * 算法原理：
 * 1. 子序列定义：在不改变相对顺序的情况下，从原序列中删除零个或多个元素后得到的序列。
 * 2. 子序列不要求连续，但必须保持原有的先后顺序。
 * 3. 使用动态规划求解：
 *    - 如果 word1[i-1] == word2[j-1]，则 dp[i][j] = dp[i-1][j-1] + 1
 *    - 否则，dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)，可优化至 O(min(m, n))
 */
public class LongestCommonSubsequence {

    /**
     * 求解最长公共子序列
     * 
     * @param s1 第一个字符串
     * @param s2 第二个字符串
     * @return 包含长度和具体内容的数组
     */
    public static String[] findLCS(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        
        // dp[i][j] 表示 s1[0..i-1] 和 s2[0..j-1] 的 LCS 长度
        int[][] dp = new int[m + 1][n + 1];
        
        // 填充 DP 表
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                    // 字符匹配，继承左上角结果 + 1
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 字符不匹配，取上方或左方的最大值
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // 回溯还原具体子序列内容
        StringBuilder sb = new StringBuilder();
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
                // 相等字符属于 LCS
                sb.append(s1.charAt(i - 1));
                i--;
                j--;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                // 向上回退
                i--;
            } else {
                // 向左回退
                j--;
            }
        }
        
        String lcs = sb.reverse().toString();
        return new String[]{String.valueOf(dp[m][n]), lcs};
    }

    /**
     * 运行测试用例
     */
    public static void runTests() {
        String[][] testCases = {
            {"ABCBDAB", "BDCAB", "4", "BCAB,BDAB"},
            {"HELLO", "HELLO", "5", "HELLO"},
            {"ABCDEF", "ACE", "3", "ACE"},
            {"ABCD", "EFGH", "0", ""},
            {"XMJYAUZ", "MZJAWXU", "4", "MJAU,MZAU"},
            // 修正后的测试用例 10
            {"123@abc", "a3@x1", "2", "3@,1@,3a"}
        };
        
        System.out.println("LCS 测试结果:");
        for (int i = 0; i < testCases.length; i++) {
            String s1 = testCases[i][0];
            String s2 = testCases[i][1];
            String expectedLen = testCases[i][2];
            String[] possibleResults = testCases[i][3].split(",");
            
            String[] result = findLCS(s1, s2);
            String actualLen = result[0];
            String actualLCS = result[1];
            
            boolean lenMatch = actualLen.equals(expectedLen);
            boolean contentMatch = false;
            for (String p : possibleResults) {
                if (p.equals(actualLCS)) {
                    contentMatch = true;
                    break;
                }
            }
            
            System.out.printf("用例 %d: [%s] vs [%s] | 长度: %s (预期: %s) | 内容: %s | 状态: %s\n",
                i + 1, s1, s2, actualLen, expectedLen, actualLCS, (lenMatch ? "OK" : "FAIL"));
        }
    }

    public static void main(String[] args) {
        runTests();
    }
}
