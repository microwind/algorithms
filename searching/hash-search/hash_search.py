"""
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
"""

"""
哈希查找 - Hash Search
使用哈希表实现O(1)时间复杂度的查找
"""


class HashTable:
    """简单的哈希表实现（使用链地址法处理冲突）"""
    
    def __init__(self, size=10):
        self.size = size
        self.table = [[] for _ in range(size)]
    
    def _hash(self, key):
        """计算哈希值"""
        return hash(key) % self.size
    
    def insert(self, key, value):
        """插入键值对"""
        index = self._hash(key)
        bucket = self.table[index]
        
        # 检查是否已存在，存在则更新
        for i, (k, v) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)
                return
        
        # 不存在则添加
        bucket.append((key, value))
    
    def search(self, key):
        """
        哈希查找
        时间复杂度: 平均O(1)，最坏O(n)（当所有键冲突时）
        """
        index = self._hash(key)
        bucket = self.table[index]
        
        for k, v in bucket:
            if k == key:
                return v  # 找到值
        
        return None  # 未找到
    
    def delete(self, key):
        """删除键值对"""
        index = self._hash(key)
        bucket = self.table[index]
        
        for i, (k, v) in enumerate(bucket):
            if k == key:
                del bucket[i]
                return True
        
        return False
    
    def display(self):
        """显示哈希表内容"""
        for i, bucket in enumerate(self.table):
            if bucket:
                print(f"  桶 {i}: {bucket}")


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("哈希查找 (Hash Search)")
    print("=" * 50)
    
    # 创建哈希表
    hash_table = HashTable(size=5)
    
    # 插入数据
    data = {
        "apple": 100,
        "banana": 200,
        "cherry": 300,
        "date": 400,
        "elderberry": 500
    }
    
    print("\n插入数据:")
    for key, value in data.items():
        hash_table.insert(key, value)
        print(f"  {key}: {value}")
    
    print("\n哈希表结构:")
    hash_table.display()
    
    # 查找测试
    print("\n查找测试:")
    search_keys = ["banana", "cherry", "grape"]
    
    for key in search_keys:
        result = hash_table.search(key)
        if result:
            print(f"  '{key}': {result}")
        else:
            print(f"  '{key}': 未找到")
    
    print("\n性能分析:")
    print("  • 平均时间复杂度: O(1)")
    print("  • 最坏时间复杂度: O(n)（所有键冲突）")
    print("  • 空间复杂度: O(n)")
