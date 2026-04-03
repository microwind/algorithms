/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

package main

import (
	"crypto/rand"
	"encoding/base64"
	"fmt"
	"math/big"
)

type RSA struct {
	n, e, d *big.Int
}

/**
 * 创建新的RSA实例
 * @param bitLength 密钥位数
 * @return RSA指针
 */
func NewRSA(bitLength int) *RSA {
	rsa := &RSA{}
	rsa.generateKeys(bitLength)
	return rsa
}

/**
 * 生成RSA密钥对
 * @param bitLength 密钥位数
 */
func (rsa *RSA) generateKeys(bitLength int) {
	fmt.Println("生成RSA密钥对...")
	
	// 选择两个大质数
	p, _ := rand.Prime(rand.Reader, bitLength/2)
	q, _ := rand.Prime(rand.Reader, bitLength/2)
	fmt.Printf("生成质数p: %s\n", p)
	fmt.Printf("生成质数q: %s\n", q)
	
	// 计算n = p * q
	rsa.n = new(big.Int).Mul(p, q)
	fmt.Printf("计算n = p * q: %s\n", rsa.n)
	
	// 计算φ(n) = (p-1)*(q-1)
	phi := new(big.Int).Sub(p, big.NewInt(1))
	phi.Mul(phi, new(big.Int).Sub(q, big.NewInt(1)))
	fmt.Printf("计算φ(n): %s\n", phi)
	
	// 选择公钥指数e
	rsa.e = big.NewInt(65537)
	fmt.Printf("选择公钥指数e: %s\n", rsa.e)
	
	// 计算私钥指数d
	rsa.d = new(big.Int)
	rsa.d.ModInverse(rsa.e, phi)
	fmt.Printf("计算私钥指数d: %s\n", rsa.d)
	fmt.Println("RSA密钥对生成完成")
}

/**
 * RSA加密算法
 * @param message 明文消息
 * @return Base64编码的密文，错误信息
 */
func (rsa *RSA) Encrypt(message string) (string, error) {
	fmt.Println("开始RSA加密...")
	fmt.Printf("明文: %s\n", message)
	
	m := new(big.Int).SetBytes([]byte(message))
	fmt.Printf("转换为数字: %s\n", m)
	
	c := new(big.Int).Exp(m, rsa.e, rsa.n)
	fmt.Printf("加密计算 c = m^e mod n: %s\n", c)
	
	ciphertext := base64.StdEncoding.EncodeToString(c.Bytes())
	fmt.Printf("加密完成，密文长度: %d\n", len(ciphertext))
	return ciphertext, nil
}

/**
 * RSA解密算法
 * @param ciphertext Base64编码的密文
 * @return 解密后的明文，错误信息
 */
func (rsa *RSA) Decrypt(ciphertext string) (string, error) {
	fmt.Println("开始RSA解密...")
	fmt.Printf("密文: %s\n", ciphertext)
	
	c, err := base64.StdEncoding.DecodeString(ciphertext)
	if err != nil {
		return "", fmt.Errorf("Base64解码失败: %v", err)
	}
	
	fmt.Printf("转换为数字: %s\n", c)
	
	m := new(big.Int).Exp(c, rsa.d, rsa.n)
	fmt.Printf("解密计算 m = c^d mod n: %s\n", m)
	
	message := string(m.Bytes())
	fmt.Printf("解密完成，明文长度: %d\n", len(message))
	return message, nil
}

/**
 * 获取公钥信息
 * @return 公钥字符串
 */
func (rsa *RSA) GetPublicKey() string {
	return fmt.Sprintf("公钥(n,e): (%s,%s)", rsa.n, rsa.e)
}

/**
 * 获取私钥信息
 * @return 私钥字符串
 */
func (rsa *RSA) GetPrivateKey() string {
	return fmt.Sprintf("私钥(n,d): (%s,%s)", rsa.n, rsa.d)
}

/**
 * 主函数，演示RSA加密和解密
 */
func main() {
	fmt.Println("=== RSA算法演示 ===")
	
	rsa := NewRSA(512) // 512位密钥
	fmt.Println(rsa.GetPublicKey())
	fmt.Println(rsa.GetPrivateKey())
	
	message := "Hello, RSA!"
	fmt.Printf("\n原始消息: %s\n", message)
	fmt.Printf("消息长度: %d\n", len(message))
	
	// 加密
	encrypted, err := rsa.Encrypt(message)
	if err != nil {
		fmt.Printf("加密失败: %v\n", err)
		return
	}
	fmt.Printf("加密结果: %s\n", encrypted)
	
	// 解密
	decrypted, err := rsa.Decrypt(encrypted)
	if err != nil {
		fmt.Printf("解密失败: %v\n", err)
		return
	}
	fmt.Printf("解密结果: %s\n", decrypted)
	
	// 验证
	isValid := message == decrypted
	if isValid {
		fmt.Println("验证结果: ✓ 成功")
	} else {
		fmt.Println("验证结果: ✗ 失败")
	}
	fmt.Println("=== 演示结束 ===")
}
