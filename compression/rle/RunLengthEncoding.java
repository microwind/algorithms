/*
*
 * 游程编码 (RLE) - 简单的压缩算法
 *
 * 问题：将连续重复的字符压缩为字符+计数的形式
 *
 * 核心思想：
 * - 统计连续相同字符的数量
 * - 用字符+计数表示重复序列
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

public class RunLengthEncoding {

    /*
    *
     * 压缩函数
     *
     * @param text 输入文本
     * @return 压缩后的文本
    */
    public static String compress(String text) {
        if (text == null || text.isEmpty()) {
            return text;
        }

        StringBuilder compressed = new StringBuilder();
        char currentChar = text.charAt(0);
        int count = 1;

        for (int i = 1; i < text.length(); i++) {
            if (text.charAt(i) == currentChar) {
                count++;
            } else {
                compressed.append(currentChar);
                if (count > 1) {
                    compressed.append(count);
                }
                currentChar = text.charAt(i);
                count = 1;
            }
        }

        // 处理最后一个字符
        compressed.append(currentChar);
        if (count > 1) {
            compressed.append(count);
        }

        return compressed.toString();
    }

    /*
    *
     * 解压函数
     *
     * @param compressed 压缩后的文本
     * @return 解压后的文本
    */
    public static String decompress(String compressed) {
        if (compressed == null || compressed.isEmpty()) {
            return compressed;
        }

        StringBuilder decompressed = new StringBuilder();
        int i = 0;

        while (i < compressed.length()) {
            char currentChar = compressed.charAt(i);
            i++;
            StringBuilder countStr = new StringBuilder();

            // 解析数字
            while (i < compressed.length() && Character.isDigit(compressed.charAt(i))) {
                countStr.append(compressed.charAt(i));
                i++;
            }

            int count = 1;
            if (countStr.length() > 0) {
                count = Integer.parseInt(countStr.toString());
            }

            // 添加字符
            for (int j = 0; j < count; j++) {
                decompressed.append(currentChar);
            }
        }

        return decompressed.toString();
    }

    /*
    *
     * 计算压缩比
     *
     * @param original 原始文本
     * @param compressed 压缩后的文本
     * @return 压缩比
    */
    public static double compressionRatio(String original, String compressed) {
        return (double) compressed.length() / original.length();
    }

    /*
    *
     * 主函数
    */
    public static void main(String[] args) {
        String text = "AAAABBBCCDAA";
        System.out.println("=== 游程编码 (RLE) ===");
        System.out.println("原始文本: " + text);

        String compressed = compress(text);
        System.out.println("压缩后: " + compressed);

        String decompressed = decompress(compressed);
        System.out.println("解压后: " + decompressed);

        System.out.printf("压缩比: %.2f\n", compressionRatio(text, compressed));
        System.out.println("验证: " + text.equals(decompressed));

        // 测试用例2
        System.out.println("\n测试用例2:");
        String text2 = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB";
        String compressed2 = compress(text2);
        String decompressed2 = decompress(compressed2);
        System.out.println("原始文本: " + text2);
        System.out.println("压缩后: " + compressed2);
        System.out.println("解压后: " + decompressed2);
        System.out.println("验证: " + text2.equals(decompressed2));
    }
}
