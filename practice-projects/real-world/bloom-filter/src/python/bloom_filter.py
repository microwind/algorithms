"""
实际应用：布隆过滤器 (Bloom Filter)
场景：大数据去重、黑名单检测、爬虫URL去重

使用场景：
- 检查URL是否被爬过
- 垃圾邮件过滤
- 黑名单/白名单检测
- 缓存穿透防护
- 数据库查询优化
"""

import hashlib
import math


class BloomFilter:
    """布隆过滤器实现"""

    def __init__(self, expected_elements=10000, false_positive_rate=0.01):
        """
        初始化布隆过滤器

        Args:
            expected_elements: 预期元素数量
            false_positive_rate: 允许的误判率
        """
        # 计算所需的位数组大小
        self.size = self._calculate_size(expected_elements, false_positive_rate)
        # 计算所需的哈希函数数量
        self.hash_count = self._calculate_hash_count(self.size, expected_elements)

        # 初始化位数组 (使用字典存储)
        self.bit_array = [False] * self.size
        self.element_count = 0

    @staticmethod
    def _calculate_size(n, p):
        """计算位数组大小"""
        return abs(int(-(n * math.log(p)) / (math.log(2) ** 2)))

    @staticmethod
    def _calculate_hash_count(m, n):
        """计算哈希函数数量"""
        return abs(int((m / n) * math.log(2)))

    def _hash(self, item, seed):
        """使用不同seed生成不同的哈希值"""
        hash_obj = hashlib.sha256((str(item) + str(seed)).encode())
        return int(hash_obj.hexdigest(), 16) % self.size

    def add(self, item):
        """添加元素"""
        for i in range(self.hash_count):
            hash_val = self._hash(item, i)
            self.bit_array[hash_val] = True
        self.element_count += 1

    def contains(self, item):
        """检查元素是否存在"""
        for i in range(self.hash_count):
            hash_val = self._hash(item, i)
            if not self.bit_array[hash_val]:
                return False
        return True

    def get_stats(self):
        """获取过滤器统计信息"""
        bit_count = sum(self.bit_array)
        return {
            'size': self.size,
            'hash_count': self.hash_count,
            'element_count': self.element_count,
            'bit_set_count': bit_count,
            'set_ratio': f"{(bit_count / self.size * 100):.2f}%"
        }


class URLCrawlerFilter:
    """爬虫URL去重过滤器"""

    def __init__(self, expected_urls=1000000):
        self.bloom_filter = BloomFilter(expected_urls, 0.001)
        self.duplicate_count = 0
        self.new_count = 0

    def is_crawled(self, url):
        """检查URL是否被爬过"""
        return self.bloom_filter.contains(url)

    def mark_crawled(self, url):
        """标记URL已爬"""
        if self.is_crawled(url):
            self.duplicate_count += 1
            return False
        else:
            self.bloom_filter.add(url)
            self.new_count += 1
            return True

    def get_statistics(self):
        """获取统计信息"""
        total = self.duplicate_count + self.new_count
        dedup_ratio = (self.duplicate_count / total * 100) if total > 0 else 0
        return {
            'total_processed': total,
            'new_urls': self.new_count,
            'duplicate_urls': self.duplicate_count,
            'dedup_ratio': f"{dedup_ratio:.2f}%",
            'filter_stats': self.bloom_filter.get_stats()
        }


class BlacklistFilter:
    """黑名单过滤器"""

    def __init__(self, expected_items=100000):
        self.bloom_filter = BloomFilter(expected_items, 0.01)
        self.real_blacklist = set()  # 实际黑名单 (用于验证)

    def add_to_blacklist(self, item):
        """添加到黑名单"""
        self.bloom_filter.add(item)
        self.real_blacklist.add(item)

    def is_blacklisted(self, item):
        """检查是否在黑名单中"""
        # 先用布隆过滤器快速检查
        if not self.bloom_filter.contains(item):
            return False
        # 确认是否真的在黑名单中
        return item in self.real_blacklist

    def get_potential_blacklist(self, item):
        """获取可能的黑名单项"""
        # 布隆过滤器返回可能性
        return self.bloom_filter.contains(item)


class CacheAvalanchePrevention:
    """缓存穿透防护"""

    def __init__(self, expected_items=100000):
        self.bloom_filter = BloomFilter(expected_items, 0.01)
        self.cache_miss_count = 0
        self.total_queries = 0

    def query_exists(self, key):
        """查询key是否存在"""
        self.total_queries += 1

        # 如果布隆过滤器返回False，说明key一定不存在
        if not self.bloom_filter.contains(key):
            return False

        # 需要进一步查询数据库
        return None  # None表示需要查询数据库

    def add_key(self, key):
        """添加存在的key"""
        self.bloom_filter.add(key)

    def get_query_stats(self):
        """获取查询统计"""
        return {
            'total_queries': self.total_queries,
            'cache_miss_count': self.cache_miss_count,
            'filter_stats': self.bloom_filter.get_stats()
        }


class IpBlocklistFilter:
    """IP黑名单过滤器"""

    def __init__(self, expected_ips=1000000):
        self.bloom_filter = BloomFilter(expected_ips, 0.001)
        self.real_blocklist = set()
        self.blocked_count = 0
        self.allowed_count = 0

    def add_blocked_ip(self, ip):
        """添加被阻止的IP"""
        self.bloom_filter.add(ip)
        self.real_blocklist.add(ip)

    def is_blocked(self, ip):
        """检查IP是否被阻止"""
        if not self.bloom_filter.contains(ip):
            self.allowed_count += 1
            return False

        # 需要进一步检查真实列表
        is_really_blocked = ip in self.real_blocklist
        if is_really_blocked:
            self.blocked_count += 1
        else:
            self.allowed_count += 1

        return is_really_blocked

    def get_statistics(self):
        """获取统计信息"""
        total = self.blocked_count + self.allowed_count
        return {
            'total_checked': total,
            'blocked_ips': self.blocked_count,
            'allowed_ips': self.allowed_count,
            'blocked_ratio': f"{(self.blocked_count/total*100) if total > 0 else 0:.2f}%",
            'filter_stats': self.bloom_filter.get_stats()
        }


if __name__ == "__main__":
    print("=== 布隆过滤器实际应用 ===\n")

    # 1. 基础布隆过滤器演示
    print("--- 基础布隆过滤器 ---")
    bf = BloomFilter(expected_elements=1000, false_positive_rate=0.01)

    items = [f"item_{i}" for i in range(100)]
    for item in items:
        bf.add(item)

    print("添加100个元素后的统计:")
    stats = bf.get_stats()
    for key, val in stats.items():
        print(f"  {key}: {val}")

    # 检查存在的元素
    print(f"\n检查 'item_50': {bf.contains('item_50')}")
    print(f"检查 'item_999': {bf.contains('item_999')}")

    # 2. URL爬虫去重
    print("\n--- 爬虫URL去重 ---")
    crawler = URLCrawlerFilter(expected_urls=10000)

    urls = [f"http://example.com/page_{i}" for i in range(100)]
    # 第一次爬取
    for url in urls:
        crawler.mark_crawled(url)

    # 第二次爬取（重复）
    for url in urls[:50]:
        crawler.mark_crawled(url)

    stats = crawler.get_statistics()
    print(f"处理URL总数: {stats['total_processed']}")
    print(f"新URL数: {stats['new_urls']}")
    print(f"重复URL数: {stats['duplicate_urls']}")
    print(f"去重率: {stats['dedup_ratio']}")

    # 3. IP黑名单过滤
    print("\n--- IP黑名单过滤 ---")
    ip_filter = IpBlocklistFilter(expected_ips=100000)

    # 添加黑名单IP
    blacklist_ips = ["192.168.1.1", "192.168.1.2", "192.168.1.3"]
    for ip in blacklist_ips:
        ip_filter.add_blocked_ip(ip)

    # 检查IP
    test_ips = [
        "192.168.1.1",  # 被阻止
        "192.168.1.100",  # 允许
        "192.168.1.2",  # 被阻止
        "10.0.0.1",  # 允许
    ]

    print("IP检查结果:")
    for ip in test_ips:
        result = ip_filter.is_blocked(ip)
        status = "被阻止" if result else "允许"
        print(f"  {ip}: {status}")

    stats = ip_filter.get_statistics()
    print(f"\nIP过滤统计:")
    for key, val in stats.items():
        if key != 'filter_stats':
            print(f"  {key}: {val}")

    # 4. 缓存穿透防护
    print("\n--- 缓存穿透防护 ---")
    cache_guard = CacheAvalanchePrevention(expected_items=1000)

    # 添加存在的key
    for i in range(100):
        cache_guard.add_key(f"key_{i}")

    print("查询结果:")
    print(f"  查询 'key_50': {cache_guard.query_exists('key_50')} (可能存在)")
    print(f"  查询 'key_999': {cache_guard.query_exists('key_999')} (一定不存在)")
    print(f"  查询 'unknown_key': {cache_guard.query_exists('unknown_key')} (一定不存在)")

    print(f"\n过滤器统计:")
    print(f"  总查询数: {cache_guard.total_queries}")
    print(f"  阻止的无效查询: ~{cache_guard.total_queries - 1}")
