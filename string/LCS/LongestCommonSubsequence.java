public class LongestCommonSubsequence {
    /**
     * 最长公共子序列（LCS）求解函数
     * 
     * 功能：找到两个字符串中最长的公共子序列（字符顺序一致但不必连续）
     * 
     * @param firstString 第一个输入字符串
     * @param secondString 第二个输入字符串
     * @return 一个字符串数组，第一个元素是LCS的长度，第二个元素是LCS的具体内容
     * 
     * 举例：
     * 序列A为"abcdef"，序列B为"bcef"，
     * 最长公共子序列为"bcef"，
     * 注意最长公共子序列不用保证每一个字符必须连续。
     */
    /*
    示例与算法对比说明
    示例：
    若序列 A 为 “abcdef”，序列 B 为 “bcef”，其最长公共子序列为 “bcef”（即序列 B）。需注意，最长公共子序列仅要求字符顺序一致，无需连续。
    暴力解法思路：
    选择一个参照序列（如 A），遍历其每个字符作为公共子序列的起始点；
    将该字符与另一序列（如 B）的每个字符比较，若匹配，则在两序列中均向后移动指针继续比较，直至某一序列结束；
    重复上述过程，以参照序列的每个字符为起点计算可能的公共子序列长度，最终取最大值。
    暴力解法的问题：
    时间复杂度为 O (n²×m)（其中 n 为序列 A 的长度，m 为序列 B 的长度），效率过低。因此，需要更优的算法 —— 动态规划。
    */
    public static String[] findLCS(String firstString, String secondString) {
        int lengthOfFirst = firstString.length();
        int lengthOfSecond = secondString.length();
        
        // 创建DP表：dpTable[i][j]表示前i个字符与前j个字符的LCS长度
        int[][] dpTable = new int[lengthOfFirst + 1][lengthOfSecond + 1];
        
        // 填充DP表
        for (int i = 1; i <= lengthOfFirst; i++) {
            for (int j = 1; j <= lengthOfSecond; j++) {
                char charFromFirst = firstString.charAt(i - 1);
                char charFromSecond = secondString.charAt(j - 1);
                
                if (charFromFirst == charFromSecond) {
                    // 字符相同，继承前序结果+1
                    dpTable[i][j] = dpTable[i - 1][j - 1] + 1;
                } else {
                    // 字符不同，取两种情况的最大值
                    dpTable[i][j] = Math.max(dpTable[i - 1][j], dpTable[i][j - 1]);
                }
            }
        }
        
        // 回溯找到具体的LCS序列
        StringBuilder lcsBuilder = new StringBuilder();
        int currentI = lengthOfFirst;
        int currentJ = lengthOfSecond;
        
        while (currentI > 0 && currentJ > 0) {
            char currentCharFirst = firstString.charAt(currentI - 1);
            char currentCharSecond = secondString.charAt(currentJ - 1);
            
            if (currentCharFirst == currentCharSecond) {
                lcsBuilder.append(currentCharFirst);
                currentI--;
                currentJ--;
            } else if (dpTable[currentI - 1][currentJ] > dpTable[currentI][currentJ - 1]) {
                currentI--;
            } else {
                currentJ--;
            }
        }
        
        // 反转得到正确顺序
        String lcsContent = lcsBuilder.reverse().toString();
        return new String[]{String.valueOf(dpTable[lengthOfFirst][lengthOfSecond]), lcsContent};
    }
    
    public static void main(String[] args) {
        // 示例用法
        String stringOne = "AABCBDAB";
        String stringTwo = "ABDCAB";
        
        String[] result = findLCS(stringOne, stringTwo);
        System.out.println("示例计算结果：");
        System.out.println("第一个字符串: " + stringOne);
        System.out.println("第二个字符串: " + stringTwo);
        System.out.println("最长公共子序列的长度: " + result[0]);  // 输出5
        System.out.println("最长公共子序列的内容: " + result[1]);  // 输出"ABDAB"
        
        // 运行测试用例
        System.out.println("\n开始执行测试用例...");
        runLCSTests();
    }
    
    /** 运行LCS算法的测试用例集合 */
    public static void runLCSTests() {
        // 测试用例数组：{字符串1, 字符串2, 预期长度, 可能的预期结果}
        String[][] testCases = {
            {"ABCBDAB", "BDCAB", "4", "BCAB,BDAB"},
            {"HELLO", "HELLO", "5", "HELLO"},
            {"ABCDEF", "ACE", "3", "ACE"},
            {"ABCD", "EFGH", "0", ""},
            {"", "TEST", "0", ""},
            {"AABBAABB", "ABAB", "4", "AABB,ABAB,ABBA"},
            {"XMJYAUZ", "MZJAWXU", "4", "MJAU,MZAU"},
            {"A", "A", "1", "A"},
            {"A", "B", "0", ""},
            {"123@abc", "a3@x1", "3", "3@a,1@a,3a@"}
        };
        
        for (int i = 0; i < testCases.length; i++) {
            System.out.println("\n测试用例 " + (i + 1) + ":");
            String s1 = testCases[i][0];
            String s2 = testCases[i][1];
            String expectedLen = testCases[i][2];
            String[] possibleResults = testCases[i][3].split(",");
            
            System.out.println("字符串1: " + s1);
            System.out.println("字符串2: " + s2);
            
            String[] result = findLCS(s1, s2);
            String actualLen = result[0];
            String actualResult = result[1];
            
            boolean lenMatch = actualLen.equals(expectedLen);
            boolean resultMatch = false;
            for (String possible : possibleResults) {
                if (possible.equals(actualResult)) {
                    resultMatch = true;
                    break;
                }
            }
            
            System.out.println("预期长度: " + expectedLen + ", 实际长度: " + actualLen + 
                              " → " + (lenMatch ? "通过" : "失败"));
            System.out.println("预期结果之一: " + possibleResults[0] + ", 实际结果: " + actualResult + 
                              " → " + (resultMatch ? "通过" : "失败"));
            System.out.println("测试结果: " + (lenMatch && resultMatch ? "全部通过" : "存在问题"));
        }
    }
}

/**
jarry@Mac LCS % java LongestCommonSubsequence.java 
示例计算结果：
第一个字符串: AABCBDAB
第二个字符串: ABDCAB
最长公共子序列的长度: 5
最长公共子序列的内容: ABDAB

开始执行测试用例...

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: BCAB, 实际结果: BDAB → 通过
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
预期长度: 3, 实际长度: 3 → 通过
预期结果之一: ACE, 实际结果: ACE → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCD
字符串2: EFGH
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 
字符串2: TEST
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 6:
字符串1: AABBAABB
字符串2: ABAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: AABB, 实际结果: ABAB → 通过
测试结果: 全部通过

测试用例 7:
字符串1: XMJYAUZ
字符串2: MZJAWXU
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: MJAU, 实际结果: MJAU → 通过
测试结果: 全部通过

测试用例 8:
字符串1: A
字符串2: A
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 9:
字符串1: A
字符串2: B
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 10:
字符串1: 123@abc
字符串2: a3@x1
预期长度: 3, 实际长度: 2 → 失败
预期结果之一: 3@a, 实际结果: 3@ → 失败
测试结果: 存在问题
 */