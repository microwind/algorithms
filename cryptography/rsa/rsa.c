/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/**
 * 生成RSA密钥对
 * @param rsa RSA结构指针
 * @param bits 密钥位数
 * @return 是否成功
 */
int generate_keys(RSA** rsa, int bits) {
    BIGNUM* bn = BN_new();
    BN_set_word(bn, RSA_F4);
    
    *rsa = RSA_new();
    if (!RSA_generate_key_ex(*rsa, bits, bn, NULL, NULL, NULL, NULL)) {
        return 0;
    }
    
    BN_free(bn);
    return 1;
}

/**
 * RSA加密算法
 * @param rsa RSA结构指针
 * @param message 明文消息
 * @param encrypted 加密结果指针
 * @param encrypted_len 加密结果长度指针
 * @return 是否成功
 */
int encrypt_rsa(RSA* rsa, const char* message, unsigned char** encrypted, int* encrypted_len) {
    int message_len = strlen(message);
    
    *encrypted_len = RSA_size(rsa);
    *encrypted = malloc(*encrypted_len);
    
    int result = RSA_public_encrypt(
        (unsigned char*)message, message_len,
        *encrypted, (unsigned int*)encrypted_len,
        rsa, RSA_PKCS1_PADDING
    );
    
    return result >= 0;
}

/**
 * RSA解密算法
 * @param rsa RSA结构指针
 * @param encrypted 密文
 * @param encrypted_len 密文长度
 * @param decrypted 解密结果指针
 * @param decrypted_len 解密结果长度指针
 * @return 是否成功
 */
int decrypt_rsa(RSA* rsa, unsigned char* encrypted, int encrypted_len, 
               unsigned char** decrypted, int* decrypted_len) {
    *decrypted = malloc(RSA_size(rsa));
    
    int result = RSA_private_decrypt(
        encrypted, encrypted_len,
        *decrypted, (unsigned int*)decrypted_len,
        rsa, RSA_PKCS1_PADDING
    );
    
    return result >= 0;
}

/**
 * 打印密钥信息
 * @param rsa RSA结构指针
 */
void print_key_info(RSA* rsa) {
    const BIGNUM* n = RSA_get0_key(rsa->n);
    const BIGNUM* e = RSA_get0_key(rsa->e);
    const BIGNUM* d = RSA_get0_key(rsa->d);
    
    char* n_str = BN_bn2hex(n);
    char* e_str = BN_bn2hex(e);
    char* d_str = BN_bn2hex(d);
    
    printf("公钥(n,e): (%s,%s)\n", n_str, e_str);
    printf("私钥(n,d): (%s,%s)\n", n_str, d_str);
    
    OPENSSL_free(n_str);
    OPENSSL_free(e_str);
    OPENSSL_free(d_str);
}

/**
 * 主函数，演示RSA加密和解密
 */
int main() {
    printf("=== RSA算法演示 ===\n");
    
    RSA* rsa;
    
    // 生成密钥
    if (!generate_keys(&rsa, 512)) {
        printf("密钥生成失败\n");
        return 1;
    }
    
    print_key_info(&rsa);
    
    const char* message = "Hello, RSA!";
    printf("\n原始消息: %s\n", message);
    printf("消息长度: %d\n", strlen(message));
    
    // 加密
    unsigned char* encrypted;
    int encrypted_len;
    if (!encrypt_rsa(rsa, message, &encrypted, &encrypted_len)) {
        printf("加密失败\n");
        return 1;
    }
    
    printf("加密结果: ");
    for (int i = 0; i < encrypted_len; i++) {
        printf("%02x", encrypted[i]);
    }
    printf("\n");
    
    // 解密
    unsigned char* decrypted;
    int decrypted_len;
    if (!decrypt_rsa(rsa, encrypted, encrypted_len, &decrypted, &decrypted_len)) {
        printf("解密失败\n");
        return 1;
    }
    
    decrypted[decrypted_len] = '\0';
    printf("解密结果: %s\n", decrypted);
    printf("解密长度: %d\n", decrypted_len);
    
    // 验证
    int is_valid = strcmp(message, (char*)decrypted) == 0;
    printf("验证结果: %s\n", is_valid ? "✓ 成功" : "✗ 失败");
    printf("=== 演示结束 ===\n");
    
    RSA_free(rsa);
    free(encrypted);
    free(decrypted);
    
    return 0;
}
