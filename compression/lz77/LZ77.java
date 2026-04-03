/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

public class LZ77 {
    
    static class Token {
        int offset, length;
        char character;
        
        /**
         * LZ77压缩令牌构造函数
         * @param offset 偏移量
         * @param length 匹配长度
         * @param character 下一个字符
         */
        Token(int offset, int length, char character) {
            this.offset = offset;
            this.length = length;
            this.character = character;
        }
        
        @Override
        public String toString() {
            if (length > 0) {
                return String.format("(%d,%d)", offset, length);
            } else {
                return String.format("(%c)", character);
            }
        }
    }
    
    /**
     * LZ77压缩算法
     * @param input 输入字符串
     * @return 压缩后的令牌列表
     */
    public static List<Token> compress(String input) {
        System.out.println("LZ77压缩开始...");
        List<Token> tokens = new ArrayList<>();
        int windowSize = 256;
        int position = 0;
        
        while (position < input.length()) {
            int maxLength = Math.min(windowSize, position);
            String window = input.substring(Math.max(0, position - maxLength), position);
            
            int bestLength = 0;
            int bestOffset = 0;
            
            // 在窗口中搜索最长匹配
            for (int i = 0; i < window.length(); i++) {
                int matchLength = 0;
                while (position + matchLength < input.length() &&
                       i + matchLength < window.length() &&
                       input.charAt(position + matchLength) == window.charAt(i + matchLength)) {
                    matchLength++;
                }
                
                if (matchLength > bestLength) {
                    bestLength = matchLength;
                    bestOffset = window.length() - i;
                }
            }
            
            if (bestLength >= 3) { // 最小匹配长度
                char nextChar = position + bestLength < input.length() ? 
                               input.charAt(position + bestLength) : '\0';
                tokens.add(new Token(bestOffset, bestLength, nextChar));
                System.out.println("找到匹配: 偏移=" + bestOffset + ", 长度=" + bestLength);
                position += bestLength + 1;
            } else {
                tokens.add(new Token(0, 0, input.charAt(position)));
                System.out.println("字面量: " + input.charAt(position));
                position++;
            }
        }
        
        System.out.println("LZ77压缩完成，令牌数: " + tokens.size());
        return tokens;
    }
    
    /**
     * LZ77解压算法
     * @param tokens 压缩令牌列表
     * @return 解压后的字符串
     */
    public static String decompress(List<Token> tokens) {
        System.out.println("LZ77解压开始...");
        StringBuilder output = new StringBuilder();
        
        for (int i = 0; i < tokens.size(); i++) {
            Token token = tokens.get(i);
            System.out.println("处理令牌 " + i + ": " + token);
            
            if (token.length > 0) {
                int start = output.length() - token.offset;
                for (int j = 0; j < token.length; j++) {
                    output.append(output.charAt(start + j));
                }
                if (token.character != '\0') {
                    output.append(token.character);
                }
            } else {
                output.append(token.character);
            }
        }
        
        System.out.println("LZ77解压完成，长度: " + output.length());
        return output.toString();
    }
    
    /**
     * 计算压缩比
     * @param original 原始字符串
     * @param compressed 压缩令牌列表
     * @return 压缩比
     */
    public static double compressionRatio(String original, List<Token> compressed) {
        int originalSize = original.length() * 8; // 假设每个字符8位
        int compressedSize = 0;
        for (Token token : compressed) {
            compressedSize += 16; // 偏移和长度各8位
            if (token.length > 0) compressedSize += 8; // 字符8位
        }
        return (double) compressedSize / originalSize;
    }
    
    /**
     * 主函数，演示LZ77压缩和解压
     */
    public static void main(String[] args) {
        String input = "ABABABABABAABABABABA";
        System.out.println("=== LZ77算法演示 ===");
        System.out.println("原始文本: " + input);
        System.out.println("原始长度: " + input.length());
        
        // 压缩
        List<Token> compressed = compress(input);
        System.out.println("压缩结果: " + compressed);
        
        // 计算压缩比
        double ratio = compressionRatio(input, compressed);
        System.out.println("压缩比: " + String.format("%.2f", ratio));
        
        // 解压
        String decompressed = decompress(compressed);
        System.out.println("解压结果: " + decompressed);
        System.out.println("解压长度: " + decompressed.length());
        
        // 验证
        boolean isValid = input.equals(decompressed);
        System.out.println("验证结果: " + (isValid ? "✓ 成功" : "✗ 失败"));
        System.out.println("=== 演示结束 ===");
    }
}
