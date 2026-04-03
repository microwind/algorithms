/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import random
import base64
import math

def is_prime(n, k=5):
    """
    Miller-Rabin素性测试
    @param n 待测试的数
    @param k 测试轮数
    @return 是否为质数
    """
    if n <= 1:
        return False
    elif n <= 3:
        return True
    elif n % 2 == 0:
        return False
    
    # 写成 n = 2^r * d + 1
    d = n - 1
    r = 0
    while d % 2 == 0:
        d //= 2
        r += 1
    
    # 测试k次
    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d, n)
        
        if x == 1 or x == n - 1:
            continue
        
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    
    return True

def generate_prime(bits):
    """
    生成指定位数的大质数
    @param bits 位数
    @return 大质数
    """
    while True:
        num = random.getrandbits(bits)
        num |= (1 << bits - 1)  # 确保最高位为1
        num |= 1  # 确保是奇数
        
        if is_prime(num):
            return num

def extended_gcd(a, b):
    """
    扩展欧几里得算法
    @param a 第一个数
    @param b 第二个数
    @return (g, x, y) 其中g是最大公约数，ax + by = g
    """
    if a == 0:
        return b, 0, 1
    else:
        g, y, x = extended_gcd(b % a, a)
        return g, x - (b // a) * y, y

def mod_inverse(a, m):
    """
    计算模逆
    @param a 数a
    @param m 模数m
    @return a模m的逆元
    """
    g, x, y = extended_gcd(a, m)
    if g != 1:
        return None  # 不存在逆元
    else:
        return x % m

class RSA:
    """
    RSA加密算法实现类
    """
    
    def __init__(self, bit_length=512):
        """
        RSA构造函数
        @param bit_length 密钥位数
        """
        self.n, self.e, self.d = self.generate_keys(bit_length)
    
    def generate_keys(self, bit_length):
        """
        生成RSA密钥对
        @param bit_length 密钥位数
        @return (n, e, d) 密钥三元组
        """
        print("生成RSA密钥对...")
        
        # 选择两个大质数
        p = generate_prime(bit_length // 2)
        q = generate_prime(bit_length // 2)
        print(f"生成质数p: {p}")
        print(f"生成质数q: {q}")
        
        # 计算n = p * q
        n = p * q
        print(f"计算n = p * q: {n}")
        
        # 计算φ(n) = (p-1)*(q-1)
        phi = (p - 1) * (q - 1)
        print(f"计算φ(n): {phi}")
        
        # 选择公钥指数e
        e = 65537
        print(f"选择公钥指数e: {e}")
        
        # 计算私钥指数d
        d = mod_inverse(e, phi)
        print(f"计算私钥指数d: {d}")
        print("RSA密钥对生成完成")
        
        return n, e, d
    
    def encrypt(self, message):
        """
        RSA加密算法
        @param message 明文消息
        @return Base64编码的密文
        """
        print("开始RSA加密...")
        print(f"明文: {message}")
        
        m = int.from_bytes(message.encode('utf-8'), 'big')
        print(f"转换为数字: {m}")
        
        c = pow(m, self.e, self.n)
        print(f"加密计算 c = m^e mod n: {c}")
        
        result = base64.b64encode(c.to_bytes((c.bit_length() + 7) // 8, 'big')).decode('utf-8')
        print(f"加密完成，密文长度: {len(result)}")
        return result
    
    def decrypt(self, ciphertext):
        """
        RSA解密算法
        @param ciphertext Base64编码的密文
        @return 解密后的明文
        """
        print("开始RSA解密...")
        print(f"密文: {ciphertext}")
        
        c = int.from_bytes(base64.b64decode(ciphertext), 'big')
        print(f"转换为数字: {c}")
        
        m = pow(c, self.d, self.n)
        print(f"解密计算 m = c^d mod n: {m}")
        
        result = m.to_bytes((m.bit_length() + 7) // 8, 'big').decode('utf-8')
        print(f"解密完成，明文长度: {len(result)}")
        return result
    
    def get_public_key(self):
        """
        获取公钥信息
        @return 公钥字符串
        """
        return f"公钥(n,e): ({self.n},{self.e})"
    
    def get_private_key(self):
        """
        获取私钥信息
        @return 私钥字符串
        """
        return f"私钥(n,d): ({self.n},{self.d})"

def main():
    """
    主函数，演示RSA加密和解密
    """
    print("=== RSA算法演示 ===")
    
    rsa = RSA(512)  # 512位密钥
    print(rsa.get_public_key())
    print(rsa.get_private_key())
    
    message = "Hello, RSA!"
    print(f"\n原始消息: {message}")
    print(f"消息长度: {len(message)}")
    
    # 加密
    encrypted = rsa.encrypt(message)
    print(f"加密结果: {encrypted}")
    
    # 解密
    decrypted = rsa.decrypt(encrypted)
    print(f"解密结果: {decrypted}")
    
    # 验证
    is_valid = message == decrypted
    print(f"验证结果: {'✓ 成功' if is_valid else '✗ 失败'}")
    print("=== 演示结束 ===")

if __name__ == "__main__":
    main()
