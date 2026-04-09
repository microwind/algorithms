/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.ArrayList;
import java.util.List;

/**
 * 字符串算法 - Rabin-Karp 模式匹配
 * 
 * 算法原理：
 * 1. 使用哈希函数对模式串进行哈希计算。
 * 2. 在主串中使用滑动窗口，计算每个窗口的哈希值。
 * 3. 利用滚动哈希 (Rolling Hash) 技巧，在 O(1) 时间内从当前窗口哈希计算出下一个窗口哈希。
 * 4. 只有当哈希值相等时，才进行逐字符比较以确认是否匹配（解决哈希冲突）。
 * 
 * 时间复杂度：平均 O(n + m)，最坏 O(n * m)
 * 空间复杂度：O(1)
 */
public class RabinKarp {

    // 字符集大小（基数），通常取 256
    private static final int D = 256;
    // 用于取模的素数，防止哈希值溢出
    private static final int Q = 101;

    /**
     * Rabin-Karp 搜索算法
     * 
     * @param pattern 模式串
     * @param text 主串
     * @return 匹配位置列表
     */
    public static List<Integer> search(String pattern, String text) {
        List<Integer> matches = new ArrayList<>();
        int m = pattern.length();
        int n = text.length();
        
        if (m == 0 || m > n) return matches;

        int p = 0; // 模式串的哈希值
        int t = 0; // 文本窗口的哈希值
        int h = 1; // h = D^(m-1) % Q

        // 计算 h 的值: D^(m-1) % Q
        for (int i = 0; i < m - 1; i++) {
            h = (h * D) % Q;
        }

        // 计算模式串和文本第一个窗口的初始哈希值
        for (int i = 0; i < m; i++) {
            p = (D * p + pattern.charAt(i)) % Q;
            t = (D * t + text.charAt(i)) % Q;
        }

        // 滑动窗口遍历主串
        for (int i = 0; i <= n - m; i++) {
            // 如果哈希值匹配，再进行逐字符确认
            if (p == t) {
                int j;
                for (j = 0; j < m; j++) {
                    if (text.charAt(i + j) != pattern.charAt(j)) {
                        break;
                    }
                }
                if (j == m) {
                    matches.add(i);
                }
            }

            // 计算下一个窗口的哈希值: 移除最左侧字符，加入最右侧字符
            if (i < n - m) {
                t = (D * (t - text.charAt(i) * h) + text.charAt(i + m)) % Q;
                // 处理负数情况，确保 t 为正
                if (t < 0) {
                    t = (t + Q);
                }
            }
        }
        return matches;
    }

    /**
     * 主函数 - 测试 Rabin-Karp 算法
     */
    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("Rabin-Karp 模式匹配 - Java 实现");
        System.out.println("====================================================");

        String text = "ABABDABACDABABCABAB";
        String pattern = "ABABCABAB";

        System.out.println("文本: " + text);
        System.out.println("模式: " + pattern);

        List<Integer> matches = search(pattern, text);
        System.out.println("匹配位置: " + matches);

        // 更多测试用例
        String[][] testCases = {
            {"ABC", "AABABC"},
            {"AAAAA", "AAA"},
            {"TEST", "THIS IS A TEST CASE"},
            {"NONE", "ABCDEFG"}
        };

        for (String[] tc : testCases) {
            String p = tc[0];
            String t = tc[1];
            System.out.printf("模式: [%s] in [%s] -> 位置: %s\n", p, t, search(p, t));
        }
    }
}

/*打印结果
jarry@Mac pattern-matching % java RabinKarp.java
====================================================
Rabin-Karp 模式匹配 - Java 实现
====================================================
文本: ABABDABACDABABCABAB
模式: ABABCABAB
匹配位置: [10]
模式: [ABC] in [AABABC] -> 位置: [3]
模式: [AAAAA] in [AAA] -> 位置: []
模式: [TEST] in [THIS IS A TEST CASE] -> 位置: [10]
模式: [NONE] in [ABCDEFG] -> 位置: []
*/
