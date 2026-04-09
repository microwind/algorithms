/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 回文检查 (Palindrome Check)
 * 
 * 算法原理：
 * 1. 回文是指正读和反读都相同的字符串（忽略大小写、空格及非字母数字字符）。
 * 2. 提供四种不同的检测方法：
 *    - 双指针法 (Two-pointer)：从两端向中间移动。
 *    - 字符串反转法 (Reverse)：反转后与原串比较。
 *    - 递归法 (Recursive)：分解为子串检测。
 *    - 栈方法 (Stack)：利用后进先出的特性比较。
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(1) (双指针法) 或 O(n) (反转/栈)
 */
public class PalindromeChecker {

    /**
     * 双指针法检测回文 - 最推荐的方式
     * 
     * @param s 待检测字符串
     * @return 是否为回文
     */
    public static boolean isPalindromeTwoPointer(String s) {
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // 跳过非字母数字字符（模拟正则表达式处理）
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }

            // 忽略大小写进行比较
            if (Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) {
                return false;
            }

            left++;
            right--;
        }
        return true;
    }

    /**
     * 字符串反转法检测回文
     * 
     * @param s 待检测字符串
     */
    public static boolean isPalindromeReverse(String s) {
        // 清洗字符串：只保留字母数字并转为小写
        String cleaned = s.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();
        // 反转字符串
        String reversed = new StringBuilder(cleaned).reverse().toString();
        // 比较
        return cleaned.equals(reversed);
    }

    /**
     * 递归法检测回文
     */
    public static boolean isPalindromeRecursive(String s) {
        String cleaned = s.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();
        return isPalindromeRecursiveHelper(cleaned, 0, cleaned.length() - 1);
    }

    private static boolean isPalindromeRecursiveHelper(String s, int left, int right) {
        // 基准情况：重叠或相交
        if (left >= right) {
            return true;
        }
        if (s.charAt(left) != s.charAt(right)) {
            return false;
        }
        return isPalindromeRecursiveHelper(s, left + 1, right - 1);
    }

    /**
     * 栈方法检测回文
     */
    public static boolean isPalindromeStack(String s) {
        String cleaned = s.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();
        java.util.Stack<Character> stack = new java.util.Stack<>();

        int len = cleaned.length();
        int mid = len / 2;

        // 前半段入栈
        for (int i = 0; i < mid; i++) {
            stack.push(cleaned.charAt(i));
        }

        // 后半段与栈顶比较（跳过奇数中间位）
        int start = (len % 2 == 0) ? mid : mid + 1;
        for (int i = start; i < len; i++) {
            if (stack.pop() != cleaned.charAt(i)) {
                return false;
            }
        }
        return true;
    }

    /**
     * 主函数 - 测试回文检测
     */
    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("回文检测 (Palindrome Checker) - Java 实现");
        System.out.println("====================================================");

        String[] testStrings = {
            "racecar",
            "A man, a plan, a canal: Panama",
            "No lemon, no melon",
            "Hello, World!",
            "12321",
            "Madam"
        };

        for (String test : testStrings) {
            System.out.printf("字符串: [%s]\n", test);
            System.out.printf("  双指针: %s | 反转: %s | 递归: %s | 栈: %s\n",
                isPalindromeTwoPointer(test),
                isPalindromeReverse(test),
                isPalindromeRecursive(test),
                isPalindromeStack(test));
        }
    }
}
