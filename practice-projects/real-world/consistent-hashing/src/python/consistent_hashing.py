"""
实际应用：一致哈希 (Consistent Hashing)
场景：分布式缓存、负载均衡、服务发现

使用场景：
- Redis集群中的key分布
- Memcached多服务器环境
- CDN节点选择
- 数据库分片
- 微服务负载均衡
"""

import hashlib
import bisect
from collections import defaultdict


class ConsistentHash:
    """一致哈希实现"""

    def __init__(self, replicas=3):
        """
        初始化一致哈希环

        Args:
            replicas: 每个节点的虚拟副本数，增加副本数可提高负载均衡
        """
        self.replicas = replicas
        self.ring = {}  # hash -> node
        self.sorted_keys = []  # 排序的hash值列表
        self.nodes = set()  # 所有节点

    def _hash(self, key):
        """计算key的hash值"""
        return int(hashlib.md5(key.encode()).hexdigest(), 16)

    def add_node(self, node):
        """添加节点"""
        self.nodes.add(node)
        # 添加虚拟节点
        for i in range(self.replicas):
            virtual_key = f"{node}:{i}"
            hash_val = self._hash(virtual_key)
            self.ring[hash_val] = node
            bisect.insort(self.sorted_keys, hash_val)

    def remove_node(self, node):
        """移除节点"""
        self.nodes.discard(node)
        # 移除虚拟节点
        for i in range(self.replicas):
            virtual_key = f"{node}:{i}"
            hash_val = self._hash(virtual_key)
            del self.ring[hash_val]
            self.sorted_keys.remove(hash_val)

    def get_node(self, key):
        """获取key应该存储的节点"""
        if not self.ring:
            return None

        hash_val = self._hash(key)

        # 在排序的hash值中二分查找
        idx = bisect.bisect_right(self.sorted_keys, hash_val)
        if idx == len(self.sorted_keys):
            idx = 0

        return self.ring[self.sorted_keys[idx]]

    def get_nodes(self, key, n=1):
        """获取key的n个备份节点"""
        if not self.ring:
            return []

        nodes = []
        hash_val = self._hash(key)
        idx = bisect.bisect_right(self.sorted_keys, hash_val)

        for _ in range(n):
            if idx >= len(self.sorted_keys):
                idx = 0
            node = self.ring[self.sorted_keys[idx]]
            if node not in nodes:
                nodes.append(node)
            idx += 1

        return nodes


class DistributedCache:
    """分布式缓存系统"""

    def __init__(self, replicas=3):
        self.hash_ring = ConsistentHash(replicas)
        self.data = defaultdict(dict)  # node -> {key: value}

    def add_server(self, server):
        """添加缓存服务器"""
        self.hash_ring.add_node(server)
        print(f"添加服务器: {server}")

    def remove_server(self, server):
        """移除缓存服务器"""
        self.hash_ring.remove_node(server)
        print(f"移除服务器: {server}")

    def set(self, key, value):
        """设置缓存值"""
        node = self.hash_ring.get_node(key)
        if node:
            self.data[node][key] = value
            return True
        return False

    def get(self, key):
        """获取缓存值"""
        node = self.hash_ring.get_node(key)
        if node:
            return self.data[node].get(key)
        return None

    def get_distribution(self):
        """获取数据分布统计"""
        distribution = {}
        for node in self.hash_ring.nodes:
            distribution[node] = len(self.data[node])
        return distribution

    def print_distribution(self):
        """打印数据分布"""
        dist = self.get_distribution()
        print("\n数据分布:")
        total = sum(dist.values())
        for node, count in sorted(dist.items()):
            percentage = (count / total * 100) if total > 0 else 0
            print(f"  {node}: {count} 条 ({percentage:.1f}%)")


class LoadBalancer:
    """负载均衡器"""

    def __init__(self, replicas=3):
        self.hash_ring = ConsistentHash(replicas)
        self.request_count = defaultdict(int)

    def add_server(self, server):
        """添加服务器"""
        self.hash_ring.add_node(server)

    def remove_server(self, server):
        """移除服务器"""
        self.hash_ring.remove_node(server)

    def route_request(self, request_id):
        """根据请求ID路由到服务器"""
        server = self.hash_ring.get_node(request_id)
        if server:
            self.request_count[server] += 1
        return server

    def get_load_balance_stats(self):
        """获取负载均衡统计"""
        total = sum(self.request_count.values())
        stats = {}
        for server in self.hash_ring.nodes:
            count = self.request_count[server]
            percentage = (count / total * 100) if total > 0 else 0
            stats[server] = {
                'requests': count,
                'percentage': percentage
            }
        return stats

    def print_load_balance_stats(self):
        """打印负载均衡统计"""
        stats = self.get_load_balance_stats()
        print("\n负载均衡统计:")
        for server, stat in sorted(stats.items()):
            print(f"  {server}: {stat['requests']} 请求 ({stat['percentage']:.1f}%)")


class ConsistentHashWithReplicas:
    """带副本的一致哈希"""

    def __init__(self, replicas=3, backup_replicas=2):
        self.hash_ring = ConsistentHash(replicas)
        self.backup_replicas = backup_replicas

    def add_node(self, node):
        """添加节点"""
        self.hash_ring.add_node(node)

    def remove_node(self, node):
        """移除节点"""
        self.hash_ring.remove_node(node)

    def get_replicas(self, key):
        """获取key的副本分布"""
        return self.hash_ring.get_nodes(key, self.backup_replicas)


if __name__ == "__main__":
    print("=== 一致哈希实际应用 ===\n")

    # 1. 基础一致哈希演示
    print("--- 基础一致哈希 ---")
    ch = ConsistentHash(replicas=3)
    ch.add_node("server1")
    ch.add_node("server2")
    ch.add_node("server3")

    # 测试key分布
    test_keys = [f"key_{i}" for i in range(100)]
    distribution = defaultdict(int)
    for key in test_keys:
        node = ch.get_node(key)
        distribution[node] += 1

    print("Key分布:")
    for node, count in sorted(distribution.items()):
        print(f"  {node}: {count} 个key")

    # 2. 分布式缓存
    print("\n--- 分布式缓存系统 ---")
    cache = DistributedCache(replicas=3)
    cache.add_server("cache1")
    cache.add_server("cache2")
    cache.add_server("cache3")

    # 添加数据
    print("\n添加缓存数据...")
    for i in range(30):
        cache.set(f"user_{i}", f"userData_{i}")

    cache.print_distribution()

    # 3. 服务器扩展
    print("\n--- 服务器扩展影响 ---")
    print("添加新服务器...")
    cache.add_server("cache4")

    # 重新计算分布 (模拟)
    print("\n重新分配后的分布:")
    cache2 = DistributedCache(replicas=3)
    for server in ["cache1", "cache2", "cache3", "cache4"]:
        cache2.add_server(server)

    for i in range(30):
        cache2.set(f"user_{i}", f"userData_{i}")

    cache2.print_distribution()

    # 4. 负载均衡
    print("\n--- 负载均衡 ---")
    lb = LoadBalancer(replicas=3)
    for i in range(1, 4):
        lb.add_server(f"server{i}")

    print("模拟1000个请求...")
    for i in range(1000):
        request_id = f"req_{i}"
        server = lb.route_request(request_id)

    lb.print_load_balance_stats()

    # 5. 副本分布
    print("\n--- 副本分布 ---")
    replicas_system = ConsistentHashWithReplicas(replicas=3, backup_replicas=2)
    replicas_system.add_node("db1")
    replicas_system.add_node("db2")
    replicas_system.add_node("db3")

    test_keys = ["user_1", "user_2", "user_3"]
    print("键的副本分布:")
    for key in test_keys:
        nodes = replicas_system.get_replicas(key)
        print(f"  {key}: {nodes}")
