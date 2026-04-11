/*
*
 * LZW压缩算法 - 字典压缩
 *
 * 问题：使用动态字典进行无损数据压缩
 *
 * 核心思想：
 * - 动态构建编码字典
 * - 查找最长匹配字符串
 * - 输出字典索引
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class LZW {

    private static final int MAX_DICT_SIZE = 4096;

    /*
    *
     * LZW压缩
    */
    public static List<Integer> compress(String input) {
        Map<String, Integer> dictionary = new HashMap<>();

        // 初始化字典（单字符）
        for (int i = 0; i < 256; i++) {
            dictionary.put(String.valueOf((char) i), i);
        }

        List<Integer> compressed = new ArrayList<>();
        String current = "";
        int dictSize = 256;

        for (int i = 0; i < input.length(); i++) {
            char nextChar = input.charAt(i);
            String combined = current + nextChar;

            if (dictionary.containsKey(combined)) {
                current = combined;
            } else {
                // 输出current的编码
                compressed.add(dictionary.get(current));

                // 将combined加入字典
                if (dictSize < MAX_DICT_SIZE) {
                    dictionary.put(combined, dictSize++);
                }

                // 重置current为next_char
                current = String.valueOf(nextChar);
            }
        }

        // 输出最后一个编码
        if (!current.isEmpty()) {
            compressed.add(dictionary.get(current));
        }

        return compressed;
    }

    /*
    *
     * LZW解压
    */
    public static String decompress(List<Integer> compressed) {
        Map<Integer, String> dictionary = new HashMap<>();

        // 初始化字典（单字符）
        for (int i = 0; i < 256; i++) {
            dictionary.put(i, String.valueOf((char) i));
        }

        StringBuilder output = new StringBuilder();
        int oldCode = compressed.get(0);
        String oldString = dictionary.get(oldCode);
        output.append(oldString);

        int dictSize = 256;

        for (int i = 1; i < compressed.size(); i++) {
            int newCode = compressed.get(i);
            String string;

            if (!dictionary.containsKey(newCode)) {
                // 特殊情况：new_code不在字典中
                string = oldString + oldString.charAt(0);
            } else {
                string = dictionary.get(newCode);
            }

            output.append(string);

            // 将old_string + string[0]加入字典
            if (dictSize < MAX_DICT_SIZE) {
                dictionary.put(dictSize++, oldString + string.charAt(0));
            }

            oldString = string;
        }

        return output.toString();
    }

    /*
    *
     * 主函数
    */
    public static void main(String[] args) {
        String input = "TOBEORNOTTOBEORTOBEORNOT";
        System.out.println("=== LZW压缩算法 ===");
        System.out.println("原始文本: " + input);

        List<Integer> compressed = compress(input);
        System.out.println("压缩后编码: " + compressed);

        String decompressed = decompress(compressed);
        System.out.println("解压后文本: " + decompressed);

        System.out.println("验证: " + input.equals(decompressed));
    }
}
