/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串递归操作示例
 * 
 * 算法特点：
 * - 演示递归在字符串处理中的应用
 * - 包含字符串反转、回文检查、元音计数
 * 
 * 学习重点：理解递归在字符串操作中的使用
 */
public class StringOperations {
    
    /**
     * 递归反转字符串
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param s 要反转的字符串
     * @return 反转后的字符串
     */
    public static String reverseString(String s) {
        // 基础情况：空字符串或单个字符
        if (s.length() <= 1) {
            return s;
        }
        
        // 递归：剩余部分反转 + 第一个字符放到末尾
        return reverseString(s.substring(1)) + s.charAt(0);
    }
    
    /**
     * 递归检查字符串是否为回文
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param s 要检查的字符串
     * @return 是否为回文
     */
    public static boolean isPalindrome(String s) {
        s = s.toLowerCase(); // 忽略大小写
        
        // 基础情况：空字符串或单个字符是回文
        if (s.length() <= 1) {
            return true;
        }
        
        // 如果首尾字符不同，不是回文
        if (s.charAt(0) != s.charAt(s.length() - 1)) {
            return false;
        }
        
        // 递归检查去掉首尾后的中间部分
        return isPalindrome(s.substring(1, s.length() - 1));
    }
    
    /**
     * 递归计算字符串中元音字母的数量
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param s 要计算的字符串
     * @return 元音字母数量
     */
    public static int countVowels(String s) {
        String vowels = "aeiouAEIOU";
        
        // 基础情况：空字符串
        if (s.isEmpty()) {
            return 0;
        }
        
        // 检查第一个字符是否是元音
        int firstIsVowel = vowels.indexOf(s.charAt(0)) != -1 ? 1 : 0;
        
        // 递归计算剩余部分
        return firstIsVowel + countVowels(s.substring(1));
    }
    
    /**
     * 主函数 - 测试字符串递归操作
     */
    public static void main(String[] args) {
        // 测试1：字符串反转
        String testStr1 = "Hello";
        System.out.println("1. 字符串反转:");
        System.out.println("   原字符串: '" + testStr1 + "'");
        System.out.println("   反转后:   '" + reverseString(testStr1) + "'");
        System.out.println("===");
        
        // 测试2：回文检查
        System.out.println("2. 回文检查:");
        String[] testCases = {"radar", "hello", "Aba", "level", "aabbaa", "cc", "ddd"};
        for (String s : testCases) {
            String result = isPalindrome(s) ? "是回文" : "不是回文";
            System.out.println("   '" + s + "' -> " + result);
        }
        System.out.println("===");
        
        // 测试3：元音计数
        System.out.println("3. 元音计数:");
        System.out.println("   字符串: '" + testStr2 + "'");
        System.out.println("   元音数量: " + countVowels(testStr2));
        System.out.println("===");
    }
}

/*打印结果
jarry@Mac string-recursion % javac StringOperations.java && java StringOperations
1. 字符串反转:
   原字符串: 'Hello'
   反转后:   'olleH'
===
2. 回文检查:
   'radar' -> 是回文
   'hello' -> 不是回文
   'Aba' -> 是回文
   'level' -> 是回文
   'aabbaa' -> 是回文
   'cc' -> 是回文
   'ddd' -> 是回文
===
3. 元音计数:
   字符串: 'Hello World'
   元音数量: 3
===
*/
