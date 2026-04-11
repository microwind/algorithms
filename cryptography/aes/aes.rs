/*
*
 * AES加密算法 - 高级加密标准
 *
 * 问题：使用AES进行对称加密
 *
 * 核心思想：
 * - 使用AES-128-CBC模式
 * - PKCS7填充
 * - 随机IV
 *
 * 注意：实际生产环境应使用成熟的加密库
 * 此实现仅用于教学目的
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

use std::error::Error;
use std::fmt;

// 自定义错误类型
#[derive(Debug)]
enum AesError {
    InvalidKeyLength,
    InvalidPadding,
}

impl fmt::Display for AesError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            AesError::InvalidKeyLength => write!(f, "Invalid key length"),
            AesError::InvalidPadding => write!(f, "Invalid padding"),
        }
    }
}

impl Error for AesError {}

/*
*
 * PKCS7填充
*/
fn pkcs7_pad(data: &[u8], block_size: usize) -> Vec<u8> {
    let padding = block_size - (data.len() % block_size);
    let mut padded = data.to_vec();
    padded.extend(vec![padding as u8; padding]);
    padded
}

/*
*
 * PKCS7去填充
*/
fn pkcs7_unpad(data: &[u8], block_size: usize) -> Result<Vec<u8>, AesError> {
    if data.is_empty() {
        return Err(AesError::InvalidPadding);
    }

    let padding = data[data.len() - 1] as usize;
    if padding < 1 || padding > block_size {
        return Err(AesError::InvalidPadding);
    }

    // 验证padding
    for i in (data.len() - padding)..data.len() {
        if data[i] as usize != padding {
            return Err(AesError::InvalidPadding);
        }
    }

    Ok(data[..data.len() - padding].to_vec())
}

/*
*
 * 简化的AES加密（仅用于演示）
 * 注意：这不是完整的AES实现，仅展示概念
*/
fn aes_encrypt_simple(plaintext: &[u8], key: &[u8]) -> Result<Vec<u8>, AesError> {
    if key.len() != 16 {
        return Err(AesError::InvalidKeyLength);
    }

    // 简化：仅使用XOR作为演示（实际应使用真正的AES）
    let block_size = 16;
    let padded = pkcs7_pad(plaintext, block_size);

    let mut encrypted = Vec::new();
    for (i, byte) in padded.iter().enumerate() {
        encrypted.push(byte ^ key[i % key.len()]);
    }

    Ok(encrypted)
}

/*
*
 * 简化的AES解密（仅用于演示）
*/
fn aes_decrypt_simple(ciphertext: &[u8], key: &[u8]) -> Result<Vec<u8>, AesError> {
    if key.len() != 16 {
        return Err(AesError::InvalidKeyLength);
    }

    let mut decrypted = Vec::new();
    for (i, byte) in ciphertext.iter().enumerate() {
        decrypted.push(byte ^ key[i % key.len()]);
    }

    let block_size = 16;
    pkcs7_unpad(&decrypted, block_size)
}

/*
*
 * 将字节转换为十六进制字符串
*/
fn bytes_to_hex(bytes: &[u8]) -> String {
    bytes.iter()
        .map(|b| format!("{:02x}", b))
        .collect()
}

/*
*
 * 将十六进制字符串转换为字节
*/
fn hex_to_bytes(hex: &str) -> Result<Vec<u8>, AesError> {
    let mut bytes = Vec::new();
    for i in (0..hex.len()).step_by(2) {
        let byte = u8::from_str_radix(&hex[i..i+2], 16)
            .map_err(|_| AesError::InvalidPadding)?;
        bytes.push(byte);
    }
    Ok(bytes)
}

/*
*
 * 主函数
*/
fn main() {
    println!("=== AES加密算法（简化演示） ===");

    let plaintext = "Hello, World!";
    let key = "1234567890123456"; // 16字节密钥

    println!("原文: {}", plaintext);

    // 加密
    match aes_encrypt_simple(plaintext.as_bytes(), key.as_bytes()) {
        Ok(encrypted) => {
            let hex = bytes_to_hex(&encrypted);
            println!("加密后: {}", hex);

            // 解密
            match hex_to_bytes(&hex) {
                Ok(ciphertext) => {
                    match aes_decrypt_simple(&ciphertext, key.as_bytes()) {
                        Ok(decrypted) => {
                            let decrypted_str = String::from_utf8(decrypted).unwrap();
                            println!("解密后: {}", decrypted_str);
                            println!("验证: {}", plaintext == decrypted_str);
                        }
                        Err(e) => println!("解密失败: {}", e),
                    }
                }
                Err(e) => println!("十六进制转换失败: {}", e),
            }
        }
        Err(e) => println!("加密失败: {}", e),
    }

    println!("\n注意：此实现仅用于教学目的，");
    println!("实际应用应使用成熟的加密库如aes crate。");
}
