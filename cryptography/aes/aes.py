from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import base64

def encrypt(plain_text, key):
    """AES加密"""
    key_bytes = key.encode('utf-8')
    plain_bytes = plain_text.encode('utf-8')
    
    # 创建加密器
    cipher = AES.new(key_bytes, AES.MODE_ECB)
    encrypted_bytes = cipher.encrypt(pad(plain_bytes, AES.block_size))
    
    return base64.b64encode(encrypted_bytes).decode('utf-8')

def decrypt(encrypted_text, key):
    """AES解密"""
    key_bytes = key.encode('utf-8')
    encrypted_bytes = base64.b64decode(encrypted_text)
    
    # 创建解密器
    cipher = AES.new(key_bytes, AES.MODE_ECB)
    decrypted_bytes = unpad(cipher.decrypt(encrypted_bytes), AES.block_size)
    
    return decrypted_bytes.decode('utf-8')

def main():
    plain_text = "Hello, World!"
    key = "1234567890123456"  # 16字节密钥
    
    print(f"原文: {plain_text}")
    
    encrypted = encrypt(plain_text, key)
    print(f"加密后: {encrypted}")
    
    decrypted = decrypt(encrypted, key)
    print(f"解密后: {decrypted}")
    
    print(f"验证: {plain_text == decrypted}")

if __name__ == "__main__":
    main()
