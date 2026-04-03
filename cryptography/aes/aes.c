#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

int aes_encrypt(const unsigned char *plaintext, int plaintext_len, 
               const unsigned char *key, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;
    
    // 创建和初始化上下文
    if(!(ctx = EVP_CIPHER_CTX_new())) return -1;
    
    // 初始化加密操作
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        return -1;
    
    // 提供要加密的消息，并获得加密后的输出
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        return -1;
    ciphertext_len = len;
    
    // 完成加密
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) return -1;
    ciphertext_len += len;
    
    // 清理
    EVP_CIPHER_CTX_free(ctx);
    
    return ciphertext_len;
}

int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len,
               const unsigned char *key, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    
    // 创建和初始化上下文
    if(!(ctx = EVP_CIPHER_CTX_new())) return -1;
    
    // 初始化解密操作
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        return -1;
    
    // 提供要解密的消息，并获得解密后的输出
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        return -1;
    plaintext_len = len;
    
    // 完成解密
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) return -1;
    plaintext_len += len;
    
    // 清理
    EVP_CIPHER_CTX_free(ctx);
    
    return plaintext_len;
}

void print_hex(const unsigned char *buf, int len) {
    for(int i = 0; i < len; i++) {
        printf("%02x", buf[i]);
    }
}

int main() {
    // 16字节密钥
    unsigned char key[16] = "1234567890123456";
    unsigned char plaintext[128] = "Hello, World!";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];
    
    int decryptedtext_len, ciphertext_len;
    
    printf("原文: %s\n", plaintext);
    
    // 加密
    ciphertext_len = aes_encrypt(plaintext, strlen((char*)plaintext), key, ciphertext);
    printf("加密后: ");
    print_hex(ciphertext, ciphertext_len);
    printf("\n");
    
    // 解密
    decryptedtext_len = aes_decrypt(ciphertext, ciphertext_len, key, decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';
    printf("解密后: %s\n", decryptedtext);
    
    printf("验证: %d\n", strcmp((char*)plaintext, (char*)decryptedtext) == 0);
    
    return 0;
}
