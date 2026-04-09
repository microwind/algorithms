/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

/**
 * 字符串算法 - Boyer-Moore (BM) 模式匹配
 * 
 * 算法原理：
 * 1. 它是最高效的字符串匹配算法之一，从模式串的末尾开始向前比较。
 * 2. 包含两个核心启发式规则：
 *    - 坏字符规则 (Bad Character Rule)：当主串中的字符与模式串不匹配时，根据该字符在模式串中的最后出现位置决定跳过的步数。
 *    - 好后缀规则 (Good Suffix Rule)：基于已成功匹配的后缀信息决定跳过步数（本实现重点展示坏字符规则）。
 * 3. 实际应用中，BM 算法往往比 KMP 还要快。
 * 
 * 时间复杂度：平均 O(n / m)，最坏 O(n * m)
 * 空间复杂度：O(字符集大小)
 */
public class BoyerMoore {

    private static final int ALPHABET_SIZE = 256;

    /**
     * 构建坏字符规则表
     * 记录每个字符在模式串中最右出现的位置
     * 
     * @param pattern 模式串
     * @return 坏字符映射数组
     */
    private static int[] buildBadCharTable(String pattern) {
        int[] badChar = new int[ALPHABET_SIZE];
        Arrays.fill(badChar, -1);
        for (int i = 0; i < pattern.length(); i++) {
            badChar[pattern.charAt(i)] = i;
        }
        return badChar;
    }

    /**
     * Boyer-Moore 搜索算法
     * 
     * @param pattern 模式串
     * @param text 主串
     * @return 匹配起始位置列表
     */
    public static List<Integer> search(String pattern, String text) {
        List<Integer> matches = new ArrayList<>();
        int m = pattern.length();
        int n = text.length();
        
        if (m == 0 || m > n) return matches;

        int[] badChar = buildBadCharTable(pattern);
        int shift = 0; // 模式串在主串中的偏移量

        while (shift <= (n - m)) {
            int j = m - 1; // 从模式串最右侧开始

            // 从右向左比较
            while (j >= 0 && pattern.charAt(j) == text.charAt(shift + j)) {
                j--;
            }

            if (j < 0) {
                // 全部匹配成功
                matches.add(shift);
                // 移动模式串（坏字符规则）
                if (shift + m < n) {
                    shift += m - badChar[text.charAt(shift + m)];
                } else {
                    shift += 1;
                }
            } else {
                // 不匹配，利用坏字符规则计算跳过步数
                int badCharValue = badChar[text.charAt(shift + j)];
                // 确保至少移动 1 位
                shift += Math.max(1, j - badCharValue);
            }
        }
        return matches;
    }

    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("Boyer-Moore 模式匹配 - Java 实现");
        System.out.println("====================================================");

        String text = "ABAAABCDABCABCABCAB";
        String pattern = "ABC";

        System.out.println("文本: " + text);
        System.out.println("模式: " + pattern);

        List<Integer> matches = search(pattern, text);
        System.out.println("匹配位置: " + matches);

        // 更多测试
        String[][] cases = {
            {"EXAMPLE", "HERE IS A SIMPLE EXAMPLE"},
            {"AAAA", "AAAAA"},
            {"XYZ", "ABCDE"}
        };
        for (String[] tc : cases) {
            System.out.printf("模式: [%s] in [%s] -> 位置: %s\n", tc[0], tc[1], search(tc[0], tc[1]));
        }
    }
}
