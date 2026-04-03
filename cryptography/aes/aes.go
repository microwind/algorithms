package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"fmt"
	"io"
)

// PKCS7填充
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := make([]byte, padding)
	for i := range padtext {
		padtext[i] = byte(padding)
	}
	return append(data, padtext...)
}

func pkcs7Unpad(data []byte, blockSize int) ([]byte, error) {
	if len(data) == 0 {
		return nil, fmt.Errorf("pkcs7: data is empty")
	}
	if len(data)%blockSize != 0 {
		return nil, fmt.Errorf("pkcs7: data is not block-aligned")
	}
	
	padding := int(data[len(data)-1])
	if padding < 1 || padding > blockSize {
		return nil, fmt.Errorf("pkcs7: invalid padding")
	}
	
	// 检查padding是否正确
	for i := len(data) - padding; i < len(data); i++ {
		if data[i] != byte(padding) {
			return nil, fmt.Errorf("pkcs7: invalid padding")
		}
	}
	
	return data[:len(data)-padding], nil
}

func encrypt(plainText, key string) (string, error) {
	keyBytes := []byte(key)
	plainBytes := []byte(plainText)
	
	block, err := aes.NewCipher(keyBytes)
	if err != nil {
		return "", err
	}
	
	// 使用PKCS7填充
	plainBytes = pkcs7Pad(plainBytes, aes.BlockSize)
	
	// 创建加密器
	ciphertext := make([]byte, aes.BlockSize+len(plainBytes))
	iv := ciphertext[:aes.BlockSize]
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return "", err
	}
	
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext[aes.BlockSize:], plainBytes)
	
	return base64.StdEncoding.EncodeToString(ciphertext), nil
}

func decrypt(encryptedText, key string) (string, error) {
	keyBytes := []byte(key)
	ciphertext, err := base64.StdEncoding.DecodeString(encryptedText)
	if err != nil {
		return "", err
	}
	
	block, err := aes.NewCipher(keyBytes)
	if err != nil {
		return "", err
	}
	
	if len(ciphertext) < aes.BlockSize {
		return "", fmt.Errorf("ciphertext too short")
	}
	
	iv := ciphertext[:aes.BlockSize]
	ciphertext = ciphertext[aes.BlockSize:]
	
	// 创建解密器
	mode := cipher.NewCBCDecrypter(block, iv)
	mode.CryptBlocks(ciphertext, ciphertext)
	
	// 移除PKCS7填充
	plainBytes, err := pkcs7Unpad(ciphertext, aes.BlockSize)
	if err != nil {
		return "", err
	}
	
	return string(plainBytes), nil
}

func main() {
	plainText := "Hello, World!"
	key := "1234567890123456" // 16字节密钥
	
	fmt.Printf("原文: %s\n", plainText)
	
	encrypted, err := encrypt(plainText, key)
	if err != nil {
		fmt.Printf("加密失败: %v\n", err)
		return
	}
	fmt.Printf("加密后: %s\n", encrypted)
	
	decrypted, err := decrypt(encrypted, key)
	if err != nil {
		fmt.Printf("解密失败: %v\n", err)
		return
	}
	fmt.Printf("解密后: %s\n", decrypted)
	
	fmt.Printf("验证: %t\n", plainText == decrypted)
}
