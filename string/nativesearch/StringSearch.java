/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 朴素字符串搜索 (Naive String Search)
 * 
 * 算法原理：
 * 1. 最基础的字符串匹配方法，也称为暴力搜索。
 * 2. 将模式串 (pattern) 与主串 (text) 的每个位置对齐。
 * 3. 逐个字符比较，若匹配成功则继续比较下一个字符。
 * 4. 若匹配失败，则将模式串向右移动一位，从头开始比较。
 * 
 * 时间复杂度：O(n * m)，其中 n 为主串长度，m 为模式串长度。
 * 空间复杂度：O(1)，仅使用常数个额外变量。
 */
public class StringSearch {

    /**
     * 朴素搜索实现 - 双重循环
     * 
     * @param pattern 模式串 (要找的内容)
     * @param text 主串 (被查找的内容)
     * @return 匹配成功的起始位置，若未找到返回 -1
     */
    public int find(String pattern, String text) {
        int m = pattern.length();
        int n = text.length();
        
        // 外层循环：移动模式串在主串中的起始位置
        // 关键点：i 的最大值应为 n - m，避免越界
        for (int i = 0; i <= n - m; i++) {
            int j = 0;
            // 内层循环：比较当前位置开始的字符
            for (; j < m; j++) {
                if (pattern.charAt(j) != text.charAt(i + j)) {
                    // 字符不匹配，跳出内层循环
                    break;
                }
            }
            // 如果 j 走到了 m，说明模式串全部字符匹配成功
            if (j == m) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 朴素搜索实现 - for + while 写法 (更严谨的边界判断)
     */
    public int find2(String pattern, String text) {
        int m = pattern.length();
        int n = text.length();
        
        if (m == 0) return 0;
        if (m > n) return -1;
        
        for (int i = 0; i <= n - m; i++) {
            int j = 0;
            while (j < m && text.charAt(i + j) == pattern.charAt(j)) {
                j++;
            }
            if (j == m) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 主函数 - 测试搜索算法
     */
    public static void main(String[] args) {
        StringSearch searcher = new StringSearch();
        
        String[][] testCases = {
            {"ABC", "AABABC", "3"},
            {"AAB", "AAAABC", "2"},
            {"ABC", "AABAC", "-1"},
            {"", "ANY", "0"},
            {"LONG_PATTERN", "SHORT", "-1"}
        };
        
        System.out.println("朴素字符串搜索测试:");
        for (String[] tc : testCases) {
            String p = tc[0];
            String t = tc[1];
            int expected = Integer.parseInt(tc[2]);
            
            int res1 = searcher.find(p, t);
            int res2 = searcher.find2(p, t);
            
            System.out.printf("模式: [%s] | 文本: [%s] | 结果: %d (预期: %d) | 状态: %s\n",
                p, t, res1, expected, (res1 == expected ? "OK" : "FAIL"));
        }
    }
}
