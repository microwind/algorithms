/*
*
 * 凯撒密码 - 简单的替换加密
 *
 * 问题：将字母表中的每个字母移动固定位数
 *
 * 核心思想：
 * - 字母替换
 * - 循环移位
 * - 保持大小写
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

public class Caesar {

    /*
    *
     * 凯撒加密
    */
    public static String encrypt(String text, int shift) {
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);

            if (Character.isUpperCase(c)) {
                c = (char) ((c - 'A' + shift) % 26 + 'A');
            } else if (Character.isLowerCase(c)) {
                c = (char) ((c - 'a' + shift) % 26 + 'a');
            }

            result.append(c);
        }

        return result.toString();
    }

    /*
    *
     * 凯撒解密
    */
    public static String decrypt(String text, int shift) {
        return encrypt(text, 26 - (shift % 26));
    }

    /*
    *
     * 主函数
    */
    public static void main(String[] args) {
        System.out.println("=== 凯撒密码 ===");

        String text = "Hello, World!";
        int shift = 3;

        System.out.println("明文: " + text);
        System.out.println("移位数: " + shift);

        // 加密
        String encrypted = encrypt(text, shift);
        System.out.println("加密后: " + encrypted);

        // 解密
        String decrypted = decrypt(encrypted, shift);
        System.out.println("解密后: " + decrypted);

        System.out.println("验证: " + text.equals(decrypted));
    }
}
