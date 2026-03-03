/**
 * 最长公共子序列（LCS）问题有两种方式定义子序列，一种是子序列不要求连续，一种是子序列要求连续。
 * 下面介绍要求子序列必须是连续的情况下，如何用算法解决最长公共子序列问题。
 * 
 * 以两个字符串 “abcdea”和“aebcda”为例，如果子序列不要求连续，其最长公共子序列为“abcda”，
 * 如果子序列要求是连续，则其最长公共子序列应为“bcd”。在这种情况下，有可能两个字符串出现多个长度相同的
 * 公共子串，比如“askdfiryetd”和“trkdffirey”两个字符串就存在两个长度为3的公共子串，分别是“kdf”和“fir”，
 * 因此问题的性质发生了变化，需要找出两个字符串所有可能存在公共子串的情况，然后取最长的一个，如果有多个
 * 最长的公共子串，只取其中一个即可。
 */
public class LongestContinuousSubsequence {

    /**
     * 最长公共子串（连续）求解函数
     * 
     * 功能：找到两个字符串中最长的连续公共子串（字符顺序一致且连续相邻）
     * 
     * 参数：
     *   str1: 第一个输入字符串
     *   str2: 第二个输入字符串
     * 
     * 返回值：
     *   一个数组，第一个元素为最长公共子串的长度，第二个元素为最长公共子串内容
     */
    public static Object[] longestContinuousSubsequence(String str1, String str2) {
        int len1 = str1.length();
        int len2 = str2.length();
        
        // 特殊情况处理
        if (len1 == 0 || len2 == 0) {
            return new Object[]{0, ""};
        }
        
        // 创建DP表：dp[i][j]表示以str1[i-1]和str2[j-1]为结尾的最长公共子串长度
        int[][] dp = new int[len1 + 1][len2 + 1];
        
        int maxLength = 0;  // 记录最长公共子串的长度
        int endIndex = 0;   // 记录最长公共子串在str1中的结束索引
        
        // 填充DP表
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
                    // 当前字符相同，长度 = 前一位的长度 + 1（连续累加）
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    
                    // 更新最长长度和结束索引
                    if (dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endIndex = i;  // 记录在str1中的结束位置
                    }
                } else {
                    // 字符不同，连续中断，长度重置为0
                    dp[i][j] = 0;
                }
            }
        }
        
        // 提取最长公共子串
        String longestSubstring = "";
        if (maxLength > 0) {
            int startIndex = endIndex - maxLength;
            longestSubstring = str1.substring(startIndex, endIndex);
        }
        
        return new Object[]{maxLength, longestSubstring};
    }
    
    // 检查字符串是否在字符串数组中
    private static boolean isInArray(String str, String[] array) {
        for (String s : array) {
            if (s.equals(str)) {
                return true;
            }
        }
        return false;
    }
    
    // 测试用例
    public static void testLongestContinuousSubsequence() {
        // 测试用例数组
        Object[][] testCases = {
            {"ABCBDAB", "BDCAB", 2, new String[]{"BC", "AB"}},
            {"HELLO", "HELLO", 5, new String[]{"HELLO"}},
            {"ABCDEF", "ACE", 1, new String[]{"A", "C", "E"}},
            {"ABCDXYZ", "XYZABCD", 4, new String[]{"ABCD"}},
            {"12345", "54321", 1, new String[]{"1", "2", "3", "4", "5"}},
            {"ABABC", "BABCA", 4, new String[]{"ABCA", "BABC"}}
        };
        
        for (int i = 0; i < testCases.length; i++) {
            System.out.printf("测试用例 %d:\n", i + 1);
            String s1 = (String) testCases[i][0];
            String s2 = (String) testCases[i][1];
            int expectedLen = (int) testCases[i][2];
            String[] possibleResults = (String[]) testCases[i][3];
            
            System.out.printf("字符串1: %s\n", s1);
            System.out.printf("字符串2: %s\n", s2);
            
            Object[] result = longestContinuousSubsequence(s1, s2);
            int actualLen = (int) result[0];
            String actualResult = (String) result[1];
            
            boolean lenMatch = (actualLen == expectedLen);
            boolean resultMatch = isInArray(actualResult, possibleResults);
            
            System.out.printf("预期长度: %d, 实际长度: %d → %s\n",
                    expectedLen, actualLen, lenMatch ? "通过" : "失败");
            System.out.printf("预期结果之一: %s, 实际结果: %s → %s\n",
                    possibleResults[0], actualResult, resultMatch ? "通过" : "失败");
            System.out.printf("测试结果: %s\n\n", (lenMatch && resultMatch) ? "全部通过" : "存在问题");
        }
    }
    
    public static void main(String[] args) {
        // 示例
        String s1 = "ABCBDAB";
        String s2 = "BDCAB";
        Object[] result = longestContinuousSubsequence(s1, s2);
        
        System.out.println("示例:");
        System.out.printf("字符串1: %s\n", s1);
        System.out.printf("字符串2: %s\n", s2);
        System.out.printf("最长公共子串长度: %d\n", (int) result[0]);
        System.out.printf("最长公共子串: %s\n\n", (String) result[1]);
        
        // 运行测试
        testLongestContinuousSubsequence();
    }
}
/*
jarry@Mac LCS % java LongestContinuousSubsequence.java
示例:
字符串1: ABCBDAB
字符串2: BDCAB
最长公共子串长度: 2
最长公共子串: AB

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 2, 实际长度: 2 → 通过
预期结果之一: BC, 实际结果: AB → 通过
测试结果: 全部通过

测试用例 2:
字符串1: HELLO
字符串2: HELLO
预期长度: 5, 实际长度: 5 → 通过
预期结果之一: HELLO, 实际结果: HELLO → 通过
测试结果: 全部通过

测试用例 3:
字符串1: ABCDEF
字符串2: ACE
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCDXYZ
字符串2: XYZABCD
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCD, 实际结果: ABCD → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 12345
字符串2: 54321
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: 1, 实际结果: 1 → 通过
测试结果: 全部通过

测试用例 6:
字符串1: ABABC
字符串2: BABCA
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCA, 实际结果: BABC → 通过
测试结果: 全部通过
 */