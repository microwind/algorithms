/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 字符串反转 (String Reversal)
 * 
 * 算法原理：
 * 1. 字符串反转是指将字符串中字符的顺序颠倒。
 * 2. 提供多种实现方式：
 *    - 双指针法 (Two-pointer)：首尾互换字符数组。
 *    - 递归法 (Recursive)：逐个取出第一个字符拼在后面。
 *    - 内建 API：使用 StringBuilder 或 StringBuffer 的 reverse 方法。
 *    - 栈方法：利用先进后出的特性。
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(n) (通常需要字符数组或递归栈)
 */
public class StringReversal {

    /**
     * 双指针法反转字符串
     * 
     * @param s 原始字符串
     * @return 反转后的字符串
     */
    public static String reverseTwoPointer(String s) {
        if (s == null || s.length() <= 1) return s;
        char[] charArray = s.toCharArray();
        int left = 0;
        int right = charArray.length - 1;

        while (left < right) {
            // 交换首尾
            char temp = charArray[left];
            charArray[left] = charArray[right];
            charArray[right] = temp;
            left++;
            right--;
        }
        return new String(charArray);
    }

    /**
     * 递归法反转字符串
     */
    public static String reverseRecursive(String s) {
        if (s == null || s.length() <= 1) {
            return s;
        }
        // 分解为：剩余部分的反转 + 第一个字符
        return reverseRecursive(s.substring(1)) + s.charAt(0);
    }

    /**
     * 使用 Java 内建 API (StringBuilder)
     */
    public static String reverseBuiltIn(String s) {
        if (s == null) return null;
        return new StringBuilder(s).reverse().toString();
    }

    /**
     * 使用栈反转字符串
     */
    public static String reverseStack(String s) {
        if (s == null || s.isEmpty()) return s;
        java.util.Stack<Character> stack = new java.util.Stack<>();
        for (char c : s.toCharArray()) {
            stack.push(c);
        }
        
        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            sb.append(stack.pop());
        }
        return sb.toString();
    }

    /**
     * 主函数 - 测试反转算法
     */
    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("字符串反转 (String Reversal) - Java 实现");
        System.out.println("====================================================");

        String[] testStrings = {
            "Hello World",
            "Algorithm",
            "12345",
            "A",
            "",
            "OpenAI"
        };

        for (String test : testStrings) {
            System.out.printf("原字符串: [%s]\n", test);
            System.out.printf("  双指针: [%s] | 递归: [%s] | API: [%s] | 栈: [%s]\n",
                reverseTwoPointer(test),
                reverseRecursive(test),
                reverseBuiltIn(test),
                reverseStack(test));
        }
    }
}
