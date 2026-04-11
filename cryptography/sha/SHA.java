/*
*
 * SHA-256哈希算法 - 密码学哈希函数
 *
 * 问题：生成消息的固定长度哈希值
 *
 * 核心思想：
 * - 填充消息到512位的倍数
 * - 分块处理
 * - 位操作和逻辑运算
 *
 * 注意：此实现仅用于教学目的
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
*/

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class SHA {

    /*
    *
     * SHA-256哈希函数（使用Java内置库）
    */
    public static String sha256(String message) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(message.getBytes());

            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) {
                    hexString.append('0');
                }
                hexString.append(hex);
            }

            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("SHA-256 algorithm not found", e);
        }
    }

    /*
    *
     * 主函数
    */
    public static void main(String[] args) {
        System.out.println("=== SHA-256哈希算法 ===");

        String message = "Hello, World!";
        System.out.println("消息: " + message);

        String hash = sha256(message);
        System.out.println("SHA-256: " + hash);

        System.out.println("\n注意：此实现使用Java内置库，");
        System.out.println("实际应用应使用成熟的加密库。");
    }
}
