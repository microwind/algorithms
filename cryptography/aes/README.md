# AES加密算法

## 问题描述

AES (Advanced Encryption Standard) 是一种广泛使用的对称加密算法，用于保护电子数据。它是美国国家标准与技术研究院（NIST）于2001年发布的加密标准。

## 算法思想

### 核心原理

1. **分组密码**：将明文分成固定长度的块（128位）
2. **对称加密**：使用相同的密钥进行加密和解密
3. **多轮变换**：通过多轮的字节替换、行移位、列混合和轮密钥加
4. **密钥扩展**：将输入密钥扩展为多个轮密钥

### 加密过程

1. **初始轮密钥加**：将明文与初始轮密钥进行异或
2. **多轮变换**（9-11轮）：
   - 字节替换（SubBytes）
   - 行移位（ShiftRows）
   - 列混合（MixColumns）
   - 轮密钥加（AddRoundKey）
3. **最终轮**：不包含列混合

### 解密过程

解密是加密的逆过程，按相反顺序执行逆变换。

## 复杂度分析

- **时间复杂度**: O(n)
- **空间复杂度**: O(n)

## 实现列表

| 语言 | 文件名 |
|------|--------|
| C | [aes.c](./aes.c) |
| Java | [AES.java](./AES.java) |
| Go | [aes.go](./aes.go) |
| Python | [aes.py](./aes.py) |
| JavaScript | [aes.js](./aes.js) |
| Rust | [aes.rs](./aes.rs) |
| TypeScript | [AES.ts](./AES.ts) |

## 应用场景

- 无线网络安全（WPA2）
- 文件加密
- SSL/TLS 协议
- 数据库加密
- 存储设备加密

## 安全性

AES 被认为是安全的，目前没有已知的有效攻击方法。密钥长度支持 128位、192位和256位，密钥越长越安全。

## 注意事项

本实现为教学目的的简化版本，实际应用应使用成熟的加密库：
- Java: javax.crypto
- Go: crypto/aes
- Python: cryptography
- Node.js: crypto module
- Rust: aes crate
