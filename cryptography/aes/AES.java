import javax.crypto.*;
import javax.crypto.spec.*;
import java.security.*;
import java.util.Base64;

public class AES {
    
    public static String encrypt(String plainText, String key) throws Exception {
        // 创建密钥
        SecretKeySpec secretKey = new SecretKeySpec(key.getBytes(), "AES");
        
        // 创建加密器
        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        
        // 加密
        byte[] encryptedBytes = cipher.doFinal(plainText.getBytes());
        return Base64.getEncoder().encodeToString(encryptedBytes);
    }
    
    public static String decrypt(String encryptedText, String key) throws Exception {
        // 创建密钥
        SecretKeySpec secretKey = new SecretKeySpec(key.getBytes(), "AES");
        
        // 创建解密器
        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        
        // 解密
        byte[] decryptedBytes = cipher.doFinal(Base64.getDecoder().decode(encryptedText));
        return new String(decryptedBytes);
    }
    
    public static void main(String[] args) throws Exception {
        String plainText = "Hello, World!";
        String key = "1234567890123456"; // 16字节密钥
        
        System.out.println("原文: " + plainText);
        
        String encrypted = encrypt(plainText, key);
        System.out.println("加密后: " + encrypted);
        
        String decrypted = decrypt(encrypted, key);
        System.out.println("解密后: " + decrypted);
        
        System.out.println("验证: " + plainText.equals(decrypted));
    }
}
